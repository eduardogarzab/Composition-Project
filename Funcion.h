#include <iostream>
using namespace std;
#include"Hora.h"

class Funcion{
    public:
    Funcion();
    Funcion(string, int, int, Hora);

    int getSala();
    int getNumPeli();
    string getCveFuncion();
    Hora getHora();

    void setSala(int);
    void setNumPeli(int);
    void setCveFuncion(string);
    void setHora(Hora);

    void muestra();

    private:
    int sala;
    int numPeli;
    string cveFuncion;
    Hora hora;
};

//Constructores
Funcion::Funcion(){
    sala=0;
    numPeli=0;
    cveFuncion="";
    Hora paso;
    paso.setHh(-1);
    paso.setMm(-1);
    hora=paso;
}
Funcion::Funcion(string cve, int salaP, int numPeliP, Hora horaP){
    cveFuncion=cve;
    sala=salaP;
    numPeli=numPeliP;
    hora=horaP;
}

//Metodos de acceso
int Funcion::getSala(){
    return sala;
}
int Funcion::getNumPeli(){
    return numPeli;
}
string Funcion::getCveFuncion(){
    return cveFuncion;
}
Hora Funcion::getHora(){
    return hora;
}

//Metodos de modificacion
void Funcion::setSala(int salaP){
    sala=salaP;
}
void Funcion::setNumPeli(int numPeliP){
    numPeli=numPeliP;
}
void Funcion::setCveFuncion(string cve){
    cveFuncion=cve;
}
void Funcion::setHora(Hora horaP){
    hora=horaP;
}

//Muestra para imprimir todos los datos acerca de la funcion 
void Funcion::muestra(){
    cout<<"La funcion con la clave "<<cveFuncion<<" tiene la pelicula "<<numPeli<<" y esta disponible en la sala "<<sala<<" a las ";
    hora.muestra();
}