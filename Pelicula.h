#include <iostream>
using namespace std;

class Pelicula{
    public:
    Pelicula();

    int getNumPeli();
    string getTitulo();
    int getAnio();
    int getDuracion();
    string getGenero();
    int getCantidadActores();
    int getListaActores(int);

    void setNumPeli(int);
    void setTitulo(string);
    void setAnio(int);
    void setDuracion(int);
    void setGenero(string);

    bool agregarActor(int id);

    private:
    int numPeli;
    string titulo;
    int anio;
    int duracion;
    string genero;
    int cantidadActores;
    int listaActores[10];
    int i=0;
};

//Constructor
Pelicula::Pelicula(){
    numPeli=0;
    titulo="";
    anio=0;
    duracion=0;
    genero="";
    cantidadActores=0;
    listaActores[10] = {0};
}

//Metodos de acceso
int Pelicula::getNumPeli(){
    return numPeli;
}
string Pelicula::getTitulo(){
    return titulo;
}
int Pelicula::getAnio(){
    return anio;
}
int Pelicula::getDuracion(){
    return duracion;
}
string Pelicula::getGenero(){
    return genero;
}
int Pelicula::getListaActores(int i){
    return listaActores[i];
}
int Pelicula::getCantidadActores(){
    return cantidadActores;
}

//Metodos de modificacion
void Pelicula::setNumPeli(int numPeliP){
    numPeli=numPeliP;
}
void Pelicula::setTitulo(string tituloP){
    titulo=tituloP;
}
void Pelicula::setAnio(int anioP){
    anio=anioP;
}
void Pelicula::setDuracion(int duracionP){
    duracion=duracionP;
}
void Pelicula::setGenero(string generoP){
    genero=generoP;
}

bool Pelicula::agregarActor(int idP){
    for (int i=0; i<cantidadActores; i++){ //Ciclo para ver si el id ya existe para otro actor
        if(listaActores[i]==idP){
            return false;
        }
    }
    if(cantidadActores++>10){ //Si al sumar a cantidad de actores pasa de 10 regresa falso
        return false;
    }
    else{ //Si todo lo anterior es valido se agrega el id a a lista de actores utilizando la i
        listaActores[i]=idP;
        if(i==cantidadActores){ //Se utiliza la i para evitar errores en el guardado de la lista y sumar correctamente a cantidad de actores
            cantidadActores++;
        }
        i++; //Suma a i
        return true;
    }
}
