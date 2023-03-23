#include <mylib.h>

using namespace std;

int main(){


    int metodo=0;
    string namefile = "";
    int semilla;
    int opcion=0;
    string claveadmin = "";


    cout << "¿QUE DESEAS HACER? " << endl << endl;
    cout << "1) Codificar un archivo utilizando el primer metodo." << endl;
    cout << "2) Decodificar un archivo utilizando el primer metodo." << endl;
    cout << "3) Codificar un archivo utilizando el segundo metodo." << endl;
    cout << "4) Decodificar un archivo utilizando el segundo metodo." << endl;
    cout << "5) Utilizar la aplicacion bancaria." << endl;
    cin >> metodo;

    switch (metodo) {

    case 1:

        cout << "Ingrese el nombre del archivo a codificar (Use .txt): " << endl ;
        cin >> namefile;
        cout << "Ingrese el valor de la semilla: " << endl;
        cin >> semilla;

        metodo1(namefile, semilla);

        break;
    case 2:
        cout << "Ingrese el nombre del archivo a decodificar (Use .dat): " << endl ;
        cin >> namefile;
        cout << "Ingrese el valor de la semilla: " << endl;
        cin >> semilla;

        decodificar(namefile, semilla);

        break;
    case 3:
        cout << "Ingrese el nombre del archivo a codificar (Use .txt): " << endl ;
        cin >> namefile;
        cout << "Ingrese el valor de la semilla: " << endl;
        cin >> semilla;

        codificarstring(namefile, semilla);

        break;
    case 4:
        cout << "Ingrese el nombre del archivo a decodificar (Use .dat): " << endl ;
        cin >> namefile;
        cout << "Ingrese el valor de la semilla: " << endl;
        cin >> semilla;

        decodificarstring(namefile, semilla);

        break;

    case 5:

        //unsigned long long tam = obtener_long("sudo.dat");
        fstream archivo;

        int cantidadusuarios = 0;
        int saldoint = 0;
        string cedula = "";
        string cedula2 = "";
        string clave = "";
        string clave2 = "";
        string saldo = "0";
        string lineadatos = "";
        int semillaapp = 4;
        char* sudotext = decodificarapp("sudo.dat", semillaapp);

        cout << "Ingrese el numero de la opcion que desea seleccionar: " << endl << "[1] INGRESAR COMO ADMINISTRADOR." << endl << "[2] INGRESAR COMO USUARIO." << endl << endl;
        cin >> opcion;

        if(opcion==1){

            for(int i=0; i<3; i++){
                cout << "Ingrese la clave de administrador (Máximo 20 caracteres sin espacio): " << endl;
                cin >> claveadmin;
                if (claveadmin==sudotext){
                    cout<<"Contraseña es Correcta \t MODO: ADMINISTRADOR" << endl << endl;
                    break;
                }
                else cout<<"Contraseña Inorrecta, tiene "<<2-i<<" intentos" << endl;
            }

            if (claveadmin==sudotext){
                cout << "¿Cuantos usuarios desea registrar? " << endl;
                cin >> cantidadusuarios;

                for (int p=0; p<cantidadusuarios; p++) {
                    cout<<"Ingrese la Cedula del usuario a registrar:  ";
                    cin>>cedula;
                    cout<<"\n Ingrese la clave del usuario a registrar (Num 4 digitos):  ";
                    cin>>clave;
                    cout<<"\n Ingrese el saldo del usuario a registrar:  $(COP)";
                    cin>>saldo;

                    lineadatos.append(cedula);
                    lineadatos.append("-");
                    lineadatos.append(clave);
                    lineadatos.append("-");
                    lineadatos.append(saldo);
                    lineadatos.append("\n");

                    archivo.open("registro_userT.txt", fstream::app | fstream::binary |fstream::ate);
                    if(archivo.is_open()) archivo << lineadatos;
                    else cout << "No fue posible abrir el archivo." << endl;

                    archivo.close();
                }

                codificarapp("registro_userT.txt", semillaapp);


            }
        }

        else if(opcion==2){
            int cont = 0;
            int pos = 0;
            int pos2 = 0;
            char caracter;
            string linea = "";
            string linea2 = "";
            char* usertext = decodificarapp("registro_userT.dat", semillaapp);
            cout<<"MODO: USUARIO \n" << endl;;

            for(int i=0; i<3; i++){
                cout << "Ingrese el numero de su cedula: " << endl;
                cin >> cedula;

                while(usertext[pos]!='\0'){
                    while(usertext[cont+pos]!='\n'){
                        caracter = usertext[cont+pos];
                        linea.push_back(caracter);
                        cont++;
                    }
                    pos+=cont+1;
                    //cout << linea << endl;
                    cont = 0;
                    pos2 = linea.find("-");
                    cedula2 = linea.substr(0,pos2);
                    linea2=linea;
                    linea = "";
                    if(cedula==cedula2) break;

                }
                if(cedula==cedula2) break;
                else {
                    cout << "El numero de cedula no se encuentra registrado, tiene " << 2-i << " intentos." << endl;
                    pos=0;
                }
            }

            if(cedula==cedula2){

                int n = 0;
                cout << "Numero de cedula correcto." << endl << endl;

                for(int i=0; i<2; i++){
                    n = linea2.find("-");
                    clave2 = linea2.substr(n+1);
                    n = clave2.find("-");
                    clave2 = clave2.substr(0, n);
                    cout << "Ingrese su clave: " << endl;
                    cin >> clave;

                    if(clave==clave2){
                        int operacion = 0;
                        cout << "La clave es correcta." << endl << endl;

                        while(operacion==0){
                            cout << "¿QUE OPERACION DESEAS REALIZAR? (Cada operación tiene un costo de $1000)" << endl;
                            cout << "[1] Consultar saldo." << endl;
                            cout << "[2] Retirar dinero" << endl;
                            cout << "[3] Consignar en tu cuenta." << endl << endl;
                            cin >> operacion;

                            if(operacion==1){
                                n = linea2.find("-");
                                saldo = linea2.substr(n+1);
                                n = saldo.find("-");
                                saldo =saldo.substr(n+1);
                                saldoint = stoi(saldo);

                                cout << "Su saldo es: $" << saldo << endl << endl;
                                cout << "Costo de la operacion: -$1000" << endl << endl;
                                cout << "Saldo actual = " << saldoint-1000 << endl << endl;

                                saldoint-=1000;

                                operacion=0;
                            }

                            else if(operacion==2){

                            }

                        }




                    }
                    else {
                        cout << "La clave no es correcta, le quedan " << 2-i << " intentos." << endl;
                    }

                }
            }
        }
        break;
    }



    return 0;
}
