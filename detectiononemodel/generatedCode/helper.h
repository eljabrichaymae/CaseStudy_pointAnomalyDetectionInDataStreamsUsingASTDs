#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <getopt.h>
#include "json.hpp"

/*
 * @brief Regex expresssion used to parse
 *        event labels and parameters 
 */
#define LABEL_REGEX std::string("([a-z_A-z]+[0-9]*)")
#define PARAMS_REGEX std::string(LABEL_REGEX + "\\((.*)\\)")
/*
 * @brief Safely executes events by catching exceptions
 *     
 */
#define ERROR_1 std::cout << "Event is not recognized" << "\n"
#define ERROR_2 std::cout << "Event is not executable" << "\n"
#define ERROR_3 std::cout << "Method toString() is undefined in User types" << "\n"
#define ERROR_4 std::cout << "Method parse(...) is undefined in User types" << "\n"
/*
 * @brief External json library to be used for ontology types (e.g. Packet, Flow, etc.)
 *     
 */
using json = nlohmann::json;

/*
 * @brief Checking whether methods parse(...) and toString() exists in User types
 *     
 */
template <typename T>
class HasMethod
{
private:
    typedef char YesType[1];
    typedef char NoType[2];

    template <typename C> static YesType& hasToString(decltype(&C::toString));
    template <typename C> static NoType&  hasToString(...);
    template <typename C> static YesType& hasParse(decltype(&C::parse));
    template <typename C> static NoType&  hasParse(...);

public:
    enum 
    { 
        has_to_string = sizeof(hasToString<T>(0)) == sizeof(YesType),
        has_parse = sizeof(hasParse<T>(0)) == sizeof(YesType)  
    };
};
/*
 * @brief Call toString() method if it exists
 *     
 */
template<typename T> 
typename std::enable_if<HasMethod<T>::has_to_string, std::string>::type
call_to_string(T * t) 
{
    return t->toString();
}

std::string call_to_string(...)
{
    return "Method toString() is undefined in User types";
}

/*
 * @brief Call parse(...) method if it exists
 *     
 */
template<typename T> 
typename std::enable_if<HasMethod<T>::has_parse, T>::type call_parse(T* t, std::string s)
{
    return t->parse(s);
}

std::string call_parse(...)
{
    return "Method parse(...) is undefined in User types";
}
/*
 * @brief Checks whether an object is an instance of another
 *     
 */
template<typename Base, typename T>
inline bool instanceof(const T *ptr) 
{
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

template<typename Base, typename T>
inline bool instanceof() 
{
    T ptr;
    return dynamic_cast<const Base*>(&ptr) != nullptr;
}
/*
 * @brief An object used to serialize types and get the appropriated values as of
 *        primitive types or complex types.
 */
class Types {
    
 public:
    
    static std::string get_str(const std::string s) { return s; }
    static int get_int(const std::string s) { return std::stoi(s); }
    static float get_float(const std::string s) { return std::stof(s); }
    static double get_double(const std::string s) { return std::stod(s); }
    static bool get_bool(const std::string s) { 
        if(s == "0" || s == "false"){
            return false;
        }
        return true;
    }    
    static json get_json(const std::string s){
        std::ifstream file(s);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << s << std::endl;
        }
        json jsonData;
        file >> jsonData;
        return jsonData;
    }
    

};

/*
 * @brief Event format supported
 */
const std::string SHORTHAND = "shorthandevents";
const std::string JSON      = "json";
std::string       format    = SHORTHAND;

/*
 * @brief channel to read events
 */
static std::ifstream channel;
static std::string filename;

/*
 * @brief The event data structure containing its label and its parameters
 *
 */
struct Event 
{
    std::string label;
    std::vector<std::string> params;
};

json window_parameters;
double threshold;

class IO
{
public:
    /*
     * @brief parses event parameters and sets the event object with these params
     * @param The event object to be set
     * @param The event string to be parsed 
     * @param The input regex to be used for parsing
     * @return 
     */
    static void get_event_params(Event& e, const std::string in, const std::regex regex) 
    {
        if(format.compare(JSON) == 0)
        {
            try 
            {
                if(!in.empty()) 
                {
                    json j_evt = json::parse(in);
                    if(!j_evt.is_null() && j_evt.contains("arguments"))
                    {
                        for(auto& elem : j_evt["arguments"].items())
                        {
                            json obj = elem.value();
                            std::string it = obj.dump();
	                    e.params.push_back(it);
                        }
                    }
                }
	    } 
            catch(json::parse_error) 
            {
	        std::cout << "Improper json event arguments !!!" << std::endl;  
	    } 
        }
        else
        {
            std::smatch matches;
            if(regex_search(in, matches, regex)) 
            {
                std::stringstream ss(matches.str(2));
	        while(ss.good()) 
	        { 
	            std::string it; 
	            getline(ss, it, ',');
	            e.params.push_back(it); 
	        }
            }
        }
  
        return;   
    }

    /*
     * @brief parses event label and returns its value
     * @param The event string to be parsed
     * @return The event label
     */
    static std::string get_event_label(const std::string in) 
    {
        if(format.compare(JSON) == 0) 
        {
            try 
            {
                if(!in.empty())
                {
	            json j_evt = json::parse(in);
	            std::string label = j_evt["label"];
	            return label;
                }
	    } 
            catch(json::parse_error) 
            {
                std::cout << "Improper json event label !!!" << std::endl;   
	    } 
        }
        else 
        {
	    std::smatch matches;
	    if (regex_search(in, matches, std::regex(PARAMS_REGEX)))
	        return matches.str(1); 
            else if(!in.empty())
                return in;
        }

        return ""; 
    }

    /*
     * @brief Reads event from the Input stream
     * @param The cmdline arguments 
     * @return The event object
     */

    static void configInputStream(int argc, char** argv) 
    {
        const char* const short_opts = "i:f:1:2:h";

        const option long_opts[] = {
            {"window_parameters", required_argument, nullptr, '1'},
            {"threshold", required_argument, nullptr, '2'},
        };

        while (true)
        {
             const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
             if (-1 == opt)
                break;

             switch(opt)
             {
                    
             case 'i':
             {
                filename = std::string(optarg); 
                channel = std::ifstream(filename);
                if(!channel)
                    std::cout << "Error opening event file !!!";
                break;
             }
             
             case '1': 
                 window_parameters = Types::get_json(optarg); 
                 break;
             case '2': 
                 threshold = Types::get_double(optarg); 
                 break;
             case 'h':
             { 
                 std::cout << "This program has been compiled by cASTD." << "\n";
                 std::cout << "./my_program [-i <event file>] [-f <event format>] [-window_parameters <value>] [-threshold <value>]  [-h]" << "\n";
                 std::cout << "[OPTIONS]     								     " << "\n";
                 std::cout << "   -i <event  file>  Read an event file in Shorthand format." << "\n";
                 std::cout << "                     If an event file is not given, it runs in interactive" << "\n";
                 std::cout << "                     mode from command line" << "\n";
                    std::cout << "   -window_parameters <value> Parameter of the ASTD" << std::endl;
                    std::cout << "   -threshold <value> Parameter of the ASTD" << std::endl;
                 
                 std::cout << "   -f <event format> Event format. It can be a JSON or Shorthand format" << std::endl;
                 
                 std::cout << "   -h                Show this help" << "\n";
                 exit(0);
                 break;
             }
             case 'f': 
                    format = std::string(optarg); 
                    break;
         }   
     }
 }


    static Event read_event(int argc) 
    {
        Event e;
        std::string input;

        if(argc > 1) 
        {
            if(!filename.empty()) 
	        std::getline(channel, input); 
	    else 
	        std::getline(std::cin, input); 

	    e.label = get_event_label(input);
	    get_event_params(e, input, std::regex(PARAMS_REGEX));  
        }
        else 
        {
            getline(std::cin, input);
            e.label = get_event_label(input);
            get_event_params(e, input, std::regex(PARAMS_REGEX));
        }
     
        return e;
    }
};