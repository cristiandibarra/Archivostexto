#include <mylib.h>

using namespace std;

int main(){

    int metodo=0;
    string namefile = "";
    int semilla;

    cout << "¿QUE DESEAS HACER? " << endl << endl;
    cout << "1) Codificar un archivo utilizando el primer metodo." << endl;
    cout << "2) Decodificar un archivo utilizando el primer metodo." << endl;
    cout << "3) Codificar un archivo utilizando el segundo metodo." << endl;
    cout << "4) Decodificar un archivo utilizando el segundo metodo." << endl;
    cout << "5) Utilizar la aplicacion bancaria." << endl;
    cin >> metodo;

    switch (metodo) {
    case 1:

        cout << "Ingrese el nombre del archivo a codificar: " << endl ;
        cin >> namefile;
        cout << "Ingrese el valor de la semilla: " << endl;
        cin >> semilla;

        metodo1(namefile, semilla);

        break;
    case 2:
        cout << "Ingrese el nombre del archivo a decodificar: " << endl ;
        cin >> namefile;
        cout << "Ingrese el valor de la semilla: " << endl;
        cin >> semilla;

        decodificar(namefile, semilla);

        break;
    case 3:
        cout << "Ingrese el nombre del archivo a codificar: " << endl ;
        cin >> namefile;
        cout << "Ingrese el valor de la semilla: " << endl;
        cin >> semilla;

        codificarstring(namefile, semilla);

        break;
    case 4:
        cout << "Ingrese el nombre del archivo a decodificar: " << endl ;
        cin >> namefile;
        cout << "Ingrese el valor de la semilla: " << endl;
        cin >> semilla;

        decodificarstring(namefile, semilla);

        break;
    default:
        break;
    }






    return 0;
}
