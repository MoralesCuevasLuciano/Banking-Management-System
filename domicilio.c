#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domicilio.h"

stDomicilio cargaUnDomicilio()
{
    stDomicilio a;
    char nombre[30];
    int nro;
    printf("Ingrese calle: \n");
    fflush(stdin);
    gets(&nombre);
    while(!validarNombre(nombre))
    {
        printf("ERROR - Calle ingresada no valida\n");
        printf("Ingrese una calle: \n");
        fflush(stdin);
        gets(&nombre);
    }
    strcpy(a.calle, nombre);
    printf("Ingrese numero de domicilio: \n");
    fflush(stdin);
    scanf("%d", &nro);
    while(nro<0 || nro>9999)
    {
        printf("ERROR - Numero de domicilio ingresada no valido\n");
        printf("Ingrese una numero de domicilio (4 digitos maximo): \n");
        fflush(stdin);
        scanf("%d", &nro);
    }
    a.nro = nro;
    printf("Ingrese localidad: \n");
    fflush(stdin);
    gets(&nombre);
    while(!validarNombre(nombre))
    {
        printf("ERROR - Localidad ingresada no valida\n");
        printf("Ingrese una localidad: \n");
        fflush(stdin);
        gets(&nombre);
    }
    strcpy(a.localidad, nombre);
    printf("Ingrese provincia: \n");
    fflush(stdin);
    gets(&nombre);
    while(!validarNombre(nombre))
    {
        printf("ERROR - Provincia ingresada no valida\n");
        printf("Ingrese una provincia: \n");
        fflush(stdin);
        gets(&nombre);
    }
    strcpy(a.provincia, nombre);
    printf("Ingrese codigo postal: \n");
    fflush(stdin);
    gets(&nombre);
    while(!comprobarNum(nombre))
    {
        printf("ERROR - Codigo postal ingresada no valido\n");
        printf("Ingrese un codigo postal (4 digitos): \n");
        fflush(stdin);
        gets(&nombre);
    }
    strcpy(a.cpos, nombre);

    return a;
}

void mostrarDomicilio(stDomicilio a)
{
    printf("\nCalle:  %s", a.calle);
    printf("\nNumero:  %d", a.nro);
    printf("\nLocalidad:  %s", a.localidad);
    printf("\nProvincia:  %s", a.provincia);
    printf("\nCodigo postal:  %s", a.cpos);
}

int comprobarNum(char num[])
{
    int flag=1;
    int i=0;
    while(num[i] != '\0')
    {
        if(num[i] < 48 || num[i] > 57)
        {
            flag = 0;
        }
        i++;
    }

    if(i > 4)
    {
        flag=0;
    }
    return flag;
}


