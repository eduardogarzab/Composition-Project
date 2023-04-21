#include <iostream>
using namespace std;

//Hh se refiere a Hora
//Mm se refiere a Minuto

class Hora{
    public:
    Hora();
    Hora(int , int);

    int getMm();
    int getHh();

    void setMm(int);
    void setHh(int);
    
    void muestra();

    private:
    int mm; //minuto
    int hh; //hora
};

//Constructores
Hora::Hora(){
    mm=0;
    hh=0;
}
Hora::Hora(int mmP, int hhP){
    mm=mmP;
    hh=hhP;
}

//Metodos de acceso
int Hora::getHh(){
    return hh;
}
int Hora::getMm(){
    return mm;
}

//Metodos de modificacion
void Hora::setMm(int mmP){
    mm=mmP;
}
void Hora::setHh(int hhP){
    hh=hhP;
}

//Muestra para imprimir correctamente la hora y minutos
void Hora::muestra(){
    if (hh < 10 or hh==0)
        cout<<"0"<<hh<<":";
    else
        cout<<hh<<":";
    
    if (mm<10 or hh==0)
        cout<<"0"<<mm<<"\n";
    else 
        cout<<mm<<"\n";
}