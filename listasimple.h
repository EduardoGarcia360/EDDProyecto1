#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H
#include "QString"

typedef struct NodoLista NodoLista;
typedef struct ListaEnlazada ListaEnlazada;

struct NodoLista{
    char* dato;
    NodoLista * siguiente;
    NodoLista(char* dato);
};

struct ListaEnlazada{
    NodoLista * primero;
    void agregar(char* cadena);
    void mostrar();
};

#endif // LISTASIMPLE_H
