#include "Code.cpp"
#include <map>
#include <vector>
#include <string>
#include "helper.h"
#include <chrono>
#include "json.hpp"
#include "/home/local/USHERBROOKE/eljc3201/anaconda3/envs/newEnv/include/python3.9/Python.h"

using namespace std;
using json = nlohmann::json;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::microseconds;

struct dataPerUser{
    bool startTraining;
    int seen_periods;
    int window_size;
    int sliding_size;
    std::vector<double> userkde;
    PyObject *lofPyModel;
    std::vector<double> centers;
    std::vector<double> stdvars;
    std::vector<int> scores;
    std::vector<int> minutes;

};


struct users{
    int userId;
    std::map<int,dataPerUser> f;
    std::vector<std::string> alerts;

};

users global;

int main(int argc, char** argv)
{
	//std::cout<<"hello world"<<std::endl;
	IO::configInputStream(argc, argv);
	global.f.clear();
    global.alerts = {};
	setenv("PYTHONPATH", ".",0);
	Py_Initialize();
	std::map<int,double> performences;
	int count = 0;
	while (1)
	{
		auto start = high_resolution_clock::now();
		Event  _evt = IO::read_event(argc);
		if(_evt.label.empty())
		{
			break;
		
		}else if(_evt.label.compare("e") == 0)
		{
			int userId = Types::get_int(_evt.params[0]);
			std::string eventDate = Types::get_str(_evt.params[1]);
			std::string eventId = Types::get_str(_evt.params[2]);	
			if(global.f.find(userId) == global.f.end()){
				global.f[userId].startTraining = false;
				global.f[userId].minutes = {};
				global.f[userId].seen_periods = 0; 
				global.f[userId].window_size = 3000;
				global.f[userId].sliding_size = 1500;
				global.f[userId].userkde = {};
				global.f[userId].centers = {};
				global.f[userId].stdvars = {};
				global.f[userId].lofPyModel = nullptr;
			}
			Code::add(global.f[userId].startTraining,global.f[userId].seen_periods,global.f[userId].window_size,global.f[userId].sliding_size,global.f[userId].minutes,eventDate);
			Code::training(global.f[userId].minutes, global.f[userId].startTraining,global.f[userId].userkde,&global.f[userId].lofPyModel,global.f[userId].centers,global.f[userId].stdvars);
			Code::detection(global.f[userId].scores,global.alerts,eventDate,eventId,global.f[userId].userkde,global.f[userId].lofPyModel,global.f[userId].centers,global.f[userId].stdvars);		
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			count = count + 1;
			performences[count] = duration.count();
			
			
			continue;
			
		
		}else 
		{
			ERROR_1;
		
		}
		
	}
	Py_Finalize();
	std::cout<<"number of alerts :  "<<global.alerts.size()<<endl;
	json j_vec(global.alerts);
    std::ofstream o("alertscombined.json");
	json j_map(performences);
	std::ofstream o1("performences.json");
	o1<<j_map<<std::endl;
    o<<j_vec<<std::endl;
	return 0;

}
