#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#include "domicilio.h"

typedef struct
{
    int id;
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[9];
    char email[30];
    stDomicilio domicilio;
    char tel[12];
    int eliminado;
} stCliente;

stCliente cargaUnCliente();//Carrgar un cliente manualmente
void muestraUnCliente(stCliente c);//Muestra UN cliente
int cargaClientes(stCliente a[], int v, int dim);//Carga muchos clientes en un ARREGLO
void muestraClientes(stCliente a[], int v);//Muestra clientes cargados en un ARREGLO
int comprobarDNI(char dni[]);//Comprueba que un char sea un dni (7/8 digitos del 0 al 9)
int comprobarNoRepetirDNI(int d, char coleccion[][d], int v, char dni []);//Comprueba que un cliente no se haya cargado en un ARREGLO
int validarNombre(char nombre[]);//Valida que un string sean solo letras o espacio
int validarCorreo(const char *correo);//Recibe un string y valida que sea un mail
int comprobarTelefono(char dni[]);//Comprueba que un string sea un numero de telefono (10 digitos del 0 al 9)
void eliminarCliente(char nombreArchivo[], int id);//Recibe un archivo y elimina un cliente
void modificarCliente(char nombreArchivo[], int id);//Recibe un archivo y modifica un cliente
void cargaArchClientes(char nombreArchivo[], int cant);//Carga CANT clientes aleatorios en un archivo
void muestraArchClientes(char nombreArchivo[]);//Muestra los clientes de un archivo
int bucarClientePorNro(char nombreArchivo[], int nroCliente);//Busca un cliente por su numero de cliente. Si lo encuentra lo imprime y retorna su numero de id, sino imprime que no existe y retorna -1
void buscaNombreFile(char nombreArchivo[], int idCliente);//Busca por su ID a un cliente e imprime su nombre en pantalla
stCliente buscaClienteId (char archivo [], int id);//Funcion que va a buscar un cliente por su id y lo va a retornar
int comprobarNoRepetirDNI2 (char archivo [], char dni[]);//comprueba que un cliente no se haya cargado previamente mediante el dni
int cargaUnClienteArchivo (char archivo[]);//Carga un cliente al archivo
int getIdClienteRandom(char nombreArchivo[]);//devuelte el id de un cliente

#endif // CLIENTES_H_INCLUDED
