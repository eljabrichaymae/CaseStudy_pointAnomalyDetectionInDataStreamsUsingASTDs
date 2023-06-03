#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <memory>
#include "window.h"


using namespace std;

window1::window1(){
    this->window_size = 2;
    this->sliding_size = 1;
    this->num_training = 0;
    this->is_training_on = false;
    this->seen_instances = 0;
    this->type = "day";
};
window1::window1(json&  window_parameters){
    this->window_size = window_parameters["window_size"].get<int>();
    this->sliding_size = window_parameters["sliding_size"].get<int>();
    this->type = window_parameters["type"].get<std::string>();
    this->num_training = 0;
    this->is_training_on = false;
    this->seen_instances = 0; 
};
int window1::getWindow_size(){
    return this->window_size;
};
void window1::setWindow_size(int window_size){
    this->window_size = window_size;
};
int window1::getSliding_size(){
    return this->sliding_size;
};
void window1::setSliding_size(int sliding_size){
    this->sliding_size = sliding_size;
};
string window1::getType(){
    return this->type;
};
void window1::setType(string type){
    this->type = type;
};
int window1::getNum_training(){
    return this->num_training;
};
vector<int> window1::getRef_periods(){
    return this->ref_periods;
};
void window1::setRef_periods(vector<int> ref_periods){
    this->ref_periods = ref_periods;
};
vector<int> window1::getSeen_periods(){
    return this->seen_periods;
};
void window1::setSeen_periods(vector<int> seen_periods){
    this->seen_periods = seen_periods;
};

vector<int> window1::add_period(int period){
    if(this->is_training_on){
        this->num_training++;
        this->is_training_on = false;
    }
    vector<int> periods_to_delete;
    if(find(this->seen_periods.begin(),this->seen_periods.end(),period)==this->seen_periods.end() &&
        find(this->ref_periods.begin(),this->ref_periods.end(),period)==this->ref_periods.end()){
        this->seen_periods.push_back(period);
        
        if((this->seen_periods.size() - getWindow_size() - 1) % getSliding_size()== 0){
            int index = max(0, (int) this->seen_periods.size()- 1 - getWindow_size());
            int index1 = max(0,(int)  index - getSliding_size());
            periods_to_delete = vector<int>(this->seen_periods.begin() + index1, this->seen_periods.begin() + index);
            this->ref_periods = vector <int>(this->seen_periods.begin() + index  , this->seen_periods.end() - 1);
            if(this->ref_periods.size() == getWindow_size()){
                this->is_training_on = true;
            } 
        }
        
    }
    return periods_to_delete;
};

int window1::add_instance(int value){
    if(this->is_training_on){
        this->num_training++;
        this->is_training_on = false;
    }
    this->seen_instances++;
    int index = 0;
    if(this->seen_instances <= getWindow_size()){
        if(this->seen_instances == getWindow_size()){
            this->is_training_on = true;
            index = 0;
        }
    }
    else if((this->seen_instances - getWindow_size())%getSliding_size() == 0){
        this->is_training_on = true;
        index = 1;
    }
    return index;
};




void window1::fit_partial(kde* m, std::map<int,vector<int>> data_map){
    if(this->is_training_on){   
        if(this->type == "week"|| this->type == "day"){
            vector<int> data;
            for(int p : this->ref_periods){
                data.insert(data.end(),data_map[p].begin(),data_map[p].end());
            }
            m->fit_partial(data);  
        } 
        if(this->type == "instance"){
            m->fit_partial(vector<int>(data_map[0].begin(),data_map[0].end()));
        }
        
    }
}; 