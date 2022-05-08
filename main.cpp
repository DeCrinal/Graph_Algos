
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
    int op, Vam;
    Graph dir_graph;
    do{
        op = to_call_menu();
        switch(op){
        case(0):{ 										//Create or recreate graph
            std::vector<int>arr;
            int Vam;

            //std::cin>>Vam;
            while(!get_number(Vam, 2, 40, "Input amount of vertex: "));
            for(int i = 0; i<Vam-1; i++){
                //arr.push_back(lognormal_rand_generator());
                arr.push_back(lognormal_rand_generator());
            }


            /*Sorting for correct distribution*/
            sort(arr.rbegin(),arr.rend());
            for(int i = 0; i<Vam-1; i++){
                std::cout<<arr[i]<<std::endl;
            }

            /*Initializing and filling the graph*/
            //Graph dir_graph(Vam,true);
            Graph temp_graph(Vam,true);
            int sum_edges = 0;
            for(int i = 0; i<Vam;i++){
                 sum_edges+=arr[i];
            }
            fill_graph(temp_graph,sum_edges,arr);
            dir_graph=temp_graph;
            break;
        }
        case(1):												//Print graph
        {
            dir_graph.print_graph();
            break;
        }
        case(2):												//Fill weights
        {
            dir_graph.set_edges_weight();
            break;
        }
        case(3):												//Print weights
        {
           dir_graph.print_weights();
           break;
        }
        case(4):												//Print shimbell
        {
            /*Declaration and initialization of temporal degree matrix, which */
            /*includes weight of ways between vertexes                                   */
            std::vector<std::vector<int>>degree_matrix;
            int edges_am;
            //std::cout<<"Input amount of edges for Shimbel algorithm: ";
            //std::cin>>edges_am;
            while(!get_number(edges_am,1,1000,"Input amount of edges for Shimbell algorithm: "));
            degree_matrix = dir_graph.generate_shimbel(edges_am, "min");
            std::cout<<"Shimbel min:"<<std::endl;
            for(uint i = 0; i<degree_matrix.size();i++){
                for(uint j = 0; j<degree_matrix.size();j++){
                    std::cout<<degree_matrix[i][j]<<"\t";
                }
                std::cout<<std::endl;
            }
            degree_matrix = dir_graph.generate_shimbel(edges_am,"max");
            std::cout<<"Shimbel max:"<<std::endl;
            for(uint i = 0; i<degree_matrix.size();i++){
                for(uint j = 0; j<degree_matrix.size();j++){
                    std::cout<<degree_matrix[i][j]<<"\t";
                }
                std::cout<<std::endl;
            }
            break;
        }
        case(5):
        {
            std::vector<bool>visited;
            visited.assign(Vam,false);
            int v1, v2, amount_of_ways=0;
            while(!get_number(v1,0,dir_graph.V()-1,"Input vertex1 and vertex2: "));
            while(!get_number(v2,0,dir_graph.V()-1,""));
            if((v1<0||v2<0||v1>=dir_graph.V()||v2>=dir_graph.V())){
                std::cout<<"Incorrect data"<<std::endl;
                continue;
            }
            dir_graph.is_way_between(v1,v2,visited,amount_of_ways);
            if(amount_of_ways)
                std::cout<<"Yes"<<std::endl;
            else
                std::cout<<"No"<<std::endl;
            std::cout<<"Amount of ways:"<<amount_of_ways<<std::endl;
            break;
        }
        case(6):
        {
            int source;
            while(!get_number(source,0,dir_graph.V()-1,"Input source for Bellman-Ford: "));
            if(dir_graph.bellman_ford(source))
            {
                dir_graph.print_destination();
                dir_graph.print_predecessor();
            }
            else{
                std::cout<<"Negative cycle"<<std::endl;
            }
            break;
        }
        case(7):
        {
                if(dir_graph.nonnegative() == false){
                    std::cout<<"There are negative elements. Dijkstra can't be used"<<std::endl;
                    break;
                }
                int source;
                while(!get_number(source, 0, dir_graph.V()-1, "Input source for Dijkstra: "));
                if(true/*non negative, fix this*/){
                    dir_graph.dijkstra(source);
                    dir_graph.print_destination();
                    dir_graph.print_predecessor();
                }
            break;
        }
        case(8):
        {
            dir_graph.floyd_uorshall();
            break;
        }
        case(9):
        {
            std::vector<int>arr;
            int Vam;

            //std::cin>>Vam;
            while(!get_number(Vam, 2, 40, "Input amount of vertex: "));
            for(int i = 0; i<Vam-1; i++){
                //arr.push_back(lognormal_rand_generator());
                arr.push_back(lognormal_rand_generator());
            }


            /*Sorting for correct distribution*/
            sort(arr.rbegin(),arr.rend());
            for(int i = 0; i<Vam-1; i++){
                std::cout<<arr[i]<<std::endl;
            }

            /*Initializing and filling the graph*/
            //Graph dir_graph(Vam,true);
            Graph temp_graph(Vam,true);
            int sum_edges = 0;
            for(int i = 0; i<Vam;i++){
                 sum_edges+=arr[i];
            }
            fill_graph(temp_graph,sum_edges,arr);
            temp_graph.set_edges_weight();
            temp_graph.set_edges_capacity();
            temp_graph.set_edges_costs();
            dir_graph=temp_graph;
            dir_graph.print_weights();
            dir_graph.print_capacity();
            dir_graph.print_costs();
            break;
        }
        case(10):
        {
            dir_graph.ford_falkerson();
        }
        }
    }
    while(op!=100);
    return 0;
}
