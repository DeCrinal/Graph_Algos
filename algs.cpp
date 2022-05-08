#include "includes.h"
#define MAX 10000
const std::regex kRxNum("[0-9]{1,4}");
const std::regex kRxDec("[YyNn]");
int lognormal_rand_generator(){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    double p = 0.7;
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
int binomial_rand_generator()
{
    int n = 4;
    double p = 0.18;
    int i = 0, x = 0;
    std::random_device rd;
    std::mt19937 mersenne(rd());
    do{
        double r = mersenne()%(MAX-1)+1;
        r /=static_cast<double>(MAX);
        if(r<p){
            x++;
        }
        i++;
    }
    while(i<n);
    if(x==0)
        return 1;
    return x;
}
bool get_number(int &n, int min, int max, std::string info){
    std::cout<<info;
    std::string strInp;
    bool res = false;;
    //getline(std::cin, strInp);
    std::cin>>strInp;
    if(regex_match(strInp, kRxNum)){
        n=stoi(strInp);
        if(n>=min&&n<=max)
        {
            res = true;
        }
    }
    if(!res)
    {
        std::cout<<"Incorrect data, try again: "<<std::endl;
    }
    return res;
}
bool get_decision(std::string&str, std::string info){
   std::cout<<info;
   std::fflush(stdin);
   std::fflush(stdout);
   std::string strInp;
   bool res = false;
   getline(std::cin, strInp);
   if(regex_match(strInp, kRxDec)){
       str = strInp;
       res = true;
   }
   return res;
}

int to_call_menu()
{
   int op;
   std::cout<<"\t\t\t\t\t\t0. Create or recreate graph"<<std::endl;
   std::cout<<"\t\t\t\t\t\t1. Print graph"<<std::endl;
   std::cout<<"\t\t\t\t\t\t2. Fill weights"<<std::endl;
   std::cout<<"\t\t\t\t\t\t3. Print weights"<<std::endl;
   std::cout<<"\t\t\t\t\t\t4. Calculate Shimbell matrix\t\t\t\t - 1 Lab"<<std::endl;
   std::cout<<"\t\t\t\t\t\t5. Is way between v1 and v2"<<std::endl;
   std::cout<<"\t\t\t\t\t\t6. Use Bellman-Ford algorithm\t\t\t\t - 2 Lab"<<std::endl;
   std::cout<<"\t\t\t\t\t\t7. Use Dijkstra algorithm"<<std::endl;
   std::cout<<"\t\t\t\t\t\t8. Use Floyd-Uorshall algorithm"<<std::endl;
   std::cout<<"\t\t\t\t\t\t9. Generate capacity and costs for graph - 3 Lab"<<std::endl;
   std::cout<<"\t\t\t\t\t\t10. Use Ford-Falkerson"<<std::endl;
   std::cout<<"\t\t\t\t\t\t100. Exit"<<std::endl;
   while(!get_number(op,0,100,""));
   return op;
}


