#ifndef CUENTA_H_INCLUDED
#define CUENTA_H_INCLUDED
#define AR_CUENTA "cuentas.bin"
#include "clientes.h"

typedef struct
{
    int id; /// campo único y autoincremental
    int idCliente; /// Id del Cliente dueño de la Cuenta
    int nroCuenta;
    int tipoDeCuenta; /// 1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en Dólares, 3. Cta Cte en $
    float costoMensual; /// Costo de mantenimiento del producto;
    float saldo; /// Debe actualizarse al modidificar o cargar un movimiento.
    int eliminado; /// 0 si está activo - 1 si está eliminado
} stCuenta;

stCuenta cargaUnaCuenta(int idCliente);//Funcion para cargar una cuenta. Debe recibir el cliente propietario de la cuenta
int cuentaUltimoArchivo(char nombreArchivo[], int tamEstructura);//Cuenta registros cargados hay en un archivo
int crearCaja();//Funcion para crear una caja para la cuenta (se usa para crear una cuenta manual)
float costoMensual(int tipoCuenta);//Funcion que le asigna un monto mensual a la caja en base al tipo de cuenta
void muestraUnaCuenta(stCuenta a);//Funcion para mostrar una cuenta
void modificarCuenta(char nombreArchivo[], int id);//Modifica una cuenta existente
int listaCuentasPorCliente(char nombreArchivo[], int idCliente); //Muestra las cuentas de un cliente y devuleve cuantas se han cargado
void cargaArchCuentas(char nombreArchivo[], int idCliente);//Carga una cuenta en un archivo
void muestraArchCuentas(char nombreArchivo[]);//Muestra TODAS las cuentas ACTIVAS de un archivo
void editSaldoCuenta(char nombreArchivo[], int nroCuenta, float cant);//Edita el saldo de UNA cuenta
void eliminarCuenta(char nombreArchivo[], int nro);//Elimina una cuenta
void eliminarCuentaCliente(char nombreArchivo[], int idCliente);//Elimina las cuentas de un cliente
stCuenta buscaCuentaId (char archivo [], int nroCuenta);//Funcion que buscara una cuenta por su numero de cuneta y la retornara
stCuenta buscaCuentaId2 (char archivo [], int id);//Funcion que buscara una cuenta por su id y la retornara
int cuentaExiste(char archivo[], int nroCuenta);//Funcion que buscara una cuenta por su numero y retornara su id si existe o -1 si no existe
stCuenta getCuentaRandom(int idCliente, int idCuenta);//Devuelve una cuenta aleatoria
void cargaCuentasRandom(char nombreArchivo[], int cantidad, int idCliente);//Carga al archivo CANTIDAD de cuentas aleatorias

#endif // CUENTA_H_INCLUDED
