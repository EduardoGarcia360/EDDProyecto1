#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "string.h"
#include "QMessageBox"
#include "cstdlib"
#include "iostream"
#include "fstream"
#include "cstdlib"
#include "MatrizOrtogonal.h"
#include "listasimple.h"
#include "QThread"
using namespace std;

/*fichas*/
QImage peonnegro, alfilnegro, caballonegro, torrenegro, damanegro, reynegro;
QImage peonblanco, alfilblanco, caballoblanco, torreblanco, damablanco, reyblanco;
QImage grafica;
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
QString jug1, jug2;
/*para almacenar los nodos para graficar*/
//ListaEnlazada * lista_nodos = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));
ListaEnlazada * lista_numero = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));
//ListaEnlazada * lista_x = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));
ListaEnlazada * lista_y = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));
//
QButtonGroup* estado_tablero = new QButtonGroup;
QButtonGroup* lin_tablero = new QButtonGroup;
QButtonGroup* lin_filcol = new QButtonGroup;
QButtonGroup* config = new QButtonGroup;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    estado_tablero->addButton(ui->rbtnlvl0);
    estado_tablero->addButton(ui->rbtnlvl1);
    estado_tablero->addButton(ui->rbtnlvl2);
    lin_tablero->addButton(ui->rbtnlvl0lin);
    lin_tablero->addButton(ui->rbtnlvl1lin);
    lin_tablero->addButton(ui->rbtnlvl2lin);
    lin_filcol->addButton(ui->rbtnfilaslin);
    lin_filcol->addButton(ui->rbtncolumnaslin);
    config->addButton(ui->rbtncontratiempo);
    config->addButton(ui->rbtnnormal);
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
    //tablogic1->estado_columnas();
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
    //crear_grafico_columna(0);
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
bool MainWindow::validar_nombre_pieza(QString p){
    if(p=="R"||p=="D"||p=="T"||p=="A"||p=="C"||p=="P"){
        return true;
    }else{
        return false;
    }
}

void MainWindow::jugador_negro(QStringList arreglocoordenada, QString coordenada){
    QString ficha = arreglocoordenada.at(0); //ficha = "p"
    if(validar_nombre_pieza(ficha)==true){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt(); //"1" a 1

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*qstring a char* */
            QString nficha = ficha+"n"; //An, Tn, Pn,...
            char* cnficha = (char*)malloc(2);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);

            /*validando si tiene almenos una pieza*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha); //retorna false en caso de no haber ninguna
            haypiezas2 = tablogic2->hayficha(cnficha);

            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        if(ficha=="R"){

                        }else if(ficha=="D"){

                        }else if(ficha=="T"){
                            torre_negro(cnficha, destino_x, destino_y, tabdest, coordenada);
                        }else if(ficha=="A"){
                            alfil_negro(cnficha, destino_x, destino_y, tabdest, coordenada);
                        }else if(ficha=="C"){
                            caballo_negro(cnficha, destino_x, destino_y, tabdest, coordenada);
                        }else if(ficha=="P"){
                            peon_negro(cnficha, destino_x, destino_y, tabdest, coordenada);
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila desconocida.");
                }
            }else{
                QString tmp = nombre_pieza_error(ficha);
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes: "+tmp+".");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Letra no coincide con ninguna ficha.");
    }
}

float MainWindow::obtenerAleatorio(int desde, int hasta){
   return std::floor( rand() * ( hasta - desde + 1.0 ) ) + desde;
}

void MainWindow::peon_negro(char* cnficha, int destino_x, int destino_y, int tabdest, QString coordenada){
    //validar si el peon se puede mover a la posicion destino
    int ub0 = tablogic0->ubicacion_peon(cnficha,destino_x,destino_y);
    int ub1 = tablogic1->ubicacion_peon(cnficha,destino_x,destino_y); //retorna pos actual
    int ub2 = tablogic2->ubicacion_peon(cnficha,destino_x,destino_y);

    if(ub0>0 && tabdest==0){
        QString coo = QString::number(ub0); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        int p = tabpos0[destino_x][destino_y];
        if(destino_x==8 && p!=8){
            //fila promocion sube al nivel 1
            tabpos0[actual_x][actual_y] = 0;
            tablogic0->eliminar(actual_x, actual_y, "Pn");
            tab0[actual_x][actual_y]->setText(" ");
            tabpos1[1][1]=6;
            tablogic1->insertar(1,1,"Pn");
            tab1[1][1]->setPixmap(QPixmap::fromImage(peonnegro));
        }else{
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                //vacio
                tabpos0[actual_x][actual_y] = 0;
                tablogic0->eliminar(actual_x, actual_y, "Pn");
                tab0[actual_x][actual_y]->setText(" ");

                tabpos0[destino_x][destino_y] = 6;
                tablogic0->insertar(destino_x,destino_y,"Pn");
                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonnegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else if(pieza>=7 && pieza<=12){
                if(pieza==8){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos0[actual_x][actual_y] = 0;
                    tablogic0->eliminar(actual_x, actual_y, "Pn");
                    tab0[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos0[destino_x][destino_y]=6;
                    tablogic0->eliminar(destino_x, destino_y, pab);
                    tablogic0->insertar(destino_x,destino_y,"Pn");
                    tab0[destino_x][destino_y]->setText(" ");
                    tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonnegro));

                    ui->listamovimientos->addItem("-"+jug1);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=false;
                    ui->lblturnoactual->setText(jug2);
                }

            }else{
                //pieza mismo color
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
            }
        }
    }else if(ub1>0 && tabdest==1){
        QString coo = QString::number(ub1); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        int p = tabpos0[destino_x][destino_y];
        if(destino_x==8 && p!=8){
            //fila promocion sube al nivel 2
            tabpos1[actual_x][actual_y] = 0;
            tablogic1->eliminar(actual_x, actual_y, "Pn");
            tab1[actual_x][actual_y]->setText(" ");
            tabpos2[1][8]=6;
            tablogic2->insertar(1,8,"Pn");
            tab2[1][8]->setPixmap(QPixmap::fromImage(peonnegro));
        }else{
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                //vacio
                tabpos1[actual_x][actual_y] = 0;
                tablogic1->eliminar(actual_x, actual_y, "Pn");
                tab1[actual_x][actual_y]->setText(" ");

                tabpos1[destino_x][destino_y] = 6;
                tablogic1->insertar(destino_x,destino_y,"Pn");
                tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonnegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else if(pieza>=7 && pieza<=12){
                if(pieza==8){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos1[actual_x][actual_y] = 0;
                    tablogic1->eliminar(actual_x, actual_y, "Pn");
                    tab1[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos1[destino_x][destino_y]=6;
                    tablogic1->eliminar(destino_x, destino_y, pab);
                    tablogic1->insertar(destino_x,destino_y,"Pn");
                    tab1[destino_x][destino_y]->setText(" ");
                    tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonnegro));

                    ui->listamovimientos->addItem("-"+jug1);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=false;
                    ui->lblturnoactual->setText(jug2);
                }

            }else{
                //pieza mismo color
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
            }
        }
    }else if(ub2>0 && tabdest==2){
        QString coo = QString::number(ub2); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6

        if(destino_x==8){
            //fila promocion baja al nivel 0 se convierte en otra pieza
            tabpos2[actual_x][actual_y] = 0;
            tablogic2->eliminar(actual_x, actual_y, "Pn");
            tab2[actual_x][actual_y]->setText(" ");
            tabpos2[8][8]=6;
            tablogic2->insertar(8,8,"Pn");
            tab2[8][8]->setPixmap(QPixmap::fromImage(peonnegro));
        }else{
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                //vacio
                tabpos2[actual_x][actual_y] = 0;
                tablogic2->eliminar(actual_x, actual_y, "Pn");
                tab2[actual_x][actual_y]->setText(" ");

                tabpos2[destino_x][destino_y] = 6;
                tablogic2->insertar(destino_x,destino_y,"Pn");
                tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonnegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else if(pieza>=7 && pieza<=12){
                if(pieza==8){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos2[actual_x][actual_y] = 0;
                    tablogic2->eliminar(actual_x, actual_y, "Pn");
                    tab2[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos2[destino_x][destino_y]=6;
                    tablogic2->eliminar(destino_x, destino_y, pab);
                    tablogic2->insertar(destino_x,destino_y,"Pn");
                    tab2[destino_x][destino_y]->setText(" ");
                    tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonnegro));

                    ui->listamovimientos->addItem("-"+jug1);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=false;
                    ui->lblturnoactual->setText(jug2);
                }

            }else{
                //pieza mismo color
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
            }
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Ningun peon puede moverse a esa posicion.");
    }
}

void MainWindow::peon_blanco(char *cnficha, int destino_x, int destino_y, int tabdest, QString coordenada){
    //validar si el peon se puede mover a la posicion destino
    int ub0 = tablogic0->ubicacion_peon(cnficha,destino_x,destino_y);
    int ub1 = tablogic1->ubicacion_peon(cnficha,destino_x,destino_y); //retorna pos actual
    int ub2 = tablogic2->ubicacion_peon(cnficha,destino_x,destino_y);

    if(ub0>0 && tabdest==0){
        QString coo = QString::number(ub0); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        int p = tabpos0[destino_x][destino_y];
        if(destino_x==1 && p!=2){
            //fila promocion sube al nivel 1
            tabpos0[actual_x][actual_y] = 0;
            tablogic0->eliminar(actual_x, actual_y, "Pb");
            tab0[actual_x][actual_y]->setText(" ");
            tabpos1[8][8]=12;
            tablogic1->insertar(8,8,"Pb");
            tab1[8][8]->setPixmap(QPixmap::fromImage(peonblanco));
        }else{
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                //vacio
                tabpos0[actual_x][actual_y] = 0;
                tablogic0->eliminar(actual_x, actual_y, "Pb");
                tab0[actual_x][actual_y]->setText(" ");

                tabpos0[destino_x][destino_y] = 12;
                tablogic0->insertar(destino_x,destino_y,"Pb");
                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else if(pieza>=1 && pieza<=6){
                if(pieza==2){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos0[actual_x][actual_y] = 0;
                    tablogic0->eliminar(actual_x, actual_y, "Pb");
                    tab0[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos0[destino_x][destino_y]=12;
                    tablogic0->eliminar(destino_x, destino_y, pab);
                    tablogic0->insertar(destino_x, destino_y, "Pb");
                    tab0[destino_x][destino_y]->setText(" ");
                    tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonblanco));

                    ui->listamovimientos->addItem("-"+jug2);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=true;
                    ui->lblturnoactual->setText(jug1);
                }

            }else{
                //pieza mismo color
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
            }
        }
    }else if(ub1>0 && tabdest==1){
        QString coo = QString::number(ub1); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        int p = tabpos0[destino_x][destino_y];
        if(destino_x==1 && p!=2){
            //fila promocion sube al nivel 1
            tabpos1[actual_x][actual_y] = 0;
            tablogic1->eliminar(actual_x, actual_y, "Pb");
            tab1[actual_x][actual_y]->setText(" ");
            tabpos2[8][1]=12;
            tablogic2->insertar(8,1,"Pb");
            tab2[8][1]->setPixmap(QPixmap::fromImage(peonblanco));
        }else{
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                //vacio
                tabpos1[actual_x][actual_y] = 0;
                tablogic1->eliminar(actual_x, actual_y, "Pb");
                tab1[actual_x][actual_y]->setText(" ");

                tabpos1[destino_x][destino_y] = 12;
                tablogic1->insertar(destino_x,destino_y,"Pb");
                tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else if(pieza>=1 && pieza<=6){
                if(pieza==2){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos1[actual_x][actual_y] = 0;
                    tablogic1->eliminar(actual_x, actual_y, "Pb");
                    tab1[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos1[destino_x][destino_y]=12;
                    tablogic1->eliminar(destino_x, destino_y, pab);
                    tablogic1->insertar(destino_x, destino_y, "Pb");
                    tab1[destino_x][destino_y]->setText(" ");
                    tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonblanco));

                    ui->listamovimientos->addItem("-"+jug2);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=true;
                    ui->lblturnoactual->setText(jug1);
                }

            }else{
                //pieza mismo color
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
            }
        }
    }else if(ub2>0 && tabdest==2){
        QString coo = QString::number(ub2); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        int p = tabpos0[destino_x][destino_y];
        if(destino_x==1 && p!=2){
            //fila promocion sube al nivel 1
            tabpos2[actual_x][actual_y] = 0;
            tablogic2->eliminar(actual_x, actual_y, "Pb");
            tab2[actual_x][actual_y]->setText(" ");
            tabpos0[5][8]=12;
            tablogic0->insertar(5,8,"Pb");
            tab0[5][8]->setPixmap(QPixmap::fromImage(peonblanco));
        }else{
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                //vacio
                tabpos2[actual_x][actual_y] = 0;
                tablogic2->eliminar(actual_x, actual_y, "Pb");
                tab2[actual_x][actual_y]->setText(" ");

                tabpos2[destino_x][destino_y] = 12;
                tablogic2->insertar(destino_x,destino_y,"Pb");
                tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else if(pieza>=1 && pieza<=6){
                if(pieza==2){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos2[actual_x][actual_y] = 0;
                    tablogic2->eliminar(actual_x, actual_y, "Pb");
                    tab2[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos2[destino_x][destino_y]=12;
                    tablogic2->eliminar(destino_x, destino_y, pab);
                    tablogic2->insertar(destino_x, destino_y, "Pb");
                    tab2[destino_x][destino_y]->setText(" ");
                    tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(peonblanco));

                    ui->listamovimientos->addItem("-"+jug2);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=true;
                    ui->lblturnoactual->setText(jug1);
                }

            }else{
                //pieza mismo color
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
            }
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Ningun peon puede moverse a esa posicion.");
    }
}

QString MainWindow::nombre_pieza_error(QString p){
    if(p=="R"){
        return "Rey";
    }else if(p=="T"){
        return "Torre";
    }else if(p=="A"){
        return "Alfil";
    }else if(p=="C"){
        return "Caballo";
    }else if(p=="P"){
        return "Peon";
    }
}

void MainWindow::jugador_blanco(QStringList arreglocoordenada, QString coordenada){
    QString ficha = arreglocoordenada.at(0); //ficha = "p"
    if(validar_nombre_pieza(ficha)==true){
        QString tablero_destino = arreglocoordenada.at(1);
        int tabdest = tablero_destino.toInt(); //"1" a 1

        /*validar tablero, numero correcto*/
        if(tabdest==0||tabdest==1||tabdest==2){
            /*qstring a char* */
            QString nficha = ficha+"b"; //Ab, Tb, Pb,...
            char* cnficha = (char*)malloc(2);
            char* tmp = nficha.toLatin1().data();
            strcpy(cnficha, tmp);

            /*validando si tiene almenos una pieza*/
            bool haypiezas0, haypiezas1, haypiezas2;
            haypiezas0 = tablogic0->hayficha(cnficha);
            haypiezas1 = tablogic1->hayficha(cnficha); //retorna false en caso de no haber ninguna
            haypiezas2 = tablogic2->hayficha(cnficha);

            if(haypiezas0==true||haypiezas1==true||haypiezas2==true){
                QString destino = arreglocoordenada.at(2); //"C4"
                int destino_x = letra_a_numero(destino.at(0)); //"C" a 6
                if(destino_x!=0){
                    QString qsy = destino.at(1); //"4"
                    int destino_y = qsy.toInt(); //"4" a 4
                    if(destino_y>0 && destino_y<=8){
                        if(ficha=="R"){

                        }else if(ficha=="D"){

                        }else if(ficha=="T"){
                            torre_blanco(cnficha, destino_x, destino_y, tabdest, coordenada);
                        }else if(ficha=="A"){
                            alfil_blanco(cnficha, destino_x, destino_y, tabdest, coordenada);
                        }else if(ficha=="C"){
                            caballo_blanco(cnficha, destino_x, destino_y, tabdest, coordenada);
                        }else if(ficha=="P"){
                            peon_blanco(cnficha, destino_x, destino_y, tabdest, coordenada);
                        }
                    }else{
                        ui->txtmovimiento->setText("");
                        QMessageBox::information(this,"Error!","Numero de columna fuera de rango.");
                    }
                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Error!","Letra de fila desconocida.");
                }
            }else{
                QString tmp = nombre_pieza_error(ficha);
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Error!","Ya no tienes: "+tmp+".");
            }
        }else{
            QMessageBox::information(this,"Error!","Num. de Tablero no Valido.");
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Letra no coincide con ninguna ficha.");
    }
}

void MainWindow::alfil_negro(char* cnficha, int destino_x, int destino_y, int tabdest, QString coordenada){
    //validar si el peon se puede mover a la posicion destino
    int ub0 = tablogic0->ubicacion_alfil(cnficha,destino_x,destino_y);
    int ub1 = tablogic1->ubicacion_alfil(cnficha,destino_x,destino_y); //retorna pos actual 502
    int ub2 = tablogic2->ubicacion_alfil(cnficha,destino_x,destino_y);
    if(ub0>0 && tabdest==0){
        QString coo = QString::number(ub0); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6

        if(actual_x==destino_x && actual_y==destino_y){
            //sube de nivel
        }else{
            bool puede = validar_camino_alfil("An",actual_x,actual_y,destino_x,destino_y,tabdest);
            if(puede==true){
                int pieza = tabpos0[destino_x][destino_y];
                if(pieza==0){
                    tabpos0[actual_x][actual_y] = 0;
                    tablogic0->eliminar(actual_x, actual_y, "An");
                    tab0[actual_x][actual_y]->setText(" ");

                    tabpos0[destino_x][destino_y] = 4;
                    tablogic0->insertar(destino_x,destino_y,"An");
                    tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilnegro));

                    ui->listamovimientos->addItem("-"+jug1);
                    ui->listamovimientos->addItem(coordenada);
                    ui->txtmovimiento->setText("");

                    jugador1=false;
                    ui->lblturnoactual->setText(jug2);
                }else if(pieza>=7 && pieza<=12){
                    if(pieza==8){
                        ui->btnmover->setEnabled(false);
                        ui->txtmovimiento->setEnabled(false);
                        ui->btniniciar->setEnabled(true);
                        ui->txtjugador1->setEnabled(true);
                        ui->txtjugador2->setEnabled(true);
                        ui->txtjugador1->setText("");
                        ui->txtjugador2->setText("");
                        ui->txtcontratiempo->setEnabled(false);
                        jugador1=true;
                        QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                    }else{
                        tabpos0[actual_x][actual_y] = 0;
                        tablogic0->eliminar(actual_x, actual_y, "An");
                        tab0[actual_x][actual_y]->setText(" ");

                        QString pieza_a_borrar = nombre_pieza(pieza);
                        char * pab = (char*)malloc(2);
                        char * tmp = pieza_a_borrar.toLatin1().data();
                        strcpy(pab, tmp);

                        tabpos0[destino_x][destino_y]=4;
                        tablogic0->eliminar(destino_x, destino_y, pab);
                        tablogic0->insertar(destino_x, destino_y, "An");
                        tab0[destino_x][destino_y]->setText(" ");
                        tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilnegro));

                        ui->listamovimientos->addItem("-"+jug1);
                        ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                        ui->txtmovimiento->setText("");

                        jugador1=false;
                        ui->lblturnoactual->setText(jug2);
                    }

                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
            }
        }
    }else if(ub1>0 && tabdest==1){
        QString coo = QString::number(ub1); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6

        if(actual_x==destino_x && actual_y==destino_y){
            //sube de nivel
        }else{
            bool puede = validar_camino_alfil("An",actual_x,actual_y,destino_x,destino_y,tabdest);
            if(puede==true){
                int pieza = tabpos1[destino_x][destino_y];
                if(pieza==0){
                    tabpos1[actual_x][actual_y] = 0;
                    tablogic1->eliminar(actual_x, actual_y, "An");
                    tab1[actual_x][actual_y]->setText(" ");

                    tabpos1[destino_x][destino_y] = 4;
                    tablogic1->insertar(destino_x,destino_y,"An");
                    tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilnegro));

                    ui->listamovimientos->addItem("-"+jug1);
                    ui->listamovimientos->addItem(coordenada);
                    ui->txtmovimiento->setText("");

                    jugador1=false;
                    ui->lblturnoactual->setText(jug2);
                }else if(pieza>=7 && pieza<=12){
                    if(pieza==8){
                        ui->btnmover->setEnabled(false);
                        ui->txtmovimiento->setEnabled(false);
                        ui->btniniciar->setEnabled(true);
                        ui->txtjugador1->setEnabled(true);
                        ui->txtjugador2->setEnabled(true);
                        ui->txtjugador1->setText("");
                        ui->txtjugador2->setText("");
                        ui->txtcontratiempo->setEnabled(false);
                        jugador1=true;
                        QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                    }else{
                        tabpos1[actual_x][actual_y] = 0;
                        tablogic1->eliminar(actual_x, actual_y, "An");
                        tab1[actual_x][actual_y]->setText(" ");

                        QString pieza_a_borrar = nombre_pieza(pieza);
                        char * pab = (char*)malloc(2);
                        char * tmp = pieza_a_borrar.toLatin1().data();
                        strcpy(pab, tmp);

                        tabpos1[destino_x][destino_y]=4;
                        tablogic1->eliminar(destino_x, destino_y, pab);
                        tablogic1->insertar(destino_x, destino_y, "An");
                        tab1[destino_x][destino_y]->setText(" ");
                        tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilnegro));

                        ui->listamovimientos->addItem("-"+jug1);
                        ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                        ui->txtmovimiento->setText("");

                        jugador1=false;
                        ui->lblturnoactual->setText(jug2);
                    }

                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
            }
        }
    }else if(ub2>0 && tabdest==2){
        QString coo = QString::number(ub2); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6

        if(actual_x==destino_x && actual_y==destino_y){
            //sube de nivel
        }else{
            bool puede = validar_camino_alfil("An",actual_x,actual_y,destino_x,destino_y,tabdest);
            if(puede==true){
                int pieza = tabpos2[destino_x][destino_y];
                if(pieza==0){
                    tabpos2[actual_x][actual_y] = 0;
                    tablogic2->eliminar(actual_x, actual_y, "An");
                    tab2[actual_x][actual_y]->setText(" ");

                    tabpos2[destino_x][destino_y] = 4;
                    tablogic2->insertar(destino_x,destino_y,"An");
                    tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilnegro));

                    ui->listamovimientos->addItem("-"+jug1);
                    ui->listamovimientos->addItem(coordenada);
                    ui->txtmovimiento->setText("");

                    jugador1=false;
                    ui->lblturnoactual->setText(jug2);
                }else if(pieza>=7 && pieza<=12){
                    if(pieza==8){
                        ui->btnmover->setEnabled(false);
                        ui->txtmovimiento->setEnabled(false);
                        ui->btniniciar->setEnabled(true);
                        ui->txtjugador1->setEnabled(true);
                        ui->txtjugador2->setEnabled(true);
                        ui->txtjugador1->setText("");
                        ui->txtjugador2->setText("");
                        ui->txtcontratiempo->setEnabled(false);
                        jugador1=true;
                        QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                    }else{
                        tabpos2[actual_x][actual_y] = 0;
                        tablogic2->eliminar(actual_x, actual_y, "An");
                        tab2[actual_x][actual_y]->setText(" ");

                        QString pieza_a_borrar = nombre_pieza(pieza);
                        char * pab = (char*)malloc(2);
                        char * tmp = pieza_a_borrar.toLatin1().data();
                        strcpy(pab, tmp);

                        tabpos2[destino_x][destino_y]=4;
                        tablogic2->eliminar(destino_x, destino_y, pab);
                        tablogic2->insertar(destino_x, destino_y, "An");
                        tab2[destino_x][destino_y]->setText(" ");
                        tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilnegro));

                        ui->listamovimientos->addItem("-"+jug1);
                        ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                        ui->txtmovimiento->setText("");

                        jugador1=false;
                        ui->lblturnoactual->setText(jug2);
                    }

                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
            }
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Ningun alfil puede moverse a esa posicion.");
    }
}

void MainWindow::alfil_blanco(char* cnficha, int destino_x, int destino_y, int tabdest, QString coordenada){
    //validar si el peon se puede mover a la posicion destino
    int ub0 = tablogic0->ubicacion_alfil(cnficha,destino_x,destino_y);
    int ub1 = tablogic1->ubicacion_alfil(cnficha,destino_x,destino_y); //retorna pos actual 502
    int ub2 = tablogic2->ubicacion_alfil(cnficha,destino_x,destino_y);
    if(ub0>0 && tabdest==0){
        QString coo = QString::number(ub0); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6

        if(actual_x==destino_x && actual_y==destino_y){
            //sube de nivel
        }else{
            bool puede = validar_camino_alfil("Ab",actual_x,actual_y,destino_x,destino_y,tabdest);
            if(puede==true){
                int pieza = tabpos0[destino_x][destino_y];
                if(pieza==0){
                    tabpos0[actual_x][actual_y] = 0;
                    tablogic0->eliminar(actual_x, actual_y, "Ab");
                    tab0[actual_x][actual_y]->setText(" ");

                    tabpos0[destino_x][destino_y] = 10;
                    tablogic0->insertar(destino_x,destino_y,"Ab");
                    tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilblanco));

                    ui->listamovimientos->addItem("-"+jug2);
                    ui->listamovimientos->addItem(coordenada);
                    ui->txtmovimiento->setText("");

                    jugador1=true;
                    ui->lblturnoactual->setText(jug1);
                }else if(pieza>=1 && pieza<=6){
                    if(pieza==2){
                        ui->btnmover->setEnabled(false);
                        ui->txtmovimiento->setEnabled(false);
                        ui->btniniciar->setEnabled(true);
                        ui->txtjugador1->setEnabled(true);
                        ui->txtjugador2->setEnabled(true);
                        ui->txtjugador1->setText("");
                        ui->txtjugador2->setText("");
                        ui->txtcontratiempo->setEnabled(false);
                        jugador1=true;
                        QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                    }else{
                        tabpos0[actual_x][actual_y] = 0;
                        tablogic0->eliminar(actual_x, actual_y, "Ab");
                        tab0[actual_x][actual_y]->setText(" ");

                        QString pieza_a_borrar = nombre_pieza(pieza);
                        char * pab = (char*)malloc(2);
                        char * tmp = pieza_a_borrar.toLatin1().data();
                        strcpy(pab, tmp);

                        tabpos0[destino_x][destino_y]=10;
                        tablogic0->eliminar(destino_x, destino_y, pab);
                        tablogic0->insertar(destino_x, destino_y, "Ab");
                        tab0[destino_x][destino_y]->setText(" ");
                        tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilblanco));

                        ui->listamovimientos->addItem("-"+jug2);
                        ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                        ui->txtmovimiento->setText("");

                        jugador1=true;
                        ui->lblturnoactual->setText(jug1);
                    }

                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
            }
        }
    }else if(ub1>0 && tabdest==1){
        QString coo = QString::number(ub1); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6

        if(actual_x==destino_x && actual_y==destino_y){
            //sube de nivel
        }else{
            bool puede = validar_camino_alfil("Ab",actual_x,actual_y,destino_x,destino_y,tabdest);
            if(puede==true){
                int pieza = tabpos1[destino_x][destino_y];
                if(pieza==0){
                    tabpos1[actual_x][actual_y] = 0;
                    tablogic1->eliminar(actual_x, actual_y, "Ab");
                    tab1[actual_x][actual_y]->setText(" ");

                    tabpos1[destino_x][destino_y] = 10;
                    tablogic1->insertar(destino_x,destino_y,"Ab");
                    tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilblanco));

                    ui->listamovimientos->addItem("-"+jug2);
                    ui->listamovimientos->addItem(coordenada);
                    ui->txtmovimiento->setText("");

                    jugador1=true;
                    ui->lblturnoactual->setText(jug1);
                }else if(pieza>=1 && pieza<=6){
                    if(pieza==2){
                        ui->btnmover->setEnabled(false);
                        ui->txtmovimiento->setEnabled(false);
                        ui->btniniciar->setEnabled(true);
                        ui->txtjugador1->setEnabled(true);
                        ui->txtjugador2->setEnabled(true);
                        ui->txtjugador1->setText("");
                        ui->txtjugador2->setText("");
                        ui->txtcontratiempo->setEnabled(false);
                        jugador1=true;
                        QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                    }else{
                        tabpos1[actual_x][actual_y] = 0;
                        tablogic1->eliminar(actual_x, actual_y, "Ab");
                        tab1[actual_x][actual_y]->setText(" ");

                        QString pieza_a_borrar = nombre_pieza(pieza);
                        char * pab = (char*)malloc(2);
                        char * tmp = pieza_a_borrar.toLatin1().data();
                        strcpy(pab, tmp);

                        tabpos1[destino_x][destino_y]=10;
                        tablogic1->eliminar(destino_x, destino_y, pab);
                        tablogic1->insertar(destino_x, destino_y, "Ab");
                        tab1[destino_x][destino_y]->setText(" ");
                        tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilblanco));

                        ui->listamovimientos->addItem("-"+jug2);
                        ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                        ui->txtmovimiento->setText("");

                        jugador1=true;
                        ui->lblturnoactual->setText(jug1);
                    }

                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
            }
        }
    }else if(ub2>0 && tabdest==2){
        QString coo = QString::number(ub2); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6

        if(actual_x==destino_x && actual_y==destino_y){
            //sube de nivel
        }else{
            bool puede = validar_camino_alfil("Ab",actual_x,actual_y,destino_x,destino_y,tabdest);
            if(puede==true){
                int pieza = tabpos2[destino_x][destino_y];
                if(pieza==0){
                    tabpos2[actual_x][actual_y] = 0;
                    tablogic2->eliminar(actual_x, actual_y, "Ab");
                    tab2[actual_x][actual_y]->setText(" ");

                    tabpos2[destino_x][destino_y] = 10;
                    tablogic2->insertar(destino_x,destino_y,"Ab");
                    tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilblanco));

                    ui->listamovimientos->addItem("-"+jug2);
                    ui->listamovimientos->addItem(coordenada);
                    ui->txtmovimiento->setText("");

                    jugador1=true;
                    ui->lblturnoactual->setText(jug1);
                }else if(pieza>=1 && pieza<=6){
                    if(pieza==2){
                        ui->btnmover->setEnabled(false);
                        ui->txtmovimiento->setEnabled(false);
                        ui->btniniciar->setEnabled(true);
                        ui->txtjugador1->setEnabled(true);
                        ui->txtjugador2->setEnabled(true);
                        ui->txtjugador1->setText("");
                        ui->txtjugador2->setText("");
                        ui->txtcontratiempo->setEnabled(false);
                        jugador1=true;
                        QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                    }else{
                        tabpos2[actual_x][actual_y] = 0;
                        tablogic2->eliminar(actual_x, actual_y, "Ab");
                        tab2[actual_x][actual_y]->setText(" ");

                        QString pieza_a_borrar = nombre_pieza(pieza);
                        char * pab = (char*)malloc(2);
                        char * tmp = pieza_a_borrar.toLatin1().data();
                        strcpy(pab, tmp);

                        tabpos2[destino_x][destino_y]=10;
                        tablogic2->eliminar(destino_x, destino_y, pab);
                        tablogic2->insertar(destino_x, destino_y, "Ab");
                        tab2[destino_x][destino_y]->setText(" ");
                        tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(alfilblanco));

                        ui->listamovimientos->addItem("-"+jug2);
                        ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                        ui->txtmovimiento->setText("");

                        jugador1=true;
                        ui->lblturnoactual->setText(jug1);
                    }

                }else{
                    ui->txtmovimiento->setText("");
                    QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
                }
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
            }
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Ningun alfil puede moverse a esa posicion.");
    }
}

void MainWindow::caballo_negro(char *cnficha, int destino_x, int destino_y, int tabdest, QString coordenada){
    int ub0 = tablogic0->ubicacion_caballo(cnficha,destino_x,destino_y);
    int ub1 = tablogic1->ubicacion_caballo(cnficha,destino_x,destino_y); //retorna pos actual 502
    int ub2 = tablogic2->ubicacion_caballo(cnficha,destino_x,destino_y);
    if(ub0>0 && tabdest==0){
        QString coo = QString::number(ub0); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_caballo("Cn",actual_x,actual_y,destino_x,destino_y,0);
        if(puede==true){
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                tabpos0[actual_x][actual_y] = 0;
                tablogic0->eliminar(actual_x, actual_y, "Cn");
                tab0[actual_x][actual_y]->setText(" ");

                tabpos0[destino_x][destino_y] = 5;
                tablogic0->insertar(destino_x,destino_y,"Cn");
                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballonegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else if(pieza>=7 && pieza<=12){
                if(pieza==8){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos0[actual_x][actual_y] = 0;
                    tablogic0->eliminar(actual_x, actual_y, "Cn");
                    tab0[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos0[destino_x][destino_y]=5;
                    tablogic0->eliminar(destino_x, destino_y, pab);
                    tablogic0->insertar(destino_x, destino_y, "Cn");
                    tab0[destino_x][destino_y]->setText(" ");
                    tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballonegro));

                    ui->listamovimientos->addItem("-"+jug1);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=false;
                    ui->lblturnoactual->setText(jug2);
                }

            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else if(ub1>0 && tabdest==1){
        QString coo = QString::number(ub1); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_caballo("Cn",actual_x,actual_y,destino_x,destino_y,1);
        if(puede==true){
            int pieza = tabpos1[destino_x][destino_y];
            if(pieza==0){
                tabpos1[actual_x][actual_y] = 0;
                tablogic1->eliminar(actual_x, actual_y, "Cn");
                tab1[actual_x][actual_y]->setText(" ");

                tabpos1[destino_x][destino_y] = 5;
                tablogic1->insertar(destino_x,destino_y,"Cn");
                tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballonegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else if(pieza>=7 && pieza<=12){
                if(pieza==8){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos1[actual_x][actual_y] = 0;
                    tablogic1->eliminar(actual_x, actual_y, "Cn");
                    tab1[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos1[destino_x][destino_y]=5;
                    tablogic1->eliminar(destino_x, destino_y, pab);
                    tablogic1->insertar(destino_x, destino_y, "Cn");
                    tab1[destino_x][destino_y]->setText(" ");
                    tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballonegro));

                    ui->listamovimientos->addItem("-"+jug1);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=false;
                    ui->lblturnoactual->setText(jug2);
                }

            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else if(ub2>0 && tabdest==2){
        QString coo = QString::number(ub2); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_caballo("Cn",actual_x,actual_y,destino_x,destino_y,2);
        if(puede==true){
            int pieza = tabpos2[destino_x][destino_y];
            if(pieza==0){
                tabpos2[actual_x][actual_y] = 0;
                tablogic2->eliminar(actual_x, actual_y, "Cn");
                tab2[actual_x][actual_y]->setText(" ");

                tabpos2[destino_x][destino_y] = 5;
                tablogic2->insertar(destino_x,destino_y,"Cn");
                tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballonegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else if(pieza>=7 && pieza<=12){
                if(pieza==8){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos2[actual_x][actual_y] = 0;
                    tablogic2->eliminar(actual_x, actual_y, "Cn");
                    tab2[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos2[destino_x][destino_y]=5;
                    tablogic2->eliminar(destino_x, destino_y, pab);
                    tablogic2->insertar(destino_x, destino_y, "Cn");
                    tab2[destino_x][destino_y]->setText(" ");
                    tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballonegro));

                    ui->listamovimientos->addItem("-"+jug1);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=false;
                    ui->lblturnoactual->setText(jug2);
                }

            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Ningun caballo puede moverse a esa posicion.");
    }
}

void MainWindow::caballo_blanco(char *cnficha, int destino_x, int destino_y, int tabdest, QString coordenada){
    int ub0 = tablogic0->ubicacion_caballo(cnficha,destino_x,destino_y);
    int ub1 = tablogic1->ubicacion_caballo(cnficha,destino_x,destino_y); //retorna pos actual 502
    int ub2 = tablogic2->ubicacion_caballo(cnficha,destino_x,destino_y);
    if(ub0>0 && tabdest==0){
        QString coo = QString::number(ub0); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_caballo("Cb",actual_x,actual_y,destino_x,destino_y,0);
        if(puede==true){
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                tabpos0[actual_x][actual_y] = 0;
                tablogic0->eliminar(actual_x, actual_y, "Cb");
                tab0[actual_x][actual_y]->setText(" ");

                tabpos0[destino_x][destino_y] = 11;
                tablogic0->insertar(destino_x,destino_y,"Cb");
                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballoblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else if(pieza>=1 && pieza<=6){
                if(pieza==2){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos0[actual_x][actual_y] = 0;
                    tablogic0->eliminar(actual_x, actual_y, "Cb");
                    tab0[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos0[destino_x][destino_y]=11;
                    tablogic0->eliminar(destino_x, destino_y, pab);
                    tablogic0->insertar(destino_x, destino_y, "Cb");
                    tab0[destino_x][destino_y]->setText(" ");
                    tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballoblanco));

                    ui->listamovimientos->addItem("-"+jug2);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=true;
                    ui->lblturnoactual->setText(jug1);
                }

            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else if(ub1>0 && tabdest==1){
        QString coo = QString::number(ub1); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_caballo("Cb",actual_x,actual_y,destino_x,destino_y,1);
        if(puede==true){
            int pieza = tabpos1[destino_x][destino_y];
            if(pieza==0){
                tabpos1[actual_x][actual_y] = 0;
                tablogic1->eliminar(actual_x, actual_y, "Cb");
                tab1[actual_x][actual_y]->setText(" ");

                tabpos1[destino_x][destino_y] = 11;
                tablogic1->insertar(destino_x,destino_y,"Cb");
                tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballoblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else if(pieza>=1 && pieza<=6){
                if(pieza==2){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos1[actual_x][actual_y] = 0;
                    tablogic1->eliminar(actual_x, actual_y, "Cb");
                    tab1[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos1[destino_x][destino_y]=11;
                    tablogic1->eliminar(destino_x, destino_y, pab);
                    tablogic1->insertar(destino_x, destino_y, "Cb");
                    tab1[destino_x][destino_y]->setText(" ");
                    tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballoblanco));

                    ui->listamovimientos->addItem("-"+jug2);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=true;
                    ui->lblturnoactual->setText(jug1);
                }

            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else if(ub2>0 && tabdest==2){
        QString coo = QString::number(ub2); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_caballo("Cb",actual_x,actual_y,destino_x,destino_y,2);
        if(puede==true){
            int pieza = tabpos2[destino_x][destino_y];
            if(pieza==0){
                tabpos2[actual_x][actual_y] = 0;
                tablogic2->eliminar(actual_x, actual_y, "Cb");
                tab2[actual_x][actual_y]->setText(" ");

                tabpos2[destino_x][destino_y] = 11;
                tablogic2->insertar(destino_x,destino_y,"Cb");
                tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballoblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else if(pieza>=1 && pieza<=6){
                if(pieza==2){
                    ui->btnmover->setEnabled(false);
                    ui->txtmovimiento->setEnabled(false);
                    ui->btniniciar->setEnabled(true);
                    ui->txtjugador1->setEnabled(true);
                    ui->txtjugador2->setEnabled(true);
                    ui->txtjugador1->setText("");
                    ui->txtjugador2->setText("");
                    ui->txtcontratiempo->setEnabled(false);
                    jugador1=true;
                    QMessageBox::information(this,"Fin del Juego.","Dama del contrincante capturada.");
                }else{
                    tabpos2[actual_x][actual_y] = 0;
                    tablogic2->eliminar(actual_x, actual_y, "Cb");
                    tab2[actual_x][actual_y]->setText(" ");

                    QString pieza_a_borrar = nombre_pieza(pieza);
                    char * pab = (char*)malloc(2);
                    char * tmp = pieza_a_borrar.toLatin1().data();
                    strcpy(pab, tmp);

                    tabpos2[destino_x][destino_y]=11;
                    tablogic2->eliminar(destino_x, destino_y, pab);
                    tablogic2->insertar(destino_x, destino_y, "Cb");
                    tab2[destino_x][destino_y]->setText(" ");
                    tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(caballoblanco));

                    ui->listamovimientos->addItem("-"+jug2);
                    ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                    ui->txtmovimiento->setText("");

                    jugador1=true;
                    ui->lblturnoactual->setText(jug1);
                }

            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanco ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Ningun caballo puede moverse a esa posicion.");
    }
}

void MainWindow::torre_negro(char *cnficha, int destino_x, int destino_y, int tabdest, QString coordenada){
    int ub0 = tablogic0->ubicacion_torre(cnficha,destino_x,destino_y);
    int ub1 = tablogic1->ubicacion_torre(cnficha,destino_x,destino_y); //retorna pos actual 502
    int ub2 = tablogic2->ubicacion_torre(cnficha,destino_x,destino_y);
    if(ub0>0&&tabdest==0){
        QString coo = QString::number(ub0); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_torre("Tn",actual_x,actual_y,destino_x,destino_y,0);
        if(puede==true){
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                tabpos0[actual_x][actual_y] = 0;
                tablogic0->eliminar(actual_x, actual_y, "Tn");
                tab0[actual_x][actual_y]->setText(" ");

                tabpos0[destino_x][destino_y] = 3;
                tablogic0->insertar(destino_x,destino_y,"Tn");
                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torrenegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else if(pieza>=7 && pieza<=12){
                tabpos0[actual_x][actual_y] = 0;
                tablogic0->eliminar(actual_x, actual_y, "Tn");
                tab0[actual_x][actual_y]->setText(" ");

                QString pieza_a_borrar = nombre_pieza(pieza);
                char * pab = (char*)malloc(2);
                char * tmp = pieza_a_borrar.toLatin1().data();
                strcpy(pab, tmp);

                tabpos0[destino_x][destino_y]=3;
                tablogic0->eliminar(destino_x, destino_y, pab);
                tablogic0->insertar(destino_x, destino_y, "Tn");
                tab0[destino_x][destino_y]->setText(" ");
                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torrenegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else if(ub1>0&&tabdest==1){
        QString coo = QString::number(ub1); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_torre("Tn",actual_x,actual_y,destino_x,destino_y,1);
        if(puede==true){
            int pieza = tabpos1[destino_x][destino_y];
            if(pieza==0){
                tabpos1[actual_x][actual_y] = 0;
                tablogic1->eliminar(actual_x, actual_y, "Tn");
                tab1[actual_x][actual_y]->setText(" ");

                tabpos1[destino_x][destino_y] = 3;
                tablogic1->insertar(destino_x,destino_y,"Tn");
                tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torrenegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else if(pieza>=7 && pieza<=12){
                tabpos1[actual_x][actual_y] = 0;
                tablogic1->eliminar(actual_x, actual_y, "Tn");
                tab1[actual_x][actual_y]->setText(" ");

                QString pieza_a_borrar = nombre_pieza(pieza);
                char * pab = (char*)malloc(2);
                char * tmp = pieza_a_borrar.toLatin1().data();
                strcpy(pab, tmp);

                tabpos1[destino_x][destino_y]=3;
                tablogic1->eliminar(destino_x, destino_y, pab);
                tablogic1->insertar(destino_x, destino_y, "Tn");
                tab1[destino_x][destino_y]->setText(" ");
                tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torrenegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else if(ub2>0&&tabdest==2){
        QString coo = QString::number(ub2); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_torre("Tn",actual_x,actual_y,destino_x,destino_y,2);
        if(puede==true){
            int pieza = tabpos2[destino_x][destino_y];
            if(pieza==0){
                tabpos2[actual_x][actual_y] = 0;
                tablogic2->eliminar(actual_x, actual_y, "Tn");
                tab2[actual_x][actual_y]->setText(" ");

                tabpos2[destino_x][destino_y] = 3;
                tablogic2->insertar(destino_x,destino_y,"Tn");
                tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torrenegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else if(pieza>=7 && pieza<=12){
                tabpos2[actual_x][actual_y] = 0;
                tablogic2->eliminar(actual_x, actual_y, "Tn");
                tab2[actual_x][actual_y]->setText(" ");

                QString pieza_a_borrar = nombre_pieza(pieza);
                char * pab = (char*)malloc(2);
                char * tmp = pieza_a_borrar.toLatin1().data();
                strcpy(pab, tmp);

                tabpos2[destino_x][destino_y]=3;
                tablogic2->eliminar(destino_x, destino_y, pab);
                tablogic2->insertar(destino_x, destino_y, "Tn");
                tab2[destino_x][destino_y]->setText(" ");
                tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torrenegro));

                ui->listamovimientos->addItem("-"+jug1);
                ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                ui->txtmovimiento->setText("");

                jugador1=false;
                ui->lblturnoactual->setText(jug2);
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza negra ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Ninguna torre puede moverse a esa posicion.");
    }
}

void MainWindow::torre_blanco(char *cnficha, int destino_x, int destino_y, int tabdest, QString coordenada){
    int ub0 = tablogic0->ubicacion_torre(cnficha,destino_x,destino_y);
    int ub1 = tablogic1->ubicacion_torre(cnficha,destino_x,destino_y); //retorna pos actual 502
    int ub2 = tablogic2->ubicacion_torre(cnficha,destino_x,destino_y);
    if(ub0>0&&tabdest==0){
        QString coo = QString::number(ub0); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_torre("Tb",actual_x,actual_y,destino_x,destino_y,0);
        if(puede==true){
            int pieza = tabpos0[destino_x][destino_y];
            if(pieza==0){
                tabpos0[actual_x][actual_y] = 0;
                tablogic0->eliminar(actual_x, actual_y, "Tb");
                tab0[actual_x][actual_y]->setText(" ");

                tabpos0[destino_x][destino_y] = 9;
                tablogic0->insertar(destino_x,destino_y,"Tb");
                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torreblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else if(pieza>=1 && pieza<=6){
                tabpos0[actual_x][actual_y] = 0;
                tablogic0->eliminar(actual_x, actual_y, "Tb");
                tab0[actual_x][actual_y]->setText(" ");

                QString pieza_a_borrar = nombre_pieza(pieza);
                char * pab = (char*)malloc(2);
                char * tmp = pieza_a_borrar.toLatin1().data();
                strcpy(pab, tmp);

                tabpos0[destino_x][destino_y]=9;
                tablogic0->eliminar(destino_x, destino_y, pab);
                tablogic0->insertar(destino_x, destino_y, "Tb");
                tab0[destino_x][destino_y]->setText(" ");
                tab0[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torreblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else if(ub1>0&&tabdest==1){
        QString coo = QString::number(ub1); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_torre("Tb",actual_x,actual_y,destino_x,destino_y,1);
        if(puede==true){
            int pieza = tabpos1[destino_x][destino_y];
            if(pieza==0){
                tabpos1[actual_x][actual_y] = 0;
                tablogic1->eliminar(actual_x, actual_y, "Tb");
                tab1[actual_x][actual_y]->setText(" ");

                tabpos1[destino_x][destino_y] = 9;
                tablogic1->insertar(destino_x,destino_y,"Tb");
                tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torreblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else if(pieza>=1 && pieza<=6){
                tabpos1[actual_x][actual_y] = 0;
                tablogic1->eliminar(actual_x, actual_y, "Tb");
                tab1[actual_x][actual_y]->setText(" ");

                QString pieza_a_borrar = nombre_pieza(pieza);
                char * pab = (char*)malloc(2);
                char * tmp = pieza_a_borrar.toLatin1().data();
                strcpy(pab, tmp);

                tabpos1[destino_x][destino_y]=9;
                tablogic1->eliminar(destino_x, destino_y, pab);
                tablogic1->insertar(destino_x, destino_y, "Tb");
                tab1[destino_x][destino_y]->setText(" ");
                tab1[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torreblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else if(ub2>0&&tabdest==2){
        QString coo = QString::number(ub2); //ej. "406"
        QStringList arr_coo = coo.split("0"); //ej. [4][6] -> [x][y]
        QString tmp = arr_coo.at(0);
        int actual_x = tmp.toInt(); //4
        tmp = arr_coo.at(1);
        int actual_y = tmp.toInt(); //6
        bool puede = validar_camino_torre("Tb",actual_x,actual_y,destino_x,destino_y,2);
        if(puede==true){
            int pieza = tabpos2[destino_x][destino_y];
            if(pieza==0){
                tabpos2[actual_x][actual_y] = 0;
                tablogic2->eliminar(actual_x, actual_y, "Tb");
                tab2[actual_x][actual_y]->setText(" ");

                tabpos2[destino_x][destino_y] = 9;
                tablogic2->insertar(destino_x,destino_y,"Tb");
                tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torreblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else if(pieza>=1 && pieza<=6){
                tabpos2[actual_x][actual_y] = 0;
                tablogic2->eliminar(actual_x, actual_y, "Tb");
                tab2[actual_x][actual_y]->setText(" ");

                QString pieza_a_borrar = nombre_pieza(pieza);
                char * pab = (char*)malloc(2);
                char * tmp = pieza_a_borrar.toLatin1().data();
                strcpy(pab, tmp);

                tabpos2[destino_x][destino_y]=9;
                tablogic2->eliminar(destino_x, destino_y, pab);
                tablogic2->insertar(destino_x, destino_y, "Tb");
                tab2[destino_x][destino_y]->setText(" ");
                tab2[destino_x][destino_y]->setPixmap(QPixmap::fromImage(torreblanco));

                ui->listamovimientos->addItem("-"+jug2);
                ui->listamovimientos->addItem(coordenada+" comio: " + pieza_a_borrar);
                ui->txtmovimiento->setText("");

                jugador1=true;
                ui->lblturnoactual->setText(jug1);
            }else{
                ui->txtmovimiento->setText("");
                QMessageBox::information(this,"Mov. no valido","Hay una pieza blanca ubicada en la coordenada destino.");
            }
        }else{
            ui->txtmovimiento->setText("");
            QMessageBox::information(this,"Mov. no valido","Hay una pieza antes de la posicion destino.");
        }
    }else{
        ui->txtmovimiento->setText("");
        QMessageBox::information(this,"Error!","Ninguna torre puede moverse a esa posicion.");
    }
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
    }

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

    QString archivo = "digraph G{\nnode [shape=record, height=.1;]\n" + nodo_label + subgraf_cluster + "\n}";
    generar_dot(archivo);
}

void MainWindow::crear_grafico_columna(int n){
    QString tablero_completo="";
    if(n==0){
        tablero_completo=tablogic0->estado_columnas();
    }else if(n==1){
        tablero_completo=tablogic1->estado_columnas();
    }else{
        tablero_completo=tablogic2->estado_columnas();
    }
    QString nodo_columna="", nodo_label="";
    QStringList columnas = tablero_completo.split("fincol");
    for(int i=0;i<columnas.length();i++){
        QString columna = columnas.value(i);
        QStringList cada_nodo = columna.split("%");
        for(int j=0;j<cada_nodo.length()-1;j++){
            QString separado = cada_nodo.value(j);
            QStringList dato = separado.split("#");
            nodo_columna += dato.value(0);
            nodo_label += dato.value(1) + "#";
        }
    }
    //cout<<"todos los nodos"<<endl;
    //cout<<nodo_label.toStdString()<<endl;
    QStringList numero = nodo_label.split("#");
    int aux=0, contador=0;
    QString sub_cluster="", final="";
    for(int i=0;i<numero.length()-2;i++){
        QString nodo = numero.value(i);
        if(aux==0){
            //crea un nuevo subgraph
            sub_cluster += "subgraph cluster"+QString::number(contador)+"{\n";
            contador++;
        }

        if(aux==4){
            sub_cluster += "\"node"+nodo+ "\";\n}\n";
            if(i+1 < numero.length()-2){
                QString tmp = numero.value(i+1);
                final += "\"node"+nodo+"\"->\"node"+tmp+"\";";
            }

            aux=0;
        }else{
            if(i+2>numero.length()-2 && aux==0){
                sub_cluster += "\"node"+nodo + "\";\n}\n";
                aux++;
            }else{
                sub_cluster += "\"node"+nodo + "\" -> ";
                aux++;
            }
        }
    }
    QString archivo = "digraph G{\nrankdir=LR;\n[shape=record, height=.1];\n"+sub_cluster+final+"\n}";
    //cout<<archivo.toStdString()<<endl;
    generar_dot(archivo);
}

void MainWindow::crear_grafico_fila(int n){

}

void MainWindow::generar_dot(QString contenido){
    ofstream escritura;
    escritura.open("/home/eduardo/Descargas/dato.dot", ios::out);
    if(escritura.is_open()){
        cout<<"abrio el archivo"<<endl;
        escritura<<contenido.toStdString()<<endl;
    }else{
        cout<<"nell prro"<<endl;
    }
    escritura.close();
    system("dot -Tpng /home/eduardo/Descargas/dato.dot -o /home/eduardo/datosalida.png");

    grafica.load("/home/eduardo/datosalida.png");
    int w = ui->lblgrafica->width();
    int h = ui->lblgrafica->height();
    //ui->lblgrafica->setPixmap(QPixmap::fromImage(grafica));
    ui->lblgrafica->setPixmap(QPixmap::fromImage(grafica.scaled(w,h,Qt::KeepAspectRatio)));
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

void MainWindow::cronometro(int minutos){
    int segundo=0, minuto=0;
    QString tiempo="";
    bool detener=false;
    for(;;){
        if(segundo==60){
            minuto++;
            segundo=0;
        }
        if(minuto==minutos){
            detener=true;
            ui->btnmover->setEnabled(false);
            ui->txtmovimiento->setEnabled(false);
            ui->txtjugador1->setEnabled(true);
            ui->txtjugador2->setEnabled(true);
            ui->btniniciar->setEnabled(true);
            ui->txtcontratiempo->setEnabled(true);
        }
        tiempo = QString::number(minuto)+":"+QString::number(segundo);
        segundo++;
        //Sleep(1000);
    }
}

bool MainWindow::validar_camino_alfil(QString p, int actual_x, int actual_y, int destino_x, int destino_y, int tablero){
    bool c=false;
    int pi_act=0;
    if(actual_x<destino_x){
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
                        if(pi_act>=1 && pi_act<=6){
                            //hay una pieza negra en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }else{
                        //para piezas blancas
                        if(pi_act>=7 && pi_act<=12){
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
            }else{
                if(actual_x+i==destino_x){
                    c=true;
                    break;
                }
            }
        }
    }else if(actual_x>destino_x){
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
                        if(pi_act>=1 && pi_act<=6){
                            //hay una pieza negra en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }else{
                        //para piezas blancas
                        if(pi_act>=7 && pi_act<=12){
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
            }else{
                if(actual_x-i==destino_x){
                    c=true;
                    break;
                }
            }
        }
    }else if(actual_y>destino_y){
        //mov. izq
        for(int i=1;i<=destino_y;i++){
            if(tablero==0){
                pi_act = tabpos0[actual_x][actual_y-i];
            }else if(tablero==1){
                pi_act = tabpos1[actual_x][actual_y-i];
            }else{
                pi_act = tabpos2[actual_x][actual_y-i];
            }

            if(pi_act!=0){
                if(actual_y-i==destino_y){
                    //es a donde se movera
                    if(p=="An"){
                        //para piezas negras
                        if(pi_act>=1 && pi_act<=6){
                            //hay una pieza negra en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }else{
                        //para piezas blancas
                        if(pi_act>=7 && pi_act<=12){
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
            }else{
                if(actual_y-i==destino_y){
                    c=true;
                    break;
                }
            }
        }
    }else{
        //mov. der
        for(int i=1;i<=actual_y;i++){
            if(tablero==0){
                pi_act = tabpos0[actual_x][actual_y+i];
            }else if(tablero==1){
                pi_act = tabpos1[actual_x][actual_y+i];
            }else{
                pi_act = tabpos2[actual_x][actual_y+i];
            }

            if(pi_act!=0){
                if(actual_y+i==destino_y){
                    if(p=="An"){
                        //para piezas negras
                        if(pi_act>=1 && pi_act<=6){
                            //hay una pieza negra en esa posicion
                            break;
                        }else{
                            c=true;
                            break;
                        }
                    }else{
                        //para piezas blancas
                        if(pi_act>=7 && pi_act<=12){
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
            }else{
                if(actual_y+i==destino_y){
                    c=true;
                    break;
                }
            }
        }
    }
    return c;
}

bool MainWindow::validar_camino_caballo(QString p, int actual_x, int actual_y, int destino_x, int destino_y, int tablero){
    bool c=false;
    int pi_actual=0;
    if(actual_x<destino_x){
        //hacia abajo
        if(actual_y>destino_y){
            //izquierda
            if(actual_x+1==destino_x && actual_y-2==destino_y){
                bool detener=false;
                int caso=0;
                while(detener==false){
                    if(caso==0){
                        for(int i=1;i<=destino_y;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x][actual_y-i];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x][actual_y-i];
                            }else{
                                pi_actual=tabpos2[actual_x][actual_y-i];
                            }

                            if(pi_actual!=0){
                                //encontro algo
                                caso=1;
                                break;
                            }else{
                                //igual a cero
                                if(actual_y-i==destino_y){
                                    //columna destino
                                    if(tablero==0){
                                        pi_actual=tabpos0[actual_x+1][actual_y-i];
                                    }else if(tablero==1){
                                        pi_actual=tabpos1[actual_x+1][actual_y-i];
                                    }else{
                                        pi_actual=tabpos2[actual_x+1][actual_y-i];
                                    }
                                    //baja a la casilla destino
                                    if(p=="Cn"){
                                        if(pi_actual>=1 && pi_actual<=6){
                                            detener=true;//hay una pieza negra en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7 && pi_actual<=12){
                                            detener=true;//hay una pieza blanca en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }else{//------------------------------CASO 1--------------------
                        for(int i=0;i<=destino_y;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x+1][actual_y-i];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x+1][actual_y-i];
                            }else{
                                pi_actual=tabpos2[actual_x+1][actual_y-i];
                            }

                            if(pi_actual!=0){
                                //encontro algo
                                detener=true;
                                break;
                            }else{
                                //igual a cero
                                if(actual_y-i==destino_y){
                                    //columna destino
                                    if(p=="Cn"){
                                        if(pi_actual>=1 && pi_actual<=6){
                                            detener=true;//hay una pieza negra en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7 && pi_actual<=12){
                                            detener=true;//hay una pieza blanca en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }else if(actual_x+2==destino_x && actual_y-1==destino_y){
                bool detener=false;
                int caso=0;
                while(detener==false){
                    if(caso==0){
                        for(int i=1;i<=destino_x;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x+i][actual_y];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x+i][actual_y];
                            }else{
                                pi_actual=tabpos2[actual_x+i][actual_y];
                            }
                            if(pi_actual!=0){
                                caso=1;
                                break;
                            }else{
                                if(actual_x+i==destino_x){
                                    if(tablero==0){
                                        pi_actual=tabpos0[actual_x+i][actual_y-1];
                                    }else if(tablero==1){
                                        pi_actual=tabpos1[actual_x+i][actual_y-1];
                                    }else{
                                        pi_actual=tabpos2[actual_x+i][actual_y-1];
                                    }
                                    if(p=="Cn"){
                                        if(pi_actual>=1&&pi_actual<=6){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7&&pi_actual<=12){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }else{//----------------------------CASO 1------------------
                        for(int i=0;i<=destino_x;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x+i][actual_y-1];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x+i][actual_y-1];
                            }else{
                                pi_actual=tabpos2[actual_x+i][actual_y-1];
                            }
                            if(pi_actual!=0){
                                detener=true;
                                break;
                            }else{
                                if(actual_x+i==destino_x){
                                    if(p=="Cn"){
                                        if(pi_actual>=1&&pi_actual<=6){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7&&pi_actual<=12){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }else if(actual_y<destino_y){
            //derecha
            if(actual_x+1==destino_x && actual_y+2==destino_y){
                bool detener=false;
                int caso=0;
                while(detener==false){
                    if(caso==0){
                        for(int i=1;i<=destino_y;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x][actual_y+i];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x][actual_y+i];
                            }else{
                                pi_actual=tabpos2[actual_x][actual_y+i];
                            }

                            if(pi_actual!=0){
                                //encontro algo
                                caso=1;
                                break;
                            }else{
                                //igual a cero
                                if(actual_y+i==destino_y){
                                    //columna destino
                                    if(tablero==0){
                                        pi_actual=tabpos0[actual_x+1][actual_y+i];
                                    }else if(tablero==1){
                                        pi_actual=tabpos1[actual_x+1][actual_y+i];
                                    }else{
                                        pi_actual=tabpos2[actual_x+1][actual_y+i];
                                    }
                                    //baja a la casilla destino
                                    if(p=="Cn"){
                                        if(pi_actual>=1 && pi_actual<=6){
                                            detener=true;//hay una pieza negra en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7 && pi_actual<=12){
                                            detener=true;//hay una pieza blanca en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }else{//------------------------------CASO 1--------------------
                        for(int i=0;i<=destino_y;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x+1][actual_y+i];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x+1][actual_y+i];
                            }else{
                                pi_actual=tabpos2[actual_x+1][actual_y+i];
                            }

                            if(pi_actual!=0){
                                //encontro algo
                                detener=true;
                                break;
                            }else{
                                //igual a cero
                                if(actual_y+i==destino_y){
                                    //columna destino
                                    if(p=="Cn"){
                                        if(pi_actual>=1 && pi_actual<=6){
                                            detener=true;//hay una pieza negra en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7 && pi_actual<=12){
                                            detener=true;//hay una pieza blanca en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }else if(actual_x+2==destino_x && actual_y+1==destino_y){
                bool detener=false;
                int caso=0;
                while(detener==false){
                    if(caso==0){
                        for(int i=1;i<=destino_x;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x+i][actual_y];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x+i][actual_y];
                            }else{
                                pi_actual=tabpos2[actual_x+i][actual_y];
                            }
                            if(pi_actual!=0){
                                caso=1;
                                break;
                            }else{
                                if(actual_x+i==destino_x){
                                    if(tablero==0){
                                        pi_actual=tabpos0[actual_x+i][actual_y+1];
                                    }else if(tablero==1){
                                        pi_actual=tabpos1[actual_x+i][actual_y+1];
                                    }else{
                                        pi_actual=tabpos2[actual_x+i][actual_y+1];
                                    }
                                    if(p=="Cn"){
                                        if(pi_actual>=1&&pi_actual<=6){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7&&pi_actual<=12){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }else{//----------------------------CASO 1------------------
                        for(int i=0;i<=destino_x;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x+i][actual_y+1];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x+i][actual_y+1];
                            }else{
                                pi_actual=tabpos2[actual_x+i][actual_y+1];
                            }
                            if(pi_actual!=0){
                                detener=true;
                                break;
                            }else{
                                if(actual_x+i==destino_x){
                                    if(p=="Cn"){
                                        if(pi_actual>=1&&pi_actual<=6){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7&&pi_actual<=12){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }else if(actual_x>destino_x){
        //hacia arriba
        if(actual_y>destino_y){
            /*izquierda*/
            if(actual_x-1==destino_x && actual_y-2==destino_y){
                bool detener=false;
                int caso=0;
                while(detener==false){
                    if(caso==0){
                        for(int i=1;i<=destino_y;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x][actual_y-i];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x][actual_y-i];
                            }else{
                                pi_actual=tabpos2[actual_x][actual_y-i];
                            }

                            if(pi_actual!=0){
                                //encontro algo
                                caso=1;
                                break;
                            }else{
                                //igual a cero
                                if(actual_y-i==destino_y){
                                    //columna destino
                                    if(tablero==0){
                                        pi_actual=tabpos0[actual_x-1][actual_y-i];
                                    }else if(tablero==1){
                                        pi_actual=tabpos1[actual_x-1][actual_y-i];
                                    }else{
                                        pi_actual=tabpos2[actual_x-1][actual_y-i];
                                    }
                                    //baja a la casilla destino
                                    if(p=="Cn"){
                                        if(pi_actual>=1 && pi_actual<=6){
                                            detener=true;//hay una pieza negra en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7 && pi_actual<=12){
                                            detener=true;//hay una pieza blanca en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }else{//------------------------------CASO 1--------------------
                        for(int i=0;i<=destino_y;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x-1][actual_y-i];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x-1][actual_y-i];
                            }else{
                                pi_actual=tabpos2[actual_x-1][actual_y-i];
                            }

                            if(pi_actual!=0){
                                //encontro algo
                                detener=true;
                                break;
                            }else{
                                //igual a cero
                                if(actual_y-i==destino_y){
                                    //columna destino
                                    if(p=="Cn"){
                                        if(pi_actual>=1 && pi_actual<=6){
                                            detener=true;//hay una pieza negra en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7 && pi_actual<=12){
                                            detener=true;//hay una pieza blanca en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }else if(actual_x-2==destino_x && actual_y-1==destino_y){
                bool detener=false;
                int caso=0;
                while(detener==false){
                    if(caso==0){
                        for(int i=1;i<=destino_x;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x-i][actual_y];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x-i][actual_y];
                            }else{
                                pi_actual=tabpos2[actual_x-i][actual_y];
                            }
                            if(pi_actual!=0){
                                caso=1;
                                break;
                            }else{
                                if(actual_x-i==destino_x){
                                    if(tablero==0){
                                        pi_actual=tabpos0[actual_x-i][actual_y-1];
                                    }else if(tablero==1){
                                        pi_actual=tabpos1[actual_x-i][actual_y-1];
                                    }else{
                                        pi_actual=tabpos2[actual_x-i][actual_y-1];
                                    }
                                    if(p=="Cn"){
                                        if(pi_actual>=1&&pi_actual<=6){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7&&pi_actual<=12){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }else{//----------------------------CASO 1------------------
                        for(int i=0;i<=destino_x;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x-i][actual_y-1];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x-i][actual_y-1];
                            }else{
                                pi_actual=tabpos2[actual_x-i][actual_y-1];
                            }
                            if(pi_actual!=0){
                                detener=true;
                                break;
                            }else{
                                if(actual_x-i==destino_x){
                                    if(p=="Cn"){
                                        if(pi_actual>=1&&pi_actual<=6){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7&&pi_actual<=12){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }else if(actual_y<destino_y){
            /*derecha*/
            if(actual_x-1==destino_x && actual_y+2==destino_y){
                bool detener=false;
                int caso=0;
                while(detener==false){
                    if(caso==0){
                        for(int i=1;i<=destino_y;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x][actual_y+i];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x][actual_y+i];
                            }else{
                                pi_actual=tabpos2[actual_x][actual_y+i];
                            }

                            if(pi_actual!=0){
                                //encontro algo
                                caso=1;
                                break;
                            }else{
                                //igual a cero
                                if(actual_y+i==destino_y){
                                    //columna destino
                                    if(tablero==0){
                                        pi_actual=tabpos0[actual_x-1][actual_y+i];
                                    }else if(tablero==1){
                                        pi_actual=tabpos1[actual_x-1][actual_y+i];
                                    }else{
                                        pi_actual=tabpos2[actual_x-1][actual_y+i];
                                    }
                                    //baja a la casilla destino
                                    if(p=="Cn"){
                                        if(pi_actual>=1 && pi_actual<=6){
                                            detener=true;//hay una pieza negra en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7 && pi_actual<=12){
                                            detener=true;//hay una pieza blanca en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }else{//------------------------------CASO 1--------------------
                        for(int i=0;i<=destino_y;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x-1][actual_y+i];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x-1][actual_y+i];
                            }else{
                                pi_actual=tabpos2[actual_x-1][actual_y+i];
                            }

                            if(pi_actual!=0){
                                //encontro algo
                                detener=true;
                                break;
                            }else{
                                //igual a cero
                                if(actual_y+i==destino_y){
                                    //columna destino
                                    if(p=="Cn"){
                                        if(pi_actual>=1 && pi_actual<=6){
                                            detener=true;//hay una pieza negra en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7 && pi_actual<=12){
                                            detener=true;//hay una pieza blanca en esa posicion
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;//hay una pieza blanca o vacia en esa posicion
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }else if(actual_x-2==destino_x && actual_y+1==destino_y){
                bool detener=false;
                int caso=0;
                while(detener==false){
                    if(caso==0){
                        for(int i=1;i<=destino_x;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x-i][actual_y];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x-i][actual_y];
                            }else{
                                pi_actual=tabpos2[actual_x-i][actual_y];
                            }
                            if(pi_actual!=0){
                                caso=1;
                                break;
                            }else{
                                if(actual_x-i==destino_x){
                                    if(tablero==0){
                                        pi_actual=tabpos0[actual_x-i][actual_y+1];
                                    }else if(tablero==1){
                                        pi_actual=tabpos1[actual_x-i][actual_y+1];
                                    }else{
                                        pi_actual=tabpos2[actual_x-i][actual_y+1];
                                    }
                                    if(p=="Cn"){
                                        if(pi_actual>=1&&pi_actual<=6){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7&&pi_actual<=12){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }else{//----------------------------CASO 1------------------
                        for(int i=0;i<=destino_x;i++){
                            if(tablero==0){
                                pi_actual=tabpos0[actual_x-i][actual_y+1];
                            }else if(tablero==1){
                                pi_actual=tabpos1[actual_x-i][actual_y+1];
                            }else{
                                pi_actual=tabpos2[actual_x-i][actual_y+1];
                            }
                            if(pi_actual!=0){
                                detener=true;
                                break;
                            }else{
                                if(actual_x-i==destino_x){
                                    if(p=="Cn"){
                                        if(pi_actual>=1&&pi_actual<=6){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }else{
                                        if(pi_actual>=7&&pi_actual<=12){
                                            detener=true;
                                            break;
                                        }else{
                                            detener=true;
                                            c=true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return c;
}

bool MainWindow::validar_camino_torre(QString p, int actual_x, int actual_y, int destino_x, int destino_y, int tablero){
    bool c=false;
    int pi_actual=0;
    if(actual_x < destino_x){
        /*hacia abajo*/
        if(actual_y < destino_y){
            //hacia derecha
            int tmp = destino_y - actual_y;
            for(int i=1;i<=tmp;i++){
                if(tablero==0){
                    pi_actual = tabpos0[actual_x+i][actual_y+i];
                }else if(tablero==1){
                    pi_actual = tabpos1[actual_x+i][actual_y+i];
                }else{
                    pi_actual = tabpos2[actual_x+i][actual_y+i];
                }
                if(pi_actual!=0){
                    if(actual_x+i==destino_x && actual_y+i==destino_y){
                        if(p=="Tn"){
                            if(pi_actual>=1 && pi_actual<=6){
                                //hay una pieza negra en esa posicion
                                break;
                            }else{
                                c=true;
                                break;
                            }
                        }else{
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
                }else{
                    if(actual_x+i==destino_x && actual_y+i==destino_y){
                        c=true;
                        break;
                    }
                }
            }
        }else if(actual_y > destino_y){
            //hacia izquierda
            int tmp = actual_y - destino_y;
            for(int i=1;i<=tmp;i++){
                if(tablero==0){
                    pi_actual = tabpos0[actual_x+i][actual_y-i];
                }else if(tablero==1){
                    pi_actual = tabpos1[actual_x+i][actual_y-i];
                }else{
                    pi_actual = tabpos2[actual_x+i][actual_y-i];
                }
                if(pi_actual!=0){
                    if(actual_x+i==destino_x && actual_y-i==destino_y){
                        if(p=="Tn"){
                            if(pi_actual>=1 && pi_actual<=6){
                                //hay una pieza negra en esa posicion
                                break;
                            }else{
                                c=true;
                                break;
                            }
                        }else{
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
                }else{
                    if(actual_x+i==destino_x && actual_y-i==destino_y){
                        c=true;
                        break;
                    }
                }
            }
        }
    }else if(actual_x > destino_x){
        /*hacia arriba*/
        if(actual_y < destino_y){
            //hacia derecha
            int tmp = destino_y - actual_y;
            for(int i=1;i<=tmp;i++){
                if(tablero==0){
                    pi_actual = tabpos0[actual_x-i][actual_y+i];
                }else if(tablero==1){
                    pi_actual = tabpos1[actual_x-i][actual_y+i];
                }else{
                    pi_actual = tabpos2[actual_x-i][actual_y+i];
                }
                if(pi_actual!=0){
                    if(actual_x-i==destino_x && actual_y+i==destino_y){
                        if(p=="Tn"){
                            if(pi_actual>=1 && pi_actual<=6){
                                //hay una pieza negra en esa posicion
                                break;
                            }else{
                                c=true;
                                break;
                            }
                        }else{
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
                }else{
                    if(actual_x-i==destino_x && actual_y+i==destino_y){
                        c=true;
                        break;
                    }
                }
            }
        }else if(actual_y > destino_y){
            //hacia izquierda
            int tmp = actual_y - destino_y;
            for(int i=1;i<=tmp;i++){
                if(tablero==0){
                    pi_actual = tabpos0[actual_x-i][actual_y-i];
                }else if(tablero==1){
                    pi_actual = tabpos1[actual_x-i][actual_y-i];
                }else{
                    pi_actual = tabpos2[actual_x-i][actual_y-i];
                }
                if(pi_actual!=0){
                    if(actual_x-i==destino_x && actual_y-i==destino_y){
                        if(p=="Tn"){
                            if(pi_actual>=1 && pi_actual<=6){
                                //hay una pieza negra en esa posicion
                                break;
                            }else{
                                c=true;
                                break;
                            }
                        }else{
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
                }else{
                    if(actual_x-i==destino_x && actual_y-i==destino_y){
                        c=true;
                        break;
                    }
                }
            }
        }
    }
    return c;
}

void MainWindow::on_btnestado_clicked()
{
    if(ui->rbtnlvl0->isChecked()){
        crear_grafico_tablero(0);
    }
    if(ui->rbtnlvl1->isChecked()){
        crear_grafico_tablero(1);
    }
    if(ui->rbtnlvl2->isChecked()){
        crear_grafico_tablero(2);
    }
}

void MainWindow::on_btnlinealizacion_clicked()
{
    if(ui->rbtnlvl0lin->isChecked() && ui->rbtnfilaslin->isChecked()){

    }
    if(ui->rbtnlvl0lin->isChecked() && ui->rbtncolumnaslin->isChecked()){

    }
    if(ui->rbtnlvl1lin->isChecked() && ui->rbtnfilaslin->isChecked()){

    }
    if(ui->rbtnlvl1lin->isChecked() && ui->rbtncolumnaslin->isChecked()){

    }
    if(ui->rbtnlvl2lin->isChecked() && ui->rbtnfilaslin->isChecked()){

    }
    if(ui->rbtnlvl2lin->isChecked() && ui->rbtncolumnaslin->isChecked()){

    }
}

void MainWindow::on_btniniciar_clicked()
{
    jug1 = ui->txtjugador1->text();
    jug2 = ui->txtjugador2->text();
    if(jug1.isEmpty()||jug1.isNull()||jug2.isEmpty()||jug2.isNull()){
        QMessageBox::information(this,"Error!","Deben llenar los campos con los nombres de usuario.");
    }else{
        if(ui->rbtncontratiempo->isChecked()){
            QString tiempo = ui->txtcontratiempo->text();
            if(tiempo.isEmpty()||tiempo.isNull()){
                QMessageBox::information(this,"Error!","Ingresa un tiempo (min).");
            }else{
                ui->btnmover->setEnabled(true);
                ui->txtmovimiento->setEnabled(true);
                ui->btniniciar->setEnabled(false);
                ui->txtjugador1->setEnabled(false);
                ui->txtjugador2->setEnabled(false);
                ui->txtcontratiempo->setEnabled(false);
                //comienza el juego
            }
        }
        if(ui->rbtnnormal->isChecked()){
            ui->btnmover->setEnabled(true);
            ui->txtmovimiento->setEnabled(true);
            ui->btniniciar->setEnabled(false);
            ui->txtjugador1->setEnabled(false);
            ui->txtjugador2->setEnabled(false);
            ui->txtcontratiempo->setEnabled(false);
            ui->lblturnoactual->setText(jug1);
            ui->listamovimientos->addItem("**INICIO DE PARTIDA**");
            //comienza el juego
        }
    }
}
