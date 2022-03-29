
/*------------------------------------------------------------------------------------------------------------------------*/
/*                                    The Graph Theory course, lab work No.1
*
*    @author: Kuznetsov A.D
*    @date: 	28 March 2022
*
*    @brief:
*                   This work includes:
*                   1. Generation of non-cycled oriented graph with lognormal probability
*              distribution of vertexes' degrees
*                   2. Shimbell method realization
*                   3. The determination of amount (or it's absence) of ways from vertex1
*              to vertex2
*
*   	@sources:
*    			   1. Cormen, Thomas H.; Leiserson, Charles E.; Rivest, Ronald L.; Stein,
*    		   Clifford. Introduction to Algorithms. — 3rd. — MIT Press, 2009.
*              ISBN 0-262-03384-4.
*                 2. Sedgewick, Robert (2002). Algorithms, 3rd Edition, in C++, Part 5:
*              Graph Algorithms. Reading, MA: Addison-Wesley. ISBN 978-0201361186.
*                3. Vadzinskiy R N 2001 Spravochnik po veroyatnostnym raspredeleniyam
*   		   [Handbook of Probability Distributions] (Saint-Petersburg: Nauka) p. 82
*
*		@information:
*   			 https://https://github.com/DeCrinal/TGraph_1Lab_NoGui
*/

#include "includes.h"
using namespace std;

int main()
{
    std::vector<int>arr;
    int Vam;
    std::cout<<"Input amount of vertex: ";
    std::cin>>Vam;
    for(int i = 0; i<Vam; i++){
        arr.push_back(lognormal_rand_generator());
    }

    /*Sorting for correct distribution*/
    sort(arr.rbegin(),arr.rend());
    for(int i = 0; i<Vam; i++){
        std::cout<<arr[i]<<std::endl;
    }

    /*Initializing and filling the graph*/
    Graph dir_graph(Vam,true);
    int sum_edges = 0;
    for(int i = 0; i<Vam;i++){
        sum_edges+=arr[i];
    }
    fill_graph(dir_graph,sum_edges,arr);
    dir_graph.print_graph();

    /*Setting weights of edges*/
    set_edges_weight(dir_graph);
    dir_graph.print_weights();

    /*Declaration and initialization of temporal degree matrix, which */
    /*includes weight of ways between vertexes                                   */
    std::vector<std::vector<int>>degree_matrix;
    int edges_am;
    std::cout<<"Input amount of edges for Shimbell algorithm:"<<std::endl;
    std::cin>>edges_am;
    degree_matrix = dir_graph.generate_shimbel(edges_am);
    std::cout<<std::endl;
    for(uint i = 0; i<degree_matrix.size();i++){
        for(uint j = 0; j<degree_matrix.size();j++){
           std::cout<<degree_matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    /*Calculation the amount of ways between vertex1 and vertex2*/
    while(1){
        std::vector<bool>visited;
        visited.assign(Vam,false);
        int v1, v2, amount_of_ways=0;
        std::cin>>v1>>v2;
        dir_graph.is_way_between(v1,v2,visited,amount_of_ways);
        if(amount_of_ways)
            std::cout<<"Yes"<<std::endl;
        else
            std::cout<<"No"<<std::endl;
        std::cout<<"Amount of ways:"<<amount_of_ways<<std::endl;
    }
    return 0;
}
