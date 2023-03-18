#ifndef MYLIB_H
#define MYLIB_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//_________________________________________________________Parte 1________________________________________________________________________

char* lectura1(string namefile);

char* caracter_a_binario(int num);

unsigned long long obtener_long(string nombretxt);

void copiar_arreglo(char* original, char* copia,unsigned long long tam);

int contar_bits(char *bloque, int semilla);

char invertir_bits(char a);

void escribir_dat(char *informacion, string nombrearchivo, unsigned long long tam);

int levar(int numero, int potencia);

int enterocodificado(char *bytes);

char* convertir_bytes(char* archivo_binario,unsigned long long tam);

void metodo1(string namefile, int n);

char* decodificar(string namefile, int n);


//////////////////////////////////////////////////////SEGUNDO MÉTODO//////////////////////////////////////////////////////////////

string obtenerstring(string namefiletxt);

string obtenerbinario(string namefile);

string stringbinario(int num);

string obtenerbinariocodificado(string namefile, int n);

int obtenerentero(string binario8bits);

string caracterescodificados(string namefile, int semilla);

void escribirdatstring(string namefile, string informacion);

void codificarstring(string namefile, int n);

string obtenerbinariodecodificado(string namefile, int n);

#endif // MYLIB_H
