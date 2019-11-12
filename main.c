#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
    char Nombre[];
    char Localidad[30];
    int Genero;
    int Interes;
} PersonaEntrada;
int CantidadDeLineas(FILE *Archivo){
    long Lineas = 0;
    char caracter;
    caracter= fgetc(Archivo);
    while(caracter!=EOF){
        if(caracter =='\n'){
            Lineas++;
        }
        caracter= fgetc(Archivo);
    }
    return Lineas;
}
int FuncionSubPrincipal(int N,int NumPersonas){
    int NumeroR, Index[NumPersonas]; //Arreglo de numeros random
    for(int i=0;i<NumPersonas;++i){
        Index[i]=0; // Inicializa
    }
    for(int i=N; i!=0;--i){
        NumeroR = rand() % NumPersonas;
        if(N[NumeroR]!=-1)
    }
}
int main (){
    int Cantidad=0,Lineas=0;
    FILE *Entrada;
    printf("Ingrese la cantidad de personas: ");
    scanf("%d",&Cantidad);
    Entrada =fopen("personas.txt","r");
    Lineas = CantidadDeLineas(Entrada);
    fclose(Entrada);
    while (Cantidad>Lineas){
        printf("Por favor ingrese una cantidad menor a %d: ",Lineas);
        scanf("%d",&Cantidad);
    }
    FuncionSubPrincipal(Cantidad,Lineas);

    return 0;
}
