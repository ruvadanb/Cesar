#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	setbuf(stdout,NULL);
	int n,o,h;
	char cadena[100];
	char cadena2[100],espacio[1];
	printf("Escribe el desplazamiento: ");
	scanf("%d",&n);
	gets(espacio);
	printf("Escribe tu cadena: ");
	gets(cadena);

	for(int i=0;cadena[i]!='\0';i++)
	{
		if((cadena[i]>=65)|(cadena[i]<=90))
		{
			if((cadena[i]+n)>90)
			{
				o=(cadena[i]+n)-90;
				cadena2[i]=65+o;
			}
			else
			{
				cadena2[i]=cadena[i]+n;
			}
		}

		if((cadena[i]>=97)|(cadena[i]<=122))
		{
			if((cadena[i]+n)>122)
			{
				h=(cadena[i]+n)-122;
				cadena2[i]=97+h;
			}
			else{
				cadena2[i]=cadena[i]+n;
			}
		}

	}

	printf("Tu cadena cifrada es: ");
		puts(cadena2);

	return 0;
}
