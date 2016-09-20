#include "listasimple.h"
#include "stdlib.h"
#include "iostream"
#include "QString"
#include "string.h"

using namespace std;

NodoLista::NodoLista(char *dato){
    this->dato = dato;
}

void ListaEnlazada::agregar(char* cadena){
    NodoLista* nuevo = new NodoLista(cadena);
    nuevo->siguiente = NULL;
    if(primero == NULL){
        primero = nuevo;
    }else{
        NodoLista* actual = primero;
        int pos = 1;
        while(actual->siguiente != NULL){
            actual = actual->siguiente;
            pos++;
        }
        actual->siguiente = nuevo;
        nuevo->posicion = pos;
    }
}

void ListaEnlazada::mostrar(){
    NodoLista * actual = primero;
    while(actual->siguiente != NULL){
        cout << actual->dato << endl;
        actual = actual->siguiente;
    }
    cout << actual->dato << endl;
    cout << actual->posicion << endl;
}

int ListaEnlazada::tam_lista(){
    NodoLista* actual = primero;
    int tam=0;
    while(actual != NULL){
        tam++;
        actual = actual->siguiente;
    }
    return tam;
}


