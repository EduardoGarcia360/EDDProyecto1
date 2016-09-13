#include <MatrizOrtogonal.h>
#include <stdlib.h>
#include <iostream>
#include "string.h"

using namespace std;

Nodo::Nodo(int fila, int columna, char * valor)
{
    this->fila = fila;
    this->columna = columna;
    this->valor = valor;
}

Encabezado::Encabezado(int id)
{
    this->id = id;
}

void ListaEncabezados::insertar(Encabezado * nuevo)
{
    if(primero == NULL)
    {
       primero = nuevo;
    }
    else
    {
        if(nuevo->id < primero->id) //Inserción al inicio
        {
            nuevo->siguiente = primero;
            primero->anterior = nuevo;
            primero = nuevo;
        }
        else
        {
            Encabezado * actual = primero;
            while(actual->siguiente != NULL)
            {
                if(nuevo->id < actual->siguiente->id) //Inserción en el medio
                {
                    nuevo->siguiente = actual->siguiente;
                    actual->siguiente->anterior = nuevo;
                    nuevo->anterior = actual;
                    actual->siguiente = nuevo;
                    break;
                }

                actual = actual->siguiente;
            }

            if(actual->siguiente == NULL) //Inserción al final
            {
                actual->siguiente = nuevo;
                nuevo->anterior = actual;
            }
        }
    }
}

Encabezado * ListaEncabezados::getEncabezado(int id)
{
    Encabezado * actual = primero;
    while(actual != NULL)
    {
        if(actual->id == id)
        {
            return actual;
        }

        actual = actual->siguiente;
    }

    return NULL;
}

Matriz::Matriz()
{
    this->eFilas = new ListaEncabezados();
    this->eColumnas = new ListaEncabezados();
}

void Matriz::insertar(int fila, int columna, char * valor)
{
    Nodo * nuevo = new Nodo(fila, columna, valor);

    //INSERCION_FILAS
    Encabezado * eFila = eFilas->getEncabezado(fila);
    if(eFila == NULL) //Si no existe encabezado se crea.
    {
        eFila = new Encabezado(fila);
        eFilas->insertar(eFila);
        eFila->acceso = nuevo;
    }
    else
    {
        if(nuevo->columna < eFila->acceso->columna) //Inserción al inicio
        {
            nuevo->derecha = eFila->acceso;
            eFila->acceso->izquierda = nuevo;
            eFila->acceso = nuevo;
        }
        else
        {
            Nodo * actual = eFila->acceso;
            while(actual->derecha != NULL)
            {
                if(nuevo->columna < actual->derecha->columna) //Inserción en el medio
                {
                    nuevo->derecha = actual->derecha;
                    actual->derecha->izquierda = nuevo;
                    nuevo->izquierda = actual;
                    actual->derecha = nuevo;
                    break;
                }

                actual = actual->derecha;
            }

            if(actual->derecha == NULL) //Inserción al final
            {
                actual->derecha = nuevo;
                nuevo->izquierda = actual;
            }
        }
    }
    //FIN_FILAS

    //INSERCION_COLUMNAS
    Encabezado * eColumna = eColumnas->getEncabezado(columna);
    if(eColumna == NULL) //Si no existe encabezado se crea.
    {
        eColumna = new Encabezado(columna);
        eColumnas->insertar(eColumna);
        eColumna->acceso = nuevo;
    }
    else
    {
        if(nuevo->fila < eColumna->acceso->fila) //Inserción al inicio
        {
            nuevo->abajo = eColumna->acceso;
            eColumna->acceso->arriba = nuevo;
            eColumna->acceso = nuevo;
        }
        else
        {
            Nodo * actual = eColumna->acceso;
            while(actual->abajo != NULL)
            {
                if(nuevo->fila < actual->abajo->fila) //Inserción en el medio
                {
                    nuevo->abajo = actual->abajo;
                    actual->abajo->arriba = nuevo;
                    nuevo->arriba = actual;
                    actual->abajo = nuevo;
                    break;
                }

                actual = actual->abajo;
            }

            if(actual->abajo == NULL) //Inserción al final
            {
                actual->abajo = nuevo;
                nuevo->arriba = actual;
            }
        }
    }
    //FIN_COLUMNAS
}

void Matriz::recorrerColumnas()
{
    Encabezado * eFila = eFilas->primero;
    cout << "Recorrido Por Columnas: ";

    while(eFila != NULL)
    {
        Nodo * actual = eFila->acceso;
        while(actual != NULL)
        {
            if(actual->valor != NULL){
                cout << actual->valor;
                if(eFila->siguiente != NULL || actual->derecha != NULL)
                {
                    cout << "->";
                }else{
                    cout << "||";
                }

                actual = actual->derecha;
            }else{
                break;
            }
        }
        cout << "||";
        eFila = eFila->siguiente;
    }

    cout << endl;
}

void Matriz::recorrerFilas()
{
    Encabezado * eColumna = eColumnas->primero;
    cout << "Recorrido Por Filas: ";

    while(eColumna != NULL)
    {
        Nodo * actual = eColumna->acceso;
        while(actual != NULL)
        {
            if(actual->valor != NULL){
                cout << actual->valor;

                if(eColumna->siguiente != NULL || actual->abajo != NULL)
                {
                    cout << "->";
                }else{
                    cout << "||";
                }

                actual = actual->abajo;
            }else{
                break;
            }

        }
        cout << "||";
        eColumna = eColumna->siguiente;
    }

    cout << endl;
}

/*verificamos la existencia de alguna ficha*/
bool Matriz::hayficha(char * nombre){
    /*se hace un recorrido por columnas*/
    Encabezado * eFila = eFilas->primero;
    int contador = 0;
    while(eFila != NULL){
        Nodo * actual = eFila->acceso;
        while(actual!=NULL){
            if(strcmp(actual->valor,nombre)){ //si encuetra almenos una ficha
                contador++;
            }
            actual = actual->derecha;
        }
        eFila = eFila->siguiente;
    }
    if(contador>0){
        return true;
    }else{
        return false;
    }
}

/*movimientos*/
bool Matriz::moverpeon(char * pieza, int destino_x, int destino_y){//char *pieza
    /*recorrido por columnas*/
    Encabezado * eFila = eFilas->primero;
    bool correcto=false;
    while(eFila != NULL){
        Nodo * actual = eFila->acceso;
        while(actual != NULL){
            if(actual->valor != NULL){
                if(strcmp(actual->valor,pieza) == 0){
                    int actual_x = actual->fila;
                    int actual_y = actual->columna;
                    cout << "posicion actual x" << endl;
                    cout << actual_x << endl;
                    cout << "posicion actual y" << endl;
                    cout << actual_y << endl;
                    if(actual_x < destino_x){
                        cout << "-----ENTRO EN ACTUAL_X < DESTINO_X" << endl;
                        /*---mover en diagonal a la columna derecha:
                         * ej. para piezas blancas:
                         * pos. actual (4,7)
                         * pos. destino (5,6)
                         * () () []
                         * () []/()
                         * ej. para piezas negras:
                         * pos. actual (4,2)
                         * pos. destino (5,3)
                         * () []\()
                         * () () []
                         * */
                        if(destino_x == actual_x+1){
                            /*peon solo puede moverse una casilla*/
                            if(destino_y == actual_y-1 || destino_y == actual_y+1){
                                /*si coincide la posicion es valida para mover el peon*/
                                correcto=true;
                                break;
                            }else{
                                /*si no coincide sigue avanzando*/
                                actual = actual->derecha;
                            }
                        }else{
                            /*si es una casilla ubicada a 2 pos, sigue recorriendo*/
                            actual = actual->derecha;
                        }
                    }else if(actual_x == destino_x){
                        cout << "-----ENTRO EN ACTUAL_X = DESTINO_X" << endl;
                        /*---mover en la misma columna:
                         * ej. posicion actual (3,4)
                         * posicion destino (3,3)
                         * (2,3) [3,3] (4,3)
                         *         ^
                         * (2,4) [3,4] (4,4)
                         * actual_y -1 para las piezas negras que van bajando
                         * actual_y +1 para las piezas blancas que van subiendo
                         * */
                        if(destino_y==actual_y-1 || destino_y==actual_y+1){
                            /*si coincide la posicion es valida*/
                            correcto=true;
                            break;
                        }else{
                            actual = actual->derecha;
                        }
                    }else if(actual_x > destino_x){
                        cout << "-----ENTRO EN ACTUAL_X > DESTINO_X" << endl;
                        /*---mover en diagonal a la columna izquierda:
                         * ej. para piezas blancas:
                         * pos. actual (4,7)
                         * pos. destino (3,6)
                         * () () []
                         * ()\[] ()
                         * ej. para piezas negras:
                         * pos. actual (4,2)
                         * pos. destino (3,3)
                         * ()/[] ()
                         * () () []
                         * */
                        if(destino_x == actual_x-1){
                            if(destino_y == actual_y-1 || destino_y == actual_y+1){
                                /*si coincide la posicion es valida para mover el peon*/
                                correcto=true;
                                break;
                            }else{
                                /*si no coincide sigue avanzando*/
                                actual = actual->derecha;
                            }
                        }else{
                            /*si no es igual sigue avanzando*/
                            actual = actual->derecha;
                        }
                    }else{
                        cout << "-----ENTRO EN ULTIMO ELSE" << endl;
                        break;
                    }
                }else{
                    /*sigue recorriendo si no encuentra
                     * la pieza buscada
                     * */
                    actual = actual->derecha;
                }
            }else{
                break;
            }
        }//fin segundo while
        if(correcto == true){
            /*si alguna pieza coincide, se detiene el primer while*/
           break;
        }else{
            eFila = eFila->siguiente;
        }
    }//fin primer while

    if(correcto == true){
        return true;
    }else{
        cout << "-----NINGUNA COINCIDENCIA" << endl;
        return false;
    }
}
