#ifndef LOF_H
#define LOF_H

#include <vector>
#include <map>
#include "../model.h"
#include <Python.h>

using namespace std;
class lof : public model{
    
    private:
        PyObject* pyModel;
        double meanScores;
        double sdScores;
        double threshold;
        int numNeighbors;
        std::vector<std::string> alerts;
    public:
        
        lof();
        lof(int);
        PyObject* getPyModel();
        void setPyModel(PyObject*);
        double getMeanScores();
        void setMeanScores(double);
        double getSdScores();
        void setSdScores(double);
        double getThreshold();
        void setThreshold(double);
        int getNumNeighbors();
        void setNumNeighbors(int);
        std::vector<std::string> getAlerts();
        void setAlerts(std::vector<std::string>);
        void training(std::vector<int> data);
        void detection(std::string,std::string,std::vector<int>&); 

};


#endif