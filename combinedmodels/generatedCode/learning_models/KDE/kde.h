#ifndef KDE_H
#define KDE_H

#include <iostream>
#include <vector>
#include "../model.h"


using namespace std;
class kde : public model {
    private:
        std::vector<double> data_post_training;
        std::vector<std::string> alerts;
        double threshold;
    public:
        kde();
        kde(double);
        void setData_post_training(std::vector<double> data_post_training);
        void setThreshold(double threshold);
        std::vector<double> getData_post_training();
        int getBins();
        double getThreshold();
        std::vector<std::string> getAlerts();
        void training(std::vector<int> data);
        void score_partial(std::string,std::string,std::vector<int>&);
        ~kde();
};



#endif