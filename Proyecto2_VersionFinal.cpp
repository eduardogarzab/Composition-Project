//Proyecto Programacion Orientada a Objetos
//Eduardo Garza Briceño #611441

/*Aclaraciones
Para validar que las horas, ids, numeros, etc fueran realmente solo numeros y el programa no se cicle se preguntaron y guardaron
en un string para despues de eso ese string validarlo mediante la funcion validarNum que revisara cada caracter del string si es numero
en caso de que solo sean numeros regresara true y luego en el main se convertira a int para no afectar el programa.

Tambien importante mecionar que para guardar los datos de las peliculas decidi convertir la linea a un objeto mediante istringstream
ya que estuve investigando y es una manera muy sencilla y mucho as comoda de guardar datos de una linea a variables por lo que decidi
implementarla de esa manera en el programa, no obstante para demostrar que puedo hacerlo con los conocimientos aprendidos en clase
voy a poner el codigo que se utilizaria o el esqueleto del codigo que se utilizaria para guardar los datos a variables utilizando
substr, finds, erase, etc.

PARA NUMEROS INT
espacio=linea.find(" "); //Buscar el primer espacio y lo guarda en la variable espacio
numPeli/año/duracion/cantidadActores/IDs=stoi(linea.substr(0,espacio)); //Hacer un substr desde el inicio hasta uno antes del espacio que seria solo el numero y convertirlo a int
linea.erase(0, espacio+1); //Borrar el numero y espacio siguiente del numero que ya se guardo
REPETIR EL PROCESO PARA EL SIGUIENTE NUMERO INT

PARA UNA UNICA PALABRA
espacio=linea.find(" "); //Buscar el primer espacio y lo guarda en la variable espacio
genero=linea.substr(0,espacio); //Hacer un substr desde el inicio hasta uno antes del espacio que seria solo la palabra del genero
linea.erase(0, espacio+1); y se vuelve a borrar lo que ya se guardo

PARA EL TITULO
Como ya es lo ultimo que nos quedaria ya que guardo todo en variables y se elminaros los demas datos entonces linea seria directamente el titulo
y lo unico que faltaria seria mandar los datos al arreglo de peliculas.
*/

#include<iostream>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;

//Clases utilizadas
#include "Actor.h"
#include "Funcion.h"
#include "Pelicula.h"

//Declaracion de variable global para poder preguntar en el menu la opcion
char opcion;

//Funcion para validar que al preguntar por numeros al usuarios sean unicamente numeros y no letras y evitar que el programa se cicle
bool validarNum(string s){
    //Solo numeros enteros
    int n = s.length(); //Se obtiene la longitud del string
    char char_array[n + 1]; //Se crea un array de char del tama;o del string + 1 para poder guardar el caracter nulo al final
    strcpy(char_array, s.c_str()); //Se copia el contenido del string al array
 
    for (int i= 0; i < n; i++){ //Se usa un ciclo para vericar que cada caracter sea un digito con la funcion isdigit
        if ((isdigit(char_array[i])==false)){ //Si no es un digito regresa falso
            return false;
        }
    }   
    return true;
}

//Funciones del programa
void mostrarMenu(){ //Funcion que imprime el menu y pregunta la opcion que desea
  cout << "\nMenu\na) Consulta de todos los actores que estan en la lista\nb) Consulta de todas las peliculas que estan en la lista\nc) Consulta de todas las funciones disponibles\nd) Consulta de funciones por hora\ne) Consulta por clave de funcion\nf) Consulta la lista peliculas en las que participa un actor\ng) Terminar\n\nSelecciona una opcion: " << endl;
  cin >> opcion;
}
void ConsultaActores(Actor arActor[], int numAct){ //La funcion imprime los IDs y nombres de todos los actores que se leyeron del archivo .txt
    cout<<"\nLos actores dados de alta son: \n"<<endl;
    for(int i=0; i<numAct; i++){ //Ciclo para recorrer el array e imprimir el id y nombre de los actores
        arActor[i].muestra();
    }
}
void ConsultaPeliculas(Pelicula arPelicula[], Actor arActor[], int numPeli, int numAct){ //La funcion imprime todas las peliculas leidas del .txt
    
    int cantidadActores, actor; //Variables

    cout<<"\nLas peliculas que estan en la lista son: "<<endl;
    for(int i=0; i<numPeli; i++){ //Ciclo for para imprimir las peliculas dadas de alta
        cout<<endl;
        cout<<arPelicula[i].getTitulo()<<endl; //Se imprime el titulo de la pelicula
        cout<<"Anio: "<<arPelicula[i].getAnio()<<endl; //Se imprime el anio
        cout<<"Duracion: "<<arPelicula[i].getDuracion()<<" min"<<endl; //Se imprime la duracion
        cout<<"Genero: "<<arPelicula[i].getGenero()<<endl; //Se imprime el genero
        cout<<"Los actores que participan son: "<<endl; 
        cantidadActores=arPelicula[i].getCantidadActores(); //Se obtiene la cantidad de actores
        for(int j=0; j<cantidadActores; j++){ //Ciclo para imprimir los actores que participan
            actor=arPelicula[i].getListaActores(j); //Se obtiene el ID del actor desde lista de actores
            for(int k=0; k<numAct; k++){ //Ciclo para comparar el ID obtenido de la lista con los dados de alta del .txt cuando coincida uno y sean iguales se imprime
                if(arActor[k].getId()==actor){
                    arActor[k].muestra();
                }
            }
        }
    }
}
void ConsultaFunciones(Funcion arFuncion[], Pelicula arPelicula[], int numFunc, int numPeli){ //La funcion imprime las funciones dadas de alta segun el numero de funciones que se dieron
    for(int i=0; i<numFunc; i++){ //Ciclo para recorrer todo el array de funciones e imprimirlas hasta que llegue a el numero de funciones ingresadas
        cout<<endl;
        arFuncion[i].muestra(); //Se imprimen las funciones con muestra de la clase
        for (int k=0; k<numPeli; k++){ //Se hace un cilo para comparar el numero de pelicula que se dio de alta en la funcion con los leidos del .txt de peliuclas
            if(arFuncion[i].getNumPeli()==arPelicula[k].getNumPeli()){ //Si coincide alguno se imprime el titulo y sala en la que esta.
                cout<<"- Pelicula: "<<arPelicula[k].getTitulo()<<endl;
            }
        }
    }
}
void ConsultaHora(Pelicula arPelicula[], Funcion arFuncion[], int numFunc, int numPeli){ //El usuario da una hora y minuto, se muestran las peliculas y salas que se presentan en esa hora
    //Variables
    string numTemp;
    int hora=-1, minuto=-1, horaFuncion, minutoFuncion;
    bool hayHora=false, valido=false;

    //Ciclo para validar la hora y minutos proporcionados
    while(valido==false){
        do{
            cout<<"\nDame la hora que deseas buscar: ";
            cin>>numTemp; //Se pregunta la hora y se guarda en string
            valido=validarNum(numTemp); //Se valida que solo sean numeros
            if(valido==false){ //Si no son solo numeros se indica y vuelve a preguntar
                cout<<"Ingresa solo numeros enteros."<<endl;
            }
        }while(valido==false);

        hora=stoi(numTemp); //Ya que se valido se convierte a int
        if (hora>23 || hora<0){ //Se valida que este entre 0 y 23
            cout<<"La hora no es valida, debe estar entre 0 y 23."<<endl;
            valido=false;
        }
    }

    valido=false; //Se reinicia valido a false para repetir el proceso pero en este caso con los minutos
    while(valido==false){
        do{
            cout<<"\nDame el minuto que deseas buscar: ";
            cin>>numTemp; //SE preunta en string 
            valido=validarNum(numTemp); //Se valida si solo son numeros
            if(valido==false){ //Si no son solo numeros se indica
                cout<<"Ingresa solo numeros enteros."<<endl;
            }
        }while(valido==false);

        minuto=stoi(numTemp); //Ya que se valido se convierte a int
        if (minuto>59 || minuto<0){ //Se valida que este entre 0 y 59
            cout<<"Los minutos no son validos, debe estar entre 0 y 59."<<endl;
            valido=false;
        }
    }

    for(int i=0; i<numFunc; i++){ //Ciclo for para comparar la hora y minuto dada por el usuario con las leidas del archivo .txt
        if(arFuncion[i].getHora().getHh()==hora && arFuncion[i].getHora().getMm()==minuto){ //Si la hora y minuto son iguales
            for (int k=0; k<numPeli; k++){ //Se hace un cilo para comparar el numero de pelicula que se dio de alta en la funcion con los leidos del .txt de peliuclas
                if(arFuncion[i].getNumPeli()==arPelicula[k].getNumPeli()){ //Si coincide alguno se imprime el titulo y sala en la que esta.
                    cout<<"\nPelicula: "<<arPelicula[k].getTitulo()<<endl;
                    cout<<"Disponible en: "<<endl;
                    cout<<"Sala "<<arFuncion[i].getSala()<<endl;
                    hayHora=true; //Si la hora y minuto coincide se hace true
                }
            }
        }
    }
    if(hayHora==false) //Si no coincide ninguna se avisa al usuario y regresa al menu principal
        cout<<"\nNo hay ninguna funcion en la hora dada."<<endl;
}
void ConsultaClave(Actor arActor[], Pelicula arPelicula[], Funcion arFuncion[], int numAct, int numPeli, int numFunc){ //Segun la clave proporcionada por el usuario se imprime la funcion, pelicula y actores que participan
    //Variables
    string clave;
    bool valido=false;
    int actor, cantidadActores;

    while(valido==false){ //Ciclo para validar que la clave exista
        cout<<"\nQue clave deseas buscar? ";
        cin>>clave;

        for(int i=0; i<numFunc; i++){ //Ciclo for para revisar todo el array y ver si alguna clave coincide con la proporcionada por el usuario
            if(clave==arFuncion[i].getCveFuncion()){
                valido=true;
            }
        }
        if(valido==false){ //Si no coincidio ninguna se avisa al usuario y se le vuelve a preguntar
            cout<<"No hay ninguna funcion con la clave proporcionada, porfavor intenta de nuevo."<<endl;
            cout<<"\nLas funciones dadas de alta son: "<<endl;
            ConsultaFunciones(arFuncion, arPelicula, numFunc, numPeli); //Se llama a la funcion que imprime todas las funciones para evitar que la persona se quede ciclada sin saber que clave usar
        }
    }
    
    //Variables de los for
    //arFuncion-------i
    //arPelicula------k
    //listadeactores--j
    //arActor---------l

    for(int i=0; i<numFunc; i++){ //Ciclo para accesar a el arreglo de funciones

        if(clave==arFuncion[i].getCveFuncion()){ //Si la clave coincide sigue, si no pasa a la siguiente funcion
            //Si la clave coincide se imprimen los datos de la funcion
            cout<<endl;
            arFuncion[i].muestra();
            
            for (int k=0; k<numPeli; k++){ //Ciclo para arPeliculas

                if(arFuncion[i].getNumPeli()==arPelicula[k].getNumPeli()){ //Si el numro de pelicula coincide se imprimen los datos
                    cout<<"Pelicula: "<<arPelicula[k].getTitulo()<<endl;
                    cout<<"Genero: "<<arPelicula[k].getGenero()<<endl;
                    cout<<"Duracion: "<<arPelicula[k].getDuracion()<<" min"<<endl;
                    cout<<"Los actores que participan son: "<<endl;
                    cantidadActores=arPelicula[k].getCantidadActores(); 

                    for(int j=0; j<cantidadActores; j++){ //Se obtiene el ID de los actores que participan en esa pelicula
                        actor=arPelicula[k].getListaActores(j);

                        for(int l=0; l<numAct; l++){ //Ciclo para comparar el ID que participa en la pelicula con los leidos del archivo para imprimir los que coincidan
                            if(arActor[l].getId()==actor){//Si el id es el mismo que el guardado se imprime mediante muestra
                                arActor[l].muestra();
                            }
                        }
                    }
                }
            }
        }
    }
}
void ConsultaListaPeliActor(Actor arActor[], Pelicula arPelicula[], int numAct, int numPeli){ //Funcion para imprimir las peliculas en las que participa un actor segun el id que haya dado el usuario
    //Variables
    string numTemp;
    int id, actor;
    bool valido=false, participa=false;
    
    //Se llama a la funcion que imprime los actores, por si el usuario no sabe el ID del actor que quiere buscar
    ConsultaActores(arActor, numAct);
    while(valido==false){ //Ciclo para validar que el ID proporcionado por el usuario coincida con uno leido del archivo .txt y sean solo numeros
        
        while(valido==false){ //Mientras valido sea falso va a validar que sea un numero
            cout<<"\nDame el ID del actor que deseas buscar: ";
            cin>>numTemp; //Pide el numero en string (temporal)
            valido=validarNum(numTemp); //La funcion arroja true o false segun si son solo numeros o no
            if(valido==false){ //Si no son solo numeros se indica y vuelve a preguntar
                cout<<"Ingresa solo numeros enteros."<<endl;
            }
        }

        valido=false; //Se reinicia valido a false para seguir validando
        id=stoi(numTemp); //Ya que se valido que sean solo numeros ahora si se pasa a int

        for(int i=0; i<20; i++){ //Ciclo para validar que el id exista
            if(arActor[i].getId()==id){ //Se revisa si coincide con uno leido del archivo
                valido=true;
                cout<<"\nEl actor seleccionado es "<<arActor[i].getNombre()<<endl;
            }
        }

        if(valido==false){ //Si no coincide el id se indica
            cout<<"El id no coincide con ningun actor, porfavor vuelve a ingresarlo."<<endl;
        }

    }
    //Si el ID fue valido se imprime las peliculas en las que participa
    cout<<"Peliculas en las que participa: "<<endl;
    for (int i=0; i<numPeli; i++){ //Ciclo para las peliculas
        for(int k=0; k<arPelicula[i].getCantidadActores(); k++){ //Ciclo para recorrer la lista de actores de esa pelicula
            actor=arPelicula[i].getListaActores(k); //Se guarda el ID en actor
            if(actor==id){ //Si el ID coincide se imprime el titulo y anio de la pelicula en la que el actor participa
                cout<<"- "<<arPelicula[i].getTitulo()<<" del anio "<<arPelicula[i].getAnio()<<endl;
                participa=true; //Participa se cambia a true ya que si participa en alguna pelicula
            }
        }
    }
    if(participa==false){ //Si participa no se cambio a true imprime
        cout<<"- El actor no participa en ninguna pelicula dada de alta"<<endl;//Imprime que no participa
    }
}

int main(){
    system("CLS"); //Borrar pantalla para que se inicie en limpio

    //Declaracion de arreglos de objetos
    Actor arActor[20];
    Funcion arFuncion[20];
    Pelicula arPelicula[20];

    //Declaracion de Variables
    ifstream archivoEntrada;
    string linea, nombre, claveFun, genero, titulo, numTemp;
    int i=0, ID, espacio, numPeli, hora, minuto, numSala, numFunciones, numPelicula, anio, duracion, cantidadActores, numeroActores=0, numeroPeliculas=0;
    bool valido=false;
    Hora horaClase;

    archivoEntrada.open("Actores.txt"); //Se abre el archivo .txt del cual se extraeran los datos de los actores
    for(int i=0;i<20;i++){ //Ciclo for para leer todos los actores del archivo
        getline(archivoEntrada, linea); //Leer toda la linea y guardarla en linea

        espacio=linea.find(" "); //Buscar el primer espacio y guardarlo en la variable espacio
        ID=stoi(linea.substr(0,espacio)); //El ID sera del incio de la linea hasta el espacio encontrado, asimismo se convierte a int ya que estaba en string
        nombre=linea.substr(espacio+1); //El nombre se extrae como substring a partir de el lugar de espacio mas 1

        arActor[i].setId(ID); //Se guarda el ID en el array
        arActor[i].setNombre(nombre); //Se guarda el nombre en el ID
        numeroActores++;
    }
    archivoEntrada.close(); //Se cierra el archivo

    archivoEntrada.open("Peliculas.txt"); //Se abre el archivo .txt del cual se extraeran los datos de las peliculas
    while (getline(archivoEntrada, linea)){ //Ciclo para leer todo el archivo linea por linea

        istringstream ss(linea); //Se crea un objeto de la linea con la finalidad de extraer los datos de esa linea de una manera mas sencilla, evitando substr, finds, erases, etc.
        ss >> numPelicula >> anio >> duracion >> genero >> cantidadActores; //Se leen todos los datos de la pelicula hasta el genero y se guardan en una variable
        for (int j=0;j<cantidadActores;j++){ //Ciclo for, segun la cantidad de actores va a leer el id del actor de la linea del archivo la guarda en ID y lo manda al array por medio de agregar actor
            ss >> ID;
            arPelicula[i].agregarActor(ID);
        }
        getline(ss, titulo); //Se obtiene el titulo con un getline y como toma los espacio incluido el del inicio se elimina el primer espacio para que no haya antes de la primer palabra
        titulo=titulo.erase(0,1);
        
        //Se guardan todos los datos
        arPelicula[i].setNumPeli(numPelicula);
        arPelicula[i].setAnio(anio);
        arPelicula[i].setDuracion(duracion);
        arPelicula[i].setGenero(genero);
        arPelicula[i].setTitulo(titulo);
        
        //Se le suma 1 a i para que la siguiente pelicula se guarde en el siguiente array y vuelve a empezar el ciclo
        i++;
        numeroPeliculas++;
    }
    archivoEntrada.close();

    //Se pregunta cuantas funciones quiere ingresar y se valida que sean mayor a 0 y menor a 21
    do{
        cout<<"Cuantas funciones quieres ingresar? ";
        cin>>numTemp;

        valido=validarNum(numTemp);
        if(valido==true){
            numFunciones=stoi(numTemp);
            if(numFunciones<1 or numFunciones>20){
                cout<<"El numero de funciones es invalido. Ingrese un numero del 1 al 20.\n"<<endl;
                valido=false;
            }
        }
        else{
            cout<<"El numero de funciones es invalido. Ingrese un numero del 1 al 20.\n"<<endl;
        }

    }while(valido==false);

    //Ciclo for para preguntar los datos de las funciones segun la cantidad de funciones que decide ingresar
    for(int i=0; i<numFunciones; i++){   

        /*En esta parte los datos se preguntas y se guardan en un string, para seguido de esto llamar a la funcion validarNum que revisara que el string contenga unicamente
        numeros enteros para asi evitar que el programa se cicle al recibir una letra u otra cosa que no sea un numero entero.*/

        do {
            cout<<"\nDame la clave de la funcion "<<i<<": "; //Pregunta la clave de la funcion 
            cin>>claveFun;
            
            valido=true;
            for (int j = 0; j < i; j++) { //Ciclo for para validar que la clave no se repita para alguna otra funcion, ya que en este caso decidi que fuese una clave unica
                if (claveFun == arFuncion[j].getCveFuncion()) {
                    valido=false;
                    cout<<"La clave "<< claveFun<< " ya existe para otra funcion. Intente de nuevo."<<endl;
                    break;
                }
            }
        }while(!valido);

        do{
            cout<<"Dame el numero de pelicula "<<i<<": "; //Pregunta el numero de pelicula
            cin>>numTemp;
            valido=validarNum(numTemp);
            if(valido==true){
                valido=false;
                numPeli=stoi(numTemp);
                for (int k = 0; k < 10; k++) { //Ciclo for para ver si el numero coincide con uno de los obtenidos del archivo .txt de peliculas
                    if (numPeli==arPelicula[k].getNumPeli()) {
                        valido=true;
                        break;
                    }
                }
                if(!valido){ //Si no existe el numero de pelicula se le dice el error y se muestra el catalogo de peliculas con su numero para evitar que tenga que salir a revisar los numeros
                    cout<<"Numero de pelicula invalido. Ingrese uno que corresponda con el catalogo.\n"<<endl;
                    cout<<"Num\tPelicula"<<endl;
                    for(int i=0; i<20; i++){
                        if(arPelicula[i].getTitulo()!=""){
                            cout<<arPelicula[i].getNumPeli()<<"\t"<<arPelicula[i].getTitulo()<<endl;
                        }
                    }
                    cout<<endl;
                }
            }
            else{
                cout<<"Numero de pelicula invalido. Ingrese solamente numeros.\n"<<endl;
            }
        }while(!valido);

        do{
            cout<<"Dame la hora de la funcion "<<i<<": "; //Pregunta la hora
            cin>>numTemp;

            valido=validarNum(numTemp);
            if(valido==true){
                valido=false;
                hora=stoi(numTemp);
                if (hora<0 || hora>23) { //Se valida que sea mayor o igual a 0 y que sea menor o igual a 23
                    cout<<"La hora debe estar entre 0 y 23. Intente de nuevo.\n"<< endl;
                }else{
                    valido=true;
                }
            }
            else{
                cout<<"Hora invalida. Ingrese unicamente numeros enteros.\n"<< endl;
            }
            
        }while(!valido);

        do{
            cout<<"Dame el minuto de la funcion "<<i<<": "; //Pregunta el minuto de la funcion
            cin>>numTemp;

            valido=validarNum(numTemp);
            if(valido==true){
                valido=false;
                minuto=stoi(numTemp);

                if (minuto<0 || minuto>59) { //Se valida que el minuto este entre 0 y 59
                    cout<<"La hora debe estar entre 0 y 59. Intente de nuevo.\n"<< endl;
                }else{
                    valido=true;
                }
            }
            else{
                cout<<"Minutos invalidos. Ingrese unicamente numeros enteros.\n"<< endl;
            }

        }while(!valido);

        do{
            cout<<"Dame el numero de la sala "<<i<<": "; //Pregunta el numero de sala de la funcion
            cin>>numTemp;

            valido=validarNum(numTemp);
            if(valido==true){
                valido=false;
                numSala=stoi(numTemp);

                if (numSala<0) { //Se valida que el numero sea un numero positivo ya que en este caso considere que no existirian salas con numeros negativos
                    cout<<"La sala debe ser un numero positivo. Intente de nuevo.\n"<< endl;
                }else{
                    valido=true;
                }
            }
            else{
                cout<<"Numero de sala invalido. Ingrese unicamente numeros enteros.\n"<< endl;
            }

        }while(!valido);

        //Se guardan los datos una vez que fueron validados y se repite el ciclo
        arFuncion[i].setCveFuncion(claveFun);
        arFuncion[i].setNumPeli(numPeli);
        horaClase.setHh(hora);
        horaClase.setMm(minuto);
        arFuncion[i].setHora(horaClase);
        arFuncion[i].setSala(numSala);
    }

    mostrarMenu(); //Llama a la funcion mostrarMenu se imprime el menu, pregunta la opcion y apartir de la opcion se va  un caso del switch
    while (opcion != 'g'){
        switch(opcion){
            case 'a':
                ConsultaActores(arActor, numeroActores); //Llama a la funcion, le envia el arreglo de actores y el numero de actores
            break;
            case 'b':
                ConsultaPeliculas(arPelicula, arActor, numeroPeliculas, numeroActores); //Llama a la funcion, le envia el arreglo de peliculas y actores ademas de el numero de peliculas y actores
            break;
            case 'c':
                ConsultaFunciones(arFuncion, arPelicula, numFunciones, numeroPeliculas); //Llama a la funcion y le envia el arreglo de funciones y el numero de funciones que se dieron de alta
            break;
            case 'd':
                ConsultaHora(arPelicula, arFuncion, numFunciones, numeroPeliculas); //Llama a la funcion y le envia el arreglo de peliculas y funciones asicomo el numero de funciones y peliculas
            break;
            case 'e':
                ConsultaClave(arActor, arPelicula, arFuncion, numeroActores, numeroPeliculas, numFunciones); //Llama a la funcion y le envia el arreglo de actores, peliculas y funciones ademas de el numero de actores, peliculas y funciones
            break;
            case 'f':
                ConsultaListaPeliActor(arActor, arPelicula, numeroActores, numeroPeliculas); //Llama a la funcion y le envia el arreglo de actores y peliculas ademas de el numero de actores y peliculas
            break;
            case 'g':
                return 0;
            break;
            default:
                cout<<"La opcion seleccionada no es valida. Intente de nuevo.\n";
            break;
        }
        //En caso de no desear terminar el programa se muestra de nuevo el menu mediante la funcion y se repite el ciclo while
        mostrarMenu();
    }
}

//"Doy mi palabra que he realizado esta actividad con integridad academica"