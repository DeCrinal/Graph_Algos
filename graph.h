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
class edge_v2 {
    int a, b, cost;
public:
    edge_v2(int m_a, int m_b, int m_cost) { a = m_a; b = m_b; cost = m_cost; }
    int getA() { return a; }
    int getB() { return b; }
    int getCost() { return cost; }
    bool operator < (const edge_v2& other) { return cost < other.cost; }
};
class Graph
{
private:
    int Vcnt, Ecnt;			//1
    bool is_directed;		//1
    bool is_all_nonnegative;
    std::vector<std::vector<int>>adj;	//1



    std::vector<std::vector<int>>weights;//1

    std::vector<std::vector<int>>weights_with_INF;
    std::vector<int>predecessor;
    std::vector<int>destination;


    std::vector<std::vector<int>>capacity;
    //std::vector<std::vector<int>>costs_with_INF;
    std::vector<std::vector<int>>costs;

    std::vector<Edge>edges;
public:
    Graph();
    Graph(int max_vertex,bool is_directed);
    Graph(const Graph&graph);//1
    ~Graph();
    int V()const;//returns amount of vertexes //1
    int E() const;//returns amount of edges		//1
    bool directed() const;//returns if graph directed //1
    bool nonnegative() const; //returns if all elements are non-negative
    void insert (Edge edge);//insert edge to graph			//1
    void remove (Edge edge);//remove edge from graph	 	//1
    void edit(Edge edge, int weight);//insert weith of edge//1
    bool edge(int vertex1, int vertex2);//returns if there is an certain edge in graph//1
    class adjIterator;//typical iterator
    friend class adjIterator;
    void print_graph();//prints graph in matrix view //1
    void print_weights();//print weights of edges in matrix view //1
    void print_destination();
    void print_predecessor();
    void print_capacity();
    void print_costs();
    std::vector<std::vector<int>>&get_weights_with_INF();
    std::vector<std::vector<int>>&get_adj();
    int shimbel_min(std::vector<int>arr_for_min);//additional for generate_shimbel()
    int shimbel_max(std::vector<int>arr_for_max);//additional for generate_shimbel()
    std::vector<std::vector<int>> generate_shimbel(int degree, std::string min_or_max);//generate shimbell matrix
    Graph operator=(const Graph&graph);

    /*returns if there is a way between temp_graph;
            break;vertex1 and vertex2*/
    bool is_way_between(int v1, int v2, std::vector<bool>visited /*,
                        std::vector<std::vector<int>> matrix*/, int &amount); 	//1
    bool is_positive_way(int v1, int v2, std::vector<std::vector<int>>&ost_net,
                         std::vector<std::vector<int>>&potok_matr,int&min, int&res_max_potok, std::vector<bool>&visisited,
                         bool &is_ost_changed);
    void initialize_single_source(int source_vertex);
    void relax(int vertex1, int vertex2,std::vector<std::vector<int>>&matrix);
    bool bellman_ford(std::vector<std::vector<int>>&matrix, int source_vertex, bool is_print);
    void dijkstra(int source_vertex);
    void floyd_uorshall();
    void set_edges_capacity();//analogical
    void set_edges_costs();//analogical
    void set_edges_weight();//analogical
    int ford_falkerson();

    int min_cost_flow();// k - needed bundwidth
    std::vector<std::set<int>>*prim(std::vector<std::vector<int>>&matr_adj,
                      std::vector<std::vector<int>>&matr_weight);
    std::vector<std::set<int>>* kruskal(std::vector<std::vector<int>>& matr_adj,
                    std::vector<std::vector<int>>& weight_matr);
    std::vector<int>generate_path_by_predcessor();
    void prufer_coding(std::vector<std::set<int>>*ostotv, std::vector<int>&prufer_code);
    void prufer_encoding(std::vector<std::set<int>>* ostov, std::vector<int>& pruferCode);
};
void kirhgof(std::vector<std::vector<int>>& arr,
             std::vector<std::vector<int>>& matrixVesov);
void fill_graph(Graph &G, int E,std::vector<int>arr);//fill graph with user's values
void swap_to_unorientied(std::vector<std::vector<int>>&matr, int value_of_block);
void swap_to_orientied(std::vector<std::vector<int>>&matr, int value_of_block);
void init_with_null(std::vector<std::vector<int>>&matr);
void init_with_INF(std::vector<std::vector<int>>&matr);

int euler(std::vector<std::vector<int>> gr);
void euler_graph_true(std::vector<std::vector<int>> EulerGr);
void is_euler(std::vector<std::vector<int>>& EulerGr);
void is_gamilton_graph(std::vector<std::vector<int>>& GamGr,
               std::vector<std::pair<int, int>>& path);
bool gamilton(std::vector<std::vector<int>>& GamGr, std::vector<std::pair<int, int>>& path,
          bool print);
void is_gam(std::vector<std::vector<int>>& GamGr, std::vector<std::pair<int, int>>& path);
void TSP(std::vector<std::vector<int>>& GamGr);
/*------------------------------------------------UNUSED PART-----------------------------------------*/
/*Priority queue. This class uses partly ordered full tree with multy-brances*/

/*Remove_minimum - d*Log_{d}V*/
/*Decrease_the_key - Log_{d}V*/
template <class keyType> class PQi{
    int d, N;
    std::vector<int>pq, qp;
    const std::vector<keyType> &a;
    void exch(int i, int j){
        int t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
        qp[pq[i]]=i;
        qp[pq[j]]=j;
    }
    void fixUp(int k){
        while(k>1 && a[pq[(k+d-2)/d]]>a[pq[k]]){
            exch(k,(k+d-2)/d);
            k = (k+d-2)/d;
        }
    }
    void fixDown(int k, int N){
        int j;
        while((j=d*(k-1)+2)<=N)
        {
            for(int i = j+1; i<j+d && i<=N;i++){
                if(a[pq[j]] > a[pq[i]]) { j=i; }
            }
            if(!(a[pq[k]] > a[pq[j]])) break;
            exch(k,j);
            k = j;
        }
    }
public:
    PQi(int N, const std::vector<keyType> &a, int d = 3):
        a(a), pq(N+1,0), qp(N+1,0), N(0), d(d){};
    int empty() const  {return N ==0;};
    void insert(int v){
        pq[++N] = v;
        qp[v] = N;
        fixUp(N);
    }
    int getmin(){
        exch(1,N);
        fixDown(1,N-1);
        return pq[N--];
    }
    void lower(int k )
    {
        fixUp(qp[k]);
    }
};
/*Minimal spanning forest, p.243 Sedjwik*/
//mst - rebra dereva
//fr - samoe korotkoe derevo, soedinyayushee nedrevesnie vershini s derevov
//wt - dlina etogo rebra
template <class Graph, class Edge> class MST{
   const Graph &G;
   std::vector<double> wt;
   std::vector<Edge *> fr, mst;
public:
   MST(const Graph &G):G(G),
       mst(G.V()), wt(G.V(), G.V()), fr(G.V())
   {
       int min = -1;
       for(int v = 0;  min!=0; v = min)
       {
           min = 0;
           for(int w = 1; w < G.V();w++){
               if(mst[w]==0){
                   double P;
                   Edge* e = G.edge(v,w);
                   if(e){
                       if((P = e->wt())<wt[w]){
                           wt[w] = P;
                           fr[w] = e; }
                       if(wt[w]<wt[min]){ min = w; }
                   }
               }
           }
           if(min){
               mst[min]=fr[min];
           }
       }
   }
   void show(){
       for(int v = 1; v<G.V();v++){
           if(mst[v]) mst[v]->show();
       }
   }
};
/*------------------------------------------------UNUSED PART-----------------------------------------*/

#endif // GRAPH_H
