#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domicilio.h"
#include "clientes.h"
#include "cuenta.h"
#include "movimientos.h"
#include "time.h"
#include "mockClientes.h"
#include "malloc.h"
#include <conio.h>

#define AR_CLIENTES "clientes.bin"
#define AR_CUENTA "cuentas.bin"
#define AR_MOVIMIENTOS "movimientos.bin"

stMovimiento cargaUnMovimiento(int idCuenta) //Funcion para cargar un movimiento manual
{
    stMovimiento m;
    int num;
    m.idCuenta = idCuenta;
    printf("Indique el monto a ingresar / descontar :\t");
    fflush(stdin);
    scanf("%f", &m.importe);
    editSaldoCuenta(AR_CUENTA,m.idCuenta,m.importe);
    printf("Ingrese un detalle para la transaccion:\t");
    fflush(stdin);
    gets(m.detalle);
    printf("Ingrese la fecha del movimiento: \n");
    printf("A%cO:\t", 165);
    scanf("%d", &num);
    while(validarAnio(num))
    {
        printf("ERROR: El a%co ingresado es incorrecto...\n",164);
        fflush(stdin);
        scanf("%d",&num);
    }
    m.anio = num;
    printf("MES:\t");
    fflush(stdin);
    scanf("%d", &num);
    while(validarMes(num))
    {
        printf("ERROR: El mes ingresado es incorrecto...\n");
        fflush(stdin);
        scanf("%d", &num);
    }
    m.mes = num;
    printf("DIA:\t");
    scanf("%d", &num);
    while(validarDia(m,num))
    {
        printf("ERROR: El dia ingresado es incorrecto...\n");
        fflush(stdin);
        scanf("%d", &num);
    }
    m.dia = num;
    m.eliminado = 0;

    return m;
}

void muestraUnMovimiento(stMovimiento m) //Funcion para mostrar un movimiento
{
    stCuenta cuentita;
    stCliente client;
    cuentita = buscaCuentaId2(AR_CUENTA, m.idCuenta);
    printf("\n----------------------------\n");
    printf("TITUALR: ");
    buscaNombreFile(AR_CLIENTES, cuentita.idCliente);
    printf("\nCUENTA N%c %d\n",167,cuentita.nroCuenta);
    printf("ID MOVIMIENTO: %i\n", m.id);
    printf("IMPORTE: $%.2f\n",  m.importe);
    printf("DETALLE: %s\n", m.detalle);
    printf("FECHA: %d/%d/%d\n", m.dia,m.mes,m.anio);
    printf("----------------------------\n");
}

int validarAnio(int num) //Funcion para validar el anio
{
    int flag = 0;
    if(num<2000 || num>2024)
    {
        flag = 1;
    }
    return flag;
}
int validarMes(int num) //funcion para validar el mes
{
    int flag = 0;
    if(num<1 || num>12)
    {
        flag = 1;
    }
    return flag;
}
int validarDia(stMovimiento m, int num) // Función para validar el día
{
    int flag = 0;

    if (m.mes < 8 && m.mes % 2 != 0)
    {
        if (num < 1 || num > 31)
        {
            flag = 1;
        }
    }
    else if (m.mes < 8 && m.mes % 2 == 0)
    {
        if (num < 1 || num > 30)
        {
            flag = 1;
        }
    }
    else if (m.mes > 7 && m.mes % 2 == 0)
    {
        if (num < 1 || num > 31)
        {
            flag = 1;
        }
    }
    else if (m.mes > 7 && m.mes % 2 != 0)
    {
        if (num < 1 || num > 30)
        {
            flag = 1;
        }
    }
    else if (m.mes == 2)
    {
        if (num < 1 || num > 28)
        {
            flag = 1;
        }
    }

    return flag;
}


int validarIdCuenta(char nombreArchivo[], int num) ///No vamos a usar
{
    FILE*archi = fopen(nombreArchivo, "rb");
    int flag=1;
    stCuenta cuenta;
    if(archi)
    {
        while(flag == 1 && fread(&cuenta,sizeof(stCuenta),1,archi)>0)
        {
            if(cuenta.nroCuenta == num)
            {
                flag = 0;
            }
        }
        fclose(archi);
    }
    return flag;
}

void eliminarMovimiento(char nombreArchivo[], int id)  //Funcion para eliminar un movimiento
{
    FILE* archi = fopen(nombreArchivo, "r+b");
    stMovimiento mov;
    int flag = 0;
    if (archi)
    {
        while (flag == 0 && fread(&mov, sizeof(stMovimiento), 1, archi) > 0)
        {
            if (mov.id == id && mov.eliminado==0)
            {
                mov.eliminado = 1;
                fseek(archi, -1 * sizeof(stMovimiento), SEEK_CUR);
                fwrite(&mov, sizeof(stMovimiento), 1, archi);
                flag = 1;
            }
        }
        fclose(archi);
    }
    if (flag == 0)
    {
        printf("No se encontró un movimiento con el ID %d\n", id);
    }
}

void eliminarMovimientoCuentas(char nombreArchivo[], int idCuenta)//Funcion para eliminar los movimientos de una cuenta
{
    FILE* archi = fopen(nombreArchivo, "r+b");
    stMovimiento mov;
    if (archi)
    {
        while (fread(&mov, sizeof(stMovimiento), 1, archi) > 0)
        {
            if (mov.idCuenta == idCuenta && mov.eliminado == 0)
            {
                mov.eliminado = 1;
                fseek(archi, -1 * sizeof(stMovimiento), SEEK_CUR);
                fwrite(&mov, sizeof(stMovimiento), 1, archi);
                fseek(archi,sizeof(stMovimiento),SEEK_CUR);
                fseek(archi, -1 * sizeof(stMovimiento), SEEK_CUR);
            }
        }
        fclose(archi);
    }
}

void modificarMovimiento(char nombreArchivo[], int id)  //Funcion que modifica un movimiento
{
    FILE* archi = fopen(nombreArchivo, "r+b");
    stMovimiento mov;
    int flag = 0;
    int idMovimiento=0;
    if (archi)
    {
        while (flag == 0 && fread(&mov, sizeof(stMovimiento), 1, archi) > 0)
        {
            if (mov.id == id && mov.eliminado==0)
            {
                printf("Ingrese los nuevos datos del movimiento:\n");
                idMovimiento = mov.id;
                mov = cargaUnMovimiento(mov.idCuenta);  // Utiliza la función existente para cargar un movimiento
                mov.id = idMovimiento;
                fseek(archi, -1 * sizeof(stMovimiento), SEEK_CUR);
                fwrite(&mov, sizeof(stMovimiento), 1, archi);
                flag = 1;
            }
        }
        fclose(archi);
    }
}

void cargaArchMovimientos(char nombreArchivo[], int idCuenta)//carga un movimiento al archivo de movimientos
{
    FILE*archi = fopen(nombreArchivo,"ab");
    stMovimiento mov;
    if(archi)
    {
        mov = cargaUnMovimiento(idCuenta);
        fwrite(&mov,sizeof(stMovimiento),1,archi);
        fclose(archi);
    }
}

int muestraArchMovimientos(char nombreArchivo[])//Muestra TODOS los movimientos ACTIVOS de un archivo
{
    FILE*archi = fopen(nombreArchivo,"rb");
    stMovimiento mov;
    int i=0;
    printf("\n=============MOVIMIENTOS ACTIVOS===============\n\n");
    if(archi)
    {
        while(fread(&mov,sizeof(stMovimiento),1,archi)>0)
        {
            if(mov.eliminado == 0)
            {
                muestraUnMovimiento(mov);
                i++;
            }
        }
        fclose(archi);
    }
    printf("\n================FIN DE ARCHIVO==================\n\n");
    return i;
}

void busquedaMovCuenta(char nombreArchivo[], int nro)//Muestra los movimientos cargado en una cuenta
{
    FILE*archi = fopen(nombreArchivo, "rb");
    stMovimiento mov;
    int cont = 0;
    if(archi)
    {
        printf("\n=============MOVIMIENTOS CUENTA N%c%d===============\n\n",167,nro);
        while(fread(&mov,sizeof(stMovimiento),1,archi)>0)
        {
            if(mov.idCuenta == nro)
            {
                muestraUnMovimiento(mov);
                cont++;
            }
        }
        printf("La cantidad de movimientos encontrados para la cuenta N%c %d es de %d\n\n",167,nro,cont);
        fclose(archi);
    }
    printf("\n================FIN DE ARCHIVO==================\n\n");
}

void busquedaMovMes(char nombreArchivo[],int mes)//Busca e imprime los movimientos de un mes en especifico
{
    FILE*archi = fopen(nombreArchivo, "rb");
    stMovimiento mov;
    int cont = 0;
    if(archi)
    {
        printf("\n=============MOVIMIENTOS DEL MES %d===============\n\n",mes);
        while(fread(&mov,sizeof(stMovimiento),1,archi)>0)
        {
            if(mov.mes == mes && mov.eliminado==0)
            {
                muestraUnMovimiento(mov);
                cont++;
            }
        }
        printf("La cantidad de movimientos encontrados en el mes %d es de %d\n", mes, cont);
        fclose(archi);
    }
    printf("\n================FIN DE ARCHIVO==================\n\n");
}

void busquedaMovAnio(char nombreArchivo[],int anio)//Busca e imprime los movimientos de un mes en especifico
{
    FILE*archi = fopen(nombreArchivo, "rb");
    stMovimiento mov;
    int cont = 0;
    if(archi)
    {
        printf("\n=============MOVIMIENTOS DEL A%cO %d===============\n\n",165,anio);
        while(fread(&mov,sizeof(stMovimiento),1,archi)>0)
        {
            if(mov.anio == anio && mov.eliminado==0)
            {
                muestraUnMovimiento(mov);
                cont++;
            }
        }
        printf("La cantidad de movimientos encontrados en el a%co %d es de %d\n",164, anio, cont);
        fclose(archi);
    }
    printf("\n================FIN DE ARCHIVO==================\n\n");
}

stMovimiento getMovimientoRandom(char nombreArchivo[])
{
    stMovimiento m;
    int idCliente = getIdClienteRandom("clientes.bin");
    if (idCliente != -1)
    {
        stCuenta cuenta = getCuentaRandom("cuentas.bin", idCliente);
        if (cuenta.id != -1)
        {
            m.idCuenta = cuenta.id;
            m.importe = rand() % 2 ? getImporteRandNegativo() : getImporteRandPositivo();
            getDetalleRand(m.detalle, m.importe);
            m.anio = 2024;
            m.mes = getMonth();
            while(m.mes>6)
            {
                m.mes = getMonth();
            }
            m.dia = getDay(m.mes);
            if(m.mes==6)
            {
                while(m.dia>24)
                {
                    m.dia = getDay(m.mes);
                }
            }

            m.eliminado = 0;
            editSaldoCuenta(AR_CUENTA, m.idCuenta, m.importe);
        }
    }
    return m;
}

int getImporteRandPositivo()// Retorna un importe random positivo
{
    int importe;
    importe = rand()%100001;
    return importe;
}

int getImporteRandNegativo()// Retorna un importe random negativo
{
    int importe;
    importe = rand()%100001;
    importe = importe * -1;
    return importe;
}

void getDetalleRand(char detalle[], int importe)
{
    char detallesNegativos[][100] = {"Alquiler", "Compra en un supermercado", "Pago de impuestos", "Gasolina", "Cena en restaurante","Pago de patente", "Compra en linea", "Entrada al cine", "Suscripcion mensual", "Servicio de transporte","Reparacion de vehiculo", "Compra de regalo", "Farmacia", "Ferreteria", "Restaurante", "Pago de transporte"};

    char detallesPositivos[][100] = {"Deposito de salario", "Transferencia", "Devolucion de compra", "Reembolso", "Bonificacion mensual","Prestamo devuelto", "Descuento aplicado", "Ingreso por venta", "Devolucion de garantia", "Beneficio de compra","Indemnizacion", "Bonificacion por cumplimiento de objetivos"};

    if (importe < 0)
    {
        strcpy(detalle, detallesNegativos[rand() % (sizeof(detallesNegativos) / sizeof(detallesNegativos[0]))]);
    }
    else
    {
        strcpy(detalle, detallesPositivos[rand() % (sizeof(detallesPositivos) / sizeof(detallesPositivos[0]))]);
    }
}


int getYear()//Retorna un anio random
{
    int num;
    num = rand()%25 + 2000;
    return num;
}

int getMonth()//Retorna un mes random
{
    int num;
    num = rand()%12+1;
    return num;
}
int getDay(int mes)//Retorna un dia random dependiendo del mes
{
    int num;
    if(mes<8 && mes%2 !=0)
    {
        num = rand()%31+1;
    }
    else if(mes<8 && mes%2==0)
    {
        num = rand()%30+1;
    }
    if(mes>7 && mes%2 == 0)
    {
        num = rand()%31+1;
    }
    else if(mes>7 && mes%2 !=0)
    {
        num = rand()%30+1;
    }
    if(mes == 2)
    {
        num = rand()%28+1;
    }
    return num;
}

void cargaMovimientosRandFile(char nombreArchivo[], int cant)//Carga una cantidad de movimientos random al archivo
{
    if(cuentaRegistrosArchivo(AR_CUENTA, sizeof(stCuenta))> 0)
    {
        FILE*archi = fopen(nombreArchivo, "ab");
        stMovimiento mov;
        int i = 0;
        int num = numeroCuentaRandom(AR_CUENTA);
        int idMovimientos = cuentaRegistrosArchivo(AR_MOVIMIENTOS, sizeof(stMovimiento));
        if(archi)
        {
            while(i<cant && num!=0)
            {
                mov = getMovimientoRandom(num);
                mov.id = idMovimientos;
                fwrite(&mov,sizeof(stMovimiento),1,archi);
                i++;
                idMovimientos++;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("ERROR: La cantidad de cuentas en el sistema es igual a 0. No es posible generar un movimiento sin cuentas");
    }


}

int numeroCuentaRandom(char nombreArchivo[]) // Retorna un numero de id de una cuenta random
{
    FILE*archi = fopen(nombreArchivo,"rb");
    int cant = cuentaRegistrosArchivo(AR_CUENTA,sizeof(stCuenta));
    stCuenta cuenta;
    int pos;
    int nro = 0;
    if(archi)
    {
        while(nro == 0 && cant!=0)
        {
            pos = rand()%cant;
            fseek(archi,pos,0);
            fread(&cuenta,sizeof(stCuenta),1,archi);
            if(cuenta.eliminado==0)
            {
                nro = cuenta.id;
            }
        }
        fclose(archi);
    }
    return nro;
}

int existeMovimiento(char archivo[], int idMovimiento)//Recibe el ID de un movimiento y si el mismo exite retorna 1, caso contrario retorna 0
{
    FILE* archi = fopen(archivo, "rb");
    int flag = 0;
    stMovimiento m;
    if(archi){
        while(flag == 0 && fread(&m, sizeof(stMovimiento), 1, archi)>0){
            if(m.id==idMovimiento && m.eliminado==0){
                flag = 1;
            }
        }

        fclose(archi);
    }
    return flag;
}

void muestraMovimientoID(char archivo[], int idMovimiento)//Recibe el id de un movimiento y si el mismo existe lo imprime en pantalla
{
   FILE* archi = fopen(archivo, "rb");
    int flag = 0;
    stMovimiento m;
    if(archi){
        while(flag == 0 && fread(&m, sizeof(stMovimiento), 1, archi)>0){
            if(m.id==idMovimiento && m.eliminado==0){
                muestraUnMovimiento(m);
                flag = 1;
            }
        }
        fclose(archi);
    }
}

