#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

/*
{1, [2,3]},{}
*/

// GRAPH
struct edge
{
    int src, dest;
    char weight;
};
class Graph{
    public:
        //Vector of Vectors
        int N;
        vector<vector<pair<int,char>>> adjList;

        //Graph Constructor
        Graph(vector<edge> const &edges, int n){
            N = n;
            adjList.resize(N);
            for (auto &edge: edges)
            {
                //insert at the end
                adjList[edge.src].push_back({edge.dest,edge.weight});

            }
        }
        bool add_edge(struct edge e){
            if(e.src>=N || e.dest>=N){
                cout<< "edge is not valid.";
                return false;
            }

            for(auto edge : adjList[e.src]){
                if(edge.first == e.dest && edge.second == e.weight){
                    return false;
                }
            }

            adjList[e.src].push_back({e.dest,e.weight});
            return true;
        }
};
void printGraph(Graph const &graph)
{
    for (int i = 0; i < graph.N; i++)
    {
        // print current vertex number
        cout << i << " --> ";

        // print all neighboring vertices of vertex i
        for (pair<int,char> v : graph.adjList[i])
            cout << "["<< v.first << ","<< v.second  <<"]";
        cout << endl;
    }
}

/*
 1  ->  2  edge weight:  A
 1  ->  3  edge weight:  A
 2  ->  3  edge weight:  B
*/

// A --> (C,B)

// GRAMMER
struct transition
{
    char src, var1, var2;
};
class Grammer {
public:
    // we save grammer from right to left in order to search by key in O(logN) in searching method
    // AB --> C
    // AB --> B
    // AC --> B
    map<string,vector<char>> grammer;

    //Grammer Constructor
    Grammer(vector<transition> const &transitions){
        for (auto &transition: transitions) {
            grammer[{transition.var1, transition.var2}].push_back(transition.src);
        }
    }
};
void printGrammer(Grammer const &cfg)
{
    for (const auto &item : cfg.grammer) {
        for(char c : item.second){
            cout<< c << " --> "<< item.first<<endl;
        }
    }
}



// check
void findCFGinGraph(Graph &graph,Grammer &cfg){
    int count_new_edges = 1;
    while(count_new_edges>0){
        count_new_edges = 0;
        for(int i = 0; i < graph.N; i++){ //each V
            for(int k = graph.adjList[i].size()-1; k>=0 ; k--){
                pair<int,char> v1 = graph.adjList[i][k];

                string result = "";
                result += v1.second;
                for(pair<int,char> v2 : graph.adjList[v1.first]){
                    result = result + v2.second;

                    for(char g : cfg.grammer[result]){
                        struct edge e = {i,v2.first,g};
                        if(graph.add_edge(e))
                            count_new_edges++;
                    }

                }
            }
        }
    }

}


int main() {
    //GRAMMER
    vector<transition> grammers =
            {
                {'C','A','B'},
                {'A','C','B'},
            };
    Grammer grammer(grammers);
    printGrammer(grammer);

    // GRAPH
    vector<edge> edges =
            {
                    {0,1,'A'},
                    {1,2,'B'},
                    {2,3,'B'},
                    {3,0,'C'},
            };
    int N=4;
    Graph graph(edges, N);
    printGraph(graph);

    findCFGinGraph(graph,grammer);
    cout<<"-----------------"<<endl;
    printGraph(graph);


    return 0;
}

