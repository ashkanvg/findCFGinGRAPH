#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;


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

// GRAMMAR
struct transition
{
    char src, var1, var2;
};
class Grammar {
public:
    // we save grammar from right to left in order to search by key in O(logN) in searching method
    // AB --> C
    // AB --> B
    // AC --> B
    map<string,vector<char>> grammar;

    //Grammar Constructor
    Grammar(vector<transition> const &transitions){
        for (auto &transition: transitions) {
            grammar[{transition.var1, transition.var2}].push_back(transition.src);
        }
    }
};
void printGrammar(Grammar const &cfg)
{
    for (const auto &item : cfg.grammar) {
        for(char c : item.second){
            cout<< c << " --> "<< item.first<<endl;
        }
    }
}



// check
void findCFGinGraph(Graph &graph,Grammar &cfg){
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

                    for(char g : cfg.grammar[result]){
                        struct edge e = {i,v2.first,g};
                        if(graph.add_edge(e))
                            count_new_edges++;
                    }

                }
            }
        }
    }

}

// read input from txt
// type = 1 --> CFL type = 2 --> Graph
void readInput(string text, vector<transition> &grammars, vector<edge> &edges, int &N, char type){
    fstream my_file;
    my_file.open(text, ios::in);
    if (!my_file) {
        cout << "No such file";
        return;
    }
    else {
        char ch;
        bool open = false;

        struct transition t;
        struct edge e;

        int count = 0;
        if(type=='2'){
            N = 0;
        }
        char depth = '0'; // 0--> first item | 1--> second item | 2--> third item
        while (1) {
            my_file >> ch;
            if(my_file.eof()) break;


            // get size of graph
            if(count != -1 && type == '2'){
                if(ch != '#'){
                    N += (pow(10,count))*(ch - '0');
                    count++;
                }else{
                    count = -1;
                }
                continue;
            }

            if(ch == ',' || ch == ' ') continue;

            if(ch == '{'){
                open = true;
                continue;
            }
            if(ch == '}'){
                open = false;
                if(type=='1'){
                    grammars.push_back(t);
                }else if(type=='2'){
                    edges.push_back(e);
                }
                continue;
            }

            /*
            if(ch == '#'){
                status = '#';
                continue;
            }
            */

            // status : #-> not initialize | 1-> cfg | 2->graph | 3-> graph size
            /*if(status == '#' && (ch == '1' || ch == '2' || ch == '3')){
                status = ch;
                continue;
            }
            if(status == '3'){
                N = ch - '0';
                continue;
            }*/

            // character
            if(open){
                if(type == '1'){//cfg
                    switch (depth){
                        case '0':
                            t.src = ch;
                            depth = '1';
                            break;
                        case '1':
                            t.var1 = ch;
                            depth = '2';
                            break;
                        case '2':
                            t.var2 = ch;
                            depth = '0';
                            break;
                    }
                }else if(type == '2'){//graph
                    switch (depth){
                        case '0':
                            e.src = ch - '0';
                            depth = '1';
                            break;
                        case '1':
                            e.dest = ch - '0';
                            depth = '2';
                            break;
                        case '2':
                            e.weight = ch;
                            depth = '0';
                            break;
                    }
                }
            }
            //continue;
            //cout << ch << endl;
        }

    }
    my_file.close();
}


int main() {
    string graph_file = "../graph.txt";
    string cfl_file = "../cfl.txt";

    vector<transition> grammars = {};
    vector<edge> edges= {};
    int graph_size;

    readInput(cfl_file,grammars,edges,graph_size,'1');
    readInput(graph_file,grammars,edges,graph_size,'2');

    // GRAMMAR
    Grammar grammar(grammars);

    // GRAPH
    Graph graph(edges, graph_size);

    cout << "INPUT:"<<endl;
    printGrammar(grammar);
    printGraph(graph);

    findCFGinGraph(graph,grammar);
    cout<<"-----------------"<<endl;
    cout << "OUTPUT:"<<endl;

    printGraph(graph);

    return 0;
}

