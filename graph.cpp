#include"includes.h"
struct Edge
{
    int vertex1, vertex2;
    int weight;
    Edge(int vertex1 =-1, int vertex2 = -1): vertex1(vertex1), vertex2(vertex2){};
};
Graph::Graph(int max_vertex,bool is_directed):
        adj(max_vertex),weights(max_vertex),Vcnt(max_vertex),Ecnt(0),is_directed(is_directed)
    {
            for(int i = 0; i<max_vertex;i++)
            {
                adj[i].assign(max_vertex,false);
                weights[i].assign(max_vertex,0);
            }
    }
Graph::~Graph(){};
int Graph::V()const
{
    return Vcnt;
}
int Graph:: E() const
{
    return Ecnt;
}
bool Graph::directed() const
{
    return is_directed;
}
void Graph::insert (Edge edge)
{
    int vertex1 = edge.vertex1, vertex2 = edge.vertex2;
    if(adj[vertex1][vertex2] == false)
    {
        Ecnt++;
    }
    adj[vertex1][vertex2]=true;
    if(!is_directed)
    {
        adj[vertex2][vertex1] = true;
    }
}
void Graph::remove (Edge edge)
{
    int vertex1 = edge.vertex1, vertex2 = edge.vertex2;
    if(adj[vertex1][vertex2] == true){
        Ecnt--;
    }
    adj[vertex1][vertex2]=false;
    if(!is_directed){
        adj[vertex1][vertex2]=false;
    }
}

void Graph::edit(Edge edge, int weight)
{
    int vertex1 = edge.vertex1, vertex2 = edge.vertex2;
    weights[vertex1][vertex2] = weight;
}

bool Graph::edge(int vertex1, int vertex2)
{
    return adj[vertex1][vertex2];
}

void Graph::print_graph()
{
   for(int i = 0; i<this->Vcnt;i++){
       for(int j = 0; j<this->Vcnt;j++){
           std::cout<<adj[i][j]<<" ";
       }
       std::cout<<std::endl;
   }
}

void Graph::print_weights()
{
   for(int i = 0; i<this->Vcnt;i++){
       for(int j=0; j<this->Vcnt;j++){
           std::cout<<weights[i][j]<<" ";
       }
       std::cout<<std::endl;
   }
}
class Graph::adjIterator
{
    const Graph &G;
    int i, vertex;
    public:
    adjIterator(const Graph &G, int vertex):
        G(G),vertex(vertex),i(-1){}
    int begin()
    {
        i = -1;
        return next();
    }
    int next()
    {
        for(i++;i<G.V();i++){
            if(G.adj[vertex][i]==true)
                return i;
        }
        return -1;
    }
    int end()
    {
        return i >=G.V();
    }
};
void fill_graph(Graph &G, int E,std::vector<int>arr)
{
    for(int i = 0; i<G.V();i++)
    {
        int sum=arr[i];
        for(int j = i+1; j<G.V();j++){
            if(sum){
                G.insert(Edge(i,j));
                sum--;
            }
        }
    }
}

void set_edges_weight(Graph&G)
{
   for(int i = 0; i<G.V();i++){
       std::cout<<"Set weigths for ["<<i<<"] line"<<std::endl;
       for(int j = 0;j<G.V();j++){
            if(G.edge(i,j)){
                int input;
                std::cout<<"\tSet weight for ("<<i<<","<<j<<"):";
                std::cin>>input;
                G.edit(Edge(i,j),input);
            }
       }
   }
}
int Graph::shimbel_min(std::vector<int>arr_for_min){
    int res = 0;
    for(uint i = 0; i<arr_for_min.size();i++){
        if(res==0||(arr_for_min[i]<res&&arr_for_min[i]!=0)){
            res = arr_for_min[i];
        }
    }
    return res;
}
std::vector<std::vector<int>> Graph::generate_shimbel(int degree){
    std::vector<std::vector<int>>prev_degree_matrix;
    std::vector<std::vector<int>>res;
    if(degree == 1){
        return this->weights;
    }
    else if(degree == 2){
        prev_degree_matrix = this->weights;
    }
    else{
        prev_degree_matrix = generate_shimbel(degree-1);
    }
    res= prev_degree_matrix; //just for initialization
    for(int i = 0; i<this->V();i++){
        for(int j = 0; j<this->V();j++){
        std::vector<int>arr_for_min;
           for(int ik=0, jk=0; ik<this->V();ik++,jk++){
               if(this->weights[i][ik]&&prev_degree_matrix[jk][j]){
                    arr_for_min.push_back(this->weights[i][ik]+prev_degree_matrix[jk][j]);
               }
               else
                   arr_for_min.push_back(0);
           }
           res[i][j]=shimbel_min(arr_for_min);
        }
    }
    return res;
}
bool Graph::is_way_between(int v1, int v2, std::vector<bool>visited /*,
                    std::vector<std::vector<int>> matrix*/, int &amount){
    if(v1 == v2){
        amount++;
    }
    visited.at(v1) = true;
    int k = 0;
    for(auto vertex:weights.at(v1))
    {
        if(vertex&&!visited.at(k))
        {
            if(is_way_between(k,v2,visited,amount)){
                return true;
            }
        }
        k++;
    }
    return false;
}
