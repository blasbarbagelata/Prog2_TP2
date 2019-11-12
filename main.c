#include <stdio.h>
#include <stdlib.h>

int Pertenece (char palabra[],char letra){
    int contador=0;
    for(int i=0; palabra[i]!= '\0';++i){
        if (palabra[i]==letra){
                contador=1;
        }
    }
    return contador;
}
int main()
{
    int bandera;
    char palabra[25];
    char Caracter='a';
    printf("Ingrese una palabra: ");
    scanf("%s",palabra);
    printf("ingrese un caracter: ");
    scanf("%c",&Caracter);
    bandera = Pertenece(palabra,Caracter);
    printf("%d\n",Pertenece(palabra,Caracter));
    printf("%d\n",bandera);
    return 0;
}
