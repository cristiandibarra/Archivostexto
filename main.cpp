#include <mylib.h>

using namespace std;

int main(){

    string namefile="";
    string textos = "";
    string binario = "";
    int semilla=0;
    char* texto=nullptr;
    cout << "Ingrese el nombre del archivo (utilice .txt al final): " << endl << endl;
    cin >> namefile;
    cout << "Ingrese la semilla de codificacion: " << endl << endl;
    cin >> semilla;

    //texto=lectura1(namefile);
    //tam=obtener_long(namefile);
    //cout << texto << endl << endl ;

    //metodo1(namefile, semilla);
    //decodificar(namefile, semilla);
    //cout << texto2 << endl << endl;

    //textos = obtenerstring(namefile);
    //cout << textos << endl << endl;
    binario = obtenerbinario(namefile);
    cout << binario << endl;
    binario = obtenerbinariocodificado(namefile, semilla);
    cout << binario << endl;
    textos = caracterescodificados(namefile, semilla);
    cout << textos;
    codificarstring(namefile, semilla);

    cout << "Ingrese el nombre del archivo para decodificar (Use. txt):" << endl << endl;
    cin >> namefile;

    binario = obtenerbinariodecodificado(namefile, semilla);
    cout << binario << endl;                                       // PROBLEMA AL DECODIFICAR :(







    cout << endl;
    return 0;
}
