#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "string"
#include "QMessageBox"
#include "iostream"
using namespace std;

/*fichas*/
QImage peonnegro, alfilnegro, caballonegro, torrenegro, damanegro, reynegro;
QImage peonblanco, alfilblanco, caballoblanco, torreblanco, damablanco, reyblanco;
/*matriz de label para los tableros*/
QLabel* tab0[9][9];
QLabel* tab1[9][9];
QLabel* tab2[9][9];
/*matriz para validar posiciones*/
int tablogic0[9][9];
int tablogic1[9][9];
int tablogic2[9][9];
/*fondo para los scrollarea*/
QLabel* fondo0;
QLabel* fondo1;
QLabel* fondo2;

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

    //ui->setupUi(this);

    fondo0 = new QLabel();
    fondo1 = new QLabel();
    fondo2 = new QLabel();

    for(int x=0; x<9; x++){
        for(int y=0; y<9; y++){

            /*para tablero nivel 0*/
            tab0[x][y] = new QLabel(fondo0);
            tab0[x][y]->setGeometry(x*32,y*30,32,30); //ancho, alto
            tab0[x][y]->setAutoFillBackground(true);
            /*para tablero nivel 1*/
            tab1[x][y] = new QLabel(fondo1);
            tab1[x][y]->setGeometry(x*32 ,y*30,32,30);
            tab1[x][y]->setAutoFillBackground(true);
            /*para tablero nivel 2*/
            tab2[x][y] = new QLabel(fondo2);
            tab2[x][y]->setGeometry(x*32 ,y*30,32,30);
            tab2[x][y]->setAutoFillBackground(true);

            /*colocando nombre de fila y columna*/
            if(y==0){
                /*colocando nombre a las columnas*/
                if(x==1){
                    tab0[x][y]->setText("1");
                    tab1[x][y]->setText("1");
                    tab2[x][y]->setText("1");
                }else if(x==2){
                    tab0[x][y]->setText("2");
                    tab1[x][y]->setText("2");
                    tab2[x][y]->setText("2");
                }else if(x==3){
                    tab0[x][y]->setText("3");
                    tab1[x][y]->setText("3");
                    tab2[x][y]->setText("3");
                }else if(x==4){
                    tab0[x][y]->setText("4");
                    tab1[x][y]->setText("4");
                    tab2[x][y]->setText("4");
                }else if(x==5){
                    tab0[x][y]->setText("5");
                    tab1[x][y]->setText("5");
                    tab2[x][y]->setText("5");
                }else if(x==6){
                    tab0[x][y]->setText("6");
                    tab1[x][y]->setText("6");
                    tab2[x][y]->setText("6");
                }else if(x==7){
                    tab0[x][y]->setText("7");
                    tab1[x][y]->setText("7");
                    tab2[x][y]->setText("7");
                }else if(x==8){
                    tab0[x][y]->setText("8");
                    tab1[x][y]->setText("8");
                    tab2[x][y]->setText("8");
                }
            }else if(x==0){
                /*colocando nombre a las filas*/
                if(y==1){
                    tab0[x][y]->setText("H");
                    tab1[x][y]->setText("H");
                    tab2[x][y]->setText("H");
                }else if(y==2){
                    tab0[x][y]->setText("G");
                    tab1[x][y]->setText("G");
                    tab2[x][y]->setText("G");
                }else if(y==3){
                    tab0[x][y]->setText("F");
                    tab1[x][y]->setText("F");
                    tab2[x][y]->setText("F");
                }else if(y==4){
                    tab0[x][y]->setText("E");
                    tab1[x][y]->setText("E");
                    tab2[x][y]->setText("E");
                }else if(y==5){
                    tab0[x][y]->setText("D");
                    tab1[x][y]->setText("D");
                    tab2[x][y]->setText("D");
                }else if(y==6){
                    tab0[x][y]->setText("C");
                    tab1[x][y]->setText("C");
                    tab2[x][y]->setText("C");
                }else if(y==7){
                    tab0[x][y]->setText("B");
                    tab1[x][y]->setText("B");
                    tab2[x][y]->setText("B");
                }else if(y==8){
                    tab0[x][y]->setText("A");
                    tab1[x][y]->setText("A");
                    tab2[x][y]->setText("A");
                }
            }else{
                /*coloreando cada casilla*/
                if(y==1 || y==3 || y==5 || y==7){
                    if(x==1 || x==3 || x==5 || x==7){
                        tab0[x][y]->setPalette(blanco);
                        tab1[x][y]->setPalette(blanco);
                        tab2[x][y]->setPalette(blanco);
                    }else{
                        tab0[x][y]->setPalette(gris);
                        tab1[x][y]->setPalette(gris);
                        tab2[x][y]->setPalette(gris);
                    }
                }else{
                    if(x==1 || x==3 || x==5 || x==7){
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
        } //fin for columna
    } //fin for fila

    /*agregando las piezas*/
    for(int x=1; x<9; x++){
        for(int y=1; y<9; y++){
            /*agregando fichas negras*/
            if(y==1){
                if(x==1){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tablogic0[x][y] = 5;
                    tablogic2[x][y] = 5;
                }else if(x==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tablogic0[x][y] = 5;
                    tablogic1[x][y] = 5;
                }else if(x==2){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tablogic0[x][y] = 4;
                    tablogic2[x][y] = 4;
                }else if(x==7){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tablogic0[x][y] = 4;
                    tablogic1[x][y] = 4;
                }else if(x==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tablogic0[x][y] = 3;
                    tablogic2[x][y] = 3;
                }else if(x==6){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tablogic0[x][y] = 3;
                    tablogic1[x][y] = 3;
                }else if(x==4){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(reynegro));
                    tablogic0[x][y] = 1;
                }else if(x==5){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(damanegro));
                    tablogic0[x][y] = 2;
                }
            }else if(y==2){
                if(x==1 || x==2 || x==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tablogic0[x][y] = 6;
                    tablogic2[x][y] = 6;
                }else if(x==6 || x==7 || x==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tablogic0[x][y] = 6;
                    tablogic1[x][y] = 6;
                }else{
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tablogic0[x][y] = 6;
                    tablogic1[x][y] = 0;
                    tablogic2[x][y] = 0;
                }
            }else if(y==7){
                /*agregando fichas blancas*/
                if(x==1 || x==2 || x==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tablogic0[x][y] = 16;
                    tablogic1[x][y] = 16;
                }else if(x==6 || x==7 || x==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tablogic0[x][y] = 16;
                    tablogic2[x][y] = 16;
                }else if(x==4 || x==5){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tablogic0[x][y] = 16;
                    tablogic1[x][y] = 0;
                    tablogic2[x][y] = 0;
                }
            }else if(y==8){
                if(x==1){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tablogic0[x][y] = 15;
                    tablogic1[x][y] = 15;
                }else if(x==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tablogic0[x][y] = 15;
                    tablogic2[x][y] = 15;
                }else if(x==2){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tablogic0[x][y] = 14;
                    tablogic1[x][y] = 14;
                }else if(x==7){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tablogic0[x][y] = 14;
                    tablogic2[x][y] = 14;
                }else if(x==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tablogic0[x][y] = 13;
                    tablogic1[x][y] = 13;
                }else if(x==6){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tablogic0[x][y] = 13;
                    tablogic2[x][y] = 13;
                }else if(x==4){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(reyblanco));
                    tablogic0[x][y] = 11;
                }else if(x==5){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(damablanco));
                    tablogic0[x][y] = 12;
                }
            }else{
                tablogic0[x][y] = 0;
                tablogic1[x][y] = 0;
                tablogic2[x][y] = 0;
            }
        }
    }

    std::cout<<tablogic0[3][3]<<std::endl;
    std::cout<<tablogic0[2][1]<<std::endl;
    std::cout<<tablogic1[2][1]<<std::endl;

    /*lo agregamos al scrollpane*/
    ui->tablero0->setWidget(fondo0);
    ui->tablero1->setWidget(fondo1);
    ui->tablero2->setWidget(fondo2);

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
     * Piezas negras: 1=REY, 2=DAMA, 3=TORRE, 4=ALFIL, 5=CABALLO, 6=PEON
     * Piezas blancas: 11=REY, 12=DAMA, 13=TORRE, 14=ALFIL, 15=CABALLO, 16=PEON
     * servira para ubicar las fichas en el tablero
     * */
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
         * P-0-C4
         * [P][0][C4]
         * */
        QStringList arreglocoordenada = coordenada.split("-");
        if(arreglocoordenada.length() != 2){
            QMessageBox::information(this,"Error","Debes ingresar una coordenada valida.");
        }else{

        }

        for(int i=0;i<arreglocoordenada.length(); i++){
            /*recorro el arreglo y agrego los item*/
            ui->listamovimientos->addItem(arreglocoordenada.value(i));
        }
        /*obtengo la posicion 2 ([0][1][2]) que contiene la casilla*/
        QString uno = arreglocoordenada.at(2);
        /*en "uno" esta almacenada la posicion 2, luego retorno el primer
         *caracter de "uno" de (C4) retorna (C)
         * */
        ui->listamovimientos->addItem(uno.at(0));

    }



}//fin boton movimiento
/*
private bool validarcoordenada(QString ficha, QString tablero, QString ubicacion){
    if(ficha=="P" || ficha=="A" || ficha=="C" || ficha=="T" || ficha=="D" || ficha=="R"){
        if(tablero=="0" || tablero=="2" || tablero=="3"){
            if(true){
                return true;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}
*/
