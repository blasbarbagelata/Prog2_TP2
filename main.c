#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*CantidadDeLineas: File -> Int
recibe un archivo, lee caracter por caracter, contando los saltos de linea.
devuelve la cantidad de lineas que tenga ese archivo en forma de entero*/
int CantidadDeLineas(FILE *Archivo){
    int Lineas = 0;
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
/* Normalizar: char[], int
recibe una cadena de caracteres y su largo,
devuelve la misma cadena sin espacios de mas*/
void Normalizar(char array[],int largo){
    int i=0;
    while (array[i]!=' '||array[i+1]!=' '){
      i++;
    }
    array[i]='\0' ;
    }
/* CrearArregloLocalidades: FILE* , int , char**
recibe un archivo de localidades, la cantidad de lineas del archivo
y un arreglo de punteros char y le asigna a cada puntero char una localidad
del archivo, la cual esta en una posicion que representa su codigo-1 en el archivo*/
void CrearArregloLocalidades(FILE *Archivo,int Tamano,char *Localidades[]){
    int largo=100;
    char basura[10], buffer[largo];
    for (int i=0; i < Tamano;++i){
        fscanf(Archivo,"%[^,],",basura);
        fscanf(Archivo,"%[^\n]",buffer);
        Normalizar(buffer,largo);
        Localidades[i] = malloc(sizeof(char)*60);
        strcpy(Localidades[i], buffer);
    }
}
/*funcionlectura: int, int[]
recibe la cantidad de personas solicitadas por teclado (N)
y un arreglo de N numeros arrayRandom.
crea un archivo en el cual escribe la cantidad de personas solicitadas, elegidas
de forma aleatoria del siguiente modo:
Nombre, Apellido, localidad, edad, genero, interes*/
void funcionlectura(int CantPersonas, int arrayRandom[]){
    FILE *Archivopersonas,*Archivolocalidades,*ArchivoSalida;
    char buffer[100],Genero[2]={'M','F'},Interes[4]={'F','M','A','N'};
    char Nombre[50],Apellido[50];
    int Linea=0,Codigo,Sexo,Sexualidad,Edad,tamano;
    Archivolocalidades =fopen("codigoLocalidades.txt","r");
    tamano = CantidadDeLineas(Archivolocalidades);
    char *ArregloLocalidades[tamano];
    rewind(Archivolocalidades);
    CrearArregloLocalidades(Archivolocalidades,tamano,ArregloLocalidades);
    fclose(Archivolocalidades);
    Archivopersonas =fopen("personas.txt","r");
    ArchivoSalida =fopen("ArchivoSalida.txt","w");
    for(int i=0; i< CantPersonas; i++){
        while(Linea<arrayRandom[i]){
            fgets(buffer,100,Archivopersonas);
            Linea++;
        }
        fscanf(Archivopersonas,"%[^,],%[^,],%d,%d,%d,%d",Nombre,Apellido,&Codigo,&Edad,&Sexo,&Sexualidad);
        fprintf(ArchivoSalida,"%s, %s, %s, %d, %c, %c\n",Nombre,Apellido,ArregloLocalidades[Codigo-1],Edad,Genero[Sexo-1],Interes[Sexualidad-1]);
    }
    fclose(Archivopersonas);
    fclose(ArchivoSalida);
}
/* CrearArregloRandom: int, int
recibe la cantidad(N) de personas solicitadas y la cantidad total de personas
que hay en el archivo.
Crea un arreglo con N numeros random de 0 a TotalPersonas sin repetir */
void CrearArregloRandom(int CantPersonas,int TotalPersonas){
    int *Array_Index=(int*)malloc(sizeof(int)*CantPersonas);
    int *Array_Random=(int*)malloc(sizeof(int)*TotalPersonas);
    int NumeroRandom;
    for(int i=0;i<TotalPersonas;++i){
        Array_Random[i]=0;
    }
    srand((unsigned int)time(NULL));
    for(int i=CantPersonas; i!=0;--i){
        NumeroRandom = rand() % (TotalPersonas);
        while(Array_Random[NumeroRandom]!=0){
            NumeroRandom = rand() % (TotalPersonas);
        }
        Array_Random[NumeroRandom]=-1;
    }
    int idx=0;
    for(int i=0;i<TotalPersonas;++i){
        if(Array_Random[i]==-1){
            Array_Index[idx]=i;
            idx++;
        }
    }
    funcionlectura(CantPersonas,Array_Index);
}
int main (){
    int Cantidad=0,Lineas=0;
    FILE *Entrada;
    Entrada =fopen("personas.txt","r");
    Lineas = CantidadDeLineas(Entrada);
    fclose(Entrada);
    printf("Ingrese la cantidad de personas: ");
    scanf("%d",&Cantidad);
    while ((Cantidad>Lineas)||(Cantidad<0)){
        printf("Por favor ingrese una cantidad menor a %d y mayor a 0: ",Lineas);
        scanf("%d",&Cantidad);
    }
    CrearArregloRandom(Cantidad,Lineas);
    return 0;
}
