#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
    char Nombre[50];
    char Apellido[50];
    char Localidad[30];
    int edad;
    int Genero;
    int Interes;
} Persona;
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
char CrearArreglo(FILE *Archivo,int Tamano){
    char *P,basura[50];
    char Localidades[Tamano];
    for (int i=0; i < Tamano;++i){
        P = malloc(sizeof(char)*30);
        fscanf(Archivo,"%s[,]",basura);
        fscanf(Archivo,"%s[\n]",P);
        Localidades[i] = *P;

    }
    return Localidades[Tamano]; 
}
int funcionlectura(int arreglin[], int CantPersonas){
    FILE *Archibopersonas,*archibolocalidades;
    char caracter;
    int n=1,Codigo,Sexo,Sexualidad,tamano,Edad;
    char  Genero[2]={"M","F"},Interes[4]={"F","M","A","N"};
    Persona Personas[CantPersonas]; 
    Archibopersonas =fopen("personas.txt","r");
    archibolocalidades =fopen("codigoLocalidades.txt","r");
    tamano = CantidadDeLineas(archibolocalidades);
    char ArregloLocalidades[tamano] = CrearArreglo(archibolocalidades,tamano);
    fclose(archibolocalidades);
    caracter=fgetc(Archibopersonas);
    for(int i=0; i< CantPersonas; ++i){
        while(n<arreglin[i]){
            if(caracter == '\n'){
                ++n;
            }
            caracter=fgetc(Archibopersonas);
        }
        fscanf(Archibopersonas,"%s[,]",Personas[i].Nombre);
        fscanf(Archibopersonas,"%s[,]",Personas[i].Apellido);
        fscanf(Archibopersonas,"%d[,]",&Codigo);
        Personas[i].Localidad=ArregloLocalidades[Codigo-1];
        fscanf(Archibopersonas,"%d[,]",&Edad);
        Personas[i].edad=Edad;
        fscanf(Archibopersonas,"%d[,]",&Sexo);
        Personas[i].Genero=Genero[Sexo-1];
        fscanf(Archibopersonas,"%d[,]",&Sexualidad);
        Personas[i].Interes=Interes[Sexualidad-1];
    }
}

void FuncionSubPrincipal(int N,int NumPersonas){
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
    funcionlectura(Array_Index,N);
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
