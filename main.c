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
#include "gotoxy.h"

#define AR_CLIENTES "clientes.bin"
#define AR_CUENTA "cuentas.bin"
#define AR_MOVIMIENTOS "movimientos.bin"
#define ENTER 13
#define ESC 27
#define BACKSPACE 8

void menuPrincipal();
void printMenuPrincipal();
void listadoClientes();
void cuentasClientes();
void menuCuentas(int idCliente);
void printMenuCuentas(int id);
void altaUnaCuenta(int idCliente);
void bajaUnaCuenta();
void editarUnaCuenta();

void altaUnCliente();
void bajaUnCliente();
void editarUnCliente();
void printAltaClientes();
void altaClientes();
void menuMovimientos();
void printMenuMovimientos();
void anadirMovimiento();
void mostrarTodosMovimientos();
void mostrarMovimientosAnio();
void mostrarMovimientosMes();
void mostrarMovimientosCuenta();
void generarMovimientos();
void creditos();
void verCuentasCargadas(int idCliente);
void eliminarMovimientoMenu();
void editarMovimiento();

int main()
{
    srand(time(NULL));

    menuPrincipal();
    return 0;
}

void menuPrincipal()//Funcion que ejecuta el menu principal
{
    char opcion;//variable que reconocera la tecla que apriete el usuario
    char puntero = 175;//Puntero para navegar por el menu
    int x=49;
    int y=8;//con x e y se ajusta la posicion por defecto del puntero
    printMenuPrincipal();//se imprime el menu principal
    gotoxy(x,y);
    printf("%c", puntero);//se imprime el puntero
    int menorY=8;//se ajusta la menor posicion de Y que puede tener el puntero
    int maxY=14;//se ajusta la mayor posicion de Y que puede tener el puntero

    do
    {
        opcion = getch();//se lee la tecla que aprieta el usuario
        printMenuPrincipal();//se imprime nuevamente el menu pero esta vez con la posicion del puntero actualizada
        switch(opcion)
        {
        case ENTER://Si el usuario presiona la tecla ENTER, se seleccionara una de las siguientes opciones
            switch(y)
            {
            case 8:
                listadoClientes();
                break;
            case 9:
                cuentasClientes();
                break;
            case 10:
                altaClientes();
                break;
            case 11:
                bajaUnCliente();
                break;
            case 12:
                editarUnCliente();
                break;
            case 13:
                menuMovimientos();
                break;
            case 14:
                creditos();
                opcion=ESC;
                exit(0);
                break;
            }

        case 72: //si el usuario presiona la flecha de arriba se decrementa el valor de Y moviendo el puntero hacia arriba
            if(y>menorY)
            {
                y--;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            else //si y supera el limite menor se le asigna la posicion mayor poniendo el puntero abajo del todo
            {
                y=maxY;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            break;
        case 80:
            if(y<maxY) //si el usuario presiona la flecha de abajo se incrementa el valor de Y moviendo el puntero hacia abajo
            {
                y++;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            else //si y supera el limite mayor se le asigna la posicion menor poniendo el puntero arriba del todo
            {
                y=menorY;
                gotoxy(x, y);
                printf("%c", puntero);
            }
            break;
        case 27:
            creditos();
            opcion = ESC;
            break;
        default: //Si el usuario presiona una tecla que no sea flecha arriba, flecha abajo o enter
            gotoxy(x,y);
            printf("%c",puntero);
        }

    }
    while(opcion!=ESC);
    exit(0);
}

void printMenuPrincipal()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",176,176, 176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176);
    gotoxy(50,1);
    printf("%cBICICLETA FACIL S.A.%c",176,176);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",176,176, 176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176);

    gotoxy(1, 20);
    printf("Flecha arriba: Arriba");
    gotoxy(1, 21);
    printf("Flecha abajo: Abajo");
    gotoxy(1, 22);
    printf("ENTER: Seleccionar");
    gotoxy(1, 23);
    printf("ESC: Salir a Windows");

    gotoxy(50, 8);
    printf("%cVer listado de clientes",254);
    gotoxy(50, 9);
    printf("%cVer cuenta/s de un cliente",254);
    gotoxy(50, 10);
    printf("%cDar de alta uno o varios cliente/s",254);
    gotoxy(50, 11);
    printf("%cDar de baja un cliente",254);
    gotoxy(50, 12);
    printf("%cEditar un cliente",254);
    gotoxy(50, 13);
    printf("%cMovimientos",254);
    gotoxy(50, 14);
    printf("%cSalir del programa",254);
}

void listadoClientes()
{
    char opcion;
    system("cls");
    gotoxy(0,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(0,1);
    printf("%cLISTADO DE CLIENTES %c",240,240);
    gotoxy(0,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    gotoxy(10,3);
    printf("\nPresione BACKSPACE para volver al menu");
    printf("\n\n");
    muestraArchClientes(AR_CLIENTES);
    printf("\nPresione BACKSPACE para volver al menu");
    do
    {
        opcion = getch();

    }
    while(opcion!=BACKSPACE);

    menuPrincipal();
}

void cuentasClientes()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%c CUENTAS DE UN CLIENTE %c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    int numeroCliente;
    char opcion;
    printf("\n\nIngrese el numero de su cliente: ");
    scanf("%i", &numeroCliente);
    stCliente clientito;
    numeroCliente = bucarClientePorNro(AR_CLIENTES, numeroCliente);

    if(numeroCliente!=-1)
    {
        clientito = buscaClienteId(AR_CLIENTES, numeroCliente);
        printf("Presione ENTER para ver opciones de cuenta de ");
        buscaNombreFile(AR_CLIENTES, clientito.id);
        printf("\nPresione cualquier otra tecla para volver al menu\n");
        opcion = getch();
        if(opcion == ENTER)
        {
            menuCuentas(clientito.id);
        }
        else
        {
            menuPrincipal();
        }
    }
    else
    {
        printf("\nNo se ha encontrado un cliente con ese numero de cliente\n");
        printf("\nPresione cualquier tecla para volver al menu\n");
        opcion =getch();
        menuPrincipal();
    }


}

void menuCuentas(int idCliente)
{
    char opcion;
    char puntero = 175;

    int x=1;
    int y=8;
    printMenuCuentas(idCliente);
    gotoxy(x,y);
    printf("%c", puntero);

    int menorY=8;
    int maxY=13;

    do
    {
        opcion = getch();
        printMenuCuentas(idCliente);
        switch(opcion)
        {
        case ENTER:
            switch(y)
            {
            case 8:
                verCuentasCargadas(idCliente);
                break;
            case 9:
                anadirMovimiento();
                break;
            case 10:
                altaUnaCuenta(idCliente);
                break;
            case 11:
                bajaUnaCuenta();
                break;
            case 12:
                editarUnaCuenta();
                break;
            case 13:
                menuPrincipal();
                break;
            }

        case 72:
            if(y>menorY)
            {
                y--;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            else
            {
                y=maxY;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            break;
        case 80:
            if(y<maxY)
            {
                y++;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            else
            {
                y=menorY;
                gotoxy(x, y);
                printf("%c", puntero);
            }
            break;
        default:
            gotoxy(x,y);
            printf("%c",puntero);
        }

    }
    while(opcion!=BACKSPACE);
    menuPrincipal();
}

void printMenuCuentas(int id)
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%c      CUENTAS       %c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    gotoxy(60, 8);
    printf("Flecha arriba: Arriba");
    gotoxy(60, 9);
    printf("Flecha abajo: Abajo");
    gotoxy(60, 10);
    printf("ENTER: Seleccionar");
    gotoxy(60, 11);
    printf("BACKSPACE: Volver al menu");

    gotoxy(2,5);
    printf("Cliente: ");
    buscaNombreFile(AR_CLIENTES, id);
    gotoxy(2,6);
    printf("Numero de cliente: %i", id+1);

    gotoxy(2, 8);
    printf("%cVer Cuentas activas",254,164);
    gotoxy(2, 9);
    printf("%cA%cadir movimiento a una cuenta",254,164);
    gotoxy(2, 10);
    printf("%cDar de alta una cuenta",254);
    gotoxy(2, 11);
    printf("%cDar de baja una cuenta",254);
    gotoxy(2, 12);
    printf("%cModificar una cuenta",254);
    gotoxy(2, 13);
    printf("%cVolver al menu",254);
}

void verCuentasCargadas(int idCliente)
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cCUENTAS ACTIVAS%c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    char opcion;
    int cantidad;
    cantidad = listaCuentasPorCliente(AR_CUENTA, idCliente);
    printf("\nSe han registrado %i cuentas activas\n", cantidad);
    printf("\nPresione cualquier tecla para volver al menu de cuentas\n");
    opcion = getch();
    menuCuentas(idCliente);
}

void altaUnaCuenta(int idCliente)
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cDAR DE ALTA UNA CUENTA%c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    char opcion;
    printf("\n\n%cSeguro que desea de dar de alta una cuenta? Presione S para continuar, cualquier tecla para volver al menu\n\n",168);
    opcion = getch();

    if(opcion == 's' || opcion == 'S')
    {
        cargaArchCuentas(AR_CUENTA, idCliente);
        printf("Cuenta cargada exitosamente\n");
        printf("\nPresione cualquier tecla para volver al menu\n");
        opcion =getch();
        menuPrincipal();
    }
    else
    {
        menuPrincipal();
    }
}

void bajaUnaCuenta()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cDAR DE BAJA UNA CUENTA%c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    char opcion;
    printf("\n\n%cSeguro que desea de dar de baja una cuenta? Presione S para continuar, cualquier tecla para volver al menu\n\n",168);
    opcion = getch();

    int nroCuenta;
    stCuenta cuentita;
    if(opcion == 's' || opcion == 'S')
    {
        printf("Ingrese el n%cmero de cuenta: ", 163);
        scanf("%i", &nroCuenta);

        if(cuentaExiste(AR_CUENTA, nroCuenta)!=-1)
        {
            cuentita = buscaCuentaId(AR_CUENTA, nroCuenta);
            muestraUnaCuenta(cuentita);
            printf("%\ncSeguro que desea elminiar la cuenta?  Presione S para continuar, cualquier tecla para volver al menu\n\n", 168);
            opcion = getch();
            if(opcion == 's' || opcion == 'S')
            {
                eliminarMovimientoCuentas(AR_MOVIMIENTOS, cuentita.id);
                eliminarCuenta(AR_CUENTA, nroCuenta);
                printf("Cuenta eliminada con exito\n");
                opcion=getch();
                printf("\nPresione cualquier tecla para volver al menu\n");
                menuPrincipal();
            }
            else
            {
                menuPrincipal();
            }
        }
        else
        {
            printf("No existe una cuenta con ese numero de cuenta.\n");
            opcion=getch();
            printf("\nPresione cualquier tecla para volver al menu\n");
            menuPrincipal();
        }
    }
    else
    {
        menuPrincipal();
    }
}
void editarUnaCuenta()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cMODIFICAR UNA CUENTA%c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    char opcion;
    printf("\n\n%cSeguro que desea modificar una cuenta? Presione S para continuar, cualquier tecla para volver al menu\n\n",168);
    opcion = getch();

    int nroCuenta;
    stCuenta cuentita;
    if(opcion == 's' || opcion == 'S')
    {
        printf("Ingrese el n%cmero de cuenta: ", 163);
        scanf("%i", &nroCuenta);

        if(cuentaExiste(AR_CUENTA, nroCuenta)!=-1)
        {
            cuentita = buscaCuentaId(AR_CUENTA, nroCuenta);
            muestraUnaCuenta(cuentita);
            printf("\n\n%cSeguro que desea editar la cuenta?  Presione S para continuar, cualquier tecla para volver al menu\n\n", 168);
            opcion = getch();
            if(opcion == 's' || opcion == 'S')
            {
                modificarCuenta(AR_CUENTA, cuentita.id);
                printf("\nCuenta modificada con exito\n");
                opcion=getch();
                printf("\nPresione cualquier tecla para volver al menu\n");
                menuPrincipal();
            }
            else
            {
                menuPrincipal();
            }
        }
        else
        {
            printf("No existe una cuenta con ese numero de cuenta.\n");
            opcion=getch();
            printf("\nPresione cualquier tecla para volver al menu\n");
            menuPrincipal();
        }
    }
    else
    {
        menuPrincipal();
    }
}

void printAltaClientes()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%c   ALTA CLIENTES    %c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    gotoxy(1, 20);
    printf("Flecha arriba: Arriba");
    gotoxy(1, 21);
    printf("Flecha abajo: Abajo");
    gotoxy(1, 22);
    printf("ENTER: Seleccionar");
    gotoxy(1, 23);

    printf("BACKSPACE: Volver al menu");
    gotoxy(50, 8);
    printf("%cDar de alta un cliente manualmente",254);
    gotoxy(50, 9);
    printf("%cDar de alta X clientes aleatorios",254);
    gotoxy(50, 10);
    printf("%cVolver al menu",254);
}

void altaClientes()
{
    char opcion;
    char puntero = 175;
    int x=49;
    int y=8;
    printAltaClientes();
    gotoxy(x,y);
    printf("%c", puntero);
    int menorY=8;
    int maxY=10;

    do
    {
        opcion = getch();
        printAltaClientes();
        switch(opcion)
        {
        case ENTER:
            switch(y)
            {
            case 8:
                altaUnCliente();
                break;
            case 9:
                altaVariosClientes();
                break;
            case 10:
                menuPrincipal();
                break;
            }

        case 72:
            if(y>menorY)
            {
                y--;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            else
            {
                y=maxY;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            break;
        case 80:
            if(y<maxY)
            {
                y++;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            else
            {
                y=menorY;
                gotoxy(x, y);
                printf("%c", puntero);
            }
            break;
        default:
            gotoxy(x,y);
            printf("%c",puntero);
        }

    }
    while(opcion!=BACKSPACE);
    menuPrincipal();
}

void altaUnCliente()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cDAR DE ALTA UN CLIENTE%c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    char opcion;
    printf("\n\n%cSeguro que desea de dar de alta un cliente? Presione S para continuar, cualquier tecla para volver al menu\n\n",168);
    opcion = getch();

    if(opcion == 's' || opcion == 'S')
    {
        int flag = cargaUnClienteArchivo(AR_CLIENTES);
        if(flag)
        {
            printf("Cliente cargado exitosamente\n");
            printf("\nPresione cualquier tecla para volver al menu\n");
            opcion =getch();
            menuPrincipal();
        }
        else
        {
            printf("Ya se habia cargado un cliente con ese DNI, no puede cargar el mismo cliente dos veces.\n");
            printf("\nPresione cualquier tecla para volver al menu\n");
            opcion =getch();
            menuPrincipal();
        }

    }
    else
    {
        menuPrincipal();
    }
}

void altaVariosClientes()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240,240,240,240,240,240,240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cDAR DE ALTA CLIENTES ALEATORIOS%c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240,240,240,240,240,240,240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    char opcion;
    int cantidad;
    printf("\nIngrese cuantos clientes aleatorios desea cargar: ");
    scanf("%i", &cantidad);

    printf("\n\n%cSeguro que desea de dar de alta %i clientes aleatorios? Presione S para continuar, cualquier tecla para volver al menu\n\n",168, cantidad);
    opcion = getch();

    if(opcion == 's' || opcion == 'S')
    {
        cargaArchClientes(AR_CLIENTES, cantidad);
        printf("Se han cargado %i clientes aleatorios exitosamente. Cada cliente cuenta con 2 cuentas aleatorias\n", cantidad);
        printf("Presione cualquier tecla para volver al menu\n");
        opcion =getch();
        menuPrincipal();
    }
    else
    {
        menuPrincipal();
    }
}

void bajaUnCliente()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cDAR DE BAJA UN CLIENTE%c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    char opcion;
    printf("\n\n%cSeguro que desea de dar de baja un cliente? Presione S para continuar, cualquier tecla para volver al menu",168);
    opcion = getch();
    int numeroCliente;

    if(opcion == 's' || opcion == 'S')
    {
        gotoxy(50,10);
        printf("Ingrese el numero de su cliente: ");
        scanf("%i", &numeroCliente);
        numeroCliente = bucarClientePorNro(AR_CLIENTES, numeroCliente);
        if(numeroCliente != -1)
        {
            printf("%cSeguro que desea dar de baja este cliente? Presione S para continuar, cualquier tecla para volver al menu\n\n",168);
            opcion = getch();
            if(opcion == 's' || opcion == 'S')
            {
                //eliminarCuentaCliente(AR_CUENTA, numeroCliente);
                eliminarCliente(AR_CLIENTES, numeroCliente);
                printf("Cliente borrado exitosamente\n");
                printf("Presione cualquier tecla para volver al menu\n");
                opcion =getch();
                menuPrincipal();
            }
            else
            {
                menuPrincipal();
            }
        }
        else
        {
            printf("No existe un cliente con ese numero\n");
            printf("Presione cualquier tecla para volver al menu\n");
            opcion =getch();
            menuPrincipal();
        }
    }
    else
    {
        menuPrincipal();
    }
}

void editarUnCliente()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cEDITAR UN CLIENTE%c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    char opcion;
    printf("\n\n%cSeguro que desea editar un cliente? Presione S para continuar, cualquier tecla para volver al menu",168);
    opcion = getch();
    int numeroCliente;

    if(opcion == 's' || opcion == 'S')
    {
        gotoxy(50,10);
        printf("Ingrese el numero de su cliente: ");
        scanf("%i", &numeroCliente);
        numeroCliente = bucarClientePorNro(AR_CLIENTES, numeroCliente);
        if(numeroCliente != -1)
        {
            printf("%cSeguro que desea editar este cliente? Presione S para continuar, cualquier tecla para volver al menu\n\n",168);
            opcion = getch();
            if(opcion == 's' || opcion == 'S')
            {
                modificarCliente(AR_CLIENTES, numeroCliente);
                printf("\nCliente editado exitosamente\n");
                printf("Presione cualquier tecla para volver al menu\n");
                opcion =getch();
                menuPrincipal();
            }
            else
            {
                menuPrincipal();
            }
        }
        else
        {
            printf("No existe un cliente con ese numero\n");
            printf("Presione cualquier tecla para volver al menu\n");
            opcion =getch();
            menuPrincipal();
        }


    }
    else
    {
        menuPrincipal();
    }
}

void menuMovimientos()
{
    char opcion;
    char puntero = 175;
    int x=49;
    int y=8;
    printMenuMovimientos();
    gotoxy(x,y);
    printf("%c", puntero);
    int menorY=8;
    int maxY=16;

    do
    {
        opcion = getch();
        printMenuMovimientos();
        switch(opcion)
        {
        case ENTER:
            switch(y)
            {
            case 8:
                mostrarTodosMovimientos();
                break;
            case 9:
                mostrarMovimientosAnio();
                break;
            case 10:
                mostrarMovimientosMes();
                break;
            case 11:
                mostrarMovimientosCuenta();
                break;
            case 12:
                anadirMovimiento();
                break;
            case 13:
                generarMovimientos();
                break;
            case 14:
                editarMovimiento();
                break;
            case 15:
                eliminarMovimientoMenu();
                break;
            case 16:
                menuPrincipal();
                break;
            }

        case 72:
            if(y>menorY)
            {
                y--;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            else
            {
                y=maxY;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            break;
        case 80:
            if(y<maxY)
            {
                y++;
                gotoxy(x,y);
                printf("%c", puntero);
            }
            else
            {
                y=menorY;
                gotoxy(x, y);
                printf("%c", puntero);
            }
            break;
        default:
            gotoxy(x,y);
            printf("%c",puntero);
        }

    }
    while(opcion!=BACKSPACE);
    menuPrincipal();
}
void printMenuMovimientos()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%c   MOVIMIENTOS    %c",240,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    gotoxy(1, 20);
    printf("Flecha arriba: Arriba");
    gotoxy(1, 21);
    printf("Flecha abajo: Abajo");
    gotoxy(1, 22);
    printf("ENTER: Seleccionar");
    gotoxy(1, 23);
    printf("BACKSPACE: Volver al menu");

    gotoxy(50, 8);
    printf("%cMostrar todos los movimientos",254);
    gotoxy(50, 9);
    printf("%cMostrar movimientos por a%co",254,164);
    gotoxy(50, 10);
    printf("%cMostrar movimientos por mes",254);
    gotoxy(50, 11);
    printf("%cMostrar movimientos por n%cmero de cuenta",254, 163);
    gotoxy(50, 12);
    printf("%cA%cadir un movimiento manualmente",254, 164);
    gotoxy(50, 13);
    printf("%cGenerar movimientos aleatorios",254);
    gotoxy(50, 14);
    printf("%cEditar un movimiento",254);
    gotoxy(50, 15);
    printf("%cEliminar un movimiento",254);
    gotoxy(50, 16);
    printf("%cVolver al menu",254);
}

void anadirMovimiento()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cA%cADIR UN MOVIMIENTO%c",240, 165,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    char opcion;
    int numeroCuenta;
    printf("\n\nIngrese el n%cmero de cuenta a la que desea a%cadir un movimiento: ",163, 164);
    scanf("%i", &numeroCuenta);
    numeroCuenta = cuentaExiste(AR_CUENTA, numeroCuenta);
    if(numeroCuenta != -1)
    {
        cargaArchMovimientos(AR_MOVIMIENTOS, numeroCuenta);
        printf("\nMovimiento a%cadido con exito.\n",164);
        printf("Presione cualquier tecla para volver al menu\n");
        opcion =getch();
        menuPrincipal();
    }
    else
    {
        printf("\nNo existe una cuenta con ese numero de cuenta.\n");
        printf("Presione cualquier tecla para volver al menu\n");
        opcion =getch();
        menuPrincipal();
    }
}

void mostrarTodosMovimientos()
{
    char opcion;
    system("cls");
    gotoxy(0,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(0,1);
    printf("%cLISTADO DE MOVIMIENTOS %c",240,240);
    gotoxy(0,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);

    gotoxy(10,3);
    printf("\nPresione BACKSPACE para volver al menu");
    printf("\n\n");
    int cant;
    cant = muestraArchMovimientos(AR_MOVIMIENTOS);
    printf("Se han registrado %i movimientos activos", cant);
    printf("\nPresione BACKSPACE para volver al menu");
    do
    {
        opcion = getch();

    }
    while(opcion!=BACKSPACE);

    menuPrincipal();
}

void mostrarMovimientosAnio()
{
    char opcion;
    system("cls");
    gotoxy(0,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(0,1);
    printf("%cLISTADO DE MOVIMIENTOS POR A%cO%c",240, 165,240);
    gotoxy(0,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    int anio;
    printf("Ingrese el a%co del que desea ver los movimientos: ",164);
    scanf("%i", &anio);
    printf("\nMovimientos del a%co %i\n", 164, anio);
    gotoxy(10,3);
    printf("\nPresione BACKSPACE para volver al menu");
    printf("\n\n");
    busquedaMovAnio(AR_MOVIMIENTOS, anio);
    printf("\nPresione BACKSPACE para volver al menu");
    do
    {
        opcion = getch();

    }
    while(opcion!=BACKSPACE);

    menuPrincipal();
}
void mostrarMovimientosMes()
{
    char opcion;
    system("cls");
    gotoxy(0,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(0,1);
    printf("%cLISTADO DE MOVIMIENTOS POR MESc",240, 165,240);
    gotoxy(0,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    int mes;
    printf("Ingrese el mes del que desea ver los movimientos: ");
    scanf("%i", &mes);
    printf("\nMovimientos del mes %i\n", mes);
    gotoxy(10,3);
    printf("\nPresione BACKSPACE para volver al menu");
    printf("\n\n");
    busquedaMovMes(AR_MOVIMIENTOS, mes);
    printf("\nPresione BACKSPACE para volver al menu");
    do
    {
        opcion = getch();

    }
    while(opcion!=BACKSPACE);

    menuPrincipal();
}
void mostrarMovimientosCuenta()
{
    char opcion;
    system("cls");
    gotoxy(0,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(0,1);
    printf("%cLISTADO DE MOVIMIENTOS POR CUENTAc",240, 165,240);
    gotoxy(0,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    int nroCuenta;
    int id;
    printf("Ingrese el numero de cuenta que desea ver los movimientos: ");
    scanf("%i", &nroCuenta);
    id = cuentaExiste(AR_CUENTA, nroCuenta);
    if(id != -1)
    {
        printf("Movimientos de la cuenta nro: %i", nroCuenta);
        printf("\nPresione BACKSPACE para volver al menu");
        busquedaMovCuenta(AR_CUENTA, id);
        printf("\nPresione BACKSPACE para volver al menu");
        do
        {
            opcion = getch();

        }
        while(opcion!=BACKSPACE);
    }
    else
    {
        printf("No existe una cuenta con ese numero de cuenta.\n");
        printf("Presione cualquier tecla para volver al menu\n");
        opcion = getch();
        menuPrincipal();
    }
    menuPrincipal();
}
void generarMovimientos()
{
    char opcion;
    system("cls");
    gotoxy(0,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(0,1);
    printf("%cGENERAR MOVIMIENTOS RANDOM%c",240,240);
    gotoxy(0,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    int cantidad;
    printf("Ingrese la cantidad de movimientos aleatorios que desea generar: ");
    scanf("%i", &cantidad);
    cargaMovimientosRandFile(AR_MOVIMIENTOS, cantidad);
    printf("\nSe han generado %i movimientos aleatorios exitosamente\n", cantidad);
    printf("\nPresione cualquier tecla para volver al menu");

    opcion = getch();

    menuPrincipal();
}

void editarMovimiento()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cEDITAR UN MOVIMIENTO%c",240, 165,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    char opcion;
    int numeroMovimiento;
    printf("\n\nIngrese el n%cmero de ID del movimiento que desea modificar: ",163);
    scanf("%i", &numeroMovimiento);
    if(existeMovimiento(AR_MOVIMIENTOS, numeroMovimiento))
    {
        muestraMovimientoID(AR_MOVIMIENTOS, numeroMovimiento);
        printf("%cSeguro que desea modificar este movimiento?. Presione S para si, cualquier tecla para volver el men%c\n", 168, 163);
        opcion = getch();
        if(opcion == 's' || opcion == 'S')
        {
            modificarMovimiento(AR_MOVIMIENTOS, numeroMovimiento);
            printf("\nMovimiento modificado con exito\n");
            printf("Presione cualquier tecla para volver al men%c\n", 163);
            opcion = getch();
            menuPrincipal();
        }
        else
        {
            menuPrincipal();
        }
    }
    else
    {
        printf("No existe un movimiento con ese n%cmero de ID\n", 163);
        printf("Presione cualquier tecla para volver al men%c\n", 163);
        opcion = getch();
        menuPrincipal();
    }
}

void eliminarMovimientoMenu()
{
    system("cls");
    gotoxy(50,0);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    gotoxy(50,1);
    printf("%cDAR DE BAJA UN MOVIMIENTO%c",240, 165,240);
    gotoxy(50,2);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",240,240,240,240, 240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240,240);
    char opcion;
    int numeroMovimiento;
    printf("\n\nIngrese el n%cmero de ID del movimiento que desea dar de baja: ",163);
    scanf("%i", &numeroMovimiento);
    if(existeMovimiento(AR_MOVIMIENTOS, numeroMovimiento))
    {
        muestraMovimientoID(AR_MOVIMIENTOS, numeroMovimiento);
        printf("%cSeguro que desea dar de baja este movimiento?. Presione S para si, cualquier tecla para volver el men%c\n", 168, 163);
        opcion = getch();
        if(opcion == 's' || opcion == 'S')
        {
            eliminarMovimiento(AR_MOVIMIENTOS, numeroMovimiento);
            printf("\nMovimiento dado de baja con exito\n");
            printf("Presione cualquier tecla para volver al men%c\n", 163);
            opcion = getch();
            menuPrincipal();
        }
        else
        {
            menuPrincipal();
        }
    }
    else
    {
        printf("No existe un movimiento con ese n%cmero de ID\n", 163);
        printf("Presione cualquier tecla para volver al men%c\n", 163);
        opcion = getch();
        menuPrincipal();
    }
}

void creditos()
{
    system("cls");
    gotoxy(40,5);
    printf("Gracias por usar nuestro programa :)");
    gotoxy(40, 10);
    printf("DESARROLADORES");
    gotoxy(40,11);
    printf("%cMac Guire Tomas", 254);
    gotoxy(40,12);
    printf("%cMedina Giugni Sof%ca", 254, 161);
    gotoxy(40,13);
    printf("%cMorales Cuevas Luciano", 254);
    gotoxy(40,14);
    printf("%cPardo Sim%cn", 254, 162);
    Sleep(3000);
    system("cls");
}
