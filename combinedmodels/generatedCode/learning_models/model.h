
#ifndef __MODEL__
#define __MODEL__
#include <iostream>
#include <vector>


using namespace std;

class model {
   public: 
    virtual void training(vector<int> data)=0;
    virtual void score_partial(std::string,std::string,std::vector<int>&)=0;
    virtual ~model() = default;
};
#endif 