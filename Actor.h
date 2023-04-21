#include <iostream>
#include <string>
using namespace std;

class Actor{
    public:
    Actor();
    Actor(int , string);

    int getId();
    string getNombre();

    void setId(int);
    void setNombre(string);

    void muestra();

    private:
    int id;
    string nombre;
};

//Constructores
Actor::Actor(){
    id=0;
    nombre="";
}
Actor::Actor(int idP, string nombreP){
    id=idP;
    nombre=nombreP;
}

//Metodos de acceso
string Actor::getNombre(){
    return nombre;
}
int Actor::getId(){
    return id;
}

//Metodos de modificacion
void Actor::setId(int idP){
    id=idP;
}
void Actor::setNombre(string nombreP){
    nombre=nombreP;
}

//Muestra para imprimir el ID junto con el nombre de actor en forma de lista
void Actor::muestra(){
    cout<<id<<" | "<<nombre<<"\n";
}