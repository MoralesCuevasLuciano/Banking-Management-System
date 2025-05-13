#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domicilio.h"
#include "clientes.h"
#include "time.h"
#include "malloc.h"
#include <ctype.h>

#define AR_CLIENTES "clientes.bin"
int cuentaRegistrosArchivo(char nombreArchivo[], int tamEstructura);


void getNameRand(char name[])
{
    char names[][30]= {"Juan", "Maria", "Sofia", "Laura", "Isabel", "Carmen", "Pedro", "Ana", "Lucia", "Luisa", "Elena", "Rosa", "Natalia", "Patricia", "Julia", "Clara", "Diana", "Javier", "Miguel", "David", "Alejandro", "Jorge", "Pablo", "Jose", "Silvia", "Martina", "Andrea", "Beatriz", "Cristina", "Paula", "Sara", "Raquel", "Alejandra", "Antonio", "Fernando", "Roberto", "Ricardo", "Daniel", "Emilio", "Federico", "Gerardo", "Hector", "Ivan", "Kevin", "Manuel", "Nelson", "Oscar", "Rodrigo"};
    strcpy(name,names[rand()%(sizeof(names)/30)]);
}

void getLastnameRand(char lastName[])
{
    char lastNames[][30]= {"Gomez", "Fernandez", "Perez", "Gonzalez", "Rodriguez", "Lopez", "Martinez", "Sanchez", "Perez", "Martin", "Garcia", "Diaz", "Hernandez", "Alvarez", "Torres", "Ruiz", "Jimenez", "Moreno", "Munoz", "Romero", "Alonso", "Gutierrez", "Navarro", "Iglesias", "Serrano", "Marquez", "Cano", "Cortes", "Castillo", "Herrera", "Aguilar", "Flores", "Vargas", "Ramos", "Ortega", "Nunez", "Medina", "Vicente", "Fuentes", "Cabrera", "Reyes", "Tomas", "Santos", "Calvo", "Vidal", "Lorenzo", "Mora", "Pardo"};
    strcpy(lastName, lastNames[rand()%(sizeof(lastNames)/30)]);
}

void getDNIrand(char dni[])
{
    dni[0]= '1' + rand()%3;
    for(int i=1; i<8; i++)
    {
        dni[i]= '0' + rand()%9;
    }
    dni[8] = '\0';
}

void getEmail(stCliente * a)
{
    char mail[50]="";
    char dominio[]="@gmail.com";
    strcat(mail,a->nombre);
    strcat(mail,a->apellido);
    strcat(mail,dominio);

    strcpy(a->email, mail);
}

//char* getEmailRand(stCliente * a){ ///ESTA NO
//
//    char* mail= (char*)malloc(51*sizeof(char));
//    char dominio[]="@gmail.com";
//    strcat(mail,a->nombre);
//    strcat(mail,a->apellido);
//    strcat(mail,dominio);
//
//    return mail;
//
//}

void getTelRand(char tel[])
{
    tel[0]='2';
    tel[1]='2';
    tel[2]='3';
    tel[3]='0'+rand()%4+3;
    for(int i=4; i<10; i++)
    {
        tel[i]='0'+rand()%9;
    }
    tel[10] = '\0';
}

void getCalle(char calle[])
{
    char calles[][50] = {"Avenida Constitucion", "Boulevard Maritimo", "Calle San Martin", "Avenida Colon", "Avenida Luro", "Calle Guemes", "Avenida Independencia", "Calle Mitre", "Avenida Juan B. Justo", "Calle Alvarado", "Avenida Jara", "Calle 20 de Septiembre", "Avenida de los Trabajadores", "Calle Rawson", "Avenida Champagnat", "Calle Roca", "Avenida Fortunato de la Plaza", "Calle Brown", "Avenida Edison", "Calle Garay", "Avenida Mario Bravo", "Calle Alvear", "Avenida Juan B. Justo", "Calle Chile", "Avenida Pedersen", "Calle San Lorenzo", "Avenida Libertad", "Calle España", "Avenida Peralta Ramos", "Calle Alberti"};

    strcpy(calle, calles[rand()%30]);
}

int getNroCalle()
{
    return(rand()%9999-100);
}

void getLocalidad(char localidad[])
{
    char localidades[][40]= {"Ushuaia", "Rio Grande", "Rawson", "Resistencia", "Catamarca", "San Salvador", "La Rioja", "Mendoza", "Posadas", "Neuquen", "Viedma", "Salta", "San Juan", "San Luis", "Santa Rosa", "Santiago del Estero", "San Miguel de Tucuman", "Parana", "Santa Fe", "Bariloche", "San Rafael", "Merlo", "Rawson"};

    strcpy(localidad, localidades[rand()%20+1]);
}

void getProvincia(char provincia[])
{
    char provincias[][40]= {"Buenos Aires", "Catamarca", "Chaco", "Chubut", "Cordoba", "Corrientes", "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones", "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe", "Santiago del Estero", "Tierra del Fuego", "Tucuman"};

    strcpy(provincia, provincias[rand()%22+1]);
}

void getCpos(char *cpos)
{
    char *codigos[] = {"1000", "5000", "2000", "5500", "4000", "1900", "7600", "4400", "3000", "5400"};
    strcpy(cpos, codigos[rand() % (sizeof(codigos) / sizeof(codigos[0]))]);
}


stDomicilio getDomicilioRand()
{
    stDomicilio a;
    getCalle(a.calle);
//    strcpy(a.calle,"calle 1");
    a.nro = rand()%9999+100;
    getLocalidad(a.localidad);
    getProvincia(a.provincia);
    getCpos(a.cpos);

    return a;
}

stCliente getClienteRandom()
{
    stCliente c;
    c.id= cuentaRegistrosArchivo(AR_CLIENTES, sizeof(stCliente));
    c.nroCliente= c.id+1;
    getNameRand(c.nombre);
    getLastnameRand(c.apellido);
    getDNIrand(c.dni);
    getEmail(&c);
    getTelRand(c.tel);
    c.eliminado=0;
    c.domicilio = getDomicilioRand();


    return c;
}

int cuentaRegistrosArchivo(char nombreArchivo[], int tamEstructura)
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




