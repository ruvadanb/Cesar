#ifndef GRAPH_H_
#define GRAPH_H_

typedef enum {false,true} boolean;
typedef void * Type;
typedef struct strGraph *Graph;
typedef void (*Print) (Type);
typedef int (*CMP)(Type, Type);

Graph graph_create(CMP comparator, Print print, Index index);
void graph_destroy(Graph g);
boolean graph_addVertex(Graph g, Type data);
boolean graph_addEdge(Graph g, Type source, Type skin);
unsigned long graph_vertexCount(Graph g);
unsigned long graph_edgeCount(Graph g);
unsigned long graph_outDegree(Graph g, Type source);
boolean graph_hasEdge(Graph g, Type source, Type skin);
void graph_print(Graph g, Print p);

#endif /* GRAPH_H_ */
