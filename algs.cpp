#include "includes.h"
#define MAX 10000
int lognormal_rand_generator(){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    double p = 0.9;
    double q = 1 - p, a = p;
    p = (-1)*p/(log(q));
    double r = (mersenne()%(MAX-1)+1), x = 1.0;
    r /=static_cast<double>(MAX);
    r = r - p;
    while(r/*-__DBL_MIN__*/>=0){
        x = x+1;
        p = p*a*(x-1)/x;
        r = r - p;
        //std::cout<<"p:"<<p<<std::endl;
        //std::cout<<"r:"<<r<<std::endl;
        //std::cout<<"x:"<<x<<std::endl;
    }
    return x;
}
