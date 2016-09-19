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
    //nuevo->dato = cadena;
    if(primero == NULL){
        primero = nuevo;
    }else{
        NodoLista* actual = primero;
        //actual = primero;
        while(actual->siguiente != NULL){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void ListaEnlazada::mostrar(){
    //QString dato_nodo = "";
    cout << "entro aca" << endl;
    NodoLista * actual = primero;
    //QString algo="";
    while(actual->siguiente != NULL){
        cout << actual->dato << endl;
        //dato_nodo = actual->dato;
        //algo += dato_nodo;
        actual = actual->siguiente;
    }
    //cout << algo.toStdString() << endl;
}
