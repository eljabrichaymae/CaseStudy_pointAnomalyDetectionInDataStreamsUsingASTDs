#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <getopt.h>
#include <stdexcept>
#include "json.hpp"
#include <stdexcept>
#include <string>
#include <iomanip>

/*
 * @brief Regex expresssion used to parse
 *            event labels and parameters 
 */
#define LABEL_REGEX std::string("([0-9a-zA-Z*+_]*)")
#define PARAMS_REGEX std::string(LABEL_REGEX + "\\((.*)\\)")
#define SEPARATE_PARAMS_REGEX std::string("(\".*?\"|[^\",]+)(?=\\s*,|\\s*$)")
/*
 * @brief Safely executes events by catching exceptions
 *     
 */
#define ERROR_1 std::cout << "Event is not recognized" << "\n"
#define ERROR_2 std::cout << "Event is not executable" << "\n"
#define ERROR_5 std::cout << "Empty event label, terminating execution" << "\n"
#define ERROR_6 std::cout << "Wrong parameters type given" << "\n";
#define ERROR_7 std::cout << "Wrong number of parameters given" << "\n";
/*
 * @brief External json library to be used for JSON types (e.g. Packet, Flow, etc.)
 *     
 */
using json = nlohmann::json;

/*
 * @brief An object used to serialize types and get the appropriated values as of
 *        primitive types or complex types.
 */
class Types {
    
 public:
    
    static std::string get_str(const std::string s) { 
        return s; 
    }
    static int get_int(const std::string s, bool& flag) {
        std::istringstream iss(s);
        int temp;
        char c;
        if (!(iss >> temp) || (iss.get(c))){
            std::cerr << "Error: Failed to convert string to int: " << s << std::endl;
            flag = true;
            return 0;
        }
        return temp;
    }
    static float get_float(const std::string s, bool& flag) {
        try {
            return std::stof(s);
        } catch(const std::exception& e) {
            std::cerr << "Error: Failed to convert string to float: " << e.what() << std::endl;
            flag = true;
            return 0.0f; // Return only to allow program to continue
        }
    }
    static double get_double(const std::string s, bool& flag) {
        try {
            return std::stod(s);
        } catch(const std::exception& e) {
            std::cerr << "Error: Failed to convert string to double: " << e.what() << std::endl;
            flag = true;
            return 0.0; // Return only to allow program to continue
        }
    }
    static bool get_bool(const std::string s) { 
        if(s == "0" || s == "false"){
            return false;
        }
        return true;
    }static json get_json(const std::string s,  bool& flag){
        std::ifstream file(s);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << s << std::endl;
            flag = true;
        }
        json jsonData;
        file >> jsonData;
        return jsonData;
    }
};

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
    static void get_event_params(Event& e, const std::string in) 
    {
        std::smatch matches;
        std::smatch matches2;
        if(regex_search(in, matches, std::regex(PARAMS_REGEX))) 
        {
            std::string ss = matches.str(2);
	        while(regex_search(ss, matches2, std::regex(SEPARATE_PARAMS_REGEX))){
                std::string input = matches2[0];
                std::stringstream ss2(input);

                std::string output;
                ss2 >> std::quoted(output);

                e.params.push_back(output);
                ss = matches2.suffix().str();
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
        std::smatch matches;
        if(regex_search(in, matches, std::regex(LABEL_REGEX)))
	    return matches.str(1);

        return ""; 
    }

    /*
     * @brief Reads event from the Input stream
     * @param The cmdline arguments 
     * @return The event object
     */

    static void configInputStream(int argc, char** argv) 
    {
        const char* const short_opts = "i:1:2:h";

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
             {
                 
                 bool flag = false;
                 window_parameters = Types::get_json(optarg, flag);  
                 if(flag){
                      ERROR_6;
                 }
                 break;
             }
             case '2': 
             {
                 
                 bool flag = false;
                 threshold = Types::get_double(optarg, flag);  
                 if(flag){
                      ERROR_6;
                 }
                 break;
             }
             case 'h':
             { 
                 std::cout << "This program has been compiled by cASTD." << "\n";
                 std::cout << "./my_program [-i <event file>] [-window_parameters <value>] [-threshold <value>]  [-h]" << "\n";
                 std::cout << "[OPTIONS]     								     " << "\n";
                 std::cout << "   -i <event  file>  Read an event file in Shorthand format." << "\n";
                 std::cout << "                     If an event file is not given, it runs in interactive" << "\n";
                 std::cout << "                     mode from command line" << "\n";
                    std::cout << "   -window_parameters <value> Parameter of the ASTD" << std::endl;
                    std::cout << "   -threshold <value> Parameter of the ASTD" << std::endl;
                 
                 
                 
                 std::cout << "   -h                Show this help" << "\n";
                 exit(0);
                 break;
             }
             
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
	        get_event_params(e, input);  
        }
        else 
        {
            getline(std::cin, input);
            e.label = get_event_label(input);
            get_event_params(e, input);
        }
     
        return e;
    }
};