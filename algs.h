
/*------------------------------------------------------------------------------------------------------------------------*/
/*                            The file for additional functions for lab work No.1
*
*    @author: Kuznetsov A.D
*    @date: 	28 March 2022
*
*    @brief:
*                   This file includes:
*                   1. Function for lognormal distribution numbers generation
*
*   	@sources:
*   			   1. Vadzinskiy R N 2001 Spravochnik po veroyatnostnym raspredeleniyam
*   		  [Handbook of Probability Distributions] (Saint-Petersburg: Nauka) p. 82
*
*		@information:
*   			 https://https://github.com/DeCrinal/TGraph_1Lab_NoGui
*/

#ifndef ALGS_H
#define ALGS_H
#include"includes.h"
int lognormal_rand_generator();
int binomial_rand_generator();
bool get_number(int&n,int min, int max,std::string info);
bool get_decision(std::string &str, std::string info);
int to_call_menu();
#endif // ALGS_H
