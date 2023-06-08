#include <iostream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <fstream>
#include "kde.h"
#include "../json.hpp"
#include <Python.h>
#include "numpy/arrayobject.h"

using json = nlohmann::json;
using namespace std;


kde::kde(){
    this->data_post_training={};
    this->alerts={};
    this->threshold=0.0001;
};
kde::kde(double threshold){
    this->data_post_training={};
    this->alerts={};
    this->threshold=threshold;
};

void kde::setData_post_training(std::vector<double> data_post_training){
    this->data_post_training = data_post_training;
};
void kde::setThreshold(double threshold){
    this->threshold =threshold;
};
std::vector<double> kde::getData_post_training(){
    return this->data_post_training;
};
std::vector<std::string> kde::getAlerts(){
    return this->alerts;
};
double kde::getThreshold(){
    return this->threshold;
};
void kde::fit_partial(std::vector<int> data){
        //créer le PyObject
        PyObject* result = PyList_New(0);
        for (int i = 0; i < data.size(); i++) {
            PyList_Append(result, PyLong_FromLong(data[i]));
        }

        //appeler la fonction avec les argument nécessaires
        PyObject *pName1, *pModule, *pFunc, *pArgs, *pValue;
        pName1 = PyUnicode_FromString((char*)"vonMises");
        pModule = PyImport_Import(pName1);
        pFunc = PyObject_GetAttrString(pModule, (char*)"circular_kde");
        pArgs = PyTuple_Pack(1, result);

        //exécuter et stocker le résultat
        pValue = PyObject_CallObject(pFunc, pArgs);

        //convertir en un c++ vector
        PyArrayObject *np_ret2 = reinterpret_cast<PyArrayObject*>(pValue);
        int len = PyArray_SHAPE(np_ret2)[0];
        double* c_out2= reinterpret_cast<double*>(PyArray_DATA(np_ret2));
        std::vector<double> dataMiraculeuse(c_out2,c_out2+len);
        setData_post_training(dataMiraculeuse);
        //json j_vec(getData_post_training());
        //std::ofstream o("kde1106.json");
        //o<<j_vec<<std::endl;
       
};
void kde::score_partial(std::string eventDate, std::string eventId, std::vector<tuple<std::string,std::string>>& alerts){
    if(getData_post_training().size()!=0){
        int heure = stoi(eventDate.substr(12, 2));
        int minute = stoi(eventDate.substr(15, 2));
        int value = heure * 60 + minute;
        if(getData_post_training()[value] <= getThreshold()){
            alerts.push_back(make_tuple(eventId,eventDate));
            std::cout<< eventId <<" is malicious"<<std::endl;
        }
    }
};

kde::~kde(){};
