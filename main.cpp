#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>


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

// read txt
void readInput(string text, vector<transition> &grammers, vector<edge> &edges, int &N){
    fstream my_file;
    my_file.open(text, ios::in);
    if (!my_file) {
        cout << "No such file";
        return;
    }
    else {
        char ch;

        struct transition t = {};
        struct edge e = {};

        char status = ' ';
        bool open = 0;
        char depth = '0'; // 0--> first item | 1--> second item | 2--> third item

        while (1) {
            my_file >> ch;
            if (my_file.eof()) break;

            if(ch == ',' || ch == ' ') continue;

            if(ch == '{'){
                open = 1;
                continue;
            }
            if(ch == '}'){
                open = 0;
                if(status=='1'){
                    grammers.push_back(t);
                }else if(status=='2'){
                    edges.push_back(e);
                }
                continue;
            }

            if(ch == '#'){
                status = '#';
                continue;
            }

            // status : #-> not initialize | 1-> cfg | 2->graph | 3-> graph size
            if(status == '#' && (ch == '1' || ch == '2' || ch == '3')){
                status = ch;
                continue;
            }
            if(status == '3'){
                N = ch - '0';
                continue;
            }

            // character
            if(open){
                if(status == '1'){//cfg
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
                }else if(status == '2'){//graph
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
            //cout << ch << endl;
        }

    }
    my_file.close();
}


int main() {
    string input_file = "../input.txt";

    vector<transition> grammers = {};
    vector<edge> edges= {};
    int graph_size;

    readInput(input_file,grammers,edges,graph_size);

    //GRAMMER
    Grammer grammer(grammers);

    // GRAPH
    Graph graph(edges, graph_size);

    cout << "INPUT:"<<endl;
    printGrammer(grammer);
    printGraph(graph);

    findCFGinGraph(graph,grammer);
    cout<<"-----------------"<<endl;
    cout << "OUTPUT:"<<endl;

    printGraph(graph);

    return 0;
}

