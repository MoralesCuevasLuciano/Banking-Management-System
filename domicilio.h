#ifndef DOMICILIO_H_INCLUDED
#define DOMICILIO_H_INCLUDED


typedef struct
{
    char calle[30];
    int nro;
    char localidad[50];
    char provincia[40];
    char cpos[6];
} stDomicilio;

stDomicilio cargaUnDomicilio();//Carga un domicilio manualmente
void mostrarDomicilio(stDomicilio a);//Muestra un domicilio
int comprobarNum(char num[]);//Valida que un string sea un numero de maximo 4 digitos

#endif // DOMICILIO_H_INCLUDED
