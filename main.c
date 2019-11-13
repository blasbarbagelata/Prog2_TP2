#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
    char Nombre[50];
    char Localidad[30];
    int Edad;
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
    int Array_Index[N], NumeroRandom, Array_Random[NumPersonas];
    for(int i=0;i<NumPersonas;++i){
        Array_Random[i]=0; // Inicializa
    }
    srand((unsigned int)time(NULL));
    for(int i=N; i!=0;--i){
        NumeroRandom = rand() % (NumPersonas+1);
        while(Array_Random[NumeroRandom]!=0){
            NumeroRandom = rand() % (NumPersonas+1);
        }
        Array_Random[NumeroRandom]=-1;
    }
    int n=0;
    for(int i=0;i<NumPersonas;++i){
        if(Array_Random[i]==-1){
            Array_Index[n]=i;
            n++;
        }
    }
    for(int i=0;i<N;++i){
        printf("%d\n",Array_Index[i]);
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
    while ((Cantidad>Lineas)|(Cantidad<0)){
        printf("Por favor ingrese una cantidad menor a %d y mayor a 0: ",Lineas);
        scanf("%d",&Cantidad);
    }
    FuncionSubPrincipal(Cantidad,Lineas);

    return 0;
}
