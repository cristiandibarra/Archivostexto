#include <mylib.h>

using namespace std;

int main(){

    string namefile="";
    int semilla=0;
    char* texto=nullptr;
    char* texto2=nullptr;
    cout << "Ingrese el nombre del archivo (utilice .txt al final): " << endl << endl;
    cin >> namefile;
    cout << "Ingrese la semilla de codificacion: " << endl << endl;
    cin >> semilla;

    texto=lectura1(namefile);
    //tam=obtener_long(namefile);

    cout << texto << endl << endl ;

    //metodo1(namefile, semilla);
    DESINVERTIR(namefile, semilla);

   //cout << texto2 << endl << endl;





    cout << endl;
    return 0;
}
