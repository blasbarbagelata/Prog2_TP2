#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
    return Lineas+1;
}
void Normalizar(char array[]){
    int i=0;
    while(array[i]!=' '||array[i+1]!=' '){
      i++;
    }
    array[i]='\0';
}
void CrearArregloLocalidades(FILE *Archivo,int Tamano,char *Localidades[]){
    char basura[50], buffer[100];
    for (int i=0; i < Tamano;++i){
        fscanf(Archivo,"%[^,],",basura);
        fscanf(Archivo,"%[^\n]\n",buffer);
        Normalizar(buffer);
        Localidades[i] = malloc(sizeof(char)*60);
        strcpy(Localidades[i], buffer);
    }
}
void funcionlectura(int CantPersonas, int arrayRandom[]){
    FILE *Archibopersonas,*archibolocalidades,*ArchivoSalida;
    char buffer[100],Genero[2]={'M','F'},Interes[4]={'F','M','A','N'};
    char Nombre[50],Apellido[50];
    int linea=1,Codigo,Sexo,Sexualidad,Edad,tamano;
    archibolocalidades =fopen("codigoLocalidades.txt","r");
    tamano = CantidadDeLineas(archibolocalidades);
    char *ArregloLocalidades[tamano];
    rewind(archibolocalidades);
    CrearArregloLocalidades(archibolocalidades,tamano,ArregloLocalidades);
    fclose(archibolocalidades);
    Archibopersonas =fopen("personas.txt","r");
    ArchivoSalida =fopen("ArchivoSalida.txt","w");
    for(int i=0; i< CantPersonas; i++){
        while(linea<arrayRandom[i]){
            fgets(buffer,100,Archibopersonas);
            linea++;
        }
        fscanf(Archibopersonas,"%[^,],%[^,],",Nombre,Apellido);
        fscanf(Archibopersonas,"%d,",&Codigo);
        fscanf(Archibopersonas,"%d,",&Edad);
        fscanf(Archibopersonas,"%d,",&Sexo);
        fscanf(Archibopersonas,"%d",&Sexualidad);
        fprintf(ArchivoSalida,"%s, %s, %s, %d, %c, %c\n",Nombre,Apellido,ArregloLocalidades[Codigo-1],Edad,Genero[Sexo-1],Interes[Sexualidad-1]);
    }
    fclose(Archibopersonas);
    fclose(ArchivoSalida);
}
void FuncionSubPrincipal(int CantPersonas,int TotalPersonas){
    int *Array_Index=(int*)malloc(sizeof(int)*CantPersonas);
    int *Array_Random=(int*)malloc(sizeof(int)*TotalPersonas);
    int NumeroRandom;
    for(int i=0;i<TotalPersonas;++i){
        Array_Random[i]=0; // Inicializa
    }
    srand((unsigned int)time(NULL));
    for(int i=CantPersonas; i!=0;--i){
        NumeroRandom = rand() % (TotalPersonas+1);
        while(Array_Random[NumeroRandom]!=0){
            NumeroRandom = rand() % (TotalPersonas+1);
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
