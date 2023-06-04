#include <iostream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "lof.h"
#include "../../nlohmann/json.hpp"
#include <Python.h>

using json = nlohmann::json;
using namespace std;
    
    lof::lof(){
        this->pyModel=NULL;
        this->numNeighbors = 20;
        this->alerts={};
    };
    lof::lof(int numNeighbors){
        this->pyModel=NULL;
        this->numNeighbors = numNeighbors;
        this->alerts={};
    };
    PyObject* lof::getPyModel(){
        return this->pyModel;
    };
    void lof::setPyModel(PyObject* pyModel){
        this->pyModel = pyModel;
    };
    double lof::getMeanScores(){
        return this->meanScores;
    };
    void lof::setMeanScores(double meanScores){
        this->meanScores = meanScores;
    };
    double lof::getSdScores(){
        return this->sdScores;
    };
    void lof::setSdScores(double sdScores){
        this->sdScores = sdScores;
    };
    double lof::getThreshold(){
        return this->threshold;
    };
    void lof::setThreshold(double threshold){
        this->threshold = threshold;
    };
    int lof::getNumNeighbors(){
        return this->numNeighbors;
    };
    void lof::setNumNeighbors(int numNeighbors){
        this->numNeighbors = numNeighbors;
    };
    std::vector<std::string> lof::getAlerts(){
        return this->alerts;
    };
    void lof::setAlerts(std::vector<std::string> alerts){
        this->alerts = alerts;
    };
    void lof::training(std::vector<int> data){
        PyObject* result = PyList_New(0);
        for (int i = 0; i < data.size(); i++) {
            PyList_Append(result, PyLong_FromLong(data[i]));
        }
        PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
        pName = PyUnicode_FromString((char*)"LOF");
        //PyObject_Print(pName, stdout, 0);
        pModule = PyImport_Import(pName);
        if (pModule == nullptr)
        {
            PyErr_Print();
            std::exit(1);
        }
        pFunc = PyObject_GetAttrString(pModule, (char*)"train");
        pArgs = PyTuple_Pack(2, result,PyLong_FromLong(getNumNeighbors()));
        pValue = PyObject_CallObject(pFunc, pArgs);
        setPyModel(pValue);
        
        Py_DECREF(pName);
        Py_DECREF(pModule);
        Py_DECREF(pFunc);
        Py_DECREF(pArgs);
            
        

    };
    void lof::detection(std::string eventDate,std::string eventId,std::vector<int>& labels){
        
        if(getPyModel() != NULL){
            int heure = stoi(eventDate.substr(12, 2));
            int minute = stoi(eventDate.substr(15, 2));
            int value = heure * 60 + minute;
            PyObject *pFunc,*pArgs,*pName,*pModule;
            PyObject *pValue = PyTuple_New(1);
            pName = PyUnicode_FromString((char*)"LOF");
            pModule = PyImport_Import(pName);
            pFunc = PyObject_GetAttrString(pModule, (char*)"score");
            pArgs = PyTuple_Pack(2, getPyModel(),PyLong_FromLong(value));
            pValue = PyObject_CallObject(pFunc, pArgs);
            if (pValue == nullptr)
            {
                PyErr_Print();
                std::exit(1);
            }
            double score = PyFloat_AsDouble(PyTuple_GetItem(pValue,0));
            int label = int (PyFloat_AsDouble(PyTuple_GetItem(pValue,1)));
            if(label == -1){
                this->alerts.push_back(eventId);
                labels.push_back(1);
            }else{
                labels.push_back(0);
            }
            Py_DECREF(pName);
            Py_DECREF(pModule);
            Py_DECREF(pFunc);
            Py_DECREF(pArgs);
      
        }
    }; 