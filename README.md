#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 20

int main()
{
	setbuf(stdout,NULL);
	typedef struct{
		int exp;
		char nombre[max];
		int semestre;
		int edad;
	}alumno;
	char eleccion,name[max];
	int h=0,expediente;
	static alumno alumnos[20],borrar[1];
	alumno *palumnos;
	palumnos=&alumnos;
	while (eleccion!=102)
	{
		printf("         MENU\n");
		printf("Registrar un alumno(a)\n");
		printf("Imprimir datos(b)\n");
		printf("Eliminar alumno(c)\n");
		printf("Buscar alumno(d)\n");
		printf("Salir(f)\n\n");
		printf("Que desea hacer?");
		scanf("%c",&eleccion);

		if(eleccion==97)
		{

			printf("escribe el expediente: ");
			scanf("%d",&palumnos[h].exp);
			printf("Escribe el nombre: ");
			scanf("%s",&palumnos[h].nombre);
			printf("escribe el semestre: ");
			scanf("%d",&palumnos[h].semestre);
			printf("escribe la edad: ");
			scanf("%d",&palumnos[h].edad);
			printf("Se han agregado correctamente\n\n");
		}
		if(eleccion==98)
		{
			for(int i=0;i<20;i++)
			{

				printf("ALUMNO NUMERO: %d\n",i+1);
				printf("Expediente: %d\n",palumnos[i].exp);
				printf("Nombre: %s\n",palumnos[i].nombre);
				printf("Semestre: %d\n",palumnos[i].semestre);
				printf("Edad: %d\n\n",palumnos[i].edad);

			}
		}

		if(eleccion==99)
		{

			printf("Escriba el expediente del alumno que desea borrar: ");
			scanf("%d",&expediente);
			for(int i=0;i<20;i++)
			{
				if(palumnos[i].exp==expediente)
				{
					palumnos[i]=borrar[0];
					printf("El alumno fue eliminado exitsosamente\n");
				}
				else{
					printf("Ese expediente no esta.\n");
				}
			}
		}

		if(eleccion==101)
		{

			printf("Escriba el nombre del alumno que quiere buscar: ");
					scanf("%s",&name);
			for(int i=0;i<20;i++)
			{
				if(palumnos[i].nombre==name)
				{
					printf("El alumno fue encontrado: %s\n",palumnos[i].nombre);

				}
				else{
					printf("Ese alumno no esta.\n");
				}
			}
		}
		h++;
	}


	printf("Gracias  por usar el pregrama");
	return 0;
}
