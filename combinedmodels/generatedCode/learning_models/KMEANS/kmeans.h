#ifndef KMEANS_H
#define KMEANS_H

#include <iostream>
#include <vector>
#include <map>
#include "../model.h"


using namespace std;
class kmeans : public model {
    private:
        std::vector<std::string> alerts;
        std::vector<double> centers;
        std::map<int,double> seuils;
        std::vector<double> means;
        std::vector<double> stdvars;
        std::map<int,vector<double>> clusters;
        double threshold;
        int risInitialized;
        int numClusters;

    public:
        kmeans();
        kmeans(double);
        void setThreshold(double);
        double getThreshold();
        std::map<int,vector<double>> getClusters();
        void setClusters(std::map<int,vector<double>>);
        std::map<int,double> getSeuils();
        void setSeuils(std::map<int,double>);
        std::vector<double> getCenters();
        void setCenters(std::vector<double>);  
        std::vector<double> getStdvars();
        void setStdvars(std::vector<double>); 
        int getNumClusters();
        void setNumClusters(int);       
        std::vector<std::string> getAlerts();
        double distance(double a, double b);
        void training(std::vector<int> data);
        void detection(std::string,std::string,std::vector<int>&);
        ~kmeans();
};



#endif