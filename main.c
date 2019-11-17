#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*El programa comienza solicitando que se ingrese por teclado una cantidad de personas (N), continua pidiendo hasta
que la cantidad de personas ingresadas sea mayor a 0 y menor o igual al total de personas en el archivo de entrada.

Luego, genera N numeros aleatorios sin repeir que representaran el numero de la linea de la persona a leer,
 y luego escribir en el archivo de salida, y los almacena en un arreglo.

Despues, arma un arreglo de strings con las localidades del archivo codigoLocalidades donde la posicion 
en la que se almacenan representa el codigo-1 de la respectiva localidad.

Finalmente, comienza a leer las personas que correspenden segun el numero aleatorio, almacena sus
datos en variables temporales y luego los escribe en el archivo de salida como corresponde.*/

/*CantidadDeLineas: File* -> Int
Recibe un archivo, devuelve la cantidad de lineas que posee el archivo*/
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

/* Normalizar: char[]
Recibe una cadena de caracteres,
modifica la cadena para que quede sin espacios de mas*/
void Normalizar(char array[]){
    int i=0;
    while (array[i]!='\0'){
      i++;
    }
    while(array[i]!=' '){
      i--;
    }
    while(array[i]==' '){
      i--;
    }
    array[i+1]='\0';
}

/* CrearArrayLocalidades: FILE* , int , char**
Recibe un archivo de localidades, la cantidad de lineas del archivo
y un arreglo de punteros char. 
Le asigna a cada puntero char una localidad del archivo, 
la posicion en el arreglo representa el codigo-1 de la localidad*/
void CrearArrayLocalidades(FILE *Archivo,int Tamano,char *Localidades[]){
    int largo=100;
    char basura[10], buffer[largo];
    for (int i=0; i < Tamano;++i){
        fscanf(Archivo,"%[^,],",basura);
        fscanf(Archivo,"%[^\n]",buffer);
        Normalizar(buffer);
        Localidades[i] = malloc(sizeof(char)*60);
        strcpy(Localidades[i], buffer);
    }
}

/*Lectura_Escritura: int, int[]
Recibe la cantidad de personas solicitadas por teclado (N)
y un arreglo de N numeros aleatorios.
Escribe sobre un archivo los datos de las personas que se encuentran en las lineas 
correspondientes a los numeros aleatorios del arreglo del siguiente modo:
Nombre, Apellido, Localidad, Edad, Genero, Interes */
void Lectura_Escritura(int CantPersonas, int arrayRandom[]){
    FILE *Archivopersonas,*Archivolocalidades,*ArchivoSalida;
    char buffer[100],Genero[2]={'M','F'},Interes[4]={'F','M','A','N'};
    char Nombre[50],Apellido[50];
    int Linea=0,Codigo,Sexo,Sexualidad,Edad,tamano;
    Archivolocalidades =fopen("codigoLocalidades.txt","r");
    tamano = CantidadDeLineas(Archivolocalidades);
    char *ArrayLocalidades[tamano];
    rewind(Archivolocalidades);
    CrearArrayLocalidades(Archivolocalidades,tamano,ArrayLocalidades);
    fclose(Archivolocalidades);
    Archivopersonas =fopen("personas.txt","r");
    ArchivoSalida =fopen("ArchivoSalida.txt","w");
    for(int i=0; i< CantPersonas; i++){
        while(Linea<arrayRandom[i]){
            fgets(buffer,100,Archivopersonas);
            Linea++;
        }
        fscanf(Archivopersonas,"%[^,],%[^,],%d,%d,%d,%d",Nombre,Apellido,&Codigo,&Edad,&Sexo,&Sexualidad);
        fprintf(ArchivoSalida,"%s, %s, %s, %d, %c, %c\n",Nombre,Apellido,ArrayLocalidades[Codigo-1],Edad,Genero[Sexo-1],Interes[Sexualidad-1]);
    }
    fclose(Archivopersonas);
    fclose(ArchivoSalida);
}

/* CrearArrayRandom: int, int
Recibe la cantidad(N) de personas solicitadas y la cantidad de personas en el archivo.
Crea un arreglo con N numeros aleatorios de 0 a TotalPersonas-1 sin repetir */
void CrearArrayRandom(int CantPersonas,int TotalPersonas){
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
    Lectura_Escritura(CantPersonas,Array_Index);
}

int main(){
    int Cantidad=0,Lineas=0;
    FILE *Entrada;
    Entrada = fopen("personas.txt","r");
    Lineas = CantidadDeLineas(Entrada);
    fclose(Entrada);
    printf("Ingrese la cantidad de personas: ");
    scanf("%d",&Cantidad);
    while ((Cantidad>Lineas)||(Cantidad<0)){
        printf("Por favor ingrese una cantidad menor a %d y mayor a 0: ",Lineas);
        scanf("%d",&Cantidad);
    }
    CrearArrayRandom(Cantidad,Lineas);
    return 0;
}
