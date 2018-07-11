#include <stdio.h>
#include <stdlib.h>
#include "Tarea_5.h"

struct strNode{
	unsigned id;
	Type Data;
	List Vertex;
};

typedef struct strNode *Vertex;

struct strGraph{
	Vertex *vertex;	//Arreglo de vértices, número de nodos en el grafo
	unsigned Size; //número de aristas
	unsigned Order; //número de vértices
	unsigned limit;//Control de arreglo de vertex
	Print myPrint; //Funciones asociadas
	CMP myCmp;
	Index getIndex;
};

Graph graph_create(CMP comparator, Print print, Index index ){
	Graph new = (Graph)malloc(sizeof(struct strGraph));
	if(!new) return NULL;
	new->myCmp = comparator;
	new->myPrint = print;
	new->getIndex = index;
	new->Order = 0;
	new->Size = 0;
	new->limit = 100;
	new->vertex = NULL;
	//new->vertex = (Vertex*)calloc(new->limit,sizeof(Vertex));
	return new;
}

void graph_destroy(Graph g){
	Vertex temp;
	unsigned start = 0;
	if(g){
		while(start < g->limit){
			temp = g->vertex[start];
			if(temp){
				if(temp->Vertex) list_destroy(temp->Vertex);
				free(temp);
			}
			start++;
		}
		free(g);
	}
}

/*void graph_newSize(Graph g){
	if (g){
		unsigned newSize = (g->limit)*1.2, i;
		Vertex *newVertex = (Vertex*)calloc(newSize,sizeof(Vertex));
		for(i = 0; i< g->limit; i++){
			Vertex aux = g->vertex[i];
			if(aux){
				aux->id = g->getIndex(aux->Data, newSize);
				while(newVertex[aux->id]) aux->id++;
				newVertex[aux->id]=aux;
			}
		}
		g->limit=newSize;
		free(g->vertex);
		g->vertex = newVertex;
	}
}*/

boolean graph_addVertex(Graph g, Type data){
	if(!g) return false;
	unsigned id = g->getIndex(data,g->limit);
	if(g->Order == 0){
		g->vertex = (Vertex*)calloc(g->limit,sizeof(Vertex));
	}
	while(g->vertex[id]){
		if(g->myCmp(g->vertex[id]->Data,data)==0) return false;
		id ++ ;
		if(id == g->limit) id -= g->limit;
	}
	Vertex new = (Vertex)malloc(sizeof(struct strNode));
	if(!new) return false;
	new->Data = data;
	new->Vertex = list_create();
	new->id = id;
	g->vertex[id]=new;
	g->Order++;
	return true;
}

boolean graph_addEdge(Graph g, Type source, Type sink){
	if(!g) return false;
	unsigned id;
	id = g->getIndex(source, g->limit);
	while(g->myCmp(g->vertex[id]->Data, source) != 0){
		id++;
		if(id==g->limit)id -= g->limit;
	}
	if(list_add(g->vertex[id]->Vertex, sink)){
		g->Size++;
		return true;
	}
	return false;
}

unsigned long graph_vertexCount(Graph g){
	if(!g) return -1;
	return g->Order;
}

unsigned long graph_edgeCount(Graph g){
	if(!g) return -1;
	return g->Size;
}

unsigned long graph_outDegree(Graph g, Type source){
	Vertex temp;
	unsigned id;
	if(g){
		id = g->getIndex(source, g->limit);
		temp = g->vertex[id];
		while(g->myCmp(source, temp->Data)!=0){
			id++;
			if(id == g->limit) id -= g->limit;
			temp = g->vertex[id];
		}
		return list_size(temp->Vertex);
	}
	return -1;
}

boolean graph_hasEdge(Graph g, Type source, Type sink){
	if(!g)return false;
	unsigned id = g->getIndex(source,g->limit);
	while(g->myCmp(g->vertex[id]->Data, source)!= 0){
		id++;
		if(id == g->limit) id -= g->limit;
	}
	List list_Vertex = g->vertex[id]->Vertex;
	unsigned i = 1;
	Type aux;
	while(i<=list_size(list_Vertex)){
		aux = list_get(list_Vertex,i);
		if(g->myCmp(aux,sink) == 0) return true;
		i++;
	}
	return false;
}

void graph_print(Graph g, Print p){
	Vertex temp;
	unsigned id = 0;
	if(g){
		while(id < g->limit){
			temp = g->vertex[id];
			if(temp)g->myPrint(temp->Data);
			id++;
		}
	}
}
