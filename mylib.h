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

char* CONVERTIR_BYTES_AINT(char* archivo_binario,unsigned long long tam);

void metodo1(string namefile, int n);

char* DESINVERTIR(string namefile, int n);


#endif // MYLIB_H
