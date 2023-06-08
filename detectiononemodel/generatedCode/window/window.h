#ifndef __WINDOW1__
#define __WINDOW1__


#include <vector>
#include <memory>
#include <map>
#include "kde.h"
#include "../json.hpp"

using json = nlohmann::json;

using namespace std;
class window1{
    private:
        int window_size;
        int sliding_size;
        int num_training;
        bool is_training_on;
        vector<int> ref_periods;
        vector<int> seen_periods;
        int seen_instances;
        string type;

    public:
        window1();
        window1(json& );
        int getWindow_size();
        void setWindow_size(int);
        int getSliding_size();
        void setSliding_size(int);
        string getType();
        void setType(string);
        int getNum_training();
        vector<int> getRef_periods();
        void setRef_periods(vector<int>);
        vector<int> getSeen_periods();
        void setSeen_periods(vector<int>);
        vector<int> add_period(int period);
        int add_instance(int value);
        void fit_partial(kde* m ,std::map<int,vector<int>>);
        
        






};
#endif