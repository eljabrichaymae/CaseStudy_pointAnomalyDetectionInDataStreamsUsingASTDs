#include "learning_models/KMEANS/kmeans.h"
#include "learning_models/KDE/kde.h"
#include "learning_models/LOF/lof.h"
#include "learning_models/model.h"
#include "window/window.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"



using namespace std;
using json = nlohmann::json;

class Code{
    public:
        static unsigned int num_day(unsigned int const day, unsigned int const month, unsigned int const year ){
            static const unsigned int days_to_month[2][12] =
            {
                // non-leap year
                { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
                // leap year
                { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 },
            };
            static const unsigned int days_of_month[2][12] = 
            {
                // non-leap year
                { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
                // leap-year
                { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
            };
            auto leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            return days_to_month[leap][month - 1] + day;
        };
        static int num_week(int j, int m, int a){ 
            int s = 0;
            struct tm tmj = {0, 0, 12, 1, 0, a - 1900, 0, 0, 0};     //1er Janv
            struct tm tmq = {0, 0, 12, j, m - 1, a - 1900, 0, 0, 0}; //date

            if (mktime(&tmj) != (time_t)-1 && mktime(&tmq) != (time_t)-1){
                if (!(s = (tmj.tm_wday + tmq.tm_yday + 6) / 7 - (tmj.tm_wday / 5)))
                    s = num_week(31, 12, a - 1);

            if (m == 12){
                int js = (tmj.tm_wday + tmq.tm_yday) % 7;
                if ((js == 1 && (j >= 29 && j <= 31)) || (js == 2 && (j == 30 || j == 31)) || (js == 3 && j == 31))
                s = 1;
                }
            }
            return s;
        };
        static int compute_period(std::string eventDate, std::string period_type){
            int day = stoi(eventDate.substr(9, 2));
            int month = stoi(eventDate.substr(6, 2));
            int year = stoi(eventDate.substr(1, 4));
            int period = 0;
            if(period_type == "week"){
                int numsemaine = num_week(day, month, year);
                if (month == 12 && numsemaine == 1)
                    year = year + 1;
                else if (month == 1 && (numsemaine == 52 || numsemaine == 53))
                    year = year - 1;
                period = year * 100 + numsemaine;
            }else if(period_type == "day"){
                int numday = num_day(day, month, year);
                period = year * 1000 + numday;
            }
            return period;
        };

        static std::map<string, model*> init_map(double kde_parameters, double kmeans_parameters, int lof_parameters){
            std::map<string, model*> map_classes;
            map_classes.emplace(std::pair<std::string,model*>("kde", new kde(kde_parameters)));
            map_classes.emplace(std::pair<std::string,model*>("kmeans", new kmeans(kmeans_parameters)));
            //map_classes.emplace(std::pair<std::string,model*>("knn", new knn()));
            map_classes.emplace(std::pair<std::string,model*>("lof", new lof(lof_parameters)));
            return map_classes;
        };
        static void formatting_data(std::map<int,std::vector<int>> &data, window1* window,std::string eventDate){
            int heure = stoi(eventDate.substr(12, 2));
            int minute = stoi(eventDate.substr(15, 2));
            int value = heure * 60 + minute;
            std::string type = window->getType();
            if(type == "day"||type == "week"){
                int period = compute_period(eventDate,type);
                data[period].push_back(value);
                std::vector<int> periodsToDelete = window->add_period(period);
                if(periodsToDelete.size() != 0 ){
                    for(int p : periodsToDelete){
                        data[p].clear();
                        data.erase(p);
                    }
                }
            }
            if(type == "instance"){
                data[0].push_back(value);
                int sliding_on = window->add_instance(value);
                int slide_size = window->getSliding_size();
                if(sliding_on == 1) {
                    data[0] = vector<int>(data[0].begin()+slide_size,data[0].end());
                }
            }
            
        };
        static void majorityVote(std::vector<int>& labels, std::vector<tuple<string,int,string>>& alerts, string eventId, string eventDate){
            if(labels.size() != 0){
                int count =0; 
                for(int i=0;i< labels.size();i++){
                    if(labels[i] == 1) count++;
                    
                }
                if(count>=2){
                    alerts.push_back(make_tuple(eventId,count,eventDate));
                    cout<<eventId<<"is malicious"<<endl;
                }
                labels.clear();
            }
        };







};
