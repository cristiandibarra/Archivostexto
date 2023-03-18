#include <mylib.h>

char* lectura1(string namefile){
    fstream archivo;
    unsigned long long tamanio_archivo = 0;
    char* archivo_binaro = nullptr;                                //Arreglo con lo valores en binario de los caracteres en el documento
    char* caracter_convertido;                                     //Binario equivalente a cada caracter

    archivo.open(namefile, fstream::binary | fstream::in | fstream::ate);  //Abrir archivo

    if(archivo.is_open()){
        unsigned long long posicion_archivo = 0;                  //Se usará para moverse por el arreglo grande
        tamanio_archivo = archivo.tellg();                        //Utilizo tellg para determinar cuantos caracteres tendrá el arreglo
        archivo.seekg(0);                                         //Me posiciono al inicio del documento
        archivo_binaro = new char [(tamanio_archivo*8)+1];       //Inicializo el arreglo
        archivo_binaro[tamanio_archivo*8] = '\0';                //Pongo el caracter de final de archivo

        for(unsigned long long i=0; i<tamanio_archivo; i++){                      //Recorro todo el archivo
            caracter_convertido = caracter_a_binario(int(archivo.get()));         //Obtengo el valor ASCII de cada caracter
            for(int j=0; j<8; j++){
                archivo_binaro[posicion_archivo] = caracter_convertido[j];
                posicion_archivo++;
            }
        }

    }

    else cout << "No fue posible abrir el archivo." << endl << endl;
    archivo.close();
    return archivo_binaro;
}

char* caracter_a_binario(int valorascii){

    char* cadena;
    cadena = new char [9];                            //Inicializo el arrelglo donde quedará el binario
    cadena[8]='\0';                                   //Caracter de final

    for (int i=0; i<8; i++){
        if (valorascii%2==1)cadena[7-i]='1';          //Voy extrayengo los 1s y 0s
        else cadena[7-i]='0';                         //Los pongo en su respectivo orden en la cadena
        valorascii/=2;                                //Opero para poder continuar
    }
    return cadena;
}

unsigned long long obtener_long(string nombretxt){               //Funcion que devuelve el tamaño del archivo (unsigned)
    unsigned long long tamanio=0;                               //Declro la variable que almacena al tamaño
    fstream archivo;                                           //Creo el elemento archivo
    archivo.open(nombretxt, fstream::in | fstream::ate);       //Abro en modo lectura, en el último caracter
    if(archivo.is_open()){                                     //Si el
        //cout << "El archivo se abrió correctamente" << endl;
                tamanio = archivo.tellg();                             //tellg me dice donde esta el cursor y lo asigno a tamanio
    }
    else cout << "No fue posible abrir el archivo." << endl;
    archivo.close();                                           //Cierro el archivo
    return tamanio;                                             //Retorno el tamaño
}

void copiar_arreglo(char* original, char* copia,unsigned long long tam){     //Función para hacer una copia de un arreglo

    for (unsigned long long i=0;i<tam;i++){

        copia[i]=original[i];
    }

}

int contar_bits(char *bloque, int semilla){                                   //Cuenta la cantidad de bits '1' en un bloque

    int unos=0;
    for (int i=0; i<semilla; i++){                                            //Los bloques son del tamaño que indica la semilla
        if (bloque[i]=='1') unos++;
    }

    return unos;
}

char invertir_bits(char a){                                                   //Invierto un bit
    char b;
    if(a=='0') b='1';
    else b='0';
    return b;

}

void escribir_dat(char *informacion, string nombrearchivo, unsigned long long tam){       //Escribir informacion en un archivo
    fstream archivo;                                                                      //Creo el objeto fstream
    archivo.open(nombrearchivo, fstream::out | fstream::binary);                          //abro el archivo
    if(archivo.is_open()){                                                                //Si el archivo abrió correctamente ejecuto...
        cout << "\nEscribiendo .dat..." << endl;
        archivo.write(informacion, tam);                                                  //Escribo la informacion sobre el archivo
    }
    else cout << "No fue posible abrir el archivo." << endl;
    archivo.close();                                                                      //Cierro el archivo
    cout<<"Informacion de la funcion escribiendo \n"<<informacion<<endl;

}

int levar(int numero, int potencia){                                        //Elevo un numero a una potencia n

    int resultado_potencia=0;

    if(potencia==0)resultado_potencia=1;
    else if (potencia==1) resultado_potencia = numero;
    else {
        resultado_potencia=numero;
        for(int p=0;p<potencia-1;p++) resultado_potencia*=numero;             //Multiplico hasta obtener la potencia

    }
    return resultado_potencia;
}

int enterocodificado(char *bytes){                                          //Convierto el valor binario de un caracter ASCII a un entero
        int resultado=0,m;
        for(int k=7; k>=0; k--){                                            //Recorro el arreglo de atras para adelante
            if(bytes[k]=='1'){                                              //Si hay un uno aplico...
                if (k==-8)resultado+=levar(2,8);                            //SI ya me pase y hay un '1', elevo 2**8 y lo sumo
                else {                                                      //Elevo y sumo
                    m=(7-k);
                    resultado+=levar(2,m);}
            }
       }
    return resultado;
}

char* convertir_bytes(char* archivo_binario,unsigned long long tam){             //Convierto todo el archivo en binario a ASCII

    char* bloque;
    char* letras;
    char caracter;
    letras=new char [tam+1];
    letras[tam]='\0';
    bloque = new char [9];
    bloque[8]='\0';
    unsigned long long indx=0, cont=0;
    while (indx<tam*8){                                                 //Recorro el arreglo en todo su tamaño
        for (int p=0; p<8; p++){                                          //Comienzo recorriendo el primer bloque de 8 bits
            bloque[p]=archivo_binario[indx+p];                          //Copio este segmento en la variable bloque
        }
        caracter=enterocodificado(bloque);                              //Lo paso de binario a ASCII
        letras[cont]=caracter;                                          //Lo pongo en su posicion en el arreglo que contendrá al nuevo archivo
        indx+=8;                                                        //Me muevo otros 8 bits
        cont++;                                                         //Aumento en 1 las posiciones para el archivo de caracteres
        //cout<<"\n\n Letras \n"<<letras<<endl;
    }
    //cout<<endl;
    return letras;
}

void metodo1(string namefile, int n){                         //Codificacion por el metodo 1 CHAR
    string namedat="";
    unsigned long long tam=0, cont=0;
    int unos=0, ceros=0;
    char* archivo_binario = lectura1(namefile);               //Obtengo el arreglo con el contenido en el archivo
    char* archivo_codificado = archivo_binario;               //Hago una copia que almacenará el codificado
    char* bloque;

    tam = obtener_long(namefile);                               //Obtengo la longitud del archivo

    archivo_codificado = new char [(tam*8)+1];                 //Asigno memoria
    archivo_codificado[tam*8] = '\0';                          //Pongo caracter de final
    bloque = new char [n+1];                                   //Defino el tamaño de los bloques (Segun la semilla)
    bloque[n] = '\0';                                                //Asigno caracter final
    copiar_arreglo(archivo_binario,archivo_codificado,(tam*8));      //copio

    while (cont<(tam*8)){                                            //Mientras el cursor aun esté dentro del arreglo

       for (int p=0; p<n; p++) bloque[p] = archivo_binario[cont+p];                           //Me muevo por bloques segun lo indica la semilla

       if (cont==0) for (int m=0;m<n;m++)archivo_codificado[m]=invertir_bits(bloque[m]);      //Aplico la regla especifica para el primer bloque

       else {
           if (ceros==unos) for (int q=0; q<n; q++) archivo_codificado[cont+q]=invertir_bits(bloque[q]);           //Aplico las reglas para los otros bloques
           else if (ceros>unos) for (int q=1; q<n;q=q+2) archivo_codificado[cont+q]=invertir_bits(bloque[q]);
           else if (unos>ceros) for (int q=2; q<n;q=q+3) archivo_codificado[cont+q]=invertir_bits(bloque[q]);
       }
       cont+=n;                          //Me muevo donde indique la semilla
       unos = contar_bits(bloque,n);     //Cuento los bits para saber que regla sique
       ceros = (n-unos);
    }
    cout << "\n\n EL BINARIO CODIFICADO \n\n"<<archivo_codificado<<endl;
    cout << "Ingrese el nombre del archivo de salida CODIFICADO (Use .dat): " << endl ;    //Nombre que recibirá el nuevo archivo
    cin >> namedat;

    char* letras = convertir_bytes(archivo_codificado, tam);                                //Paso el binario a letras

    escribir_dat(letras,namedat,tam);                                                       //Escribo sobre el archivo

}

char* decodificar(string namefile, int n){

    unsigned long long tam=0, cont=0;
    int unos=0, ceros=0;
   char* archivo_binario_codificado = lectura1(namefile);                        //Leo el archivo codificado
    char* archivo_decodificado;
    char* bloque;
    char* bloque2; //Bloque invertido
    bloque2 = new char [n+1];
    bloque2[n] = '\0';

   tam=obtener_long(namefile);                                                 //Obtengo el tamaño del archivo
    archivo_decodificado = new char [(tam*8)+1];                               //Asigno memoria
    archivo_decodificado[tam*8] = '\0';                                        //Pongo caracter de final
    bloque = new char [n+1];
    bloque[n] = '\0';
    copiar_arreglo(archivo_binario_codificado,archivo_decodificado,(tam*8));       //Hago una copia del archivo

    while (cont<(tam*8)){                                                          //Recorro todo el archivo

       for (int p=0;p<n;p++) bloque[p] = archivo_binario_codificado[cont+p];         //Me muevo en bloques segun indique la semilla

       if (cont==0) for (int m=0; m<n; m++){                                         //Reglas para el promer bloque
           archivo_decodificado[m] = invertir_bits(bloque[m]);
           bloque2[m] = invertir_bits(archivo_binario_codificado[cont+m]);
       }

       else {                                                                     //Reglas para los bloques que siguen
           if (ceros==unos) for (int q=0; q<n;q++) {
               archivo_decodificado[cont+q] = invertir_bits(bloque[q]);
               bloque2[q] = invertir_bits(archivo_binario_codificado[cont+q]);
           }
           else if (ceros>unos) for (int q=1; q<n;q=q+2) {
               archivo_decodificado[cont+q] = invertir_bits(bloque[q]);
               bloque2[q] = invertir_bits(archivo_binario_codificado[cont+q]);
           }
           else if (unos>ceros) for (int q=2; q<n;q=q+3) {
               archivo_decodificado[cont+q] = invertir_bits(bloque[q]);
               bloque2[q] = invertir_bits(archivo_binario_codificado[cont+q]);
           }
       }
       for (int x=0;x<n;x++)bloque2[x] = archivo_decodificado[cont+x];
       cont+=n;
       unos=contar_bits(bloque2,n);
       ceros=(n-unos);
    }

        char* letras = convertir_bytes(archivo_decodificado, tam);                //Arreglo con todos los caracteres

        cout << "Ingrese el nombre del archivo de salida DECODIFICADO (Use .txt): " << endl << endl;
        cin>>namefile;

        escribir_dat(letras, namefile, tam);
        return letras;

}


/////////////////////////////////////////////////////////SEGUNDO MÉTODO/////////////////////////////////////////////////////////////////////////

string obtenerstring(string namefiletxt){                        //Obtengo un string con toda la informacion del archivo
    unsigned long long tam = 0;
    string textoinicial = "";
    fstream archivo1;
    archivo1.open(namefiletxt, fstream::in | fstream::out | fstream::binary | fstream::ate);
    tam = obtener_long(namefiletxt);
    archivo1.seekg(0);
    string elemento;
    elemento = "";
    char c;
     for (unsigned long long i=0; i<tam; i++){
          archivo1.seekg(i);
          archivo1.get(c);
          textoinicial.push_back(c);

      }
     archivo1.close();
     return textoinicial;

}

string obtenerbinario(string namefile){                                  //Obtengo el binario equivalente al archivo
    fstream archivo1;
    int entero1;
    char c;
    archivo1.open(namefile, fstream::in | fstream::out | fstream::binary);
    string binarionatural;
    binarionatural = "";
    unsigned long long tam;
    tam = 0;
    tam = obtener_long(namefile);
    for (unsigned long long i=0; i<tam; i++){                             //Recorro el archivo
         archivo1.seekg(i);                                               //Posiciono el cursor en i
         archivo1.get(c);                                                 //Obtengo el caracter
         entero1 = int(c);
         binarionatural += stringbinario(entero1);                        //Lo convierto a binario y lo agrego al string que lo contiene todo


     }
    //cout << binarionatural << endl;
    archivo1.close();
    return binarionatural;

}

string stringbinario(int num){                                            //Convierto el valor entero de un caracter a su binario

    string bloquebinario="00000000";
    for (int i=0; i<8; i++){
        if (num%2==1) bloquebinario[7-i] = '1';
        num=num/2;
    }

    return bloquebinario;
}

string obtenerbinariocodificado(string namefile, int n){    //Obtengo el string binario con las reglas del segundo método aplicadas
    fstream archivo1;
    unsigned long long cont;
    cont = 0;
    archivo1.open(namefile, fstream::out | fstream::in | fstream::binary);
    string bloque;
    bloque = "";
    string bloque2 = "";
    unsigned long long tam=0;
    tam = obtener_long(namefile);
    string binario = obtenerbinario(namefile);              //Obtengo el binario
    //cout << binario << endl;
    archivo1.seekg(0);
    while (cont<(tam*8)){                                   //Me muevo en bloques de n bits

       for (int p=0; p<n; p++) bloque[p] = binario[cont+p]; //Saco un bloque del binario original

         bloque2[0] = bloque[n-1];                          //Ultimo bit del bloque se convierte en el primero
         for (int m=1; m<n; m++) bloque2[m] = bloque[m-1];  //Muevo los demás bits una posicion

          for (int x=0; x<n; x++) binario[cont+x] = bloque2[x];  //Lo pongo en el string binario de salida

       cont+=n;
    }
    archivo1.close();

    return binario;
}

int obtenerentero(string binario8bits){                          //Convierto un bloque de 1 y 0s a su equivalente entero
    int numero1=0, numero2=0;
    string elemento="";
    for(int i=0; i<8; i++){                                      //Recorro el bloque de atras a adelante
        elemento = binario8bits[7-i];
        numero1=stoi(elemento);                                  //Convierto a entero para poder operar
        if(numero1==1) numero2 = numero2+levar(2, i);            //Si hay un 1 elevo 2 a su correspodiente potencia y sumo
    }
    return numero2;
}

string caracterescodificados(string namefile, int semilla){      //Obtengo los caracteres encriptados
    unsigned long long cont = 0;
    int numero = 0;
    char caracter;
    string texto;
    texto = "";
    string bloque;
    bloque = "        ";
    unsigned long long tam = 0;
    tam = obtener_long(namefile);
    string binario1 = obtenerbinariocodificado(namefile, semilla);
    while (cont<(tam*8)){                                           //Me muevo la cantidad de espacios que tenga el archivo
        for (int p=0; p<8; p++) bloque[p] = binario1[cont+p];       //Voy sacando bloques de binarios
        numero = obtenerentero(bloque);                             //Los convierto a enteros
        caracter = char(numero);                                    //Los convierto a caracteres
        texto.push_back(caracter);                                  //Los agrego al string con toda la informacion

        cont+=8;                                                    //Me muevo 8 posiciones mas
    }
    return texto;

}

void escribirdatstring(string namefile, string informacion){       //Escribir en el documento
    fstream archivo;
    archivo.open(namefile, fstream::out | fstream::binary);
    if(archivo.is_open()){
        cout << "\nEscribiendo .dat..." << endl;
        archivo<<informacion;
    }
    else cout << "No fue posible abrir el archivo." << endl;
    archivo.close();
}

void codificarstring(string namefile, int n){                        //Codificar por el metodo 2 string
    string informacion, nombre;
    informacion = caracterescodificados(namefile, n);
    cout << "Ingrese el nombre del archivo CODIFICADO de salida (Use .dat):" << endl << endl;
    cin >> nombre;
    escribirdatstring(nombre, informacion);
}

string obtenerbinariodecodificado(string namefile, int n){           //Obtengo el binario decodificado
    string strbool;
    strbool = "";
    strbool = obtenerbinario(namefile);

    fstream archivo1;
    unsigned long long cont;
    cont = 0;
    archivo1.open(namefile, fstream::out | fstream::in | fstream::binary);
    string bloque;
    bloque = "";
    string bloque2 = "";
    unsigned long long tam = 0;
    tam = obtener_long(namefile);
    archivo1.seekg(0);
    while (cont<(tam*8)){                                            //Aplico las mismas reglas para codificar pero a la inversa

       for (int p=0; p<n; p++) bloque[p] = strbool[cont+p];

         bloque2[n-1] = bloque[0];
         for (int m=n-1; m>0; m--) bloque2[m-1] = bloque[m];

          for (int x=0; x<n; x++)strbool[cont+x] = bloque2[x];
          //archivo_codificado[0] = archivo_binario[(tam*8)-1];

       cont+=n;
    }
    archivo1.close();

    //cout << binario << endl;
    return strbool;
}

string stringdecodificado(string namefile, int n){                       //Obtebgo el string con los caracteres ya decodificados
    unsigned long long tam=0;
    tam = obtener_long(namefile)*8;
    unsigned long long cont = 0;
    int numero = 0;
    char caracter;
    string texto;
    texto = "";
    string bloque;
    bloque = "        ";
    string binario1 = obtenerbinariodecodificado(namefile, n);
    //cout << binario1 << endl;
    while (cont<(tam)){
        for (int p=0;p<8;p++) bloque[p]=binario1[cont+p];
        numero=obtenerentero(bloque);
        caracter=char(numero);
        texto.push_back(caracter);

        cont+=8;
    }
    //cout << texto << endl;
    return texto;
}

void decodificarstring(string namefile, int n){                               //Aplico el metodo completo
    string informacion, nombre;
    //letras=obtenerbinariodecodificado(namefile, n);
    informacion=stringdecodificado(namefile, n);
    //cout << "Listo: " << str <<endl;

    cout << "Ingrese el nombre del archivo de salida DECODIFICADO por string (Use .txt):" << endl << endl;
    cin >> nombre;
    escribirdatstring(nombre, informacion);
}






