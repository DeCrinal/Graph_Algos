#include"includes.h"
const int INF = (__INT32_MAX__)/2-1;
struct Edge
{
    int vertex1, vertex2;
    int weight;
    Edge(int vertex1 =-1, int vertex2 = -1): vertex1(vertex1), vertex2(vertex2){};
};
Graph::Graph()
{

}

Graph::Graph(int max_vertex,bool is_directed):
        adj(max_vertex),weights(max_vertex),Vcnt(max_vertex),Ecnt(0),is_directed(is_directed),
        destination(max_vertex),predecessor(max_vertex),weights_with_blocks(max_vertex),costs(max_vertex),
        capacity(max_vertex)
    {
            is_all_nonnegative = true;
            for(int i = 0; i<max_vertex;i++)
            {
                adj[i].assign(max_vertex,false);
                weights[i].assign(max_vertex,0);
                weights_with_blocks[i].assign(max_vertex,(__INT32_MAX__)/2 -1);
                capacity[i].assign(max_vertex,0);
                costs[i].assign(max_vertex,(__INT32_MAX__)/2-1);
            }
}

Graph::Graph(const Graph &graph)
{

    for(uint i = 0; i<this->weights.size();i++){
        weights[i].clear();
        weights_with_blocks[i].clear();
    }
    this->weights.clear();
    this->weights_with_blocks.clear();
    this->predecessor.clear();
    this->destination.clear();

    this->Ecnt=graph.Ecnt;
    this->Vcnt=graph.Vcnt;
    this->is_directed=graph.is_directed;
    this->is_all_nonnegative=graph.is_all_nonnegative;
    this->adj=graph.adj;
    this->weights=graph.weights;
    this->weights_with_blocks=graph.weights_with_blocks;
    this->predecessor=graph.predecessor;
    this->destination=graph.destination;
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

bool Graph::nonnegative() const
{
   return is_all_nonnegative;
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
    weights_with_blocks[vertex1][vertex2] = weight;
    if(weight<0)
        is_all_nonnegative = false;
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
           std::cout<<weights[i][j]<<"\t";
       }
       std::cout<<std::endl;
   }
}

void Graph::print_destination()
{
   for(uint i =0; i<destination.size();i++){
       if(destination[i]<(INF-1000))
       {
            std::cout<<destination[i]<<"\t";
       }
       else
       {
           std::cout<<"Inf ";
       }
   }
   std::cout<<std::endl;
}

void Graph::print_predecessor()
{
   for(uint i = 0; i<predecessor.size();i++){
       std::cout<<predecessor[i]<<"\t";
   }
   std::cout<<std::endl;
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

void Graph::set_edges_weight()
{
   for(int i = 0; i<this->V();i++){
       //std::cout<<"Set weigths for ["<<i<<"] line"<<std::endl;
       for(int j = 0;j<this->V();j++){
            if(this->edge(i,j)){
                int input;
                //std::cout<<"\tSet weight for ("<<i<<","<<j<<"):";
                //std::cin>>input;
                input = (rand()%100)-5;
                this->edit(Edge(i,j),input);
            }
       }
   }
   std::cout<<"Was successfully completed."<<std::endl;
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
int Graph::shimbel_max(std::vector<int>arr_for_max){
    int res = 0;
    for(uint i = 0; i<arr_for_max.size();i++){
        if(res==0||(arr_for_max[i]>res&&arr_for_max[i]!=0)){
            res = arr_for_max[i];
        }
    }
    return res;
}
std::vector<std::vector<int>> Graph::generate_shimbel(int degree, std::string min_or_max){
    std::vector<std::vector<int>>prev_degree_matrix;
    std::vector<std::vector<int>>res;
    bool is_min = true;
    if(min_or_max == "max"){
        is_min = false;
    }
    if(degree == 1){
        return this->weights;
    }
    else if(degree == 2){
        prev_degree_matrix = this->weights;
    }
    else{
        prev_degree_matrix = generate_shimbel(degree-1, min_or_max);
    }
    res = prev_degree_matrix; //just for initialization
    for(int i = 0; i<this->V();i++){
        for(int j = 0; j<this->V();j++){
        std::vector<int>arr_for_res;
           for(int ik=0, jk=0; ik<this->V();ik++,jk++){
               if(this->weights[i][ik]&&prev_degree_matrix[jk][j]){
                    arr_for_res.push_back(this->weights[i][ik]+prev_degree_matrix[jk][j]);
               }
               else
               {
                   arr_for_res.push_back(0);
               }
           }
           if(is_min)
                res[i][j]=shimbel_min(arr_for_res);
           else
               res[i][j]=shimbel_max(arr_for_res);
        }
    }
    return res;
}

Graph Graph::operator=(const Graph &graph)
{
    for(uint i = 0; i<this->weights.size();i++){
        weights[i].clear();
        weights_with_blocks[i].clear();
        capacity[i].clear();
        costs[i].clear();
    }
    this->weights.clear();
    this->weights_with_blocks.clear();
    this->predecessor.clear();
    this->destination.clear();
    this->costs.clear();
    this->capacity.clear();

    this->Ecnt=graph.Ecnt;
    this->Vcnt=graph.Vcnt;
    this->is_directed=graph.is_directed;
    this->is_all_nonnegative=graph.is_all_nonnegative;
    this->adj=graph.adj;
    this->weights=graph.weights;
    this->weights_with_blocks=graph.weights_with_blocks;
    this->predecessor=graph.predecessor;
    this->destination=graph.destination;
    this->costs = graph.costs;
    this->capacity=graph.capacity;
    return *this;
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

void Graph::initialize_single_source(int source_vertex)
{
   for(int i = 0; i<this->V();i++){
       destination[i]=INF;
       predecessor[i]=-1;
   }
   destination[source_vertex]=0;
}

void Graph::relax(int vertex1, int vertex2)
{
    if(destination[vertex2] > destination[vertex1]+weights_with_blocks[vertex1][vertex2]){
        destination[vertex2]=destination[vertex1]+weights_with_blocks[vertex1][vertex2];
        predecessor[vertex2]=vertex1;
    }
}

bool Graph::bellman_ford(int source_vertex)
{
    int iterations_am=0;
    initialize_single_source(source_vertex);
    for(int i = 0; i<this->V();i++){
        for(int j = 0; j<this->V();j++){
            relax(i,j);
        }
    }
    for(int j = 0; j<this->V();j++){
        const int src_tmp_vert=0;
        if(destination[j]>destination[src_tmp_vert]+weights_with_blocks[src_tmp_vert][j]){
            return false;
        }
        iterations_am++;
    }
    std::cout<<"Iterations for Bellman-Ford: "<<iterations_am<<std::endl;
    return true;
}

void Graph::dijkstra(int source_vertex)
{
    initialize_single_source(source_vertex);
    int iterations_am=0;
    int min_index;
    std::vector<bool>node(destination.size());
    for(uint i = 0; i<destination.size();i++){
        int min_vertex=INF;
        for(uint j = 0; j<destination.size();j++){
            if(!node[j]&&destination[j]<min_vertex){
                min_vertex = destination[j];
                min_index  = j;
            }
        }
        node[min_index] = true;
        for(uint j = 0; j<destination.size();j++){
            iterations_am++;
            if(!node[j]&& weights_with_blocks[min_index][j] > 0 &&
                    destination[min_index]<INF&&
                    destination[min_index]+weights_with_blocks[min_index][j]<destination[j])
            {
                destination[j]=destination[min_index]+weights_with_blocks[min_index][j];
                predecessor[j]=min_index;
            }
        }
    }
    predecessor[source_vertex]=-1;
    /*for(int i = 0; i<this->V();i++){
        if(Skk)
    }*/
    std::cout<<"Iterations for Dijkstra: "<<iterations_am<<std::endl;
}
void Graph::floyd_uorshall(){
    int iteration_am=0;
    std::vector<std::vector<int>>copy_weights = weights_with_blocks;
    for(int i = 0; i<this->V(); i++){
       for(int j = 0; j<this->V();j++){
           for(int k = 0; k<this->V();k++){
                copy_weights[j][k] = std::min(copy_weights[j][k],copy_weights[j][i]+copy_weights[i][k]);
                iteration_am++;
           }
       }
    }
    for(int i = 0; i<this->V();i++){
        copy_weights[i][i] = 0;
    }
    for(int i = 0; i<this->V();i++){
        for(int j = 0; j<this->V();j++){
            if(copy_weights[i][j]<INF)
                std::cout<<copy_weights[i][j]<<"\t";
            else
                std::cout<<"INF"<<"\t";
        }
        std::cout<<std::endl;
    }
    std::cout<<"Iterations for Floyd-Uorshall: "<<iteration_am<<std::endl;
    return;
}
void Graph::set_edges_capacity()
{
   for(int i = 0; i<this->V();i++){
       //std::cout<<"Set weigths for ["<<i<<"] line"<<std::endl;
       for(int j = 0;j<this->V();j++){
            if(this->edge(i,j)){
                int input;
                //std::cout<<"\tSet weight for ("<<i<<","<<j<<"):";
                //std::cin>>input;
                input = (rand()%100)+1;
                this->capacity[i][j] = input;
            }
       }
   }
   std::cout<<"Capacities were successfully completed."<<std::endl;
}
void Graph::set_edges_costs()
{
   for(int i = 0; i<this->V();i++){
       //std::cout<<"Set weigths for ["<<i<<"] line"<<std::endl;
       for(int j = 0;j<this->V();j++){
            if(this->edge(i,j)){
                int input;
                input = (rand()%10);
                this->costs[i][j]=input;
            }
       }
   }
   std::cout<<"Costs were successfully completed."<<std::endl;
}
void Graph::print_capacity(){
    std::cout<<"Capacities: "<<std::endl;
    for(uint i = 0; i<capacity.size();i++){
        for(uint j = 0; j<capacity.size();j++){
            std::cout<<capacity[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
void Graph::print_costs(){
    std::cout<<"Costs: "<<std::endl;
    for(uint i = 0; i<costs.size();i++){
        for(uint j = 0; j<costs.size();j++){
            if(costs[i][j]<INF-1000)
                std::cout<<costs[i][j]<<" ";
            else
                std::cout<<"INF"<<" ";
        }
        std::cout<<std::endl;
    }
}
bool Graph::is_positive_way(int v1, int v2, std::vector<std::vector<int>>&ost_net,
                std::vector<std::vector<int>>&potok_matr, int&min,int&res_max_potok,
                std::vector<bool>&visited,int &delMeCounter, bool &is_ost_changed){
    visited[v1]=true;
    int temp_min = min;
    bool is_way_from_cur=false;
    if(v1 == v2){
        visited[v1]=false;
        return true;
    }
    bool ost_probably_can_be_changed_again=false;		//there can be several ways from one vertex
    for (int i = 0; i<this->V(); i++){
        if(ost_net[v1][i]!=0){
            if(ost_net[v1][i]<min)
                min = ost_net[v1][i];
            if(visited[i]){
                is_way_from_cur=false;
                continue;
            }
            if(is_positive_way(i,v2,ost_net,potok_matr,min,res_max_potok, visited, delMeCounter, is_ost_changed))
            {
                ost_net[v1][i] -=min;
                ost_net[i][v1] +=min;
                is_ost_changed=true;
                potok_matr[v1][i]+=min;
                ost_probably_can_be_changed_again=true;
                std::cout<<v1<<"---------------"<<i<<std::endl;
                if(v1==0){
                    for(uint ki = 0; ki <ost_net.size();ki++){
                        for(uint kj = 0; kj<ost_net.size();kj++){
                            std::cout<<ost_net[ki][kj]<<" ";
                        }
                        std::cout<<std::endl;
                    }
                }
                std::cout<<min<<std::endl;
                is_way_from_cur=true;

                visited[v1]=false;
            }
            else{
                min = temp_min;
            }
        }
        if(is_ost_changed&&v1!=0){
            visited[v1]=false;
            return is_way_from_cur;
        }
        is_ost_changed=false;
        if(v1==0){
            min = INF;
            is_way_from_cur = false;
            visited[0]=true;
        }
        if(i+1 == this->V()&&ost_probably_can_be_changed_again){
            i=0;
            ost_probably_can_be_changed_again=false;
        }
    }
    return is_way_from_cur;
}
/*bool Graph::is_positive_way(int v1, int v2, std::vector<std::vector<int>>&ost_net,
                std::vector<std::vector<int>>&potok_matr, int&min,int&res_max_potok, std::vector<bool>visited){
    if(v1 == v2){
        return true;
    }
    visited.at(v1) = true;
    int k = 0;
    for(auto vertex_ost_capacity:ost_net.at(v1))
    {
        if(vertex_ost_capacity&&!visited.at(k))
        {
            if(vertex_ost_capacity<min)
                min = vertex_ost_capacity;
            if(is_positive_way(k,v2,ost_net, potok_matr,min, res_max_potok, visited))
            {
                if(v1!=0)
                    return true;
                else{

                }
            }
        }
        k++;
    }
    return false;
}*/
int Graph::ford_falkerson(){
    std::cout<<"-----1"<<std::endl;
    int delMeCounter = 0;
    bool is_ost_changed = false;
    std::vector<std::vector<int>>ost_net(this->V());
    std::vector<std::vector<int>>potok_matrix(this->V());
    std::vector<bool>visited_vertex;
    visited_vertex.assign(this->V(),false);
    for(int i = 0; i<this->V();i++){
        potok_matrix[i].assign(this->V(),0);
        ost_net[i].assign(this->V(),0);
    }
    ost_net = this->capacity;
    int v1 = 0, res_max_potok=0, min = INF;
    //is_positive_way(v1, this->V()-1, ost_net, potok_matrix, min, res_max_potok, visited_vertex, delMeCounter, is_ost_changed);
    is_positive_way(v1, this->V()-1, ost_net, potok_matrix, min,
                  res_max_potok, visited_vertex,delMeCounter, is_ost_changed);
    /*while(is_positive_way(v1, this->V()-1, ost_net, potok_matrix, min,
              res_max_potok, visited_vertex,delMeCounter, is_ost_changed))
    {
        if(is_ost_changed){
            std::cout<<"No, Cycled here"<<std::endl;
            min = INF;
            for(uint i = 0; i<visited_vertex.size();i++){
                visited_vertex[i]=false;
            }
            is_ost_changed=false;
        }
    }*/
    for(int i = 0; i<this->V();i++){
        res_max_potok +=potok_matrix[i][this->V()-1];
    }
    std::cout<<"------------------------------------res: " <<res_max_potok<<std::endl;
    for(int i = 0; i<this->V();i++){
        for(int j = 0; j<this->V();j++){
            std::cout<<potok_matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}
