#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "string.h"
#include "QMessageBox"
#include "cstdlib"
#include "iostream"
#include "fstream"
#include "MatrizOrtogonal.h"
#include "listasimple.h"
using namespace std;

/*fichas*/
QImage peonnegro, alfilnegro, caballonegro, torrenegro, damanegro, reynegro;
QImage peonblanco, alfilblanco, caballoblanco, torreblanco, damablanco, reyblanco;
/*matriz de label para los tableros*/
QLabel* tab0[9][9];
QLabel* tab1[9][9];
QLabel* tab2[9][9];
/*matriz de numero para validar posiciones de las piezas*/
int tabpos0[9][9];
int tabpos1[9][9];
int tabpos2[9][9];
/*matriz para validar posiciones*/
Matriz* tablogic0 = new Matriz();
Matriz* tablogic1 = new Matriz();
Matriz* tablogic2 = new Matriz();
/*fondo para los scrollarea*/
QLabel* fondo0;
QLabel* fondo1;
QLabel* fondo2;
/*bool para validar el turno del jugador*/
bool jugador1 = true;
/*para almacenar los nodos para graficar*/
//ListaEnlazada * lista_nodos = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));
ListaEnlazada * lista_numero = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));
//ListaEnlazada * lista_x = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));
ListaEnlazada * lista_y = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*imagenes de las fichas negras*/
    peonnegro.load("/home/eduardo/Descargas/peonnegro.png");
    alfilnegro.load("/home/eduardo/Descargas/alfilnegro.png");
    caballonegro.load("/home/eduardo/Descargas/caballonegro.png");
    torrenegro.load("/home/eduardo/Descargas/torrenegro.png");
    damanegro.load("/home/eduardo/Descargas/damanegro.png");
    reynegro.load("/home/eduardo/Descargas/reynegro.png");

    /*imagenes de las fichas blancas*/
    peonblanco.load("/home/eduardo/Descargas/peonblanco.png");
    alfilblanco.load("/home/eduardo/Descargas/alfilblanco.png");
    caballoblanco.load("/home/eduardo/Descargas/caballoblanco.png");
    torreblanco.load("/home/eduardo/Descargas/torreblanco.png");
    damablanco.load("/home/eduardo/Descargas/damablanco.png");
    reyblanco.load("/home/eduardo/Descargas/reyblanco.png");

    /*color de fondo para cada casilla*/
    QPalette blanco, gris;
    blanco.setColor(QPalette::Window, Qt::white);
    gris.setColor(QPalette::Window, Qt::gray);

    fondo0 = new QLabel();
    fondo1 = new QLabel();
    fondo2 = new QLabel();

    /*creando tableros*/
    for(int y=0; y<9; y++){
        for(int x=0; x<9; x++){

            /*para tablero nivel 0*/
            tab0[x][y] = new QLabel(fondo0);
            tab0[x][y]->setGeometry(y*32,x*30,32,30); //ancho, alto
            tab0[x][y]->setAutoFillBackground(true);
            /*para tablero nivel 1*/
            tab1[x][y] = new QLabel(fondo1);
            tab1[x][y]->setGeometry(y*32 ,x*30,32,30);
            tab1[x][y]->setAutoFillBackground(true);
            /*para tablero nivel 2*/
            tab2[x][y] = new QLabel(fondo2);
            tab2[x][y]->setGeometry(y*32 ,x*30,32,30);
            tab2[x][y]->setAutoFillBackground(true);

            /*colocando nombre de fila y columna*/
            if(x==0){
                /*colocando nombre a las columnas*/
                if(y==1){
                    tab0[x][y]->setText("1");
                    tab1[x][y]->setText("1");
                    tab2[x][y]->setText("1");
                }else if(y==2){
                    tab0[x][y]->setText("2");
                    tab1[x][y]->setText("2");
                    tab2[x][y]->setText("2");
                }else if(y==3){
                    tab0[x][y]->setText("3");
                    tab1[x][y]->setText("3");
                    tab2[x][y]->setText("3");
                }else if(y==4){
                    tab0[x][y]->setText("4");
                    tab1[x][y]->setText("4");
                    tab2[x][y]->setText("4");
                }else if(y==5){
                    tab0[x][y]->setText("5");
                    tab1[x][y]->setText("5");
                    tab2[x][y]->setText("5");
                }else if(y==6){
                    tab0[x][y]->setText("6");
                    tab1[x][y]->setText("6");
                    tab2[x][y]->setText("6");
                }else if(y==7){
                    tab0[x][y]->setText("7");
                    tab1[x][y]->setText("7");
                    tab2[x][y]->setText("7");
                }else if(y==8){
                    tab0[x][y]->setText("8");
                    tab1[x][y]->setText("8");
                    tab2[x][y]->setText("8");
                }
            }else if(y==0){
                /*colocando nombre a las filas*/
                if(x==1){
                    tab0[x][y]->setText("H");
                    tab1[x][y]->setText("H");
                    tab2[x][y]->setText("H");
                }else if(x==2){
                    tab0[x][y]->setText("G");
                    tab1[x][y]->setText("G");
                    tab2[x][y]->setText("G");
                }else if(x==3){
                    tab0[x][y]->setText("F");
                    tab1[x][y]->setText("F");
                    tab2[x][y]->setText("F");
                }else if(x==4){
                    tab0[x][y]->setText("E");
                    tab1[x][y]->setText("E");
                    tab2[x][y]->setText("E");
                }else if(x==5){
                    tab0[x][y]->setText("D");
                    tab1[x][y]->setText("D");
                    tab2[x][y]->setText("D");
                }else if(x==6){
                    tab0[x][y]->setText("C");
                    tab1[x][y]->setText("C");
                    tab2[x][y]->setText("C");
                }else if(x==7){
                    tab0[x][y]->setText("B");
                    tab1[x][y]->setText("B");
                    tab2[x][y]->setText("B");
                }else if(x==8){
                    tab0[x][y]->setText("A");
                    tab1[x][y]->setText("A");
                    tab2[x][y]->setText("A");
                }
            }else{
                /*coloreando cada casilla*/
                if(x==1 || x==3 || x==5 || x==7){
                    if(y==1 || y==3 || y==5 || y==7){
                        tab0[x][y]->setPalette(blanco);
                        tab1[x][y]->setPalette(blanco);
                        tab2[x][y]->setPalette(blanco);
                    }else{
                        tab0[x][y]->setPalette(gris);
                        tab1[x][y]->setPalette(gris);
                        tab2[x][y]->setPalette(gris);
                    }
                }else{
                    if(y==1 || y==3 || y==5 || y==7){
                        tab0[x][y]->setPalette(gris);
                        tab1[x][y]->setPalette(gris);
                        tab2[x][y]->setPalette(gris);
                    }else{
                        tab0[x][y]->setPalette(blanco);
                        tab1[x][y]->setPalette(blanco);
                        tab2[x][y]->setPalette(blanco);
                    }
                }
            }
        }
    }

    /*agregando las piezas*/
    for(int y=1; y<9; y++){
        for(int x=1; x<9; x++){
            /*agregando fichas negras*/
            if(x==1){
                if(y==1){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tablogic0->insertar(x,y,"Cn");
                    tablogic2->insertar(x,y,"Cn");
                    tabpos0[x][y]=5;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=5;
                }else if(y==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tablogic0->insertar(x,y,"Cn");
                    tablogic1->insertar(x,y,"Cn");
                    tabpos0[x][y]=5;
                    tabpos1[x][y]=5;
                    tabpos2[x][y]=0;
                }else if(y==2){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tablogic0->insertar(x,y,"An");
                    tablogic2->insertar(x,y,"An");
                    tabpos0[x][y]=4;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=4;
                }else if(y==7){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tablogic0->insertar(x,y,"An");
                    tablogic1->insertar(x,y,"An");
                    tabpos0[x][y]=4;
                    tabpos1[x][y]=4;
                    tabpos2[x][y]=0;
                }else if(y==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tablogic0->insertar(x,y,"Tn");
                    tablogic2->insertar(x,y,"Tn");
                    tabpos0[x][y]=3;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=3;
                }else if(y==6){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tablogic0->insertar(x,y,"Tn");
                    tablogic1->insertar(x,y,"Tn");
                    tabpos0[x][y]=3;
                    tabpos1[x][y]=3;
                    tabpos2[x][y]=0;
                }else if(y==4){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(reynegro));
                    tablogic0->insertar(x,y,"Rn");
                    tabpos0[x][y]=1;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=0;
                }else if(y==5){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(damanegro));
                    tablogic0->insertar(x,y,"Dn");
                    tabpos0[x][y]=2;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=0;
                }
            }else if(x==2){
                if(y==1 || y==2 || y==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tablogic0->insertar(x,y,"Pn");
                    tablogic2->insertar(x,y,"Pn");
                    tabpos0[x][y]=6;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=6;
                }else if(y==6 || y==7 || y==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tablogic0->insertar(x,y,"Pn");
                    tablogic1->insertar(x,y,"Pn");
                    tabpos0[x][y]=6;
                    tabpos1[x][y]=6;
                    tabpos2[x][y]=0;
                }else{
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tablogic0->insertar(x,y,"Pn");
                    tabpos0[x][y]=6;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=0;
                }
            }else if(x==7){
                /*agregando fichas blancas*/
                if(y==1 || y==2 || y==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tablogic0->insertar(x,y,"Pb");
                    tablogic1->insertar(x,y,"Pb");
                    tabpos0[x][y]=12;
                    tabpos1[x][y]=12;
                    tabpos2[x][y]=0;
                }else if(y==6 || y==7 || y==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tablogic0->insertar(x,y,"Pb");
                    tablogic2->insertar(x,y,"Pb");
                    tabpos0[x][y]=12;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=12;
                }else if(y==4 || y==5){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tablogic0->insertar(x,y,"Pb");
                    tabpos0[x][y]=12;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=0;
                }
            }else if(x==8){
                if(y==1){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tablogic0->insertar(x,y,"Cb");
                    tablogic1->insertar(x,y,"Cb");
                    tabpos0[x][y]=11;
                    tabpos1[x][y]=11;
                    tabpos2[x][y]=0;
                }else if(y==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tablogic0->insertar(x,y,"Cb");
                    tablogic2->insertar(x,y,"Cb");
                    tabpos0[x][y]=11;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=11;
                }else if(y==2){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tablogic0->insertar(x,y,"Ab");
                    tablogic1->insertar(x,y,"Ab");
                    tabpos0[x][y]=10;
                    tabpos1[x][y]=10;
                    tabpos2[x][y]=0;
                }else if(y==7){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tablogic0->insertar(x,y,"Ab");
                    tablogic2->insertar(x,y,"Ab");
                    tabpos0[x][y]=10;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=10;
                }else if(y==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tablogic0->insertar(x,y,"Tb");
                    tablogic1->insertar(x,y,"Tb");
                    tabpos0[x][y]=9;
                    tabpos1[x][y]=9;
                    tabpos2[x][y]=0;
                }else if(y==6){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tablogic0->insertar(x,y,"Tb");
                    tablogic2->insertar(x,y,"Tb");
                    tabpos0[x][y]=9;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=9;
                }else if(y==4){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(reyblanco));
                    tablogic0->insertar(x,y,"Rb");
                    tabpos0[x][y]=7;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=0;
                }else if(y==5){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(damablanco));
                    tablogic0->insertar(x,y,"Db");
                    tabpos0[x][y]=8;
                    tabpos1[x][y]=0;
                    tabpos2[x][y]=0;
                }
            }else{
                tabpos0[x][y]=0;
                tabpos1[x][y]=0;
                tabpos2[x][y]=0;
            }
        }
    }

    /*lo agregamos al scrollpane*/
    ui->tablero0->setWidget(fondo0);
    ui->tablero1->setWidget(fondo1);
    ui->tablero2->setWidget(fondo2);
    //tablogic0->insertar(4, 5, "aqui");
    //tablogic0->recorrerColumnas();
    //tablogic0->recorrerFilas();
    /*--------------MODIFICAR EL LABEL----------------
         * QLabel *ejemplo = new QLabel("algo para mostrar");
         * ---para cambiar el color del label
         * ejemplo->setAutoFillBackground(true);
         * ejemplo->setPalette(gris);
         * ---para colocar una imagen en el label
         * ejemplo->setPixmap(QPixmap::fromImage(peonnegro));
         * */

        /*-------------COORDENADAS DEL TABLERO (x,y)-------------
         * (0,0)(1,0)(2,0)(3,0)..
         * (0,1)(1,1)(2,1)(3,1)..
         * (0,2)(1,2)(2,2)(3,2)..
         * (0,3)(1,3)(2,3)(3,3)..
         * (0,4)..
         * */

        /*-------------MATRIZ LOGICA-------------
         * Piezas negras: rn=REY, dn=DAMA, tn=TORRE, an=ALFIL, cn=CABALLO, pn=PEON
         * Piezas blancas: rb=REY, db=DAMA, tb=TORRE, ab=ALFIL, cb=CABALLO, pb=PEON
         * n = nada.
         * servira para ubicar las fichas en el tablero
         * */
    //crear_grafico_tablero(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnmover_clicked()
{
    QString coordenada = ui->txtmovimiento->text();
    if(coordenada.isEmpty() || coordenada.isNull()){
        ui->lblerror->setText("debes ingresar algo coño!");
    }else{
        /*se separa la coordenada ingresada
         * ej. P-0-C4
         * [P][0][C4]
         * (0)(1)(2)
         * */
        QStringList arreglocoordenada = coordenada.split("-");
        if(arreglocoordenada.length()-1 != 2){
            QMessageBox::information(this,"Error","Debes ingresar una coordenada valida.");
        }else{
            if(jugador1){
                /*turno del jugador 1 fichas negras*/
                jugador_negro(arreglocoordenada, coordenada);
            }else{
                /*turno del jugador 2 fichas blancas*/
                jugador_blanco(arreglocoordenada, coordenada);
            }
        }
    }
}

/*la declaracion de los nuevos metodos se hace en mainwindow.h*/

void MainWindow::jugador_negro(QStringList arreglocoordenada, QString coordenada){
    QString ficha = arreglocoordenada.at(0); //ficha = "p"
    /*validando que sea una ficha correcta*/
    if(ficha=="R"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*converciono qstring a char* */
            QString nficha = ficha+"n";
            char* cnficha = (char*)malloc(3);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            /*validando si aun hay alfiles negros*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida para moverse*/
                        int ub0 = tablogic0->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_peon(cnficha, destino_x, destino_y);
                        if(ub0>0){

                        }else if(ub1>0){

                        }else if(ub2>0){

                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Alfiles.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }
    }else if(ficha=="D"){
        //al perder a la dama pierde el juego
    }else if(ficha=="T"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*converciono qstring a char* */
            QString nficha = ficha+"n";
            char* cnficha = (char*)malloc(3);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            /*validando si aun hay alfiles negros*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida para moverse*/
                        int ub0 = tablogic0->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_peon(cnficha, destino_x, destino_y);
                        if(ub0>0){

                        }else if(ub1>0){

                        }else if(ub2>0){

                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Torres.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }
    }else if(ficha=="A"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*converciono qstring a char* */
            QString nficha = ficha+"n";
            char* cnficha = (char*)malloc(3);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            /*validando si aun hay alfiles negros*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida para moverse*/
                        int ub0 = tablogic0->ubicacion_alfil(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_alfil(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_alfil(cnficha, destino_x, destino_y);
                        if(ub0>0){
                            /*si hay una pieza que cumpla con el movimiento en el nivel 0*/
                            int pieza = tabpos0[destino_x][destino_y];
                            QString coo = QString::number(ub0); //ej. "406"
                            QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
                            QString tmp = arr_coo.at(0);
                            int actual_x = tmp.toInt(); //4
                            tmp = arr_coo.at(1);
                            int actual_y = tmp.toInt(); //6
                            if(pieza == 0){
                                /*posicion libre*/
                                tabpos0[actual_x][actual_y] = 0;
                                tablogic0->eliminar(actual_x, actual_y, "An");
                                tab0[actual_x][actual_y]->setText(" ");
                                //cout << "despues de eliminar" << endl;
                                //tablogic0->recorrerColumnas();
                                //tablogic0->recorrerFilas();

                                tabpos0[destino_x][destino_y] = 4;
                                tablogic0->insertar(destino_x,destino_y,"An");
                                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilnegro));

                                //cout << "despues de mover" << endl;
                                //tablogic0->recorrerColumnas();
                                //tablogic0->recorrerFilas();

                                ui->listamovimientos->addItem(coordenada);
                                ui->txtmovimiento->setText("");

                                jugador1=false;
                            }else if(pieza >=7 && pieza <=12){
                                /*hay una pieza blanca para comer en esa posicion*/
                            }else{
                                /*hay una pieza negra en esa posicion*/
                                ui->txtmovimiento->setText("");
                                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                            }
                        }else if(ub1>0){

                        }else if(ub2>0){

                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Alfiles.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }

    }else if(ficha=="C"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*converciono qstring a char* */
            QString nficha = ficha+"n";
            char* cnficha = (char*)malloc(3);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            /*validando si aun hay alfiles negros*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida para moverse*/
                        int ub0 = tablogic0->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_peon(cnficha, destino_x, destino_y);
                        if(ub0>0){

                        }else if(ub1>0){

                        }else if(ub2>0){

                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Caballos.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }
    }else if(ficha=="P"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();
        /*validar tablero*/
        if(tabdest==0 || tabdest==1 || tabdest==2){
            /*convercion QString a char* */
            QString nficha = ficha+"n";
            char * cnficha = (char*)malloc(3);
            char * tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            /*validar si hay almenos una pieza en algun tablero*/
            if(haypiezas0==true || haypiezas1==true || haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x != 0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida paraq que algun peon pueda moverse*/
                        int ub0 = tablogic0->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_peon(cnficha, destino_x, destino_y);
                        if(ub0 > 0){
                            /*si hay una pieza que cumpla con el movimiento en el nivel 0*/
                            int pieza = tabpos0[destino_x][destino_y];
                            QString coo = QString::number(ub0); //ej. 406
                            QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
                            QString tmp = arr_coo.at(0);
                            int actual_x = tmp.toInt(); //4
                            tmp = arr_coo.at(1);
                            int actual_y = tmp.toInt(); //6
                            if(pieza == 0){
                                /*posicion libre*/
                                tabpos0[actual_x][actual_y] = 0;
                                tablogic0->eliminar(actual_x, actual_y, "Pn");
                                tab0[actual_x][actual_y]->setText(" ");

                                tabpos0[destino_x][destino_y] = 6;
                                tablogic0->insertar(destino_x,destino_y,"Pn");
                                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonnegro));
                                ui->listamovimientos->addItem("-Jug.1:");
                                ui->listamovimientos->addItem(coordenada);
                                ui->txtmovimiento->setText("");

                                jugador1=false;
                            }else if(pieza >=7 && pieza <=12){
                                /*hay una pieza blanca para comer en esa posicion*/
                                tabpos0[actual_x][actual_y] = 0;
                                tablogic0->eliminar(actual_x, actual_y, "Pn");
                                tab0[actual_x][actual_y]->setText(" ");

                                QString pieza_a_borrar = nombre_pieza(pieza);
                                char * pab = (char*)malloc(2);
                                char * tmp = pieza_a_borrar.toLatin1().data();
                                strcpy(pab, tmp);
                                tabpos0[destino_x][destino_y]=6;
                                tablogic0->eliminar(destino_x, destino_y, pab);
                                tab0[destino_x][destino_y]->setText(" ");
                                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonnegro));
                                ui->listamovimientos->addItem("-Jug.1:");
                                ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                                ui->txtmovimiento->setText("");
                                //free(pab);
                                //free(tmp);
                                jugador1=false;
                            }else{
                                /*hay una pieza negra en esa posicion*/
                                ui->txtmovimiento->setText("");
                                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                            }
                        }else if(ub1 >0){
                            /*si hay una pieza que cumpla con el movimiento en el nivel 1*/
                            int pieza = tabpos1[destino_x][destino_y];
                            if(pieza == 0){
                                /*posicion libre*/
                            }else if(pieza >=7 && pieza <=12){
                                /*hay una pieza blanca en esa posicion*/
                            }else{
                                /*hay una pieza negra en esa posicion*/
                                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                            }
                        }else if(ub2 >0){
                            /*si hay una pieza que cumpla con el movimiento en el nivel 2*/
                            int pieza = tabpos2[destino_x][destino_y];
                            if(pieza == 0){
                                /*posicion libre*/
                            }else if(pieza >=7 && pieza <=12){
                                /*hay una pieza blanca en esa posicion*/
                            }else{
                                /*hay una pieza negra en esa posicion*/
                                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                            }
                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Peones.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }//fin validar tablero
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Pieza invalida o Usa Mayuscula.");
    }//fin validar piezas
}

void MainWindow::jugador_blanco(QStringList arreglocoordenada, QString coordenada){
    QString ficha = arreglocoordenada.at(0); //ficha = "p"
    /*validando que sea una ficha correcta*/
    if(ficha=="R"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*converciono qstring a char* */
            QString nficha = ficha+"n";
            char* cnficha = (char*)malloc(3);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            /*validando si aun hay alfiles negros*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida para moverse*/
                        int ub0 = tablogic0->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_peon(cnficha, destino_x, destino_y);
                        if(ub0>0){

                        }else if(ub1>0){

                        }else if(ub2>0){

                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Alfiles.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }
    }else if(ficha=="D"){
        //al perder a la dama pierde el juego
    }else if(ficha=="T"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*converciono qstring a char* */
            QString nficha = ficha+"n";
            char* cnficha = (char*)malloc(3);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            /*validando si aun hay alfiles negros*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida para moverse*/
                        int ub0 = tablogic0->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_peon(cnficha, destino_x, destino_y);
                        if(ub0>0){

                        }else if(ub1>0){

                        }else if(ub2>0){

                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Torres.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }
    }else if(ficha=="A"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*converciono qstring a char* */
            QString nficha = ficha+"n";
            char* cnficha = (char*)malloc(3);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            /*validando si aun hay alfiles negros*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida para moverse*/
                        int ub0 = tablogic0->ubicacion_alfil(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_alfil(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_alfil(cnficha, destino_x, destino_y);
                        if(ub0>0){
                            /*si hay una pieza que cumpla con el movimiento en el nivel 0*/
                            int pieza = tabpos0[destino_x][destino_y];
                            QString coo = QString::number(ub0); //ej. "406"
                            QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
                            QString tmp = arr_coo.at(0);
                            int actual_x = tmp.toInt(); //4
                            tmp = arr_coo.at(1);
                            int actual_y = tmp.toInt(); //6
                            if(pieza == 0){
                                /*posicion libre*/
                                tabpos0[actual_x][actual_y] = 0;
                                tablogic0->eliminar(actual_x, actual_y, "An");
                                tab0[actual_x][actual_y]->setText(" ");
                                //cout << "despues de eliminar" << endl;
                                //tablogic0->recorrerColumnas();
                                //tablogic0->recorrerFilas();

                                tabpos0[destino_x][destino_y] = 4;
                                tablogic0->insertar(destino_x,destino_y,"An");
                                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilnegro));

                                //cout << "despues de mover" << endl;
                                //tablogic0->recorrerColumnas();
                                //tablogic0->recorrerFilas();

                                ui->listamovimientos->addItem(coordenada);
                                ui->txtmovimiento->setText("");

                                jugador1=false;
                            }else if(pieza >=7 && pieza <=12){
                                /*hay una pieza blanca para comer en esa posicion*/
                            }else{
                                /*hay una pieza negra en esa posicion*/
                                ui->txtmovimiento->setText("");
                                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                            }
                        }else if(ub1>0){

                        }else if(ub2>0){

                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Alfiles.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }

    }else if(ficha=="C"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*converciono qstring a char* */
            QString nficha = ficha+"n";
            char* cnficha = (char*)malloc(3);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            /*validando si aun hay alfiles negros*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida para moverse*/
                        int ub0 = tablogic0->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_peon(cnficha, destino_x, destino_y);
                        if(ub0>0){

                        }else if(ub1>0){

                        }else if(ub2>0){

                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Caballos.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }
    }else if(ficha=="P"){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt();
        /*validar tablero*/
        if(tabdest==0 || tabdest==1 || tabdest==2){
            /*convercion QString a char* */
            QString nficha = ficha+"b";
            char * cnficha = (char*)malloc(3);
            char * tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha);
            haypiezas2 = tablogic2->hayficha(cnficha);
            /*validar si hay almenos una pieza en algun tablero*/
            if(haypiezas0==true || haypiezas1==true || haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x != 0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        /*valido si la coordenada es valida paraq que algun peon pueda moverse*/
                        int ub0 = tablogic0->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub1 = tablogic1->ubicacion_peon(cnficha, destino_x, destino_y);
                        int ub2 = tablogic2->ubicacion_peon(cnficha, destino_x, destino_y);
                        if(ub0 > 0){
                            /*si hay una pieza que cumpla con el movimiento en el nivel 0*/
                            int pieza = tabpos0[destino_x][destino_y];
                            QString coo = QString::number(ub0); //ej. 406
                            QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
                            QString tmp = arr_coo.at(0);
                            int actual_x = tmp.toInt(); //4
                            tmp = arr_coo.at(1);
                            int actual_y = tmp.toInt(); //6
                            if(pieza == 0){
                                /*posicion libre*/
                                tabpos0[actual_x][actual_y] = 0;
                                tablogic0->eliminar(actual_x, actual_y, "Pb");
                                tab0[actual_x][actual_y]->setText(" ");

                                tabpos0[destino_x][destino_y] = 12;
                                tablogic0->insertar(destino_x,destino_y,"Pb");
                                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonblanco));
                                ui->listamovimientos->addItem("-Jug.2:");
                                ui->listamovimientos->addItem(coordenada);
                                ui->txtmovimiento->setText("");

                                jugador1=true;
                            }else if(pieza >=1 && pieza <=6){
                                /*hay una pieza negra para comer en esa posicion*/
                                tabpos0[actual_x][actual_y]=0;
                                tablogic0->eliminar(actual_x, actual_y, "Pb");
                                tab0[actual_x][actual_y]->setText(" ");

                                QString pieza_a_borrar = nombre_pieza(pieza);
                                char * pab = (char*)malloc(2);
                                char * tmp = pieza_a_borrar.toLatin1().data();
                                strcpy(pab, tmp);
                                tabpos0[destino_x][destino_y]=12;
                                tablogic0->eliminar(destino_x, destino_y, pab);
                                tab0[destino_x][destino_y]->setText(" ");
                                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonblanco));
                                ui->listamovimientos->addItem("-Jug.2:");
                                ui->listamovimientos->addItem(coordenada);
                                ui->txtmovimiento->setText("");
                                //free(pab);
                                //free(tmp);
                                jugador1=true;
                            }else{
                                /*hay una pieza blanca en esa posicion*/
                                ui->txtmovimiento->setText("");
                                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
                            }
                        }else if(ub1 >0){
                            /*si hay una pieza que cumpla con el movimiento en el nivel 1*/
                            int pieza = tabpos1[destino_x][destino_y];
                            if(pieza == 0){
                                /*posicion libre*/
                            }else if(pieza >=7 && pieza <=12){
                                /*hay una pieza blanca en esa posicion*/
                            }else{
                                /*hay una pieza negra en esa posicion*/
                                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                            }
                        }else if(ub2 >0){
                            /*si hay una pieza que cumpla con el movimiento en el nivel 2*/
                            int pieza = tabpos2[destino_x][destino_y];
                            if(pieza == 0){
                                /*posicion libre*/
                            }else if(pieza >=7 && pieza <=12){
                                /*hay una pieza blanca en esa posicion*/
                            }else{
                                /*hay una pieza negra en esa posicion*/
                                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                            }
                        }else{
                            ui->txtmovimiento->setText("");
                            QMessageBox::information(this,"Error!","Ninguna pieza puede moverse a esa posicion.");
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila fuera de Rango.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes Peones.");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }//fin validar tablero
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Pieza invalida o Usa Mayuscula.");
    }//fin validar piezas
}

int MainWindow::letra_a_numero(QString letra){
    if(letra == "A"){
        return 8;
    }else if(letra == "B"){
        return 7;
    }else if(letra == "C"){
        return 6;
    }else if(letra == "D"){
        return 5;
    }else if(letra == "E"){
        return 4;
    }else if(letra == "F"){
        return 3;
    }else if(letra == "G"){
        return 2;
    }else if(letra == "H"){
        return 1;
    }else{
        return 0;
    }
}

void MainWindow::crear_grafico_tablero(int n){
    QString tablero_completo="";

    if(n == 0){
        tablero_completo = tablogic0->estado_matriz();
    }else if(n == 1){
        tablero_completo = tablogic1->estado_matriz();
    }else{
        tablero_completo = tablogic2->estado_matriz();
    }
    QString nodo_por_columna="", nodo_label="";


    /*primero separar por columnas*/
    QStringList columnas = tablero_completo.split("fincol");

    for(int i=0; i<columnas.length()-1; i++){
        QString columna = columnas.value(i);

        /*separar cada nodo*/
        QStringList datos_nodo = columna.split("%");

        /*-1 debido a que queda un espacio vacio al final :v*/
        for(int k=0; k<datos_nodo.length()-1; k++){
            QString cada_nodo = datos_nodo.value(k);
            /*separar cada dato del nodo*/
            QStringList separado = cada_nodo.split("#");

            for(int j=0; j<separado.length(); j++){
                if(j == 0){
                    QString nodo = separado.value(j);
                    nodo_label += nodo; //se almacena node0[label="peon"];
                }else if(j == 1){
                    QString numero = separado.value(j);
                    nodo_por_columna += numero + "#"; //se almacena el numero correspondiente al nodo

                    char* cnumero = (char*)malloc(2);
                    char* tmp = numero.toLatin1().data();
                    strcpy(cnumero, tmp);
                    lista_numero->agregar(cnumero);
                }else if(j == 2){
                    QString y = separado.value(j); //se almacena la coordena en y
                    //nodo_por_columna += y;
                    char* cy = (char*)malloc(1);
                    char* tmp = y.toLatin1().data();
                    strcpy(cy, tmp);
                    lista_y->agregar(cy);
                }
            }//fin recorrer separando #
        }//fin recorrer separando %
        nodo_por_columna += "fincol";
    }//fin recorrer separando fincol
    /*fin separar datos y mandarlos a sus respectivas listas*/

    //cout << "-----------nodo_por_columna------------- " << endl;
    //cout << nodo_por_columna.toStdString() << endl;

    /*creando los subgraph cluster*/
    //cout << "------- subgraf----------------- " << endl;
    //cout << nodo_por_columna.toStdString() << endl;

    QStringList subgraf = nodo_por_columna.split("fincol");
    /*queda:
     * subgraf=[0#1#2#3#][4#5#6#7#][...]
     * */
    QString subgraf_cluster = "";
    int contador_subclust =0;

    for(int i=0; i<subgraf.length()-1; i++){
        subgraf_cluster += "subgraph cluster"+QString::number(contador_subclust)+"{";
        QString columna =  subgraf.value(i);

        QStringList nodos = columna.split("#");
        /*queda:
         * nodos = [0][1][2][3][]
         * */
        for(int j=0; j<nodos.length()-2; j++){
            QString nodo = nodos.value(j); //nodo=[0]

            int numero_nodo = nodo.toInt(); //0
            int numero_nodo_siguiente = numero_nodo +1;//1

            subgraf_cluster += "\"node"+QString::number(numero_nodo) + "\" -> \"node" + QString::number(numero_nodo_siguiente)+"\";\n";
            subgraf_cluster += "\"node"+QString::number(numero_nodo_siguiente) + "\" -> \"node" + QString::number(numero_nodo)+"\";\n";

        }//fin recorrer, separando #
        subgraf_cluster += "}";
        contador_subclust++;
    }

    //fin recorrer, separando fincol
    //cout << "---------------- subgraf_cluster------------------" << endl;
    //cout << subgraf_cluster.toStdString() << endl;

    QString archivo = "digraph G{\nnode [shape=record, height=.1;]\n" + nodo_label + subgraf_cluster + "\n}";
    generar_dot(archivo);
}

void MainWindow::generar_dot(QString contenido){
    ofstream escritura;
    escritura.open("dato.dot", ios::out);
    if(escritura.is_open()){
        cout<<"abrio el archivo"<<endl;
        escritura<<contenido.toStdString()<<endl;
    }else{
        cout<<"nell prro"<<endl;
    }
    escritura.close();
}

QString MainWindow::nombre_pieza(int n){
    if(n==1){
        return "Rn";
    }else if(n==2){
        return "Dn";
    }else if(n==3){
        return "Tn";
    }else if(n==4){
        return "An";
    }else if(n==5){
        return "Cn";
    }else if(n==6){
        return "Pn";
    }else if(n==7){
        return "Rb";
    }else if(n==8){
        return "Db";
    }else if(n==9){
        return "Tb";
    }else if(n==10){
        return "Ab";
    }else if(n==11){
        return "Cb";
    }else if(n==12){
        return "Pb";
    }
}

bool MainWindow::validar_camino_alfil(int n, QString p, int actual_x, int actual_y, int destino_x, int destino_y, int tablero){
    bool c=false;
    int pi_act=0;
    if(n==1){
        //mov. abajo
        for(int i=1;i<=destino_x;i++){
            if(tablero==0){
                pi_act = tabpos0[actual_x + i][actual_y];
            }else if(tablero==1){
                pi_act = tabpos1[actual_x + i][actual_y];
            }else{
                pi_act = tabpos2[actual_x + i][actual_y];
            }

            if(pi_act!=0){
                //no es una posicion vacia
                if(actual_x+i == destino_x){
                    //es a donde se movera la pieza
                    if(p=="An"){
                        //para piezas negras
                        if(pi_actual>=1 && pi_actual<=6){
                            //hay una pieza negra en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }else{
                        //para piezas blancas
                        if(pi_actual>=7 && pi_actual<=12){
                            //hay una pieza blanca en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }
                }else{
                    //hay una pieza en medio
                    break;
                }
            }
        }
    }else if(n==2){
        //mov. arriba
        for(int i=1;i<=actual_x;i++){
            if(tablero==0){
                pi_act = tabpos0[actual_x-i][actual_y];
            }else if(tablero==1){
                pi_act = tabpos1[actual_x-i][actual_y];
            }else{
                pi_act = tabpos2[actual_x-i][actual_y];
            }

            if(pi_act!=0){
                if(actual_x-i==destino_x){
                    //es a donde se movera la pieza
                    if(p=="An"){
                        //para piezas negras
                        if(pi_actual>=1 && pi_actual<=6){
                            //hay una pieza negra en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }else{
                        //para piezas blancas
                        if(pi_actual>=7 && pi_actual<=12){
                            //hay una pieza blanca en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }
                }else{
                    break;
                }
            }
        }
    }else if(n==3){
        //mov. izq
        for(int i=1;i<=destino_y;i++){
            if(tablero==0){
                pi_act = tabpos0[actual_x][actual_y+i];
            }else if(tablero==1){
                pi_act = tabpos1[actual_x][actual_y+i];
            }else{
                pi_act = tabpos2[actual_x][actual_y+i];
            }

            if(pi_act!=0){
                if(actual_y+i==destino_y){
                    //es a donde se movera
                    if(p=="An"){
                        //para piezas negras
                        if(pi_actual>=1 && pi_actual<=6){
                            //hay una pieza negra en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }else{
                        //para piezas blancas
                        if(pi_actual>=7 && pi_actual<=12){
                            //hay una pieza blanca en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }
                }else{
                    break;
                }
            }
        }
    }else{
        //mov. der
        for(int i=1;i<=actual_y;i++){
            if(tablero==0){
                pi_act = tabpos0[destino_x][destino_y-i];
            }else if(tablero==1){
                pi_act = tabpos1[destino_x][destino_y-i];
            }else{
                pi_act = tabpos2[destino_x][destino_y-i];
            }

            if(pi_act!=0){
                if(actual_y-i==destino_y){
                    if(p=="An"){
                        //para piezas negras
                        if(pi_actual>=1 && pi_actual<=6){
                            //hay una pieza negra en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }else{
                        //para piezas blancas
                        if(pi_actual>=7 && pi_actual<=12){
                            //hay una pieza blanca en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }
                }else{
                    break;
                }
            }

        }
    }
    return c;
}
