#include <MatrizOrtogonal.h>
#include <stdlib.h>
#include <iostream>
#include "string.h"
#include "QString"

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
    }//FIN_FILAS
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
    }//FIN_COLUMNAS
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
                    //cout << "||";
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

int Matriz::ubicacion_peon(char *pieza, int destino_x, int destino_y){
    /*recorrido por columnas*/
    Encabezado * eFila = eFilas->primero;
    bool correcto=false;
    QString coordenada;
    while(eFila != NULL){
        Nodo * actual = eFila->acceso;
        while(actual != NULL){
            if(actual->valor != NULL){
                if(strcmp(actual->valor,pieza) == 0){
                    int actual_x = actual->fila;
                    int actual_y = actual->columna;

                    if(actual_x < destino_x){
                        if(destino_x == actual_x+1){
                            if(destino_y == actual_y-1 || destino_y == actual_y+1){
                                coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                                correcto=true;
                                break;
                            }else{
                                actual = actual->derecha;
                            }
                        }else{
                            actual = actual->derecha;
                        }
                    }else if(actual_x == destino_x){
                        if(destino_y==actual_y-1 || destino_y==actual_y+1){
                            correcto=true;
                            coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                            break;
                        }else{
                            actual = actual->derecha;
                        }
                    }else if(actual_x > destino_x){
                        if(destino_x == actual_x-1){
                            if(destino_y == actual_y-1 || destino_y == actual_y+1){
                                coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                                correcto=true;
                                break;
                            }else{
                                actual = actual->derecha;
                            }
                        }else{
                            actual = actual->derecha;
                        }
                    }else{
                        break;
                    }
                }else{
                    actual = actual->derecha;
                }
            }else{
                break;
            }
        }//fin segundo while
        if(correcto == true){
           break;
        }else{
            eFila = eFila->siguiente;
        }
    }//fin primer while

    if(correcto == true){
        int ncoor = coordenada.toInt(); //retorno coordenada separada por un 0 205 = (2,5)
        return ncoor;
    }else{
        return 0;
    }

}

QString Matriz::estado_matriz(){
    /*recorrido por columnas*/
    Encabezado * eFila = eFilas->primero;
    QString tablero = "";
    char* dato_nodo = (char*)malloc(2);
    int contador =0, x=0, y=0;
    while(eFila != NULL)
    {
        Nodo * actual = eFila->acceso;
        while(actual != NULL)
        {
            if(actual->valor != NULL){
                strcpy(dato_nodo, actual->valor); //dato_nodo = "Rn"
                /*char* a qstring*/
                x = actual->fila;
                y = actual->columna;
                QString texto_nodo = QString::fromStdString(dato_nodo);
                tablero += "node" + QString::number(contador) + "[label=\"" + texto_nodo + "\"];#" + QString::number(contador) + "#" + QString::number(x) + "#" + QString::number(y);
                if(eFila->siguiente != NULL || actual->derecha != NULL)
                {
                    tablero += "%";
                    /*valores=node0[label="Rn"];#0#2#3%
                     * Rn->
                     * */
                    contador++;
                }else{
                    tablero += "%";
                }
                actual = actual->derecha;
            }else{
                break;
            }
        }//fin segundo while
        tablero += "fincol";
        /*node0label[]#0%....%node10[label...]#10%fincol
         * cn->pn->cb->fincol
         * */
        eFila = eFila->siguiente;
    }//fin primer while

    return tablero;
}

