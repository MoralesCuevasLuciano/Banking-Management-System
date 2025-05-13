#include "cuenta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domicilio.h"
#include "clientes.h"
#include "time.h"
#include "mockClientes.h"


#define AR_CLIENTES "clientes.bin"
#define AR_CUENTA "cuentas.bin"
#define AR_MOVIMIENTOS "movimientos.bin"


stCuenta cargaUnaCuenta(int idCliente)//Funcion para cargar una cuenta. Debe recibir el cliente propietario de la cuenta
{
    stCuenta a;

    a.id=cuentaUltimoArchivo(AR_CUENTA, sizeof(stCuenta));
    a.idCliente = idCliente;
    a.nroCuenta=rand()%10000-1;
    while(cuentaExiste(AR_CUENTA, a.nroCuenta)!=-1)
    {
        a.nroCuenta=rand()%10000-1;
    }
    a.tipoDeCuenta=crearCaja();
    a.costoMensual=costoMensual(a.tipoDeCuenta);
    a.saldo=0;
    a.eliminado=0;


    return a;
}

int cuentaUltimoArchivo(char nombreArchivo[], int tamEstructura)//Cuenta registros cargados hay en un archivo
{
    FILE* archi = fopen(nombreArchivo, "rb");
    int total = 0;
    if(archi)
    {
        fseek(archi,0,SEEK_END);
        total = ftell(archi)/tamEstructura;
        fclose(archi);
    }
    return total;
}

int crearCaja()//Funcion para crear una caja para la cuenta (se usa para crear una cuenta manual)
{
    int resp=0;
    int dato;
    while(resp==0)
    {
        printf("\nINGRESE: \n1. Caja de Ahorro en Pesos\n2. Caja de Ahorro en Dolares\n3. Cuenta Corriente en Pesos \n");
        scanf("%d",&resp);
        while(resp<1 || resp>3)
        {
            printf("El dato NO es valido ingrese 1, 2 o 3\n");
            scanf("%i", &resp);
        }
        dato=resp;
    }
    return dato;
}

float costoMensual(int tipoCuenta)//Funcion que le asigna un monto mensual a la caja en base al tipo de cuenta
{
    float costo=0;
    if(tipoCuenta==1)
    {
        costo=1000;
    }
    else if(tipoCuenta==2)
    {
        costo=5000;
    }
    else
    {
        costo=3000;
    }
    return costo;
}

void muestraUnaCuenta(stCuenta a)//Funcion para mostrar una cuenta
{
    printf("\n------------------------------------\n");
    printf("Numero de cuenta: %i\n\n", a.nroCuenta);
    printf("Id Cliente: %i\n",a.idCliente);
    if(a.tipoDeCuenta == 1)
    {
        printf("Caja de Ahorro en Pesos\n");
    }
    else if (a.tipoDeCuenta==2)
    {
        printf("Caja de Ahorro en Dolares\n");
    }
    else
    {
        printf("Cuenta Corriente en Pesos\n");
    }

    printf("Saldo: $%.2f\n\n", a.saldo);
    printf("Costo mensual de la cuenta: $%.2f\n", a.costoMensual);
    printf("\n------------------------------------");
}

int validarIdCliente(char nombreArchivo[], int num) ///No la vamos a usar
{
    FILE*archi = fopen(nombreArchivo, "rb");
    int flag = 1;
    stCliente cliente;
    if(archi)
    {
        while(flag==1 && fread(&cliente, sizeof(stCliente),1,archi)>0)
        {
            if(cliente.nroCliente == num)
            {
                flag = 0;
            }
        }
        fclose(archi);
    }
    return flag;
}
int listaCuentasPorCliente(char nombreArchivo[], int idCliente)  //Muestra las cuentas de un cliente y devuleve cuantas se han cargado
{
    FILE* archi = fopen(nombreArchivo, "rb");
    stCuenta cuenta;
    int i=0;
    if (archi)
    {
        printf("\nCuentas de ");
        buscaNombreFile(AR_CLIENTES, idCliente);
        printf(":\n\n");
        while (fread(&cuenta, sizeof(stCuenta), 1, archi) > 0)
        {
            if (cuenta.idCliente == idCliente && cuenta.eliminado == 0)
            {
                muestraUnaCuenta(cuenta);
                i++;
            }
        }
        fclose(archi);
    }
    return i;
}
void modificarCuenta(char nombreArchivo[], int id)  //Modifica una cuenta existente
{
    FILE* archi = fopen(nombreArchivo, "r+b");
    stCuenta cuenta;
    int flag = 0;
    if (archi)
    {
        while (flag == 0 && fread(&cuenta, sizeof(stCuenta), 1, archi) > 0)
        {
            if (cuenta.id == id)
            {
                printf("Ingrese los nuevos datos de la cuenta:\n");
                cuenta = cargaUnaCuenta(cuenta.idCliente);
                fseek(archi, -1 * sizeof(stCuenta), SEEK_CUR);
                fwrite(&cuenta, sizeof(stCuenta), 1, archi);
                flag = 1;
            }
        }
        fclose(archi);
    }
    if (flag == 0)
    {
        printf("No se encontró una cuenta con el ID %d\n", id);
    }
}

void cargaArchCuentas(char nombreArchivo[], int idCliente) //Carga UNA cuenta en un archivo
{
    FILE*archi = fopen(nombreArchivo, "ab");
    stCuenta cuenta;
    if(archi)
    {
        cuenta = cargaUnaCuenta(idCliente);
        fwrite(&cuenta,sizeof(stCuenta),1,archi);
        fclose(archi);
    }
}

void muestraArchCuentas(char nombreArchivo[])//Muestra TODAS las cuentas ACTIVAS de un archivo
{
    FILE*archi = fopen(nombreArchivo, "rb");
    stCuenta cuenta;
    if(archi)
    {
        printf("\n=============CUENTAS ACTIVAS===============\n\n");
        while(fread(&cuenta, sizeof(stCuenta),1,archi)>0)
        {

            if(cuenta.eliminado == 0)
            {
                muestraUnaCuenta(cuenta);
            }

        }
        fclose(archi);
        printf("\n==============FIN DE ARCHIVO================\n\n");
    }
    else
    {
        printf("ERROR : EL ARCHIVO DE CUENTAS SE ENCUENTRA VACIO");
    }

}

void editSaldoCuenta(char nombreArchivo[], int idCuenta, float cant)//Edita el saldo de UNA cuenta
{
    FILE*archi = fopen(nombreArchivo, "r+b");
    stCuenta cuenta;
    int flag = 0;
    if(archi)
    {
        while(flag == 0 && fread(&cuenta, sizeof(stCuenta),1,archi)>0)
        {
            if(idCuenta == cuenta.id)
            {
                cuenta.saldo = cuenta.saldo + (cant);
                flag = 1;
                fseek(archi,-1*(sizeof(stCuenta)),1);
                fwrite(&cuenta, sizeof(stCuenta),1,archi);
            }

        }
        fclose(archi);
    }
    else
    {
        printf("ERROR : EL ARCHIVO DE CUENTAS SE ENCUENTRA VACIO");
    }
}

void eliminarCuenta(char nombreArchivo[], int nro)//Elimina una cuenta
{
    FILE*archi = fopen(nombreArchivo,"r+b");
    stCuenta cuenta;
    int flag = 0;
    if(archi)
    {

        while(flag == 0 && fread(&cuenta,sizeof(stCuenta),1,archi)>0)
        {
            if(cuenta.nroCuenta == nro)
            {
                cuenta.eliminado = 1;
                fseek(archi,-1*sizeof(stCuenta),1);
                fwrite(&cuenta,sizeof(stCuenta),1,archi);
                flag = 1;
            }
        }
        fclose(archi);
    }
}


void eliminarCuentaCliente(char nombreArchivo[], int idCliente)//Elimina las cuentas de un cliente
{
    FILE*archi = fopen(nombreArchivo,"r+b");
    int i = 0;


    stCuenta cuenta;

    if(archi)
    {
        while(fread(&cuenta,sizeof(stCuenta),1,archi)>0)
        {
            if(cuenta.idCliente == idCliente && cuenta.eliminado==0)
            {
                eliminarMovimientoCuentas(AR_MOVIMIENTOS, cuenta.id);
                cuenta.eliminado = 1;
                fseek(archi,(-1)* sizeof(stCuenta),SEEK_CUR);
                fwrite(&cuenta,sizeof(stCuenta),1,archi);
                fseek(archi,sizeof(stCuenta),SEEK_CUR);
                fseek(archi,(-1)* sizeof(stCuenta),SEEK_CUR);

                //printf("\n Cuenta nro %d - Cliente %d - ciclo %d dentro \n ",cuenta.id, cuenta.idCliente,i);

            }

            //printf("\n Cuenta nro %d - Cliente %d - ciclo %d fuera %d \n ",cuenta.id, cuenta.idCliente,i,cuenta.eliminado);
             //i++;
        }
        fclose(archi);
       // muestraArchCuentas(AR_CUENTA);
        //system("pause");
    }
}

stCuenta buscaCuentaId (char archivo [], int nroCuenta)//Funcion que buscara una cuenta por su id y la retornara
{
    int flag = 0;
    FILE *archi = fopen (archivo, "rb");
    stCuenta cuenta;
    if (archi)
    {
        while (flag == 0 && fread (&cuenta, sizeof (stCuenta), 1, archi) > 0)
        {
            if (cuenta.nroCuenta == nroCuenta)
            {
                flag = 1;
            }
        }
        fclose (archi);
    }
    return cuenta;
}

stCuenta buscaCuentaId2 (char archivo [], int id)//Funcion que buscara una cuenta por su id y la retornara
{
    int flag = 0;
    FILE *archi = fopen (archivo, "rb");
    stCuenta cuenta;
    if (archi)
    {
        while (flag == 0 && fread (&cuenta, sizeof (stCuenta), 1, archi) > 0)
        {
            if (cuenta.id == id)
            {
                flag = 1;
            }
        }
        fclose (archi);
    }
    return cuenta;
}

int cuentaExiste(char archivo[], int nroCuenta)//Busca una cuenta por su numero y retorna si la encontro o no
{
    FILE* archi = fopen(archivo, "rb");
    stCuenta cuentita;
    int id=-1;
    if(archi)
    {
        while(id == -1 && fread(&cuentita, sizeof(stCuenta), 1, archi)>0)
        {
            if(nroCuenta == cuentita.nroCuenta && cuentita.eliminado==0)
            {
                id=cuentita.id;
            }
        }

        fclose(archi);
    }
    return id;
}

stCuenta getCuentaRandom(int idCliente, int idCuenta)//Devuelve una cuenta aleatoria
{
    stCuenta cuenta;
    cuenta.id = idCuenta;
    cuenta.idCliente = idCliente;
    cuenta.nroCuenta = rand() % 1000000;
    cuenta.tipoDeCuenta = (rand() % 3) + 1;
    cuenta.costoMensual = costoMensual(cuenta.tipoDeCuenta);
    cuenta.eliminado = 0;
    return cuenta;
}

void cargaCuentasRandom(char nombreArchivo[], int cantidad, int idCliente)//Carga al archivo CANTIDAD de cuentas aleatorias
{
    FILE* archi = fopen(nombreArchivo, "ab");
    int i=0;
    int validos = cuentaRegistrosArchivo(AR_CUENTA, sizeof(stCuenta));
    stCuenta cuentita;
    if(archi)
    {
        while(i<cantidad)
        {
            cuentita = getCuentaRandom(idCliente, validos+i);
            if(cuentaExiste(AR_CUENTA, cuentita.nroCuenta) == -1)
            {
                fwrite(&cuentita, sizeof(stCuenta), 1, archi);
                i++;
            }
        }
        fclose(archi);
    }
}
