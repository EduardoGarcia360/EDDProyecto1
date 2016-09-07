#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

/*fichas*/
QImage peonnegro, alfilnegro, caballonegro, torrenegro, damanegro, reynegro;
QImage peonblanco, alfilblanco, caballoblanco, torreblanco, damablanco, reyblanco;
/*matriz de label para los tableros*/
QLabel* tab0[9][9];
QLabel* tab1[9][9];
QLabel* tab2[9][9];
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

    ui->setupUi(this);

    fondo0 = new QLabel();
    fondo1 = new QLabel();
    fondo2 = new QLabel();

    /*creacion de tableros eje invertido (y,x)*/
    for(int columna=1; columna<9; columna++){
        for(int fila=1; fila<9; fila++){
            /*para tablero nivel 0*/
            tab0[columna][fila] = new QLabel(fondo0);
            tab0[columna][fila]->setGeometry(fila*32 ,columna*30,32,30); //ancho, alto
            tab0[columna][fila]->setAutoFillBackground(true);
            /*para tablero nivel 1*/
            tab1[columna][fila] = new QLabel(fondo1);
            tab1[columna][fila]->setGeometry(fila*32 ,columna*30,32,30);
            tab1[columna][fila]->setAutoFillBackground(true);
            /*para tablero nivel 2*/
            tab2[columna][fila] = new QLabel(fondo2);
            tab2[columna][fila]->setGeometry(fila*32 ,columna*30,32,30);
            tab2[columna][fila]->setAutoFillBackground(true);
            /*coloreando cada casilla*/
            if(fila==1 || fila==3 || fila==5 || fila==7){
                if(columna==1 || columna==3 || columna==5 || columna==7){
                    tab0[columna][fila]->setPalette(blanco);
                    tab1[columna][fila]->setPalette(blanco);
                    tab2[columna][fila]->setPalette(blanco);
                }else{
                    tab0[columna][fila]->setPalette(gris);
                    tab1[columna][fila]->setPalette(gris);
                    tab2[columna][fila]->setPalette(gris);
                }
            }else{
                if(columna==1 || columna==3 || columna==5 || columna==7){
                    tab0[columna][fila]->setPalette(gris);
                    tab1[columna][fila]->setPalette(gris);
                    tab2[columna][fila]->setPalette(gris);
                }else{
                    tab0[columna][fila]->setPalette(blanco);
                    tab1[columna][fila]->setPalette(blanco);
                    tab2[columna][fila]->setPalette(blanco);
                }
            }
        } //fin for columna
    } //fin for fila

    /*agregando las piezas*/
    for(int fila=1; fila<9; fila++){
        for(int columna=1; columna<9; columna++){
            /*agregando fichas negras*/
            if(fila==1){
                if(columna==1){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(caballonegro));
                    tab2[fila][columna]->setPixmap(QPixmap::fromImage(caballonegro));
                }else if(columna==8){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(caballonegro));
                    tab1[fila][columna]->setPixmap(QPixmap::fromImage(caballonegro));
                }else if(columna==2){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tab2[fila][columna]->setPixmap(QPixmap::fromImage(alfilnegro));
                }else if(columna==7){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tab1[fila][columna]->setPixmap(QPixmap::fromImage(alfilnegro));
                }else if(columna==3){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(torrenegro));
                    tab2[fila][columna]->setPixmap(QPixmap::fromImage(torrenegro));
                }else if(columna==6){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(torrenegro));
                    tab1[fila][columna]->setPixmap(QPixmap::fromImage(torrenegro));
                }else if(columna==4){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(reynegro));
                }else if(columna==5){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(damanegro));
                }
            }else if(fila==2){
                if(columna==1 || columna==2 || columna==3){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(peonnegro));
                    tab2[fila][columna]->setPixmap(QPixmap::fromImage(peonnegro));
                }else if(columna==6 || columna==7 || columna==8){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(peonnegro));
                    tab1[fila][columna]->setPixmap(QPixmap::fromImage(peonnegro));
                }else{
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(peonnegro));
                }
            }else if(fila==7){ //agregando fichas blancas
                if(columna==1 || columna==2 || columna==3){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(peonblanco));
                    tab1[fila][columna]->setPixmap(QPixmap::fromImage(peonblanco));
                }else if(columna==6 || columna==7 || columna==8){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(peonblanco));
                    tab2[fila][columna]->setPixmap(QPixmap::fromImage(peonblanco));
                }else{
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(peonblanco));
                }
            }else if(fila==8){
                if(columna==1){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tab1[fila][columna]->setPixmap(QPixmap::fromImage(caballoblanco));
                }else if(columna==8){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tab2[fila][columna]->setPixmap(QPixmap::fromImage(caballoblanco));
                }else if(columna==2){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tab1[fila][columna]->setPixmap(QPixmap::fromImage(alfilblanco));
                }else if(columna==7){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tab2[fila][columna]->setPixmap(QPixmap::fromImage(alfilblanco));
                }else if(columna==3){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(torreblanco));
                    tab1[fila][columna]->setPixmap(QPixmap::fromImage(torreblanco));
                }else if(columna==6){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(torreblanco));
                    tab2[fila][columna]->setPixmap(QPixmap::fromImage(torreblanco));
                }else if(columna==4){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(reyblanco));
                }else if(columna==5){
                    tab0[fila][columna]->setPixmap(QPixmap::fromImage(damablanco));
                }
            }
        }
    }

    /*lo agregamos al scrollpane*/
    ui->tablero0->setWidget(fondo0);
    ui->tablero1->setWidget(fondo1);
    ui->tablero2->setWidget(fondo2);

    ui->label_5->setText("el papu");

    /*--------------MODIFICAR EL LABEL----------------
     * QLabel *ejemplo = new QLabel("algo para mostrar");
     * ---para cambiar el color del label
     * ejemplo->setAutoFillBackground(true);
     * ejemplo->setPalette(gris);
     * ---para colocar una imagen en el label
     * ejemplo->setPixmap(QPixmap::fromImage(peonnegro));
     * -------------AGREGAR AL TABLERO----------------
     * gridlayout (Tablero0,1,2) nos sirve para acomodar por filas y columnas un objeto
     * ui->Tablero1->addWidget(ejemplo,0,0);
     * ---addWidget(objeto,fila,columna);
     * */
}

MainWindow::~MainWindow()
{
    delete ui;
}
