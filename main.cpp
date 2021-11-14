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

vector<string> removeSpace(string str)
{
    //cout << str;
    vector<string> words;
    string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            //cout << word << endl;
            words.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    words.push_back(word);
    //cout << word << endl;
    return words;

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
        bool first_line = true;
        while (!my_file.eof()) {
            string line;
            getline(my_file, line, '\n');
            //cout << line;

            vector<string> words = removeSpace(line);

            struct transition t = {};
            struct edge e = {};

            if (type == '1') {
                t.src = words[0][0]; //just for 1 char
                t.var1 = words[1][0];
                t.var2 = words[2][0];

                grammars.push_back(t);

                continue;
            } else {// type == '2'
                if (first_line) {
                    cout << words[0].length() << "!";

                    int count = 1;
                    N = 0;
                    for (int i = words[0].length() - 1; i >= 0; i--) {
                        N += count * (words[0][i] - '0');
                        count *= 10;
                    }
                } else {

                    int count_src = 1;
                    e.src = 0;
                    for (int i = words[0].length() - 1; i >= 0; i--) {
                        e.src += count_src * (words[0][i] - '0');
                        count_src *= 10;
                    }

                    int count_dest = 1;
                    e.dest = 0;
                    for (int i = words[1].length() - 1; i >= 0; i--) {
                        e.dest += count_dest * (words[1][i] - '0');
                        count_dest *= 10;
                    }

                    e.weight = words[2][0];


                    edges.push_back(e);
                }

                first_line = false;

            }


        }
    }
    my_file.close();
}





int main() {
    string graph_file = "../graph2.txt";
    string cfl_file = "../grammar.txt";

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

