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

        while(actual->siguiente != NULL){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void ListaEnlazada::mostrar(){
    cout << "entro aca" << endl;
    NodoLista * actual = primero;
    while(actual->siguiente != NULL){
        cout << actual->dato << endl;
        actual = actual->siguiente;
    }
    cout << actual->dato << endl;

}
