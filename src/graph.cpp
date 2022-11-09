#include"includes.h"
const int INF = (__INT32_MAX__)/2-1;
std::vector<int> deg;
struct Edge
{
    int vertex1, vertex2;
    int weight;
    int capacity, cost, flow;
    Edge(int vertex1 =-1, int vertex2 = -1):
        vertex1(vertex1), vertex2(vertex2){};
};
Graph::Graph()
{

}

Graph::Graph(int max_vertex,bool is_directed):
        adj(max_vertex),weights(max_vertex),Vcnt(max_vertex),Ecnt(0),is_directed(is_directed),
        destination(max_vertex),predecessor(max_vertex),weights_with_INF(max_vertex),costs(max_vertex),
        capacity(max_vertex)
    {
            is_all_nonnegative = true;
            for(int i = 0; i<max_vertex;i++)
            {
                adj[i].assign(max_vertex,false);
                weights[i].assign(max_vertex,0);
                weights_with_INF[i].assign(max_vertex,(__INT32_MAX__)/2 -1);
                capacity[i].assign(max_vertex,0);
                costs[i].assign(max_vertex,(__INT32_MAX__)/2-1);
            }
}

Graph::Graph(const Graph &graph)
{

    for(uint i = 0; i<this->weights.size();i++){
        weights[i].clear();
        weights_with_INF[i].clear();
    }
    this->weights.clear();
    this->weights_with_INF.clear();
    this->predecessor.clear();
    this->destination.clear();

    this->edges = graph.edges;
    this->Ecnt=graph.Ecnt;
    this->Vcnt=graph.Vcnt;
    this->is_directed=graph.is_directed;
    this->is_all_nonnegative=graph.is_all_nonnegative;
    this->adj=graph.adj;
    this->weights=graph.weights;
    this->weights_with_INF=graph.weights_with_INF;
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
    edges.push_back(Edge(vertex1, vertex2));
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
    weights_with_INF[vertex1][vertex2] = weight;
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
       for(int j = 0;j<this->V();j++){
            if(this->edge(i,j)){
                int input;
                input = (rand()%100)-5;
                if(input==0)
                    input++;
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
        weights_with_INF[i].clear();
        capacity[i].clear();
        costs[i].clear();
    }
    this->weights.clear();
    this->weights_with_INF.clear();
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
    this->weights_with_INF=graph.weights_with_INF;
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

void Graph::relax(int vertex1, int vertex2, std::vector<std::vector<int>>&matrix)
{
    if(destination[vertex2] > destination[vertex1]+matrix[vertex1][vertex2]){
        destination[vertex2]=destination[vertex1]+matrix[vertex1][vertex2];
        predecessor[vertex2]=vertex1;
    }
}

bool Graph::bellman_ford(std::vector<std::vector<int>>&matrix, int source_vertex, bool is_print)
{
    int iterations_am=0;

    initialize_single_source(source_vertex);
    for(int i = 0; i<this->V();i++){
        for(int j = 0; j<this->V();j++){
            relax(i,j,matrix);
        }
    }
    for(int j = 0; j<this->V();j++){
        const int src_tmp_vert=0;
        if(destination[j]>destination[src_tmp_vert]+matrix[src_tmp_vert][j]){
            return false;
        }
        iterations_am++;
    }
    if(is_print)
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
            if(!node[j]&& weights_with_INF[min_index][j] > 0 &&
                    destination[min_index]<INF&&
                    destination[min_index]+weights_with_INF[min_index][j]<destination[j])
            {
                destination[j]=destination[min_index]+weights_with_INF[min_index][j];
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
    std::vector<std::vector<int>>copy_weights = weights_with_INF;
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
                input = (rand()%10)+1;
                this->costs[i][j]=input;
                //this->costs_with_INF[i][j]=input;
            }
            else{
                //this->costs_with_INF[i][j]=INF;
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

std::vector<std::vector<int> > &Graph::get_weights_with_INF()
{
        return this->weights_with_INF;
}

std::vector<std::vector<int> > &Graph::get_adj()
{
    return this->adj;
}
bool Graph::is_positive_way(int v1, int v2, std::vector<std::vector<int>>&ost_net,
                std::vector<std::vector<int>>&potok_matr, int&min,int&res_max_potok,
                std::vector<bool>&visited, bool &is_ost_changed){
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
            if(is_positive_way(i,v2,ost_net,potok_matr,min,res_max_potok, visited, is_ost_changed))
            {
                ost_net[v1][i] -=min;
                ost_net[i][v1] +=min;
                is_ost_changed=true;
                potok_matr[v1][i]+=min;
                ost_probably_can_be_changed_again=true;
                //std::cout<<v1<<"---------------"<<i<<std::endl;
                /*if(v1==0){
                    for(uint ki = 0; ki <ost_net.size();ki++){
                        for(uint kj = 0; kj<ost_net.size();kj++){
                            std::cout<<ost_net[ki][kj]<<" ";
                        }
                        std::cout<<std::endl;
                    }
                }*/
                //std::cout<<min<<std::endl;
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
    is_positive_way(v1, this->V()-1, ost_net, potok_matrix, min,
                  res_max_potok, visited_vertex, is_ost_changed);
    for(int i = 0; i<this->V();i++){
        res_max_potok +=potok_matrix[i][this->V()-1];
    }
    std::cout<<"Max_flow------------------------------------res: " <<res_max_potok<<std::endl;
    std::cout<<"Bandwidth matrix: "<<std::endl;
    for(int i = 0; i<this->V();i++){
        for(int j = 0; j<this->V();j++){
            std::cout<<potok_matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return res_max_potok;
}
int Graph::min_cost_flow(){
    int s=0, t=this->V()-1 ;
    int flow = this->ford_falkerson();
    int minCostFlow = 0;
    int res = 0;
    std::cout << "Max flow is " << flow << ". ";
    flow = flow * 2 / 3;
    std::cout << "Choosed 2/3*flow is: " << flow << '\n';

    std::vector<std::vector<int>> tmpModifiedWeightsMatrix(this->costs);
    std::vector<std::vector<int>> tmpCapacityMatrix(this->capacity);

    while (flow!=0)
    {
        this->bellman_ford(tmpModifiedWeightsMatrix, s,false);
        std::vector<int> route(this->generate_path_by_predcessor());

        int bottleNeck = INF;
        int cost = 0;

        for (std::vector<int>::iterator it = route.begin(); it != route.end()-1; it++)
        {
            if (tmpCapacityMatrix[*it][*(it + 1)] < bottleNeck)
                bottleNeck = tmpCapacityMatrix[*it][*(it + 1)];
            std::cout << *it << "->";
        }

        bottleNeck = std::min(bottleNeck, flow);
        std::cout << t <<" Flow of " << bottleNeck;

        for (std::vector<int>::iterator it = route.begin(); it != route.end() - 1; it++)
        {
            tmpCapacityMatrix[*it][*(it + 1)]-=bottleNeck;
            cost += tmpModifiedWeightsMatrix[*it][*(it + 1)];
            if (!tmpCapacityMatrix[*it][*(it + 1)])
                tmpModifiedWeightsMatrix[*it][*(it + 1)] = INF;
        }

    std::cout << " with cost of " << cost<<std::endl;;

    std::cout<<"Cost*flow: "<<cost*bottleNeck<<std::endl;
    minCostFlow += cost * bottleNeck;

    res+=cost;

    flow -= bottleNeck;

    }
    std::cout<<"Minicost flow-----------------------------------res: "<<res<<std::endl;
    std::cout<<"Total cost----------------------------------------res: "<<minCostFlow<<std::endl;
    return minCostFlow;
}

std::vector<int> Graph::generate_path_by_predcessor()
{
   std::vector<int>path;
   int i = this->V()-1; path.push_back(i);
   while(this->predecessor[i]!=-1){
       i = this->predecessor[i];
       path.push_back(i);
   }
   for(uint i = 0; i<path.size()/2;i++){
       std::swap(path[i],path[path.size()-1-i]);
   }
   return path;
}

/*int Graph::prim(){
    int a,b,u,v,n,i,j,ne=1;
    int min,mincost=0;
    std::vector<std::vector<int>>cost_temp(this->costs);
    swap_to_unorientied(cost_temp,INF);
    std::vector<int>visited(this->V(),0);
    std::vector<int>path(this->V()*this->V(),0);
    n = this->V();
    int path_index=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            {
                if(cost_temp[i][j]==0)
                    cost_temp[i][j]=INF;
            }
    }
    visited[0]=1;
    while(ne < n) {
        for(i=0,min=INF;i<n;i++)
            for(j=0;j<n;j++)
                if(cost_temp[i][j]< min)
                    if(visited[i]!=0)
                    {
                        min=cost_temp[i][j];
                        a=u=i;
                        b=v=j;
                    }
                    if(visited[u]==0 || visited[v]==0)
                    {
                        path[path_index]=b;
                        path_index++;
                        //cout<<"\n "<<ne++<<"  "<<a<<"  "<<b<<min; //????? ??????? ???
                        ne++; //???? ??????? ???? ????????????????? - ??? ????????????????
                        mincost+=min;
                        visited[b]=1;
                    }
                    cost_temp[a][b]=cost_temp[b][a]=INF;
            }
    std::cout<<0<<" --> ";
    for (int i=0;i<n-1;i++)
    {
        std::cout<<path[i];
        if (i<n-2)
            std::cout<<" --> ";
    }
    std::cout<<"\n Min cost:"<<mincost;
    return 0;
}*/
std::vector<std::set<int>>* Graph::prim(std::vector<std::vector<int>>&arr,std::vector<std::vector<int>>&weight_matr){
        int it = 0;

        int cost = 0;
        std::vector<bool> used(arr.size());
        std::vector<int> min_e(arr.size(), INF), sel_e(arr.size(), -1);
        min_e[0] = 0;
        std::vector<std::set<int>>* ostov = new std::vector<std::set<int>>(arr.size());
        for (uint i = 0; i < arr.size(); ++i)
        {
            int v = -1;
            for (uint j = 0; j < arr.size(); ++j)
                if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                {
                    v = j;
                }
            if (min_e[v] == INF)
            {
                std::cout << std::endl;
                std::cout << "No ostov tree";
                std::cout << std::endl;
                exit(0);
            }

            used[v] = true;


            for (uint to = 0; to < arr.size(); ++to)
            {
                if (weight_matr[v][to] < min_e[to])
                {
                    min_e[to] = weight_matr[v][to];
                    sel_e[to] = v;

                }
                it++;
            }


            if (sel_e[v] != -1)
            {
                ostov->at(sel_e[v]).insert(v);
                ostov->at(v).insert(sel_e[v]);
                if ((sel_e[v] + 1) > (v + 1))
                {
                    std::cout << v<< " --> " << sel_e[v] << std::endl;
                }
                else
                {
                    std::cout << sel_e[v] << " --> " << v << std::endl;

                }
                cost += weight_matr[sel_e[v]][v];

            }

        }
        std::cout << std::endl;
        std::cout << "\nCost of min ostov: " << cost << std::endl;
        std::cout << std::endl;
        std::cout << "Amount of iteration:" << it << std::endl;
        std::cout << std::endl;

        return ostov;
}
std::vector<std::set<int>>* Graph::kruskal(std::vector<std::vector<int>>& arr,
                    std::vector<std::vector<int>>& matrixVesov)
{

    int it = 0, m = 0;
    int count = 0;
    for (uint i = 0; i < arr.size(); i++)
        for (uint j = 0; j < arr.size(); j++)
        {
            if (arr[i][j] > 0 && arr[i][j] < (INF / 2))
                m++;
        }
    m = m / 2;

    std::vector <edge_v2> g;
    for (uint i = 0; i < arr.size(); i++)
    {
        for (uint j = i; j < arr.size(); j++)
            if (matrixVesov[i][j] < 500)
            {
                g.push_back(edge_v2(i, j, matrixVesov[i][j]));
                count++;
            }
    }
    int cost = 0;
    std::vector < std::pair<int, int> > res;

    sort(g.begin(), g.end());

    std::vector<int> tree_id(arr.size());
    for (uint i = 0; i < arr.size(); ++i)
        tree_id[i] = i;
    for (int i = 0; i < m; ++i)
    {
        int a = g[i].getA(), b = g[i].getB(), l = g[i].getCost();
        if (tree_id[a] != tree_id[b])
        {
            cost += l;

            res.push_back(std::make_pair(a, b));

            int old_id = tree_id[a], new_id = tree_id[b];


            for (int j = 0; j < arr.size(); ++j)
            {
                if (tree_id[j] == old_id)
                {
                    tree_id[j] = new_id;

                }
                it++;
            }

        }

    }
    std::vector<std::set<int>>* ostov = new std::vector<std::set<int>>(arr.size());
    for_each(res.begin(), res.end(), [&](std::pair<int, int> x)
        {
            ostov->at(x.first).insert(x.second);
            ostov->at(x.second).insert(x.first);
            if (x.first > x.second)
            {
                std:: cout << x.second<< " --> " << x.first << std::endl;
            }
            else
            {
                std::cout << x.first << " --> " << x.second << std::endl;
            }
        });
    std::cout << std::endl;
    std::cout << "\nCost of min ostov: " << cost << std::endl;
    std::cout << std::endl;
    std::cout << "\nAmount of iteration:"<< it << std::endl;
    std::cout << std::endl;

    return ostov;

}

void swap_to_unorientied(std::vector<std::vector<int>>&matr, int value_of_block){
    for(uint i = 0; i<matr.size();i++){
        for(uint j = i+1;j<matr.size();j++){
            if(matr[i][j]!=value_of_block)
                matr[j][i]=matr[i][j];
        }
    }
}
void swap_to_orientied(std::vector<std::vector<int>>&matr, int value_of_block){
    for(uint i = 0; i<matr.size();i++){
        for(uint j = i+1; j<matr.size();j++){
            if(matr[i][j]!=value_of_block)
                matr[j][i]=value_of_block;
        }
    }
}
void Graph::prufer_coding(std::vector<std::set<int>>* ostov, std::vector<int>& pruferCode)
{
    if (ostov == nullptr)
    {
        std::cout << std::endl;
        std::cout << "\nError! Get an ostov!\n";
        std::cout << std::endl;
        return;
    }
    if (ostov->size() == 2)
    {
        std::cout << "0" << std::endl;
        return;
    }
    if (pruferCode.size() == (ostov->size() - 2))
    {
        std::cout << std::endl;
        std::cout << "\nPrufer's code: " << std::endl;
        std::cout << std::endl;
        for (uint i = 0; i < ostov->size() - 2; i++)
            std::cout << pruferCode.at(i) << ' ';
        std::cout << std::endl;
        return;
    }
    std::vector<bool> visited(ostov->size());

    while (pruferCode.size() != ostov->size() - 2)
    {
        for (uint i = 0; i < ostov->size(); i++)
        {
            if (!visited[i])
                if (ostov->at(i).size() == 1)
                {
                    visited[i] = true;
                    for (uint j = 0; j < ostov->size(); j++)
                    {
                        ostov->at(i).clear();
                        auto iter = ostov->at(j).find(i);
                        if (iter != ostov->at(j).end())
                        {
                            ostov->at(j).erase(*iter);
                            pruferCode.push_back(j);

                            break;
                        }

                    }
                    break;
                }
        }
    }
    std::cout << std::endl;
    std::cout << "\nPrufer's code: " << std::endl;
    std::cout << std::endl;
    for (uint i = 0; i < ostov->size() - 2; i++)
        std::cout << pruferCode.at(i) << ' ';
    std::cout << std::endl;
}
int findMinor(std::vector<std::vector<int>>& buffer, int x, int y)
{
    int minor = 0;

    std::vector<std::vector<int>> arr(buffer.size() - 1, std::vector<int>(buffer.size() - 1));
    int k = 0, f = 0;
    for (uint i = 0; i < buffer.size(); i++)
    {
        f = 0;
        for (uint j = 0; j < buffer.size(); j++)
        {
            if ((i != x) && (j != y))
            {
                arr[k][f] = buffer[i][j];
                f++;
            }
        }
        if (i != x)
            k++;
    }
    if ((buffer.size() - 1) == 1)
    {
        minor = arr[0][0];
    }
    else
    {
        for (uint i = 0; i < buffer.size() - 1; i++)
        {
            minor += arr[0][i] * pow(-1, (1 + i + 1)) * findMinor(arr, 0, i);
        }
    }
    return minor;
}

void kirhgof(std::vector<std::vector<int>>& arr,
         std::vector<std::vector<int>>& matrixVesov)
{

    int count = 0;
    std::vector<std::vector<int>> buffer(arr.size(), std::vector<int>(arr.size()));
    for (uint i = 0; i < arr.size(); i++)
    {
        for (uint j = 0; j < arr.size(); j++)
            if (arr[i][j] == INF)
                buffer[i][j] = 0;
            else
            {
                buffer[i][j] = -arr[i][j];
                count++;
            }
        buffer[i][i] = count;
        count = 0;
    }

    std::cout << "\nKihgof matrix: \n";
    for (uint i = 0; i < arr.size(); i++)
    {
        for (uint j = 0; j < arr.size(); j++)
            std::cout << buffer[i][j] << '\t';
        std::cout << std::endl;
    }

    int minor = 1;

    std::vector<std::vector<int>> arr2(arr.size() - 1, std::vector<int>(arr.size() - 1));
    for (uint i = 1; i < arr.size(); i++)
    {
        for (uint j = 1; j < arr.size(); j++)
        {
            arr2[i - 1][j - 1] = buffer[i][j];
        }
    }

    for (uint i = 0; i < arr.size() - 1; i++)
        minor += arr2[0][i] * pow(-1, (1 + i + 1)) * findMinor(arr2, 0, i);


    if (arr.size() != 2)
        minor -= 1;
    std::cout << std::endl << "\nAmount of ost trees by Kirhgof = " << abs(minor) << std::endl << std::endl;
}

void Graph::prufer_encoding(std::vector<std::set<int>>* ostov, std::vector<int>& pruferCode)
{
    if (ostov == nullptr)
    {
        std::cout << std::endl;
        std::cout << "\nError! Get an ostov frist!\n";
        std::cout << std::endl;
        return;
    }
    if (ostov->size() == 2)
    {
        std::cout << std::endl;
        std::cout << "\nPrufer code::" << std::endl;
        std::cout << std::endl;
        std::cout << 0 << " --> " << 1 << std::endl;
        return;
    }
    if (pruferCode.size() < (ostov->size() - 2))
    {
        std::cout << std::endl;
        std::cout << "\nError! Execute Prufer's coding!\n";
        std::cout << std::endl;
        return;
    }
    std::cout << std::endl;
    std::cout << "\nPrufer's decode:" << std::endl;
    std::cout << std::endl;
    std::deque<int> v;
    bool b = false;
    for (uint i = 0; i < ostov->size(); i++)
        v.push_back(i);
    int index = 0;
    while (v.size() != 2)
    {
        bool b = false;
        for (uint i = 0; i < pruferCode.size(); i++)
            if (pruferCode.at(i) == v.at(index))
                b = true;
        if (b)
        {
            index++;
            b = false;
        }
        else
        {
            auto iter = v.begin() + index;
            std::cout << v.at(index)<< " --> " << pruferCode.at(0) << std::endl;
            v.erase(iter);
            pruferCode.erase(pruferCode.begin());
            index = 0;
            b = false;
        }
    }
    std::cout << v.at(0) << " --> " << v.at(1) << std::endl;
}
void init_with_null(std::vector<std::vector<int>>&matr){
    for(uint i = 0; i<matr.size();i++){
        for(uint j = 0; j<matr.size();j++){
            if(matr[i][j]==INF)
                matr[i][j]=0;
        }
    }
}
void init_with_INF(std::vector<std::vector<int>>&matr){
        for(uint i = 0; i<matr.size();i++){
            for(uint j = 0; j<matr.size();j++){
                if(matr[i][j]==0)
                    matr[i][j]=INF;
            }
        }
}
int euler(std::vector<std::vector<int>> gr) {
    int n = gr.size();
    std::vector<int> degree;
    for (int i = 0; i < n; i++) {
        int sst = 0;
        for (int j = 0; j < n; j++) {
            if (gr[i][j] != 0)
                sst++;
        }

        degree.push_back(sst);
    }

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (degree[i] == 0) {
            count = 1;
            deg.clear();
            for (int i = 0; i < gr.size(); i++)
                deg.push_back(i);
            break;
        }


        if (degree[i] % 2 != 0) {
            count++;
            deg.push_back(i);
        }
    }

    if (count > 0)
        return 0;
    int min = 100; int ind = 0;
    for (int i = 0; i < n; i++) {
        if (min > degree[i]) {
            min = degree[i];
            ind = i;
        }
    }

    std::vector<int> res;
    std::stack<int> s;
    s.push(ind);

    while (!s.empty()) {
        int i = s.top();

        if (degree[i] == 0) {
            s.pop();
            res.push_back(i);
        }

        else {

            for (int j = 0; j < n; j++) {
                if (gr[i][j] != 0) {
                    gr[i][j] = 0;
                    gr[j][i] = 0;
                    degree[i] -= 1;
                    degree[j] -= 1;
                    s.push(j);
                    break;
                }
            }
        }
    }
    if (res.size() != 0) {

        std::cout << std::endl << "Euler's cycle: ";

        for (size_t i = res.size() - 1; i != 0; i--)

            std::cout << res[i] << "-";

        std::cout << res[0];
    }
    std::cout << std::endl<< std::endl;
    return res.size();
}
void euler_graph_true(std::vector<std::vector<int>> EulerGr)
{
    int versh = EulerGr.size();
    if (versh == 2) {
        std::cout << std::endl;
        std::cout << "\nTwo vertex, Graph can't be Euler's!" << std::endl << std::endl;
        return;
    }


    bool flag = 0;

    if (!euler(EulerGr)){
        std::cout << std::endl << "\nGraph is not Euler's!\n" << std::endl;
    }
    else std::cout << std::endl << "Graph is Euler's!" << std::endl << std::endl;
}
void is_gamilton_true(std::vector<std::vector<int>>& GamGr,
              std::vector<std::pair<int, int>>& path)
{

    if (GamGr.size() == 2) {

        std::cout << std::endl << "\nLess than 3 vertexes. Gamilton's cycle can't exist" << std::endl << std::endl;

        return;
    }

    if (gamilton(GamGr, path, 1))
    {
        std::cout << std::endl;
        std::cout << "Graph is Gamilton's!\n";
        std::cout << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Graph is not Gamilton's!\n";
        std::cout << std::endl;
    }
}
bool gamilton(std::vector<std::vector<int>>& GamGr, std::vector<std::pair<int, int>>& path,
          bool print) {

    int versh = GamGr.size();
    int ok = 0;
    if (versh == 3) {
        if (GamGr[0][2] != INF) {
            std::cout << std::endl << "Gamilton's cycle:\n0 - 1 - 2 - 0" << std::endl << std::endl;
            return true;
        }
        else return false;
    }
    path = std::vector<std::pair<int, int>>(GamGr.size());//сколько дуг идет из одной вершины
    for (uint i = 0; i < GamGr.size(); i++)
    {
        path[i].first = i;
        for (int j = 0; j < GamGr.size(); j++)
        {
            if (GamGr[i][j] == 1)
            {
                ok++;
            }

        }
        path[i].second = ok;
        ok = 0;
    }

    for (int i = 0; i < GamGr.size(); i++) {

        if (path[i].second < ((GamGr.size() / 2))) {//если из какой-то вершины нет дуг хотя бы в половину

            return false;//то граф не является гамильтоным
        }
    }
    bool isHamiltonCicle = true;
    std::deque<int> que;
    for (uint i = 0; i < GamGr.size(); i++) {
        que.push_back(i);//добавляем вершины в дек
    }
    do {
        isHamiltonCicle = true;
        //cost = 0;
        if (GamGr[que.at(GamGr.size() - 1)][que.at(0)] > (INF / 2)) {//если не существует пути из последней в первую
            isHamiltonCicle = false;
        }
        else {
            for (int i = 0; i < GamGr.size() - 1; i++) {//проходим по всему деку
                if (GamGr[que.at(i)][que.at(i + 1)] > (INF / 2)) {//если нет пути в соседнюю вершину
                    isHamiltonCicle = false;//то нет цикла
                }
            }
        }
        if (isHamiltonCicle&&print) {//если цикл есть, то выводим инфу
            std::cout << std::endl;
            std::cout << "Gamilton's cycle:" << std::endl << std::endl;
            std::cout << que.at(0);

            for (uint i = 1; i < que.size(); i++)
            {
                std::cout << " ->" << que.at(i);
            }
            std::cout << " -> " << que.at(0);
            std::cout << "\n";
            //cout << "\nВес: " << cost << endl << endl;
            //if (cost < minCost) {
                //res.clear();
                //res.resize(que.size());
                //copy(que.begin(), que.end(), res.begin());
                //minCost = cost;
            //}
            break;
        }
             //перестановка элементов диапазоне [first,last] в лексиграфически большую перестановку
    } while (next_permutation(que.begin(), que.end())&&!isHamiltonCicle);
    return isHamiltonCicle;
}
void is_euler(std::vector<std::vector<int>>& EulerGr) {
    int versh = EulerGr.size();
    int n = versh;

    if (versh == 2) {
        std::cout << std::endl;
        std::cout << "\n2 vertexes in Graph, filling is impossible!"
                << std::endl << std::endl;

        return;
    }

    int eu = euler(EulerGr);//является ли граф эйлеровым

    bool flag = 0;

    while (!eu) {//если нет

        flag = 1;
        std::vector<int> degree1;//вектор степеней вершин
        for (int i = 0; i < n; i++) {

            int sst = 0;

            for (int j = 0; j < n; j++) {

                if (EulerGr[i][j] != 0) sst++;
            }

            degree1.push_back(sst);
        }

        srand(time(NULL));

        bool isChanged = false;

        for (int i = 0; i < deg.size(); i++) {//проходим по всем вариантам, которые сохраняли в функции-проверке

            for (int j = i + 1; j < deg.size(); j++) {//причем только верхний треугольник, тк граф неориентированный

                if (EulerGr[deg[i]][deg[j]] == 0) {//если нет ребра

                    EulerGr[deg[i]][deg[j]] = 1;//добавляем

                    EulerGr[deg[j]][deg[i]] = 1;

                    std::cout << std::endl << "Adding edge: " << deg[i] << "-" << deg[j]
                        << std::endl << std::endl;

                    isChanged = true;//отметили изменение

                    break;
                }

                if (EulerGr[deg[i]][deg[j]] == 1) {//если ребро есть


                    EulerGr[deg[i]][deg[j]] = 0;//удалаем его, обновляем значения

                    EulerGr[deg[j]][deg[i]] = 0;

                    std::cout << std::endl << "Deleting edge: " << deg[i] << "-" << deg[j]
                        << std::endl << std::endl;

                    if (degree1[deg[i]] == 1 && degree1[deg[j]] % 2 != 0 && degree1[deg[j]] != 1)//степень одной вершины равна 1, степень второй нечетная и не равна 1
                    {
                        if (deg[i] != n - 1)//добавляем ребра
                        {
                            EulerGr[deg[i]][n - 1] = 1;
                            EulerGr[n - 1][deg[i]] = 1;
                            std::cout << std::endl;
                            std::cout << "Adding edge: " << deg[i] << "-" << n-1 << std::endl << std::endl;
                        }
                        else
                        {
                            EulerGr[deg[i]][0] = 1;
                            EulerGr[0][deg[i]] = 1;
                            std::cout << std::endl;
                            std::cout << "Adding edge: " << 0 << "-" << deg[i]
                                    << std::endl << std::endl;
                        }
                        if (deg[i] != n - 2)
                        {
                            EulerGr[deg[i]][n - 2] = 1;
                            EulerGr[n - 2][deg[i]] = 1;
                            std::cout << std::endl;
                            std::cout << "Adding edge: " << deg[i] << "-" << n - 2
                      << std::endl << std::endl;
                        }
                        else
                        {
                            EulerGr[deg[i]][0] = 1;
                            EulerGr[0][deg[i]] = 1;
                            std::cout << std::endl;
                            std::cout << "Adding edge: " << 0 << "-" << deg[i] << std::endl << std::endl;
                        }

                    }

                    if (degree1[deg[j]] == 1 && degree1[deg[i]] % 2 != 0 && degree1[deg[i]] != 1)//аналогично предыдущим действиям, только в обратную сторону
                    {
                        if (deg[j] != n - 1 && EulerGr[deg[i]][deg[j]] == 0)
                        {
                            EulerGr[deg[j]][n - 1] = 1;
                            EulerGr[n - 1][deg[i]] = 1;
                            std::cout << std::endl << "Adding edge: "<< deg[j] << "-"
                        << n-1 << std::endl << std::endl;
                        }
                        else
                        {
                            EulerGr[deg[j]][0] = 1;
                            EulerGr[0][deg[j]] = 1;
                            std::cout << std::endl << "Adding edge: " << 0 << "-" << deg[j] << std::endl << std::endl;
                        }
                        if (deg[j] != n - 2 && EulerGr[deg[i]][deg[j]] == 0)
                        {
                            EulerGr[deg[j]][n - 2] = 1;
                            EulerGr[n - 2][deg[j]] = 1;
                            std::cout << std::endl << "Adding edge: " << deg[j] << "-" << n - 2 << std::endl << std::endl;
                        }
                        else
                        {
                            EulerGr[deg[j]][0] = 1;
                            EulerGr[0][deg[j]] = 1;
                            std::cout << std::endl <<"Adding edge: " << 0 << "-" << deg[j] << std::endl << std::endl;
                        }
                    }
                    isChanged = true;//отмечаем изменения
                    break;
                }
            }
            if (isChanged)
                break;
        }

        deg.clear();//очищаем вектор возможных вершин

        eu = euler(EulerGr);//проверяем
    }

    if (flag) {//если меняли граф

        std::cout << std::endl << "Changed matrix: " << std::endl << std::endl;

        for(uint i = 0; i<EulerGr.size();i++){
            for(uint j = 0; j<EulerGr.size();j++){
                std::cout<<EulerGr[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
    std::cout << std::endl;

    deg.clear();
}
void is_gam(std::vector<std::vector<int>>& GamGr, std::vector<std::pair<int, int>>& path) {


    int versh = GamGr.size();
    int n = versh;
    int c = 0;
    bool flagGam = true;
    std::vector<int> v0;
    bool flag = false; //граф содержит гамильтонов цикл
    bool add = false;
    bool first = 1;//сообщение выводится 1 раз
    bool f = true;

    if (n < 3) {
        std::cout << std::endl << "Less than 3 vertexex, can't make Gamilton's graph\n" << std::endl << std::endl;
        return;
    }

    while (flagGam)
    {
        if (gamilton(GamGr, path,1))
        {
            std::cout << std::endl;
            std::cout << "Graph is gamilton" << std::endl;
            std::cout << std::endl;
            flagGam = false;
            flag = true;
            break;
        }
        else
        {
            std::cout << std::endl;
            std::cout << "Need to fill graph to Gamilton"<<std::endl;
            std::cout << std::endl;
            add = false;
            if (n == 3)
            {
                GamGr[0][2] = GamGr[2][0] = 1;
                std::cout << std::endl << "Adding edge: " << 0 << " - " << 2 << std::endl << std::endl;
                f = true;
            }
            else
            while (!flag)
            {

                for (int i = 0; i < n; i++)
                {

                    if (path[i].second < n / 2 && !add)
                    {
                        v0.push_back(path[i].first);
                    }
                }
                for (uint i = 0; i < v0.size(); i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (!add)
                        {
                            if (GamGr[v0[i]][j] == INF && v0[i] != j)
                            {
                                if (v0.size() == 2 && GamGr[v0[i]][v0[i + 1]] == INF)
                                {
                                    GamGr[v0[i]][v0[i + 1]] = 1;
                                    GamGr[v0[i + 1]][v0[i]] = 1;
                                    if (v0[i] + 1 < v0[i + 1] + 1)
                                        std::cout << std::endl << "Adding edge: " << v0[i] << " - " << v0[i + 1] << std::endl << std::endl;
                                    else
                                        std::cout << std::endl << "Adding edge: " << v0[i + 1]<< " - " << v0[i]<< std::endl << std::endl;
                                    add = true;
                                    f = true;
                                }
                                else {
                                    GamGr[v0[i]][j] = 1;
                                    GamGr[j][v0[i]] = 1;
                                    if (v0[i] + 1 < j + 1)
                                        std::cout << std::endl << "Adding edge: " << v0[i] << " - " << j << std::endl << std::endl;
                                    else
                                        std::cout << std::endl << "Adding edge: " << j << " - " << v0[i] << std::endl << std::endl;
                                    add = true;
                                    f = true;
                                }
                            }
                        }
                    }
                }
                flag = gamilton(GamGr, path,0);
                add = false;
                v0.clear();
            }
        }
    }

    if (true)
    {
        std::cout << std::endl;
        std::cout << "Changed matrix:" << std::endl;
        for(uint i = 0; i<GamGr.size();i++){
            for(uint j = 0; j<GamGr.size();j++){
                if(GamGr[i][j]!=INF)
                    std::cout<<1<<" ";
                else
                    std::cout<<"0"<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void TSP(std::vector<std::vector<int>>& GamGr)
{
    std::vector<std::vector<int>> GamGrVes = std::vector<std::vector<int>>(GamGr.size(),
                                           std::vector<int>(GamGr.size(), 0));

    int n = GamGr.size();
    for (int i = 0; i < n; ++i)

    {
        for (int j = i + 1; j < n; j++)

        {
            if (GamGr[i][j] == INF)
            {
                GamGrVes[i][j] = 0;
                GamGrVes[j][i] = 0;
            }
            else
            {
                GamGrVes[i][j] = rand() % 9 + 1;

                GamGrVes[j][i] = rand() % 8 + 1;
            }

        }
    }
    std::cout << std::endl;
    std::cout << "Cost matrix of Gamilton graph:" << std::endl;
    //outArr(GamGrVes);
    for(uint i = 0;i<GamGrVes.size();i++){
        for(uint j = 0; j<GamGrVes.size();j++){
            std::cout<<GamGrVes[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout << std::endl;

    if (n < 3)
    {
        std::cout << std::endl;
        std::cout << "\nLess than 3 vertexes! Impossible to solve commivoyager\n";
        std::cout << std::endl;
        return;
    }
    int cost = 0;
    unsigned
    long long minCost = INF * n;
    std::deque<int> que;
    std::deque<int> res;

    std::ofstream f;
    f.open("Text.txt", std::ofstream::out);

    std::cout << std::endl;
    std::cout << "Print : \n1 - on monitor\n2 - in file\n";
    bool flag;
    int op = 1;
    switch (op)
    {
    case 1:
        flag = false;
        break;
    case 2:
        flag = true;
        break;
    }

    bool isHamiltonCicle = true;
    for (int i = 0; i < n; i++) {
        que.push_back(i);
    }
    do {
        isHamiltonCicle = true;
        cost = 0;
        if (GamGr[que.at(n - 1)][que.at(0)] > (INF / 2)) {
            isHamiltonCicle = false;
        }
        else {
            for (int i = 0; i < n - 1; i++) {
                if (GamGr[que.at(i)][que.at(i + 1)] > (INF / 2)) {
                    isHamiltonCicle = false;
                }
                else {
                    cost += GamGrVes[que.at(i)][que.at(i + 1)];
                }
            }
        }
        if (isHamiltonCicle) {

            cost += GamGrVes[que.at(n - 1)][que.at(0)];
            if (flag)
            {
                std::cout << std::endl;
                f << "Gamilton's cycle:" << std::endl;
                f << que.at(0);
                for (uint i = 1; i < que.size(); i++)
                {
                    f << " -> " << que.at(i);
                }
                f << " -> " << que.at(0);
                f << "\n";
                f << std::endl << "\nWeight: " << cost << std::endl << std::endl;
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Gamilton cycle:" << std::endl;
                std::cout << que.at(0);
                for (uint i = 1; i < que.size(); i++)
                {
                    std::cout << " -> " << que.at(i);
                }
                std::cout << " -> " << que.at(0);
                std::cout << "\n";
                std::cout << std::endl << "\nWeight: " << cost << std::endl << std::endl;
            }
            if (cost < minCost) {
                res.clear();
                res.resize(que.size());
                copy(que.begin(), que.end(), res.begin());
                minCost = cost;
            }
        }

    } while (next_permutation(que.begin(), que.end()));

    //f.close();

    std::cout << std::endl << "Minimal Gamilton cycle: " << std::endl;
    std::cout << res.at(0);
    for (uint i = 1; i < res.size(); i++)
    {
        std::cout << " -> " << res.at(i);
    }
    std::cout << " -> " << res.at(0);
    std::cout << std::endl << "\nWeight: " << minCost << std::endl << std::endl;
}


