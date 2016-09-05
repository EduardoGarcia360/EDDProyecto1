#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*imagenes de las fichas negras*/
    QImage peonnegro, alfilnegro, caballonegro, torrenegro, damanegro, reynegro;
    peonnegro.load("/home/eduardo/Descargas/peonnegro.png");
    alfilnegro.load("/home/eduardo/Descargas/alfilnegro.png");
    caballonegro.load("/home/eduardo/Descargas/caballonegro.png");
    torrenegro.load("/home/eduardo/Descargas/torrenegro.png");
    damanegro.load("/home/eduardo/Descargas/damanegro.png");
    reynegro.load("/home/eduardo/Descargas/reynegro.png");

    /*imagenes de las fichas blancas*/
    QImage peonblanco, alfilblanco, caballoblanco, torreblanco, damablanco, reyblanco;
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
    for(int fila=0; fila<4; fila++){
        for(int columna=0; columna<4; columna++){
            QLabel *label = new QLabel();
            label->setText("algojjj");
            ui->Tablero1->addWidget(label,fila,columna);
        }
    }

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
