#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int compareValues(Type, Type);
void printValue(Type);

typedef struct{
	char Texto1[50];
	char Date[5];
	char Texto2[200];
}Vertex;

typedef struct{
	Vertex actor;
	Vertex pelicula;
}Edge;

int main(){
	FILE *v_person = fopen("vertex_person.csv","r");
	FILE *v_movies = fopen("vertex_movies.csv","r");
	FILE *edges = fopen("edges_PersonMovies.csv","r");
	if(!v_person || !v_movies || !edges) {
		printf("Failed opening files...\n");
		return 0;
	}else{
		Graph g_Person = graph_create(compareValues, printValue);
		Graph g_Movies = graph_create(compareValues, printValue);
		Vertex person[105];
		Vertex movies[38];
		Edge edgeData[173];
		//Lectura y guardado de Person
		char aux;
		short i=0;
		do{
			fscanf(v_person, "%[^,]", person[i].Texto1);
			fseek(v_person,sizeof(char),SEEK_CUR);
			fscanf(v_person, "%[^,]", person[i].Date);
			fseek(v_person,sizeof(char),SEEK_CUR);
			fscanf(v_person, "%[^\n]", person[i].Texto2);
			i++;
		}while((aux=fgetc(v_person))!=EOF);
		i=0;

		do{
			fscanf(v_movies, "%[^,]", movies[i].Texto1);
			fseek(v_movies,sizeof(char),SEEK_CUR);
			fscanf(v_movies, "%[^,]", movies[i].Date);
			fseek(v_movies,sizeof(char),SEEK_CUR);
			fscanf(v_movies, "%[^\n]", movies[i].Texto2);
			i++;
		}while((aux=fgetc(v_movies))!=EOF);

		char temp[50]="";
			fgets(temp,50,edges);
			i=0;
			do{
				fscanf(edges, "%[^,]", edgeData[i].actor.Texto1);
				fseek(edges,sizeof(char),SEEK_CUR);
				fscanf(edges, "%[^\n]", edgeData[i].pelicula.Texto1);

				i++;
			}while((aux=getc(edges))!=EOF);

			g_Person=graph_create(compareValues, printValue);

			for(int i=0;i<102;i++){
				if(!graph_addVertex(g_Person,&person[i]))
					printf("Error %d\n",i);
			}
			for(int i=0;i<38;i++){
				if(!graph_addVertex(g_Person,&movies[i]))
					printf("Error %d\n",i);
			}
			/*for(int i=0;i<172;i++){
				printf("%s\t%s\n",edgeData[i].actor.Texto1,edgeData[i].pelicula.Texto1);
			}*/


			for(int i=0;i<172;i++){
				if(!graph_addEdge(g_Person,&edgeData[i].actor,&edgeData[i].pelicula))
					printf("Error %d\n",i);
			}
			if(graph_hasEdge(g_Person,&person[61],&movies[16]))
				printf("bien\n");
			graph_print(g_Person);
			graph_destroy(g_Person);

			fclose(v_person);
			fclose(v_movies);
			fclose(edges);
			printf("success");
	}
	return 0;
}

int compareValues(Type data1, Type data2){
	return strcmp((char*)data1, (char*)data2);
}

void printValue(Type data){
	Vertex imprimir=*(Vertex*)data;
	printf(" %s  %s  %s \n", imprimir.Texto1, imprimir.Date, imprimir.Texto2);
}
