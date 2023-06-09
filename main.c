#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <strings.h>
///VARIABLES GLOBALES:
const char APROBADOS[30] = {"aprobados.bin"};
const char DESAPROBADOS[30] = {"desaprobados.bin"};
const int FILA = 3;
const int COLUM = 3;
///ESTRUCTURAS:
typedef struct{
    int legajo;
    char nombreMateria[30];
    int anio;
    int nota;
}Alumno;
///PROTOTIPADO DE FUNCIONES:
void cargarMatrix(int matrix[FILA][COLUM]);
void mostrarMatrix(int matrix[FILA][COLUM]);
int buscarDatoMatrix(int matrix[FILA][COLUM], int dato);
int cargarArrStruc(Alumno alumArr[30]);
Alumno cargarUnSoloAlumnoArr();
void pasandoArchiArregloAlumnos(Alumno arrAlum[], int validos);
int cantArchiAprobados();
int cantArchiDesaprobados();
void mostrarAlumArchi(Alumno alumno);
void mostrarAlumDependeLaMateriaAprobados(char materia[30]);
void mostrarAlumDependeLaMateriaDesaprobados(char materia[30]);
int buscarAlumnoMayorNotaArchi();
void mostrandoAlumnoMayorNota(int mayor);
void mostrarAlumSegunRegistroAprobados(int registro);

int main(){
///PUNTO 1:
int matrix[FILA][COLUM];
cargarMatrix(matrix);
mostrarMatrix(matrix);
int datoBuscar;
printf("Ingrese el numero a buscar: ");
fflush(stdin);
scanf("%i", &datoBuscar);
int retorno = buscarDatoMatrix(matrix,datoBuscar);
printf("Retorno: %i ", retorno);
///PUNTO 2:
Alumno alumArr[30];
int validosArr = cargarArrStruc(alumArr);
///PUNTO 3:
pasandoArchiArregloAlumnos(alumArr, validosArr);
///PUNTO 4:
int cantAprobadosArchi;
cantAprobadosArchi = cantArchiAprobados();
printf("\nLa cantidad de alumnos registrados aprobados son: %i \n", cantAprobadosArchi);
int cantDesaprobadosArchi;
cantDesaprobadosArchi = cantArchiDesaprobados();
printf("\nLa cantidad de alumnos registrados desaprobados son: %i \n", cantDesaprobadosArchi);
///PUNTO 5:
char materia[30];
printf("Ingrese la materia: ");
fflush(stdin);
gets(materia);
mostrarAlumDependeLaMateriaAprobados(materia);
mostrarAlumDependeLaMateriaDesaprobados(materia);
///PUNTO 6:
int mayorNota = buscarAlumnoMayorNotaArchi();
printf("\nLa nota mayor es: %i \n", mayorNota);
mostrandoAlumnoMayorNota(mayorNota);
///PUNTO 7:
int cantRegistrosAprobadosArchi = cantArchiAprobados();
printf("\nLa cantidad de alumnos registrados aprobados son: %i \n", cantRegistrosAprobadosArchi);
int registroEspecificoAprobados;
int validacion = 0;
do{
    printf("\nIngrese un registro de aprobados y le mostrare el alumno: ");
    fflush(stdin);
    scanf("%i", &registroEspecificoAprobados);
    if(registroEspecificoAprobados <= cantRegistrosAprobadosArchi){
        validacion = 1;
        mostrarAlumSegunRegistroAprobados(registroEspecificoAprobados);
    }else{
        validacion = 0;
        printf("\nRegistro incorrecto. Intente nuevamente.\n");
    }
}while(validacion == 0);

}
///FUNCIONES
///--------------------------------------------------------

void cargarMatrix(int matrix[FILA][COLUM]){
    int i,j;
    srand(time(NULL));
    for(i = 0; i<FILA;i++){
        for(j = 0; j<COLUM;j++){
            matrix[i][j] = rand()%10;
        }
    }
}
void mostrarMatrix(int matrix[FILA][COLUM]){
int i,j;
    for(i = 0; i<FILA; i++){
        for(j = 0; j<COLUM;j++){
            printf("|%i| ", matrix[i][j]);
        }
        printf("\n");
    }
}
int buscarDatoMatrix(int matrix[FILA][COLUM], int dato){
    int i,j;
    int flag = 0;
    for(i = 0; i<FILA; i++){
        for(j = 0; j<COLUM;j++){
            if(matrix[i][j] == dato){
                flag = 1;
            }
        }

    }
    return flag;
}
int cargarArrStruc(Alumno alumArr[30]){
    char eleccion = 's';
    int i = 0;
    while(eleccion == 's' && i <= 30){
        alumArr[i] = cargarUnSoloAlumnoArr();
        i++;
        printf("Pulsa 's' si desea continuar: ");
        fflush(stdin);
        scanf("%c", &eleccion);
    }
    return i;
}
Alumno cargarUnSoloAlumnoArr(){
    Alumno alumno;
    int nota;
    int flag = 0;
    printf("Legajo: ");
    fflush(stdin);
    scanf("%i", &alumno.legajo);
    printf("Nombre de materia: ");
    fflush(stdin);
    gets(alumno.nombreMateria);
    printf("Anio: ");
    fflush(stdin);
    scanf("%i", &alumno.anio);
    do{
        printf("Nota (1-10): ");
        fflush(stdin);
        scanf("%i", &nota);
        if(nota <= 10 && nota >= 1){
            alumno.nota = nota;
            flag = 1;
        }else{
            printf("Nota incorrecta. Ingrese neuvamente.");
            flag = 0;
        }
    }while(flag == 0);

    return alumno;
}
void pasandoArchiArregloAlumnos(Alumno arrAlum[], int validos){
    Alumno alumnosAprobados;
    Alumno alumnosDesaprobados;
    int i = 0;
    while(i <= validos){
        if(arrAlum[i].nota >= 6){
            FILE *archi = fopen(APROBADOS,"ab");
            if(archi != NULL){
                alumnosAprobados.legajo = arrAlum[i].legajo;
                strcpy(alumnosAprobados.nombreMateria,arrAlum[i].nombreMateria);
                alumnosAprobados.anio = arrAlum[i].anio;
                alumnosAprobados.nota = arrAlum[i].nota;
                fwrite(&alumnosAprobados,sizeof(Alumno),1,archi);
                i++;
            }else{
        printf("\nERROR\n");
    }
            fclose(archi);
        }
        if(arrAlum[i].nota <= 5){
            FILE *archi2 = fopen(DESAPROBADOS,"ab");
            if(archi2 != NULL){
                alumnosDesaprobados.legajo = arrAlum[i].legajo;
                strcpy(alumnosDesaprobados.nombreMateria,arrAlum[i].nombreMateria);
                alumnosDesaprobados.anio = arrAlum[i].anio;
                alumnosDesaprobados.nota = arrAlum[i].nota;
                fwrite(&alumnosDesaprobados,sizeof(Alumno),1,archi2);
                i++;
            }else{
        printf("\nERROR\n");
    }
            fclose(archi2);
        }
    }

}
int cantArchiAprobados(){
    Alumno aprobados;
    int cantAprobados;
    FILE *archi = fopen(APROBADOS,"rb");
    if(archi != NULL){
        fseek(archi,0,SEEK_END);
        cantAprobados = ftell(archi) / sizeof(Alumno);
        fclose(archi);
    }else{
        printf("\nERROR\n");
    }
    return cantAprobados;
}
int cantArchiDesaprobados(){
    Alumno desaprobados;
    int cantDesaprobados;
    FILE *archi2 = fopen(DESAPROBADOS,"rb");
    if(archi2 != NULL){
        fseek(archi2,0,SEEK_END);
        cantDesaprobados = ftell(archi2) / sizeof(Alumno);
        fclose(archi2);
    }else{
        printf("\nERROR\n");
    }
    return cantDesaprobados;
}
void mostrarAlumDependeLaMateriaAprobados(char materia[30]){
    Alumno alumAprobados;
    int flag = 0;
    FILE *archi = fopen(APROBADOS,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            fread(&alumAprobados,sizeof(Alumno),1,archi);
            if(!feof(archi)){
                if(strcmp(alumAprobados.nombreMateria,materia) == 0 ){
                        flag = 1;
                        mostrarAlumArchi(alumAprobados);
                }else{
                    flag = 0;
                }
            }
        }
        fclose(archi);
    }else{
        printf("\nERROR\n");
    }
    if(flag == 0){
        printf("\nNo se encontraron alumnos en esa materia\n");
    }
}
void mostrarAlumArchi(Alumno alumno){
printf("\n-------------------------------------------->\n");
printf("Legajo: %i \n", alumno.legajo);
printf("Materia: %s \n", alumno.nombreMateria);
printf("Anio: %i \n", alumno.anio);
printf("Nota: %i ", alumno.nota);
printf("\n-------------------------------------------->\n");
}
void mostrarAlumDependeLaMateriaDesaprobados(char materia[30]){
    Alumno alumDesaprobados;
    int flag = 0;
    FILE *archi = fopen(DESAPROBADOS,"rb");
   if(archi != NULL){
        while(!feof(archi)){
            fread(&alumDesaprobados,sizeof(Alumno),1,archi);
            if(!feof(archi)){
                if(strcmp(alumDesaprobados.nombreMateria,materia) == 0 ){
                        flag = 1;
                        mostrarAlumArchi(alumDesaprobados);
                }else{
                    flag = 0;
                }
            }
        }
        fclose(archi);
    }else{
        printf("\nERROR\n");
    }
    if(flag == 0){
        printf("\nNo se encontraron alumnos en esa materia\n");
    }
}
int buscarAlumnoMayorNotaArchi(){
//No la hago para desaprobados xq tiene q ser la menor nota :D
    Alumno alumnos;
    int mayor = 0;
    FILE *archi = fopen(APROBADOS,"rb");
    if(archi != NULL){
            while(!feof(archi)){
                fread(&alumnos,sizeof(Alumno),1,archi);
                if(!feof(archi)){
                    if(alumnos.nota > mayor){
                        mayor = alumnos.nota;
                    }
                }
            }
            fclose(archi);
    }else{
        printf("\nERROR\n");
    }
    return mayor;
}
void mostrandoAlumnoMayorNota(int mayor){
    Alumno alum;
    FILE *archi = fopen(APROBADOS,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            fread(&alum,sizeof(Alumno),1,archi);
            if(!feof(archi)){
                if(alum.nota == mayor){
                    mostrarAlumArchi(alum);
                }
            }
        }
        fclose(archi);
    }else{
        printf("\nERROR\n");
    }
}
void mostrarAlumSegunRegistroAprobados(int registro){
    Alumno alum;
    FILE *archi = fopen(APROBADOS,"rb");
    if(archi != NULL){
        fseek(archi,sizeof(Alumno) * (registro - 1),SEEK_SET);
        fread(&alum,sizeof(Alumno),1,archi);
        mostrarAlumArchi(alum);
        fclose(archi);
    }else{
        printf("\nERROR\n");
    }
}
