#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
    char Nombre[50];
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
    long Array_Index[N], NumeroRandom, Array_Random[NumPersonas];
    for(long i=0;i<NumPersonas;++i){
        Array_Random[i]=0; // Inicializa
    }
    srand((unsigned int)time(NULL));
    printf("%d\n",(NumPersonas/RAND_MAX));
    for(int i=N; i!=0;--i){
        NumeroRandom = (NumPersonas/RAND_MAX)*(rand() % (NumPersonas+1)) + rand()%(NumPersonas-(NumPersonas%RAND_MAX)+1);
        while(Array_Random[NumeroRandom]==0){
            Array_Random[NumeroRandom]=-1;
        }
    }
    int n=0;
    for(long i=0;i<NumPersonas;++i){
        if(Array_Random[i]==-1){
            Array_Index[n]=i;
            n++;
        }
    }
    for(int i=0;i<N;++i){
        printf("%ld\n",Array_Index[i]);
    }
    return 0;
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
