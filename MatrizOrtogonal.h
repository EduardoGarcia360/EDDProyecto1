#ifndef MatrizOrtogonal
#define MatrizOrtogonal
#include "QString"

typedef struct Nodo Nodo;
typedef struct Encabezado Encabezado;
typedef struct ListaEncabezados ListaEncabezados;
typedef struct Matriz Matriz;

struct Nodo
{
    int fila;
    int columna;
    char * valor;
    Nodo * derecha;
    Nodo * izquierda;
    Nodo * arriba;
    Nodo * abajo;

    Nodo(int fila, int columna, char * valor);
};

struct Encabezado
{
    int id;
    Encabezado * siguiente;
    Encabezado * anterior;
    Nodo * acceso;
    Encabezado(int id);
};

struct ListaEncabezados
{
    Encabezado * primero;
    void insertar(Encabezado * nuevo);
    Encabezado * getEncabezado(int id);
};

struct Matriz
{
    ListaEncabezados * eFilas;
    ListaEncabezados * eColumnas;
    Matriz();
    void insertar(int fila, int columna, char * valor);
    void recorrerFilas();
    void recorrerColumnas();

    bool hayficha(char * nombre);
    int ubicacion_peon(char * pieza, int x, int y);
    int ubicacion_alfil(char * pieza, int x, int y);
    int ubicacion_caballo(char * pieza, int x, int y);
    int ubicacion_torre(char * pieza, int x, int y);
    QString estado_matriz();
    QString estado_filas();
    QString estado_columnas();
    void eliminar(int fila, int columna, char * dato);
};

QString nombre_correcto(QString pieza);

#endif // MATRIZORTOGONAL

