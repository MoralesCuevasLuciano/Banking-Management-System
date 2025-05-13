#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domicilio.h"
#include "clientes.h"
#include <ctype.h>
#include <conio.h>
#include "mockClientes.h"

#define AR_CLIENTES "clientes.bin"
#define AR_CUENTA "cuentas.bin"

stCliente cargaUnCliente()
{
    stCliente c;
    char nombre[30];
    c.id=cuentaRegistrosArchivo(AR_CLIENTES, sizeof(stCliente));
    c.nroCliente= c.id+1;
    printf("Ingrese un nombre: \n");
    fflush(stdin);
    gets(&nombre);
    while(!validarNombre(nombre))
    {
        printf("ERROR - Nombre ingresado no valido\n");
        printf("Ingrese un nombre: \n");
        fflush(stdin);
        gets(&nombre);
    }
    strcpy(c.nombre, nombre);

    printf("Ingrese un apellido: \n");
    fflush(stdin);
    gets(&nombre);
    while(!validarNombre(nombre))
    {
        printf("ERROR - Apellido ingresado no valido\n");
        printf("Ingrese un apellido: \n");
        fflush(stdin);
        gets(&nombre);
    }
    strcpy(c.apellido, nombre);

    printf("Ingrese un DNI: \n");
    fflush(stdin);
    gets(&nombre);
    while(!comprobarDNI(nombre))
    {
        printf("ERROR - DNI ingresado no valido\n");
        printf("Ingrese un DNI: \n");
        fflush(stdin);
        gets(&nombre);
    }
    strcpy(c.dni, nombre);

    printf("Ingrese un e-mail: \n");
    fflush(stdin);
    gets(&nombre);
    while(!validarCorreo(nombre))
    {
        printf("ERROR - email ingresado no valido\n");
        printf("Ingrese un email: \n");
        fflush(stdin);
        gets(&nombre);
    }
    strcpy(c.email, nombre);

    c.domicilio= cargaUnDomicilio();

    printf("Ingrese un telefono: \n");
    fflush(stdin);
    gets(&nombre);
    while(!comprobarTelefono(nombre))
    {
        printf("ERROR - telefono ingresado no valido\n");
        printf("Ingrese un telefono: \n");
        fflush(stdin);
        gets(&nombre);
    }
    strcpy(c.tel, nombre);

    c.eliminado=0;
    return c;
}

void muestraUnCliente(stCliente c)
{
    printf("\nN%c Cliente: %i", 167,c.nroCliente);
    printf("\nNombre: %s", c.nombre);
    printf("\nApellido: %s", c.apellido);
    printf("\nDNI: %s", c.dni);
    printf("\nEMAIL: %s", c.email);
    mostrarDomicilio(c.domicilio);
    printf("\nTelefono: %s", c.tel);
    printf("\n--------------------------\n");
}

int cargaClientes(stCliente c[], int v, int dim)
{
    char opcion=0;

    while(v < dim && opcion!=27)
    {
        system("cls");
        c[v]=cargaUnCliente(v);
        v++;
        printf("ESC PARA SALIR // CUALQUIER TECLA PARA CONTINUAR");
        opcion = getch();
    }

    return v;
}

void muestraClientes(stCliente c[], int v)
{
    for(int i=0; i<v; i++)
    {
        muestraUnCliente(c[i]);
        printf("\n===========================================\n");
    }
}

int comprobarDNI(char dni[])
{
    int flag=1;
    int i=0;
    while(dni[i] != '\0')
    {
        if(dni[i] < 48 || dni[i] > 57)
        {
            flag = 0;
        }
        i++;
    }

    if(i < 7 || i > 8)
    {
        flag=0;
    }
    return flag;
}

int comprobarNoRepetirDNI(int d, char coleccion[][d], int v, char dni [])
{
    int flag=1;
    for(int i=0; i<v; i++)
    {
        if(strcmp(coleccion[i], dni)==0)
            flag=0;
    }
    return flag;
}

int validarNombre(char nombre[])
{
    int i=0;
    int flag=1;
    while(flag ==1 && nombre[i] != '\0')
    {
        if(!isalpha(nombre[i]))
        {
            flag = 0;
            if(nombre[i] == 32)
                flag = 1;
        }
        i++;
    }
    return flag;
}

int comprobarTelefono(char dni[])
{
    int flag=1;
    int i=0;
    while(dni[i] != '\0')
    {
        if(dni[i] < 48 || dni[i] > 57)
        {
            flag = 0;
        }
        i++;
    }

    if(i != 10)
    {
        flag=0;
    }
    return flag;
}

int validarCorreo(const char *correo)
{
    int arroba = 0;
    int punto_despues_arroba = 0;
    int longitud = strlen(correo);

    // Verificar si la longitud del correo es menor o igual a 5, que es el mínimo para un correo válido
    if (longitud <= 5)
    {
        return 0;
    }

    // Recorrer el correo para verificar los caracteres
    for (int i = 0; i < longitud; i++)
    {
        // Verificar si hay un '@' y asegurarse de que solo haya uno
        if (correo[i] == '@')
        {
            if (arroba == 1)
            {
                return 0; // Más de un '@' encontrado
            }
            arroba = 1;
            // Verificar si hay al menos un punto después del '@'
            if (i < longitud - 2 && correo[i + 1] != '.' && correo[i + 2] != '.')
            {
                punto_despues_arroba = 1;
            }
        }
    }

    // Si hay un '@' y al menos un punto después de él, entonces es un correo válido
    if (arroba && punto_despues_arroba)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void eliminarCliente(char nombreArchivo[], int id)
{
    FILE* archi = fopen(nombreArchivo, "r+b");
    stCliente cliente;
    int flag = 0;
    if (archi)
    {
        while (flag == 0 && fread(&cliente, sizeof(stCliente), 1, archi) > 0)
        {
            if (cliente.id == id)
            {
                eliminarCuentaCliente(AR_CUENTA, cliente.id);
                cliente.eliminado = 1;
                fseek(archi, -1 * sizeof(stCliente), SEEK_CUR);
                fwrite(&cliente, sizeof(stCliente), 1, archi);
                flag = 1;
            }
        }
        fclose(archi);
    }
}
void modificarCliente(char nombreArchivo[], int id)
{
    FILE* archi = fopen(nombreArchivo, "r+b");
    stCliente cliente;
    int flag = 0;
    if (archi)
    {
        while (flag == 0 && fread(&cliente, sizeof(stCliente), 1, archi) > 0)
        {
            if (cliente.id == id)
            {
                cliente = cargaUnCliente(cliente.id-1);
                fseek(archi, -1 * sizeof(stCliente), SEEK_CUR);
                fwrite(&cliente, sizeof(stCliente), 1, archi);
                flag = 1;
            }
        }
        fclose(archi);
    }
}

void cargaArchClientes(char nombreArchivo[], int cant)//Carga CANT clientes aleatorios en un archivo
{
    FILE*archi = fopen(nombreArchivo, "ab");
    stCliente cliente;
    int i=0;
    int cantId = cuentaRegistrosArchivo(nombreArchivo,sizeof(stCliente));
    if(archi)
    {
        while(i<cant)
        {
            cliente = getClienteRandom();
            if(comprobarNoRepetirDNI2(nombreArchivo, cliente.dni))
            {
                cliente.id = cantId;
                cliente.nroCliente = cliente.id + 1;
                cargaCuentasRandom(AR_CUENTA, 2, cliente.id);
                fwrite(&cliente,sizeof(stCliente), 1, archi);
                i++;
                cantId++;
            }
        }
        fclose(archi);
    }

}

void muestraArchClientes(char nombreArchivo[])//Muestra los clientes de un archivo
{
    FILE*archi = fopen(nombreArchivo, "rb");
    stCliente cliente;
    if(archi)
    {
        while(fread(&cliente, sizeof(stCliente),1,archi)>0)
        {
            if(cliente.eliminado==0)
                muestraUnCliente(cliente);
        }
        fclose(archi);
    }

}

int bucarClientePorNro(char nombreArchivo[], int nroCliente)//Busca un cliente por su numero de cliente. Si lo encuentra lo imprime y retorna su numero de id, sino imprime que no existe y retorna -1
{
    FILE*archi = fopen(nombreArchivo, "rb");
    stCliente cliente;
    int flag = 0;
    int id = -1;
    if(archi)
    {
        while(flag == 0 && fread(&cliente,sizeof(stCliente),1,archi)>0)
        {
            if(cliente.nroCliente == nroCliente && cliente.eliminado == 0)
            {
                muestraUnCliente(cliente);
                id = cliente.id;
                flag = 1;
            }
        }

        fclose(archi);
    }
    return id;
}

void buscaNombreFile(char nombreArchivo[], int idCliente)//Busca y escribe el nombre de un cliente por su ID
{
    FILE*archi = fopen(nombreArchivo, "rb");
    stCliente cliente;
    int flag = 0;
    if(archi)
    {
        while(flag == 0 && fread(&cliente,sizeof(stCliente),1,archi)>0)
        {
            if(cliente.id == idCliente)
            {
                printf("%s %s",cliente.apellido, cliente.nombre);
                flag = 1;
            }
        }
        fclose(archi);
    }
}

stCliente buscaClienteId (char archivo [], int id)//Funcion que va a buscar un cliente por su id y lo va a retornar
{
    int flag = 0;
    FILE *archi = fopen (archivo, "rb");
    stCliente cliente;
    if (archi)
    {
        while (flag == 0 && fread (&cliente, sizeof (stCliente), 1, archi) > 0)
        {
            if (id == cliente.id)
            {
                flag = 1;
            }
        }
        fclose (archi);
    }
    return cliente;
}

int comprobarNoRepetirDNI2 (char archivo [], char dni[])//comprueba que un cliente no se haya cargado previamente mediante el dni
{
    FILE *archi = fopen (archivo, "rb");

    stCliente cliente;

    int flag = 1;

    if (archi)
    {
        while (flag == 1 && fread(&cliente, sizeof(stCliente), 1, archi) > 0)
        {
            if (cliente.eliminado==0 &&strcmp(cliente.dni, dni)==0)
            {
                flag = 0;
            }
        }
    }
    return flag;
}

int cargaUnClienteArchivo (char archivo[])//Carga un cliente al archivo, si lo pudo cargar retorna 1 sino 0
{
    FILE *archi;

    archi = fopen (archivo, "ab");
    stCliente cliente;
    int v;
    int flag =0;

    if (archi)
    {
        v = cuentaRegistrosArchivo(archivo, sizeof(stCliente));
        cliente = cargaUnCliente(v);
        if (comprobarNoRepetirDNI2(archivo, cliente.dni))
        {
            fwrite(&cliente, sizeof(stCliente), 1, archi);
            flag = 1;
        }
        fclose(archi);
    }

    return flag;
}

int getIdClienteRandom(char nombreArchivo[])
{
    FILE* archi = fopen(nombreArchivo, "rb");
    if (archi)
    {
        fseek(archi, 0, SEEK_END);
        long fileSize = ftell(archi);
        int numClientes = fileSize / sizeof(stCliente);
        fseek(archi, (rand() % numClientes) * sizeof(stCliente), SEEK_SET);
        stCliente cliente;
        fread(&cliente, sizeof(stCliente), 1, archi);
        fclose(archi);
        return cliente.id;
    }
    return -1;
}
