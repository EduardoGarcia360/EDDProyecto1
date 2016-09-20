#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H
#include "QString"

typedef struct NodoLista NodoLista;
typedef struct ListaEnlazada ListaEnlazada;

struct NodoLista{
    char* dato;
    int posicion = 0;
    NodoLista * siguiente;
    NodoLista(char* dato);
};

struct ListaEnlazada{
    NodoLista * primero;
    void agregar(char* cadena);
    void mostrar();
    int tam_lista();
    QString getPosicion(int p, int tam);
};

#endif // LISTASIMPLE_H
