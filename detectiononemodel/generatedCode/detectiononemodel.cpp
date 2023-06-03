#include "Code.cpp"
#include "helper.h"
#include "nlohmann/json.hpp"
#include <Python.h>


using json = nlohmann::json;
enum AutState
{
  S0
};
struct TState_Data_Parser
{
  AutState  autState;

};
struct TState_detection
{
  AutState  autState;

};
struct TState_training
{
  AutState  autState;

};
struct TState_Detector_instance
{
  kde*  detector;
  TState_training  ts_training;
  TState_detection  ts_detection;

};
struct TState_Detection_Per_User
{
  window1*  window;
  std::map<int,std::vector<int>>  data;
  TState_Detector_instance  ts_Detector_instance;
  TState_Data_Parser  ts_Data_Parser;

};
struct TState_Unnamed1
{
  int  userId;
  double threshold;
  json window_parameters;
  std::vector<tuple<std::string,std::string>>  alerts;
  std::map<int, TState_Detection_Per_User>  f;

};
const std::vector<AutState>  shallow_final_training = {S0};
const std::vector<AutState>  shallow_final_detection = {S0};
const std::vector<AutState>  shallow_final_Data_Parser = {S0};
TState_Unnamed1  ts_Unnamed1;

int  forall_Unnamed1final(int&  userId)
{
	int  exec = 0;
	for(auto const& c : ts_Unnamed1.f)
	{
		userId = c.first;
		if(((std::find(shallow_final_training.begin(), shallow_final_training.end(), ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_training.autState) !=shallow_final_training.end() && std::find(shallow_final_detection.begin(), shallow_final_detection.end(), ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_detection.autState) !=shallow_final_detection.end()) && std::find(shallow_final_Data_Parser.begin(), shallow_final_Data_Parser.end(), ts_Unnamed1.f[ts_Unnamed1.userId].ts_Data_Parser.autState) !=shallow_final_Data_Parser.end()))
		{
			exec = exec + 1;
		
		}
	
	}
	if((exec == ts_Unnamed1.f.size() && ((std::find(shallow_final_training.begin(), shallow_final_training.end(), S0) !=shallow_final_training.end() && std::find(shallow_final_detection.begin(), shallow_final_detection.end(), S0) !=shallow_final_detection.end()) && std::find(shallow_final_Data_Parser.begin(), shallow_final_Data_Parser.end(), S0) !=shallow_final_Data_Parser.end())))
	{
		return 1;
	
	}
	return 0;

}

int  exists_Unnamed1e_userId(int&  userId, int  _userId, std::string&  eventDate, std::string&  eventId)
{
	userId = _userId;
	if(ts_Unnamed1.f.find(userId) !=ts_Unnamed1.f.end())
	{
		if(((ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_training.autState == S0 || 
		ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_detection.autState == S0) || 
		ts_Unnamed1.f[ts_Unnamed1.userId].ts_Data_Parser.autState == S0))
		{
			return 1;
		
		}
	
	}else 
	{
		ts_Unnamed1.f[ts_Unnamed1.userId].window = new window1(ts_Unnamed1.window_parameters);
		ts_Unnamed1.f[ts_Unnamed1.userId].data = {};
		ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.detector = new kde(ts_Unnamed1.threshold);
		ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_training.autState = S0;
		ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_detection.autState = S0;
		ts_Unnamed1.f[ts_Unnamed1.userId].ts_Data_Parser.autState = S0;
		if(((ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_training.autState == S0 || ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_detection.autState == S0) || ts_Unnamed1.f[ts_Unnamed1.userId].ts_Data_Parser.autState == S0))
		{
			return 1;
		
		}
	
	}
	return 0;

}

int    e(int  _userId, std::string  eventDate, std::string  eventId)
{
	int  exec = 0;
	if(exists_Unnamed1e_userId(ts_Unnamed1.userId, _userId, eventDate, eventId))
	{
		if((ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_training.autState == S0 || ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_detection.autState == S0))
		{
			if(ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_training.autState == S0)
			{
				ts_Unnamed1.f[ts_Unnamed1.userId].window->fit_partial(ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.detector,ts_Unnamed1.f[ts_Unnamed1.userId].data);
				ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_training.autState = S0;
				exec = 1;	
			
			}
			if(ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_detection.autState == S0)
			{
				
				ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.detector->score_partial(eventDate,eventId,ts_Unnamed1.alerts);
				ts_Unnamed1.f[ts_Unnamed1.userId].ts_Detector_instance.ts_detection.autState = S0;
				exec = 1;	
			
			}
		
		}
		if(ts_Unnamed1.f[ts_Unnamed1.userId].ts_Data_Parser.autState == S0)
		{
				Code::formatting_data(ts_Unnamed1.f[ts_Unnamed1.userId].data,ts_Unnamed1.f[ts_Unnamed1.userId].window,eventDate);
				ts_Unnamed1.f[ts_Unnamed1.userId].ts_Data_Parser.autState = S0;
				exec = 1;
		
		}
	
	}
	return exec;

}
int main(int argc, char** argv)
{
	IO::configInputStream(argc, argv);
	ts_Unnamed1.window_parameters = window_parameters;
	ts_Unnamed1.threshold = threshold;
	ts_Unnamed1.alerts = {};
	ts_Unnamed1.f.clear();
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
			if(e(Types::get_int(_evt.params[0]), Types::get_str(_evt.params[1]), Types::get_str(_evt.params[2]))) 
			{
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
	std::cout<<"number of alerts :  "<<ts_Unnamed1.alerts.size()<<endl;
	json j_vec(ts_Unnamed1.alerts);
    std::ofstream o("alertsonemodel.json");
   	o<<j_vec<<std::endl;
	return 0;

}
