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
    fstream archivo1;                                           //Creo el elemento archivo
    archivo1.open(nombretxt, fstream::in | fstream::ate);       //Abro en modo lectura, en el último caracter
    if(archivo1.is_open()){                                     //Si el
        //cout << "El archivo se abrió correctamente" << endl;
                tamanio = archivo1.tellg();                             //tellg me dice donde esta el cursor y lo asigno a tamanio
    }
    else cout << "No fue posible abrir el archivo." << endl;
    archivo1.close();                                           //Cierro el archivo
    return tamanio;                                             //Retorno el tamaño
}

void copiar_arreglo(char* original, char* copia,unsigned long long tam){

    for (unsigned long long i=0;i<tam;i++){

        copia[i]=original[i];
    }

    //return copia;
}

int contar_bits(char *bloque, int semilla){

    int unos=0;
    for (int i=0; i<semilla; i++){
        if (bloque[i]=='1') unos++;
    }

    return unos;
}

char invertir_bits(char a){
    char b;
    if(a=='0') b='1';
    else b='0';
    return b;

}

void escribir_dat(char *informacion, string nombrearchivo, unsigned long long tam){
    fstream archivo;
    archivo.open(nombrearchivo, fstream::out | fstream::binary);
    if(archivo.is_open()){
        cout << "\nEscribiendo .dat..." << endl;
        archivo.write(informacion, tam);
    }
    else cout << "No fue posible abrir el archivo." << endl;
    archivo.close();
    cout<<"Informacion de la funcion escribiendo \n"<<informacion<<endl;

}

int levar(int numero, int potencia){

    int resultado_potencia=0;

    if(potencia==0)resultado_potencia=1;
    else if (potencia==1)resultado_potencia=numero;
    else {
        resultado_potencia=numero;
        for(int p=0;p<potencia-1;p++)resultado_potencia*=numero;

    }
    return resultado_potencia;
}

int enterocodificado(char *bytes){
        int resultado=0,m;
        //          8765 4321
        //o = 111 = 0110 1111
        for(int k=7; k>=0; k--){
            if(bytes[k]=='1'){
                if (k==-8)resultado+=levar(2,8);
                else {
                    m=(7-k);
                    resultado+=levar(2,m);}
            }
       }
    return resultado;
}

char* CONVERTIR_BYTES_AINT(char* archivo_binario,unsigned long long tam){

    char* bloque;
    char* letras;
    char caracter;
    letras=new char [tam+1];
    letras[tam]='\0';
    bloque = new char [9];
    bloque[8]='\0';
    unsigned long long indx=0,cont=0;
    while (indx<tam*8){
        for (int p=0;p<8;p++){
            bloque[p]=archivo_binario[indx+p];
        }
        caracter=enterocodificado(bloque);
        letras[cont]=caracter;
        indx+=8;
        cont++;
        //cout<<"\n\n Letras \n"<<letras<<endl;
    }
    //cout<<endl;
    return letras;
}

void metodo1(string namefile, int n){
    string namedat="";
    unsigned long long tam=0,cont=0;
    int unos=0,ceros=0;
    char* archivo_binario = lectura1(namefile);
    char* archivo_codificado = archivo_binario;
    char* bloque;

    tam=obtener_long(namefile);

    archivo_codificado= new char [(tam*8)+1];
    archivo_codificado[tam*8]='\0';
    bloque = new char [n+1];
    bloque[n]='\0';
    copiar_arreglo(archivo_binario,archivo_codificado,(tam*8));

    while (cont<(tam*8)){

       for (int p=0;p<n;p++) bloque[p]=archivo_binario[cont+p];

       if (cont==0) for (int m=0;m<n;m++)archivo_codificado[m]=invertir_bits(bloque[m]);

       else {
           if (ceros==unos) for (int q=0; q<n;q++) archivo_codificado[cont+q]=invertir_bits(bloque[q]);
           else if (ceros>unos) for (int q=1; q<n;q=q+2) archivo_codificado[cont+q]=invertir_bits(bloque[q]);
           else if (unos>ceros) for (int q=2; q<n;q=q+3) archivo_codificado[cont+q]=invertir_bits(bloque[q]);
       }
       cont+=n;
       unos = contar_bits(bloque,n);
       ceros = (n-unos);
    }
    //cout<<"EL BINARIO ORIGINAL \n\n"<<archivo_binario<<endl;
    cout<<"\n\n EL BINARIO INVERTIDO \n\n"<<archivo_codificado<<endl;
    cout << "Ingrese el nombre del archivo de salida (Use .dat): " << endl ;
    cin >> namedat;
    //escribir_dat(archivo_codificado, namefile, tam);

    char* letras=CONVERTIR_BYTES_AINT(archivo_codificado, tam);

   // cout<<"\n\n LOS CARACTERES RAROS \n\n"<<letras<<endl;
    escribir_dat(letras,namedat,tam);

}

char* DESINVERTIR(string namefile, int n){

    //string namefile="M1S6T.txt";
    unsigned long long tam=0,cont=0;
    int unos=0,ceros=0;
   char* archivo_binario_inverido=lectura1(namefile);
    char* archivo_desinvertido;
    char* bloque;
    char* bloque2; //Bloque invertido
    bloque2 = new char [n+1];
    bloque2[n]='\0';

   tam=obtener_long(namefile);
    archivo_desinvertido= new char [(tam*8)+1];
    archivo_desinvertido[tam*8]='\0';
    bloque = new char [n+1];
    bloque[n]='\0';
    copiar_arreglo(archivo_binario_inverido,archivo_desinvertido,(tam*8));

    while (cont<(tam*8)){

       for (int p=0;p<n;p++) bloque[p]=archivo_binario_inverido[cont+p];

       if (cont==0) for (int m=0;m<n;m++){
           archivo_desinvertido[m]=invertir_bits(bloque[m]);
           bloque2[m]=invertir_bits(archivo_binario_inverido[cont+m]);
       }

       else {
           if (ceros==unos) for (int q=0; q<n;q++) {
               archivo_desinvertido[cont+q]=invertir_bits(bloque[q]);
               bloque2[q]=invertir_bits(archivo_binario_inverido[cont+q]);
           }
           else if (ceros>unos) for (int q=1; q<n;q=q+2) {
               archivo_desinvertido[cont+q]=invertir_bits(bloque[q]);
               bloque2[q]=invertir_bits(archivo_binario_inverido[cont+q]);
           }
           else if (unos>ceros) for (int q=2; q<n;q=q+3) {
               archivo_desinvertido[cont+q]=invertir_bits(bloque[q]);
               bloque2[q]=invertir_bits(archivo_binario_inverido[cont+q]);
           }
       }
       for (int x=0;x<n;x++)bloque2[x]=archivo_desinvertido[cont+x];
       cont+=n;
       unos=contar_bits(bloque2,n);
       ceros=(n-unos);
    }

    //cout<<"EL BINARIO CODIFICADO \n\n"<<archivo_binario_inverido<<endl;
        //cout<<"\n\n EL BINARIO DECODIFCADO \n\n"<<archivo_desinvertido<<endl;
        char* letras=CONVERTIR_BYTES_AINT(archivo_desinvertido, tam);

        //cout<<"\n\n LOS CARACTERES \n\n"<<letras<<endl;
        escribir_dat(letras,namefile, tam);
        return letras;

}
