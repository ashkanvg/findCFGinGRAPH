# Find CFG in GRAPH
It is about a graph problem, called CFL-reachability. 
Given an edge-labeled graph, whether there is a path from a vertex to another vertex along which the labels form a string that is part of a context-free language (CFL).
The basic idea is simple: consider two adjacent edges in a graph labeled with "A" and "B", if there is a grammar rule C --> AB, then add a new edge labeled with "C".


# input 
There is a "graph.txt" file that GRAPH should enter there.
input file structure:
"3# {1,2,A}{0,1,B}"
which the number before "#" is about the size of the graph, everything after "#" is about the graph edges.
And also there is a "cfl.txt" file that CFL should enter there.
input file structure:
"{A,B,C}{A,B,C}"
which every {} is a grammar.

# Time Complexity
The worst case of this code is (|E|^2)|G||T|. 
In this case, |G| is the count of grammars in our CFL, |E| is the count of edges of the graph, and |T| is the count of repeating algorithm to achieve the final graph.
