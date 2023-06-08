#include "Code.cpp"
#include "KDE/kde.h"
#include "window/window.h"
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
struct TState_training
{
  AutState  autState;

};
struct TState_scoring
{
  AutState  autState;

};
struct TState_Detector_instance
{
  kde*  detector;
  TState_scoring  ts_scoring;
  TState_training  ts_training;

};
struct TState_Detection_Per_User
{
  window1*  sliding_window;
  std::map<int,std::vector<int>>  data;
  TState_Detector_instance  ts_Detector_instance;
  TState_Data_Parser  ts_Data_Parser;

};
struct TState_detectionOneModel
{
  int  userId;
  std::vector<tuple<std::string ,std::string >>  alerts;
  json  window_parameters;
  double  threshold;
  std::map<int, TState_Detection_Per_User>  f;

};
const std::vector<AutState>  shallow_final_scoring = {S0};
const std::vector<AutState>  shallow_final_training = {S0};
const std::vector<AutState>  shallow_final_Data_Parser = {S0};
TState_detectionOneModel  ts_detectionOneModel;

int  forall_detectionOneModelfinal(int&  userId)
{
	int  exec = 0;
	for(auto const& c : ts_detectionOneModel.f)
	{
		userId = c.first;
		if(((std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_scoring.autState) !=shallow_final_scoring.end() && std::find(shallow_final_training.begin(), shallow_final_training.end(), ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_training.autState) !=shallow_final_training.end()) && std::find(shallow_final_Data_Parser.begin(), shallow_final_Data_Parser.end(), ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Data_Parser.autState) !=shallow_final_Data_Parser.end()))
		{
			exec = exec + 1;
		
		}
	
	}
	if((exec == ts_detectionOneModel.f.size() && ((std::find(shallow_final_scoring.begin(), shallow_final_scoring.end(), S0) !=shallow_final_scoring.end() && std::find(shallow_final_training.begin(), shallow_final_training.end(), S0) !=shallow_final_training.end()) && std::find(shallow_final_Data_Parser.begin(), shallow_final_Data_Parser.end(), S0) !=shallow_final_Data_Parser.end())))
	{
		return 1;
	
	}
	return 0;

}

int  exists_detectionOneModele_userId(int&  p0, std::string &  p1, std::string &  p2)
{
	ts_detectionOneModel.userId = p0;
	if(ts_detectionOneModel.f.find(p0) !=ts_detectionOneModel.f.end())
	{
		if((((ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_scoring.autState == S0 && p0 == ts_detectionOneModel.userId ) || (ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_training.autState == S0 && p0 == ts_detectionOneModel.userId )) || (ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Data_Parser.autState == S0 && p0 == ts_detectionOneModel.userId )))
		{
			return 1;
		
		}
	
	}else 
	{
		ts_detectionOneModel.f[ts_detectionOneModel.userId].sliding_window = new window1(ts_detectionOneModel.window_parameters);
		ts_detectionOneModel.f[ts_detectionOneModel.userId].data = {};
		ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.detector = new kde(ts_detectionOneModel.threshold);
		ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_scoring.autState = S0;
		ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_training.autState = S0;
		ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Data_Parser.autState = S0;
		if((((ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_scoring.autState == S0 && p0 == ts_detectionOneModel.userId ) || (ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_training.autState == S0 && p0 == ts_detectionOneModel.userId )) || (ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Data_Parser.autState == S0 && p0 == ts_detectionOneModel.userId )))
		{
			return 1;
		
		}
	
	}
	return 0;

}

int    e(int  p0, std::string   p1, std::string   p2)
{
	int  exec = 0;
	if(exists_detectionOneModele_userId(p0, p1, p2))
	{
		if(((ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_scoring.autState == S0 && p0 == ts_detectionOneModel.userId ) || (ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_training.autState == S0 && p0 == ts_detectionOneModel.userId )))
		{
			if((ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_scoring.autState == S0 && p0 == ts_detectionOneModel.userId ))
			{
				if((ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_scoring.autState == S0 && p0 == ts_detectionOneModel.userId ))
				{
					ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.detector->score_partial(p1,p2,ts_detectionOneModel.alerts);ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_scoring.autState = S0;
					exec = 1;
				
				}
			
			}
			if((ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_training.autState == S0 && p0 == ts_detectionOneModel.userId ))
			{
				if((ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_training.autState == S0 && p0 == ts_detectionOneModel.userId ))
				{
					ts_detectionOneModel.f[ts_detectionOneModel.userId].sliding_window->fit_partial(ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.detector,ts_detectionOneModel.f[ts_detectionOneModel.userId].data);ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Detector_instance.ts_training.autState = S0;
					exec = 1;
				
				}
			
			}
		
		}
		if((ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Data_Parser.autState == S0 && p0 == ts_detectionOneModel.userId ))
		{
			if((ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Data_Parser.autState == S0 && p0 == ts_detectionOneModel.userId ))
			{
				Code::formatting_data(ts_detectionOneModel.f[ts_detectionOneModel.userId].data,ts_detectionOneModel.f[ts_detectionOneModel.userId].sliding_window,p1);ts_detectionOneModel.f[ts_detectionOneModel.userId].ts_Data_Parser.autState = S0;
				exec = 1;
			
			}
		
		}
	
	}
	return exec;

}
int main(int argc, char** argv)
{
	IO::configInputStream(argc, argv);
	ts_detectionOneModel.alerts = {};
	ts_detectionOneModel.window_parameters = window_parameters;
	ts_detectionOneModel.threshold = threshold;
	ts_detectionOneModel.f.clear();
	while (1)
	{
		setenv("PYTHONPATH", "../KDE",0);
		Py_Initialize();
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
	std::cout<<"number of alerts :  "<<ts_detectionOneModel.alerts.size()<<endl;
	json j_vec(ts_detectionOneModel.alerts);
    std::ofstream o("alertsonemodel.json");
   	o<<j_vec<<std::endl;
	return 0;

}
