#ifndef MOCKCLIENTES_H_INCLUDED
#define MOCKCLIENTES_H_INCLUDED

void getNameRand(char name[]);//sobreescribe en un string un nombre aleatorio
void getLastnameRand(char lastName[]);//sobreescribe en un string  un apellido aleatorio
void getDNIrand(char dni[]);//sobreescribe en un string un DNI aleatorio
void getEmail(stCliente * a);//Le asigna a un cliente un mail aleatorio en base a su apellido y nombre
void getTelRand(char tel[]);//sobreescribe en un string un numero de telefono aleatorio
stCliente getClienteRandom();//
stDomicilio getDomicilioRand();//Devuelve un domicilio aleatorio
void getCpos(char *cpos);//sobreescribe en un string  un codigo postal aleatorio
void getProvincia(char provincia[]);//sobreescribe en un string una provincia aleatoria
void getLocalidad(char localidad[]);//sobreescribe en un string una localidad aleatoria
int getNroCalle();//devuelve un numero de calle aleatorio
void getCalle(char calle[]);//sobreescribe en un string una calle aleatoria
//char* getEmailRand(stCliente a);
int cuentaRegistrosArchivo(char nombreArchivo[], int tamEstructura);


#endif // MOCKCLIENTES_H_INCLUDED
