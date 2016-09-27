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
    //agregue esto
    nuevo->derecha = NULL;
    nuevo->abajo = NULL;
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
                if(nuevo->fila <= actual->abajo->fila) //Inserción en el medio
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

void Matriz::recorrerFilas()
{
    Encabezado * eFila = eFilas->primero;
    cout << "Recorrido Por Filas: ";

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

void Matriz::recorrerColumnas()
{
    Encabezado * eColumna = eColumnas->primero;
    cout << "Recorrido Por columnas: ";

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
    Encabezado * eColumna = eColumnas->primero;
    int contador = 0;
    while(eColumna != NULL){
        Nodo * actual = eColumna->acceso;
        while(actual!=NULL){
            if(strcmp(actual->valor,nombre)){ //si encuetra almenos una ficha
                contador++;
            }
            actual = actual->abajo;
        }
        eColumna = eColumna->siguiente;
    }
    if(contador>0){
        return true;
    }else{
        return false;
    }
}

int Matriz::ubicacion_peon(char *pieza, int destino_x, int destino_y){
    /*recorrido por columnas*/
    Encabezado * eColumna = eColumnas->primero;
    bool correcto=false;
    QString coordenada;
    while(eColumna != NULL){
        Nodo * actual = eColumna->acceso;

        while(actual != NULL){
            if(actual->valor != NULL){

                /*validaciones para peon negro*/
                if(strcmp(actual->valor,pieza) == 0){
                    /*encontro la pieza*/
                    int actual_x = actual->fila;
                    int actual_y = actual->columna;

                    //cout<<"ubicacion peon: actuales"<<endl;
                    //cout<<actual_x<<endl;
                    //cout<<actual_y<<endl;
                    if(actual_x < destino_x){
                        /*movimiento hacia abajo*/
                        if(destino_x == actual_x + 1){
                            //el peon solo puede moverse una casilla
                            if(actual_y == destino_y){
                                //movera hacia abajo la pieza
                                coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                                correcto = true;
                                break;
                            }else{
                                //movera hacia abajo en diagonal izquierda/derecha la pieza
                                if(actual_x != 2){
                                    //si esta en cualquier otra fila
                                    if(actual_y + 1 == destino_y && actual_y + 1 < 9){
                                        //diagonal derecha
                                        coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                                        correcto = true;
                                        break;
                                    }else if(actual_y - 1 == destino_y && actual_y - 1 > 0){
                                        //diagonal izquierda
                                        coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                                        correcto = true;
                                        break;
                                    }else{
                                        actual = actual->abajo;
                                    }
                                }else{
                                    /* regla impuesta:
                                     * no se puede mover un peon negro en diagonal si esta en la fila inicio
                                     * */
                                    actual = actual->abajo;
                                }
                            }
                        }else{
                            actual = actual->abajo;
                        }
                    }else if(actual_x > destino_x){
                        /*movimiento hacia arriba*/
                        if(destino_x == actual_x - 1){
                            //el peon solo puede regresar una casilla
                            if(actual_y != destino_y){
                                //movera hacia arriba en diagonal izq/der la pieza
                                if(actual_y + 1 == destino_y && actual_y + 1 < 9){
                                    //diagonal derecha
                                    coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                                    correcto = true;
                                    break;
                                }else if(actual_y - 1 == destino_y && actual_y - 1 > 0){
                                    //diagonal izquierda
                                    coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                                    correcto = true;
                                    break;
                                }else{
                                    actual = actual->abajo;
                                }
                            }else{
                                actual = actual->abajo;
                            }
                        }else{
                            actual = actual->abajo;
                        }
                    }else{
                        break;
                    }
                }else{
                    /*si no la encontro continua hacia abajo de la columna*/
                    actual = actual->abajo;
                }
            }else{
                break;
            }
        }//fin segundo while

        if(correcto == true){
           break;
        }else{
            eColumna = eColumna->siguiente;
        }
    }//fin primer while

    if(correcto == true){
        int ncoor = coordenada.toInt(); //retorno coordenada separada por un 0 205 = (2,5)
        return ncoor;
    }else{
        return 0;
    }

}

int Matriz::ubicacion_alfil(char *pieza, int x, int y){
    /*recorrido por columnas*/
    Encabezado * eColumna = eColumnas->primero;
    bool correcto=false;
    QString coordenada;
    while(eColumna != NULL){
        Nodo * actual = eColumna->acceso;

        while(actual != NULL){
            if(actual->valor != NULL){

                /*validaciones para alfil negro*/
                if(strcmp(actual->valor,pieza) == 0){
                    /*encontro la pieza*/
                    int actual_x = actual->fila;
                    int actual_y = actual->columna;

                    //cout<<"ubicacion peon: actuales"<<endl;
                    //cout<<actual_x<<endl;
                    //cout<<actual_y<<endl;
                    if(actual_x < destino_x || actual_x > destino_x){
                        /*movimiento vertical*/
                        if(actual_y == destino_y){
                            coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                            correcto=true;
                            break;
                        }else{
                            actual = actual->abajo;
                        }
                    }else if(actual_x == destino_x){
                        /*movimiento horizontal*/
                        coordenada = QString::number(actual_x) + "0" + QString::number(actual_y);
                        correcto=true;
                        break;
                    }else if(actual_x == destino_x && actual_y = destino_y){
                        /*caso especial*/
                    }else{
                        break;
                    }
                }else{
                    /*si no la encontro continua hacia abajo de la columna*/
                    actual = actual->abajo;
                }
            }else{
                break;
            }
        }//fin segundo while

        if(correcto == true){
           break;
        }else{
            eColumna = eColumna->siguiente;
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
    Encabezado * eColumna = eColumnas->primero;
    QString tablero = "";
    char* dato_nodo = (char*)malloc(2);
    int contador =0, x=0, y=0;
    while(eColumna != NULL)
    {
        Nodo * actual = eColumna->acceso;
        while(actual != NULL)
        {
            if(actual->valor != NULL){
                strcpy(dato_nodo, actual->valor); //dato_nodo = "Rn"
                /*char* a qstring*/
                y = actual->columna;
                QString texto_nodo = QString::fromStdString(dato_nodo);
                if(texto_nodo != "N"){
                    QString pieza = nombre_correcto(texto_nodo);
                    tablero += "node" + QString::number(contador) + "[label=\"" + pieza + "\"];#" + QString::number(contador) + "#" + QString::number(y);
                    if(eColumna->siguiente != NULL || actual->abajo != NULL)
                    {
                        tablero += "%";
                        /*valores=node0[label="Rn"];#0#2#3%
                         * Rn->
                         * */
                        contador++;
                    }else{
                        tablero += "%";
                    }
                    actual = actual->abajo;
                }else{
                    actual = actual->abajo;
                }

            }else{
                break;
            }
        }//fin segundo while
        tablero += "fincol";
        /*node0label[]#0%....%node10[label...]#10%fincol
         * cn->pn->cb->fincol
         * */
        eColumna = eColumna->siguiente;
    }//fin primer while

    /*nota: retorna correctas las columnas*/
    return tablero;
}

QString nombre_correcto(QString pieza){
    if(pieza == "Rn"){
        return "Rey n.";
    }else if(pieza == "Dn"){
        return "Dama n.";
    }else if(pieza == "Tn"){
        return "Torre n.";
    }else if(pieza == "An"){
        return "Alfil n.";
    }else if(pieza == "Cn"){
        return "Caballo n.";
    }else if(pieza == "Pn"){
        return "Peon n.";
    }else if(pieza == "Rb"){
        return "Rey b.";
    }else if(pieza == "Db"){
        return "Dama b.";
    }else if(pieza == "Tb"){
        return "Torre b.";
    }else if(pieza == "Ab"){
        return "Alfil b.";
    }else if(pieza == "Cb"){
        return "Caballo b.";
    }else if(pieza == "Pb"){
        return "Peon b.";
    }
}

void Matriz::eliminar(int fila, int columna, char *dato){
    Encabezado * eColumna = eColumnas->primero;
    Encabezado * eFila = eFilas->primero;
    bool correcto = false;
    cout << "Eliminando:" <<endl;
    cout<<fila<<endl;
    cout<<columna<<endl;
    char* dato_nodo = (char*)malloc(5);

    while(eColumna != NULL)
    {
        Nodo * actual = eColumna->acceso;
        if(strcmp(actual->valor, dato) == 0 && actual->fila == fila && actual->columna == columna){
            /*verificamos si es el primer dato de la columna*/

            if(actual->abajo != NULL && actual->derecha != NULL){
                //1er caso: tiene nodos a la derecha y abajo

                if(actual->fila != eFila->acceso->fila){
                    while(eFila->id != fila){
                        eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                    }
                }

                //mov. vertical
                if(strcmp(dato, eColumna->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                    Nodo* arb = eColumna->acceso;
                    Nodo* abj = actual->abajo;
                    arb->abajo = abj;
                    abj->arriba = eColumna->acceso;
                }else{
                    Nodo* arb = actual->arriba;
                    Nodo* abj = actual->abajo;
                    arb->abajo = abj;
                    abj->arriba = arb;
                }

                //mov. horizontal
                Nodo* der = actual->derecha;
                if(strcmp(dato, eFila->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                    eFila->acceso->derecha = der;
                    der->izquierda = eFila->acceso;
                }else{
                    Nodo* izq = actual->izquierda;
                    izq->derecha = der;
                    der->izquierda = izq;
                }
                //se elimina
                correcto=true;
                free(actual);
            }else if(actual->abajo != NULL && actual->derecha == NULL){
                //2do caso: tiene nodos hacia abajo pero no a la derecha.

                if(actual->fila != eFila->acceso->fila){
                    while(eFila->id != fila){
                        eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                    }
                }
                //mov. vertical
                if(strcmp(dato, eColumna->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                    Nodo* arb = eColumna->acceso;
                    Nodo* abj = actual->abajo;
                    arb->abajo = abj;
                    abj->arriba = arb;
                }else{
                    Nodo* arb = actual->arriba;
                    Nodo* abj = actual->abajo;
                    arb->abajo = abj;
                    abj->arriba = arb;
                }

                //mov. horizontal
                if(strcmp(actual->valor, eFila->acceso->valor)==0 && eFila->acceso->fila == actual->fila && eColumna->acceso->columna == actual->columna){
                    eFila->acceso->derecha = NULL;
                }else{
                    cout<<eFila->acceso->fila<<endl;
                    cout<<eFila->acceso->columna<<endl;
                    Nodo* izq = actual->izquierda;
                    izq->derecha = NULL;
                }
                //se elimina
                correcto=true;
                free(actual);
                break;
            }else if(actual->abajo == NULL && actual->derecha != NULL){
                //3er caso: tiene nodos hacia la derecha pero no hacia abajo.

                if(actual->fila != eFila->acceso->fila){
                    while(eFila->id != fila){
                        eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                    }
                }

                //mov. vertical
                if(strcmp(dato, eColumna->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                    eColumna->acceso->abajo = NULL;
                }else{
                    Nodo* arb = actual->arriba;
                    arb->abajo = NULL;
                }

                //mov. horizontal
                Nodo* der = actual->derecha;
                if(strcmp(actual->valor, eFila->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                    eFila->acceso->derecha = der;
                    der->izquierda = eFila->acceso;
                }else{
                    Nodo* izq = actual->izquierda;
                    izq->derecha = der;
                    der->izquierda = izq;
                }

                //se eliminia
                correcto=true;
                free(actual);
                break;
            }else{
                //4to caso: no tiene nodos a la derecha ni hacia abajo.

                if(actual->fila != eFila->acceso->fila){
                    while(eFila->id != fila){
                        eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                    }
                }

                //mov. vertical
                if(strcmp(dato, eColumna->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                    eColumna->acceso->abajo = NULL;
                }else{
                    Nodo* arb = actual->arriba;
                    arb->abajo = NULL;
                }

                //mov. horizontal
                if(strcmp(actual->valor, eFila->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                    eFila->acceso->derecha = NULL;
                }else{
                    Nodo* izq = actual->izquierda;
                    izq->derecha = NULL;
                }

                //se elimina
                correcto=true;
                free(actual);
                break;
            }
        }else{
            /*como no es el primero recorremos el resto de la matriz*/
            //para ver que tiene el nodo
            strcpy(dato_nodo, actual->valor);
            QString texto_nodo = QString::fromStdString(dato_nodo);
            cout<<"contenido del nodo"<<endl;
            cout<<texto_nodo.toStdString()<<endl;

            while(actual != NULL)
            {
                //para ver que tiene el nodo
                //strcpy(dato_nodo, actual->valor);
                //QString texto_nodo = QString::fromStdString(dato_nodo);
                //cout<<"contenido del nodo"<<endl;
                //cout<<texto_nodo.toStdString()<<endl;

                if(strcmp(actual->valor, dato) == 0 && actual->fila == fila && actual->columna == columna){
                    /*encuentra el dato*/

                    if(actual->abajo != NULL && actual->derecha != NULL){
                        //1er caso: tiene nodos a la derecha y abajo.

                        if(actual->fila != eFila->acceso->fila){
                            while(eFila->id != fila){
                                eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                            }
                        }

                        //mov. vertical
                        Nodo* arb = actual->arriba;
                        Nodo* abj = actual->abajo;
                        arb->abajo = abj;
                        abj->arriba = arb;

                        //mov. horizontal
                        Nodo* der = actual->derecha;
                        if(strcmp(dato, eFila->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                            eFila->acceso->derecha = der;
                            der->izquierda = eFila->acceso;
                        }else{
                            Nodo* izq = actual->izquierda;
                            izq->derecha = der;
                            der->izquierda = izq;
                        }
                        //se elimina
                        correcto=true;
                        free(actual);
                        break;
                    }else if(actual->abajo != NULL && actual->derecha == NULL){
                        //2do caso: tiene nodos hacia abajo pero no a la derecha.

                        if(actual->fila != eFila->acceso->fila){
                            while(eFila->id != fila){
                                eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                            }
                        }
                        //mov. vertical
                        Nodo* arb = actual->arriba;
                        Nodo* abj = actual->abajo;
                        arb->abajo = abj;
                        abj->arriba = arb;
                        //mov. horizontal
                        if(strcmp(actual->valor, eFila->acceso->valor)==0 && eFila->acceso->fila == actual->fila && eColumna->acceso->columna == actual->columna){
                            eFila->acceso->derecha = NULL;
                        }else{
                            cout<<eFila->acceso->fila<<endl;
                            cout<<eFila->acceso->columna<<endl;
                            Nodo* izq = actual->izquierda;
                            izq->derecha = NULL;
                        }
                        //se elimina
                        correcto=true;
                        free(actual);
                        break;
                    }else if(actual->abajo == NULL && actual->derecha != NULL){
                        //3er caso: tiene nodos hacia la derecha pero no hacia abajo.

                        if(actual->fila != eFila->acceso->fila){
                            while(eFila->id != fila){
                                eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                            }
                        }

                        //mov. vertical
                        Nodo* arb = actual->arriba;
                        arb->abajo = NULL;

                        //mov. horizontal
                        Nodo* der = actual->derecha;
                        if(strcmp(actual->valor, eFila->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                            eFila->acceso->derecha = der;
                            der->izquierda = eFila->acceso;
                        }else{
                            Nodo* izq = actual->izquierda;
                            izq->derecha = der;
                            der->izquierda = izq;
                        }

                        //se eliminia
                        correcto=true;
                        free(actual);
                        break;
                    }else if(actual->derecha == NULL && actual->abajo == NULL){
                        //4to caso: no tiene nodos a la derecha ni hacia abajo.

                        if(actual->fila != eFila->acceso->fila){
                            while(eFila->id != fila){
                                eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                            }
                        }

                        //mov. vertical
                        Nodo* arb = actual->arriba;
                        arb->abajo = NULL;

                        //mov. horizontal
                        if(strcmp(actual->valor, eFila->acceso->valor)==0 && eFila->acceso->fila == fila && eColumna->acceso->columna == columna){
                            eFila->acceso->derecha = NULL;
                        }else{
                            Nodo* izq = actual->izquierda;
                            izq->derecha = NULL;
                        }

                        //se elimina
                        correcto=true;
                        free(actual);
                        break;
                    }else{
                        cout << "falta validacion" << endl;
                    }
                }else{
                    /*el dato no coincide continua hacia abajo de la columna
                     * y se avanza el numero de fila
                     * */

                    actual = actual->abajo;
                    eFila = eFila->siguiente;
                }
            }//fin segundo while

        }//fin primer if

        if(correcto == true){
            /*borro el nodo detiene el primer while*/
            break;
        }else{
            /*no encontro nada en una columna avanza a la siguiente*/
            eColumna = eColumna->siguiente;
            eFila = eFilas->primero;
        }

    }//fin primer while
}
