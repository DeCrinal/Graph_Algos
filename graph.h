/*------------------------------------------------------------------------------------------------------------------------*/
/*                  The file for general functions and classes for lab work No.1
*
*    @author: Kuznetsov A.D
*    @date: 	28 March 2022
*
*    @brief:
*                   This file includes:
*                   1. Graph-class methods and properties
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
#ifndef GRAPH_H
#define GRAPH_H
#include"includes.h"
struct Edge;
class Graph
{
private:
    int Vcnt, Ecnt;
    bool is_directed;
    std::vector<std::vector<bool>>adj;
    std::vector<std::vector<int>>weights;
public:
    Graph(int max_vertex,bool is_directed);
    ~Graph();
    int V()const;//returns amount of vertexes
    int E() const;//returns amount of edges
    bool directed() const;//returns if graph directed
    void insert (Edge edge);//insert edge to graph
    void remove (Edge edge);//remove edge from graph
    void edit(Edge edge, int weight);//insert weith of edge
    bool edge(int vertex1, int vertex2);//returns if there is an certain edge in graph
    class adjIterator;//typical iterator
    friend class adjIterator;
    void print_graph();//prints graph in matrix view
    void print_weights();//print weights of edges in matrix view
    int shimbel_min(std::vector<int>arr_for_min);//additional for generate_shimbel()
    std::vector<std::vector<int>> generate_shimbel(int degree);//generate shimbell matrix

    /*returns if there is a way between vertex1 and vertex2*/
    bool is_way_between(int v1, int v2, std::vector<bool>visited /*,
                        std::vector<std::vector<int>> matrix*/, int &amount);
};
void fill_graph(Graph &G, int E,std::vector<int>arr);//fill graph with user's values
void set_edges_weight(Graph &G);//analogical
#endif // GRAPH_H
