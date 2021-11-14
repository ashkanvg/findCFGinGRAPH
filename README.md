# Find CFG in GRAPH
It is about a graph problem, called CFL-reachability. 
Given an edge-labeled graph, whether there is a path from a vertex to another vertex along which the labels form a string that is part of a context-free language (CFL).
The basic idea is simple: consider two adjacent edges in a graph labeled with "A" and "B", if there is a grammar rule C --> AB, then add a new edge labeled with "C".


## input 
There is a "graph.txt" file that GRAPH should enter there.
The first line of the graph input file is the count of vertexes. And every line after that is about the graph edges. The structure:

```bash
[edge source]  [edge destinction]  [edge weight]
```

And also there is a "grammar.txt" file that CFL should enter there. And every line is a transition in our grammar. Input file structure (for A --> BC): 

```bash
A B C
```

Some sample is available in "other inputs" directory.

## Time Complexity
The worst case of this code is (|E|^2)|G||T|. 
In this case, |G| is the count of grammars in our CFL, |E| is the count of edges of the graph, and |T| is the count of repeating algorithm to achieve the final graph. 
I used a google sheet that recorded results of running a findCFGinGraph method for each input in this [link](https://docs.google.com/spreadsheets/d/1lQdgS_EmGMyyoxc8e744PwCrOkYFLqaa67tuA25KHsg/edit?usp=sharing).
