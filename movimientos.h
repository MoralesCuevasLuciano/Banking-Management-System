#ifndef MOVIMIENTOS_H_INCLUDED
#define MOVIMIENTOS_H_INCLUDED

typedef struct
{
    int id; /// campo único y autoincremental
    int idCuenta; /// Id de la cuenta
    char detalle[100];
    float importe;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int eliminado; /// 0 si está activo - 1 si está eliminado
} stMovimiento;

stMovimiento cargaUnMovimiento();//Funcion para cargar un movimiento manual
void muestraUnMovimiento(stMovimiento m);//funcion para mostrar un movimiento
void eliminarMovimiento(char nombreArchivo[], int id);//Funcion para eliminar un movimiento
void eliminarMovimientoCuentas(char nombreArchivo[], int idCuenta);//Funcion para eliminar los movimientos de una cuenta
void modificarMovimiento(char nombreArchivo[], int id);//Funcion para modificar un movimiento
void cargaArchMovimientos(char nombreArchivo[], int idCuenta);//carga un movimiento al archivo de movimientos
int muestraArchMovimientos(char nombreArchivo[]);//Muestra TODOS los movimientos ACTIVOS de un archivo
void busquedaMovCuenta(char nombreArchivo[], int nro);//Muestra los movimientos cargado en una cuenta
void busquedaMovMes(char nombreArchivo[],int mes);//Busca e imprime los movimientos de un mes en especifico
void busquedaMovAnio(char nombreArchivo[],int anio);//Busca e imprime los movimientos de un anio en especifico
stMovimiento getMovimientoRandom(char nombreArchivo[]);// Retorna un movimiento random
int getImporteRandPositivo();// Retorna un importe random positivo
int getImporteRandNegativo();// Retorna un importe random negativo
void getDetalleRand(char detalle[], int importe);//Retorna un detalle random dependiendo si el saldo es negativo o positivo
int getYear();//Retorna un anio random
int getMonth();//Retorna un mes random
int getDay(int mes);//Retorna un dia random dependiendo del mes
void cargaMovimientosRandFile(char nombreArchivo[], int cant);//Carga una cantidad de movimientos random al archivo
int numeroCuentaRandom(char nombreArchivo[]); // Retorna un numero de cuenta random
int randomRango (int min, int max);//funcion que retorna un numero aleatorio entre MIN y MAX
int validarAnio(int num); //Funcion para validar el anio
int getIdClienteAleatorio(char nombreArchivo[]); //Devuelve un id aleatorio
int existeMovimiento(char archivo[], int idMovimiento);//Recibe el ID de un movimiento y si el mismo exite retorna 1, caso contrario retorna 0
void muestraMovimientoID(char archivo[], int idMovimiento);//Recibe el id de un movimiento y si el mismo existe lo imprime en pantalla


#endif // MOVIMIENTOS_H_INCLUDED
