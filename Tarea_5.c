#include <stdio.h>
#include <stdlib.h>
#include "Tarea_5.h"

struct strVertex{
	unsigned id;
	Type Data;
	List Vertex;
};

typedef struct strVertex *Vertex;

struct strGraph{
	Vertex *vertex;	//Arreglo de vÃ©rtices, nÃºmero de nodos en el grafo
	unsigned Size; //nÃºmero de aristas
	unsigned Order; //nÃºmero de vÃ©rtices
	unsigned limit;//Control de arreglo de vertex
	Print myPrint; //Funciones asociadas
	CMP myCmp;
};

unsigned int indice=1;

Graph graph_create(CMP comparator, Print print){
	Graph new = (Graph)malloc(sizeof(struct strGraph));
	if(!new) return NULL;
	new->myCmp = comparator;
	new->myPrint = print;
	new->Order = 0;
	new->Size = 0;
	new->vertex = NULL;
	new->vertex = (Vertex*)malloc(sizeof(Vertex));
	return new;
}

void graph_destroy(Graph g){
	Vertex temp;
	unsigned start = 0;
	if(g){
		while(start < g->Order){
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

Vertex newVertex(Type data, unsigned int* contador){
	Vertex new=(Vertex)malloc(sizeof(Vertex));
	if(new!=NULL){
		new->Vertex=list_create();
		new->id=*contador;
		new->Data=data;
	}
	(*contador)++;
	return new;
}

boolean graph_addVertex(Graph g, Type data){
	if(g->Order==0){
		g->vertex[g->Order]=newVertex(data, &indice);
		g->Order++;
		return true;
	} else {
		g->vertex = (Vertex*)realloc(g->vertex,sizeof(Vertex)*(g->Order+1));
		g->vertex[g->Order]=newVertex(data, &indice);
		g->Order++;
		return true;
	}
	return false;
}
boolean graph_addEdge(Graph g, Type source, Type sink){
	if(!g)
		return false;
	int contador=0, destino=0;
	while(g->myCmp(g->vertex[contador]->Data, source) != 0&&contador<g->Order){
		contador++;
	}
	while(g->myCmp(g->vertex[destino]->Data, sink)!=0&&destino<g->Order){
		destino++;
	}
	if(contador==g->Order||destino==g->Order)
		return false;
	if(list_add(g->vertex[contador]->Vertex, g->vertex[destino])){
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
	unsigned verti=0;
	if(g){
		while(g->myCmp(g->vertex[verti]->Data, source)!=0&&verti<g->Order){
			verti++;
		}
		if(verti==g->Order)
			return -1;
		else
			return list_size(g->vertex[verti]->Vertex);
	}
	return -1;
}

boolean graph_hasEdge(Graph g, Type source, Type sink){
	int inicio=0, destino=0;
	while(g->myCmp(g->vertex[inicio]->Data, source)!=0&&inicio<g->Order)
		inicio++;
	if(inicio!=g->Order){
		while(g->myCmp(list_get(g->vertex[inicio]->Vertex, destino), sink)!=0&&destino<list_size(g->vertex[inicio]->Vertex)){
			destino++;
		}
		if(destino<list_size(g->vertex[inicio]->Vertex)){
			return true;
		}
	}
	return false;
}

void graph_print(Graph g){
	Vertex temp;
	unsigned id = 0;
	if(g){
		while(id < g->Order){
			temp = g->vertex[id];
			if(temp)g->myPrint(temp->Data);
			id++;
		}
	}
}
