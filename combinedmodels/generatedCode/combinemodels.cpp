#include "learning_models/KDE/kde.h"
#include "Code.cpp"
#include "learning_models/KMEANS/kmeans.h"
#include "learning_models/LOF/lof.h"
#include "learning_models/model.h"
#include "helper.h"
#include <Python.h>
enum AutState
{
  S0
};
struct TState_Data_Parser
{
  AutState  autState;

};
struct TState_majorityVote
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
struct TState_ASTDA39F
{
  TState_training  ts_training;
  TState_scoring  ts_scoring;

};
struct TState_detectors
{
  std::string   d;
  std::map<std::string ,model*>  mapdetectors;
  std::map<std::string , TState_ASTDA39F>  f;

};
struct TState_combination
{
  vector<int>  scores;
  TState_detectors  ts_detectors;
  TState_majorityVote  ts_majorityVote;

};
struct TState_Detection_Per_User
{
  window1*  sliding_window;
  std::map<int,std::vector<int>>  data;
  TState_combination  ts_combination;
  TState_Data_Parser  ts_Data_Parser;

};
struct TState_CombineModels
{
  int  userId;
  int  lof_parameters;
  json  window_parameters;
  double  kde_parameters;
  vector<tuple<std::string ,int,std::string >>  alerts;
  double  kmeans_parameters;
  std::map<int, TState_Detection_Per_User>  f;

};
const std::vector<string>  T_detectors = {json::parse("\"kmeans\""), json::parse("\"kde\""), json::parse("\"lof\"")};
const std::vector<AutState>  shallow_final_training = {S0};
const std::vector<AutState>  shallow_final_scoring = {S0};
const std::vector<AutState>  shallow_final_majorityVote = {S0};
const std::vector<AutState>  shallow_final_Data_Parser = {S0};
TState_CombineModels  ts_CombineModels;

int  forall_detectorsfinal(std::string &  d)
{
	int  exec = 0;
	for(auto const& c : ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f)
	{
		d = c.first;
		if((std::find(shallow_final_training.begin(), shallow_final_training.end(), ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState) !=shallow_final_training.end() && std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState) !=shallow_final_scoring.end()))
		{
			exec = exec + 1;
		
		}else 
		{
			return 0;
		
		}
	
	}
	if(exec == T_detectors.size())
	{
		return 1;
	
	}else if(exec < T_detectors.size())
	{
		if((std::find(shallow_final_training.begin(), shallow_final_training.end(), S0) !=shallow_final_training.end() && std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), S0) !=shallow_final_scoring.end()))
		{
			return 1;
		
		}
	
	}
	return 0;

}

int  forall_CombineModelsfinal(int&  userId)
{
	int  exec = 0;
	for(auto const& c : ts_CombineModels.f)
	{
		userId = c.first;
		if((((forall_detectorsfinal(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d) && (std::find(shallow_final_training.begin(), shallow_final_training.end(), ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState) !=shallow_final_training.end() && std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState) !=shallow_final_scoring.end())) && std::find(shallow_final_majorityVote.begin(), shallow_final_majorityVote.end(), ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majorityVote.autState) !=shallow_final_majorityVote.end()) && std::find(shallow_final_Data_Parser.begin(), shallow_final_Data_Parser.end(), ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState) !=shallow_final_Data_Parser.end()))
		{
			exec = exec + 1;
		
		}
	
	}
	if((exec == ts_CombineModels.f.size() && (((forall_detectorsfinal(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d) && (std::find(shallow_final_training.begin(), shallow_final_training.end(), ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState) !=shallow_final_training.end() && std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState) !=shallow_final_scoring.end())) && std::find(shallow_final_majorityVote.begin(), shallow_final_majorityVote.end(), S0) !=shallow_final_majorityVote.end()) && std::find(shallow_final_Data_Parser.begin(), shallow_final_Data_Parser.end(), S0) !=shallow_final_Data_Parser.end())))
	{
		return 1;
	
	}
	return 0;

}

int  exists_detectorse_d(int&  p0, std::string &  p1, std::string &  p2, std::string &  d)
{
	for(string _d_ : T_detectors)
	{
		d = _d_;
		if(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.find(d) !=ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.end())
		{
			if(((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState == S0 && p0 == ts_CombineModels.userId ) || (ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState == S0 && p0 == ts_CombineModels.userId )))
			{
				return 1;
			
			}
		
		}else 
		{
			ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState = S0;
			ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState = S0;
			if(((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState == S0 && p0 == ts_CombineModels.userId ) || (ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState == S0 && p0 == ts_CombineModels.userId )))
			{
				return 1;
			
			}
		
		}
	
	}
	return 0;

}

int  exists_CombineModelse_userId(int&  p0, std::string &  p1, std::string &  p2)
{
	ts_CombineModels.userId = p0;
	if(ts_CombineModels.f.find(p0) !=ts_CombineModels.f.end())
	{
		if(((exists_detectorse_d(p0, p1, p2, ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d) || (ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majorityVote.autState == S0 && p0 == ts_CombineModels.userId )) || (ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState == S0 && p0 == ts_CombineModels.userId )))
		{
			return 1;
		
		}
	
	}else 
	{
		ts_CombineModels.f[ts_CombineModels.userId].sliding_window = new window1(ts_CombineModels.window_parameters);
		ts_CombineModels.f[ts_CombineModels.userId].data = {};
		ts_CombineModels.f[ts_CombineModels.userId].ts_combination.scores = {};
		ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.mapdetectors = Code::init_map(ts_CombineModels.kde_parameters,ts_CombineModels.kmeans_parameters,ts_CombineModels.lof_parameters);
		ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.clear();
		ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majorityVote.autState = S0;
		ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState = S0;
		if(((exists_detectorse_d(p0, p1, p2, ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d) || (ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majorityVote.autState == S0 && p0 == ts_CombineModels.userId )) || (ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState == S0 && p0 == ts_CombineModels.userId )))
		{
			return 1;
		
		}
	
	}
	return 0;

}

int    e(int  p0, std::string   p1, std::string   p2)
{
	int  exec = 0;
	if(exists_CombineModelse_userId(p0, p1, p2))
	{
		if((exists_detectorse_d(p0, p1, p2, ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d) || (ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majorityVote.autState == S0 && p0 == ts_CombineModels.userId )))
		{
			if(exists_detectorse_d(p0, p1, p2, ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d))
			{
				if(exists_detectorse_d(p0, p1, p2, ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d))
				{
					for(string d : T_detectors)
					{
						ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d = d;
						if(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.find(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d) ==ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f.end())
						{
							ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState = S0;
							ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState = S0;
						
						}
						if((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState == S0 && p0 == ts_CombineModels.userId ))
						{
							if((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState == S0 && p0 == ts_CombineModels.userId ))
							{
								ts_CombineModels.f[ts_CombineModels.userId].sliding_window->fit_partial(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.mapdetectors[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d],ts_CombineModels.f[ts_CombineModels.userId].data);
								ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_training.autState = S0;
								exec = 1;
							
							}
						
						}
						if((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState == S0 && p0 == ts_CombineModels.userId ))
						{
							if((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState == S0 && p0 == ts_CombineModels.userId ))
							{
								ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.mapdetectors[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d]->score_partial(p1,p2,ts_CombineModels.f[ts_CombineModels.userId].ts_combination.scores);
								ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.f[ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_detectors.d].ts_scoring.autState = S0;
								exec = 1;
							
							}
						
						}
					
					}
				
				}
			
			}
			if((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majorityVote.autState == S0 && p0 == ts_CombineModels.userId ))
			{
				if((ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majorityVote.autState == S0 && p0 == ts_CombineModels.userId ))
				{
					Code::majorityVote(ts_CombineModels.f[ts_CombineModels.userId].ts_combination.scores,ts_CombineModels.alerts,p2,p1);
					ts_CombineModels.f[ts_CombineModels.userId].ts_combination.ts_majorityVote.autState = S0;
					exec = 1;
				
				}
			
			}
		
		}
		if((ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState == S0 && p0 == ts_CombineModels.userId ))
		{
			if((ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState == S0 && p0 == ts_CombineModels.userId ))
			{
				Code::formatting_data(ts_CombineModels.f[ts_CombineModels.userId].data,ts_CombineModels.f[ts_CombineModels.userId].sliding_window,p1);
				ts_CombineModels.f[ts_CombineModels.userId].ts_Data_Parser.autState = S0;
				exec = 1;
			
			}
		
		}
	
	}
	return exec;

}
int main(int argc, char** argv)
{
	IO::configInputStream(argc, argv);
	ts_CombineModels.lof_parameters = lof_parameters;
	ts_CombineModels.window_parameters = window_parameters;
	ts_CombineModels.kde_parameters = kde_parameters;
	ts_CombineModels.alerts = {};
	ts_CombineModels.kmeans_parameters = kmeans_parameters;
	ts_CombineModels.f.clear();
	setenv("PYTHONPATH", "../python_code",0);
	Py_Initialize();
	std::map<int,double> performences;
	//int count = 0;
	while (1)
	{
		//auto start = high_resolution_clock::now();
		Event  _evt = IO::read_event(argc);
		if(_evt.label.empty())
		{
			break;
		
		}else if(_evt.label.compare("e") == 0)
		{
			bool  flag = 0;
			if(_evt.params.size() == 3)
			{
				int  p0;
				p0 = Types::get_int(_evt.params[0], flag);
				std::string   p1;
				p1 = Types::get_str(_evt.params[1]);
				std::string   p2;
				p2 = Types::get_str(_evt.params[2]);
				if((!(flag) && e(p0, p1, p2)))
				{
					//auto stop = high_resolution_clock::now();
					//auto duration = duration_cast<microseconds>(stop - start);
					//count = count + 1;
					//performences[count] = duration.count();
					//std::cout<<duration.count()<<std::endl;
					continue;
				}else if(flag)
				{
					ERROR_6;
				
				}else 
				{
					ERROR_2;
				
				}
			
			}else 
			{
				ERROR_7;
			
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
