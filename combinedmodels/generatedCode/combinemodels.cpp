
#include "helper.h"
#include "learning_models/KMEANS/kmeans.h"
#include "learning_models/KDE/kde.h"
#include "learning_models/LOF/lof.h"
#include "learning_models/model.h"
#include "window/window.h"
#include "Code.cpp"
#include <Python.h>
#include <chrono>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::microseconds;
enum AutState
{
  S0
};
struct TState_majority_vote
{
  AutState  autState;

};
struct TState_scoring
{
  AutState  autState;

};
struct TState_training
{
  AutState  autState;

};
struct TState_ASTD32DE
{
  TState_training  ts_training;
  TState_scoring  ts_scoring;

};
struct TState_detectors
{
  std::string  d;
  std::map<std::string,model*>  detectors;
  std::map<std::string, TState_ASTD32DE>  f;

};
struct TState_combination
{
  std::vector<int> labels;
  
  TState_detectors  ts_detectors;
  TState_majority_vote  ts_majority_vote;

};
struct TState_Data_Parser
{
  AutState  autState;

};
struct TState_Detection_Per_User
{
  window1*  window;
  std::map<int,std::vector<int>>  data;
  TState_Data_Parser  ts_Data_Parser;
  TState_combination  ts_combination;

};
struct TState_CombineModels
{
  int  userId;
  std::vector<tuple<std::string,int,std::string>>  alerts;
  json window_parameters;
  double kde_parameters;
  double kmeans_parameters;
  int lof_parameters;
  std::map<int, TState_Detection_Per_User>  f;

};
const std::vector<AutState>  shallow_final_Data_Parser = {S0};
const std::vector<string>  T_detectors = { "kmeans","kde","lof"};
const std::vector<AutState>  shallow_final_training = {S0};
const std::vector<AutState>  shallow_final_scoring = {S0};
const std::vector<AutState>  shallow_final_majority_vote = {S0};
TState_CombineModels  ts_CombineModels;


int  exists_detectorse_d(std::string&  d, int  _userId, std::string&  eventDate, std::string&  eventId)
{
	for(string c : T_detectors)
	{
		d = c;
		if(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.find(d) !=ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.end())
		{
			if((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState == S0 || ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState == S0))
			{
				return 1;
			
			}
		
		}else 
		{
			ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState = S0;
			ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState = S0;
			if((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState == S0 || ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState == S0))
			{
				return 1;
			
			}
		
		}
	
	}
	return 0;

}

int  exists_CombineModelse_userId(int&  userId, std::string&  d, int  _userId, std::string&  eventDate, std::string&  eventId)
{
	userId = _userId;
	if(ts_CombineModels.f.find(userId) !=ts_CombineModels.f.end())
	{
		if((ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState == S0 || (exists_detectorse_d(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d, userId, eventDate, eventId) || ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majority_vote.autState == S0)))
		{
			return 1;
		
		}
	
	}else 
	{
		ts_CombineModels.f[ts_CombineModels.userId].window = new window1(ts_CombineModels.window_parameters);
		ts_CombineModels.f[ts_CombineModels.userId].data = {};
		ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState = S0;
		ts_CombineModels.f[ts_CombineModels.userId].ts_combination.labels = {};		
		ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.detectors = Code::init_map(ts_CombineModels.kde_parameters,ts_CombineModels.kmeans_parameters,ts_CombineModels.lof_parameters);
		ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.clear();
		ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majority_vote.autState = S0;
		if((ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState == S0 || (exists_detectorse_d(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d, userId, eventDate, eventId) || ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majority_vote.autState == S0)))
		{
			return 1;
		
		}
	
	}
	return 0;

}

int    e(int  _userId, std::string  eventDate, std::string  eventId)
{
	int  exec = 0;
	if(exists_CombineModelse_userId(ts_CombineModels.userId,ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d, _userId, eventDate, eventId))
	{
		if(ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState == S0)
		{
			if(ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState == S0)
			{
				Code::formatting_data(ts_CombineModels.f[ts_CombineModels.userId].data,ts_CombineModels.f[ts_CombineModels.userId].window,eventDate);
				ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState = S0;
				exec = 1;
			
			}
		
		}
		if((exists_detectorse_d(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d, _userId, eventDate, eventId) || ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majority_vote.autState == S0))
		{
			if(exists_detectorse_d(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d, _userId, eventDate, eventId))
			{
				
				for(string d : T_detectors)
				{
					ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d = d;
					if(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.find(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d) ==ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.end())
					{
						ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState = S0;
						ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState = S0;
					
					}
					if(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState == S0)
					{
						if(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState == S0)
						{
							
							ts_CombineModels.f[ts_CombineModels.userId].window->fit_partial(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.detectors[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d],ts_CombineModels.f[ts_CombineModels.userId].data);
							ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState = S0;
							exec = 1;
						
						}
					
					}
					if(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState == S0)
					{
						if(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState == S0)
						{
							ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.detectors[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d]->detection(eventDate,eventId,ts_CombineModels.f[ts_CombineModels.userId].ts_combination.labels);
							ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState = S0;
							exec = 1;
						
						}
					
					}
				
				}
				
				
			
			}
			if(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majority_vote.autState == S0)
			{
				Code::majorityVote(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.labels,ts_CombineModels.alerts,eventId,eventDate);
				ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majority_vote.autState = S0;
				exec = 1;
			
			}
		}
	
	}
	return exec;

}
int main(int argc, char** argv)
{
	IO::configInputStream(argc, argv);
	ts_CombineModels.f.clear();
	ts_CombineModels.window_parameters = window_parameters;
	ts_CombineModels.kde_parameters = kde_parameters;
	ts_CombineModels.kmeans_parameters = kmeans_parameters;
	ts_CombineModels.lof_parameters = lof_parameters;
	setenv("PYTHONPATH", "../python_code",0);
	Py_Initialize();
	std::map<int,double> performences;
	//int count = 0;
	ts_CombineModels.alerts = {};
	while (1)
	{
		//auto start = high_resolution_clock::now();
		Event  _evt = IO::read_event(argc);
		if(_evt.label.empty())
		{
			break;
		
		}else if(_evt.label.compare("e") == 0)
		{
			if(e(Types::get_int(_evt.params[0]), Types::get_str(_evt.params[1]), Types::get_str(_evt.params[2])))
			{
				//auto stop = high_resolution_clock::now();
				//auto duration = duration_cast<microseconds>(stop - start);
				//count = count + 1;
				//performences[count] = duration.count();
				//std::cout<<duration.count()<<std::endl;
				continue;
			}else 
			{
				ERROR_2;
			
			}
		
		}else 
		{
			ERROR_1;
		
		}
		
	}
	Py_Finalize();
	std::cout<<"number of alerts :  "<<ts_CombineModels.alerts.size()<<endl;
	json j_vec(ts_CombineModels.alerts);
    std::ofstream o("alertscombined.json");
	//json j_map(performences);
	//std::ofstream o1("performences.json");
	//o1<<j_map<<std::endl;
    o<<j_vec<<std::endl;
	return 0;

}
