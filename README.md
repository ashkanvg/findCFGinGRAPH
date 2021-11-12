# Find CFG in GRAPH
It is about a graph problem, called CFL-reachability. 
Given an edge-labeled graph, whether there is a path from a vertex to another vertex along which the labels form a string that is part of a context-free language (CFL).
The basic idea is simple: consider two adjacent edges in a graph labeled with "A" and "B", if there is a grammar rule C --> AB, then add a new edge labeled with "C".


# input 
There is an "input.txt" file that CFG and GRAPH should enter there. 
input file structure:
"#1 {A,B,C}{A,B,C} #2 {1,2,A}{0,1,B} #3 4"
which everything after "#1" is about the CFG, everything after "#2" is about the graph, and the number after "#3" is the size of the graph (count of vertexes). Additionally, the number of vertexes starts from 0 to Size-1, and the CFG is normalized. You can see an input and output sample in "sample.jpg".


# Time Complexity
The worst case of this code is (|E|^2)|G||T|. 
In this case, |G| is the count of grammars in our CFL, |E| is the count of edges of the graph, and |T| is the count of repeating algorithm to achieve the final graph.
