#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct{
    char Nombre[50];
    char Apellido[50];
    char Localidad[60];
    int Edad;
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
void Normalizar(char array[]){
    int i=0;
    while(array[i]!=' '||array[i+1]!=' '){
      i++;
    }
    array[i]='\0';
}
void CrearArreglo(FILE *Archivo,int Tamano,char *Localidades[]){
    char basura[50], buffer[100];
    for (int i=0; i < Tamano;++i){
        fscanf(Archivo,"%[^,]",basura);
        fgetc(Archivo);
        fscanf(Archivo,"%[^\n]",buffer);
        fgetc(Archivo);
        Normalizar(buffer);
        Localidades[i] = malloc(sizeof(char)*60);
        strcpy(Localidades[i], buffer);
    }
}


int funcionlectura(int arreglin[], int CantPersonas){
    FILE *Archibopersonas,*archibolocalidades;
    char buffer[100];
    int n=1,Codigo,Sexo,Sexualidad,tamano,Edad;
    char  Genero[2]={'M','F'},Interes[4]={'F','M','A','N'};
    Persona *Personas = (Persona*)malloc(sizeof(Persona)*CantPersonas);
    Archibopersonas =fopen("personas.txt","r");
    archibolocalidades =fopen("codigoLocalidades.txt","r");
    tamano = CantidadDeLineas(archibolocalidades);
    rewind(archibolocalidades);
    char *ArregloLocalidades[tamano];
    CrearArreglo(archibolocalidades,tamano,ArregloLocalidades);
    fclose(archibolocalidades);
    for(int i=0; i< CantPersonas; ++i){
        while(n<arreglin[i]){
            fgets(buffer,100,Archibopersonas);
            n++;
        }
        fscanf(Archibopersonas,"%[^,]",Personas[i].Nombre);
        fgetc(Archibopersonas);
        fscanf(Archibopersonas,"%[^,]",Personas[i].Apellido);
        fgetc(Archibopersonas);
        fscanf(Archibopersonas,"%d",&Codigo);
        strcpy(Personas[i].Localidad,ArregloLocalidades[Codigo-1]);
        fgetc(Archibopersonas);
        fscanf(Archibopersonas,"%d",&Edad);
        Personas[i].Edad=Edad;
        fgetc(Archibopersonas);
        fscanf(Archibopersonas,"%d",&Sexo);
        Personas[i].Genero=Genero[Sexo-1];
        fgetc(Archibopersonas);
        fscanf(Archibopersonas,"%d",&Sexualidad);
        Personas[i].Interes=Interes[Sexualidad-1];
    }

    for(int i=0; i< CantPersonas; ++i){
      printf("%s, %s, %s, %d, %c, %c\n",Personas[i].Nombre,Personas[i].Apellido,Personas[i].Localidad,Personas[i].Edad,Personas[i].Genero,Personas[i].Interes);
    }

    return 0;
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
    while ((Cantidad>Lineas)&&(Cantidad<0)){
        printf("Por favor ingrese una cantidad menor a %d y mayor a 0: ",Lineas);
        scanf("%d",&Cantidad);
    }
    FuncionSubPrincipal(Cantidad,Lineas);

    return 0;
}
