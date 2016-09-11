#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "string"
#include "QMessageBox"
#include "iostream"
#include "MatrizOrtogonal.h"
using namespace std;

/*fichas*/
QImage peonnegro, alfilnegro, caballonegro, torrenegro, damanegro, reynegro;
QImage peonblanco, alfilblanco, caballoblanco, torreblanco, damablanco, reyblanco;
/*matriz de label para los tableros*/
QLabel* tab0[9][9];
QLabel* tab1[9][9];
QLabel* tab2[9][9];
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
                    tablogic0->insertar(x,y,"Cn");
                    tablogic2->insertar(x,y,"Cn");

                    //tablogic0->insertar(3,3,"u");
                    //tablogic0->insertar(3,2,"uio");
                }else if(x==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(caballonegro));
                    tablogic0->insertar(x,y,"Cn");
                    tablogic1->insertar(x,y,"Cn");
                }else if(x==2){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tablogic0->insertar(x,y,"An");
                    tablogic2->insertar(x,y,"An");

                }else if(x==7){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(alfilnegro));
                    tablogic0->insertar(x,y,"An");
                    tablogic1->insertar(x,y,"An");
                }else if(x==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tablogic0->insertar(x,y,"Tn");
                    tablogic2->insertar(x,y,"Tn");
                }else if(x==6){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(torrenegro));
                    tablogic0->insertar(x,y,"Tn");
                    tablogic1->insertar(x,y,"Tn");
                }else if(x==4){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(reynegro));
                    tablogic0->insertar(x,y,"Rn");
                }else if(x==5){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(damanegro));
                    tablogic0->insertar(x,y,"Dn");
                }
            }else if(y==2){
                if(x==1 || x==2 || x==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tablogic0->insertar(x,y,"Pn");
                    tablogic2->insertar(x,y,"Pn");
                }else if(x==6 || x==7 || x==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tablogic0->insertar(x,y,"Pn");
                    tablogic1->insertar(x,y,"Pn");
                }else{
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonnegro));
                    tablogic0->insertar(x,y,"Pn");
                }
            }else if(y==7){
                /*agregando fichas blancas*/
                if(x==1 || x==2 || x==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tablogic0->insertar(x,y,"Pb");
                    tablogic1->insertar(x,y,"Pb");
                }else if(x==6 || x==7 || x==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tablogic0->insertar(x,y,"Pb");
                    tablogic2->insertar(x,y,"Pb");
                }else if(x==4 || x==5){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(peonblanco));
                    tablogic0->insertar(x,y,"Pb");
                }
            }else if(y==8){
                if(x==1){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tablogic0->insertar(x,y,"Cb");
                    tablogic1->insertar(x,y,"Cb");
                }else if(x==8){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(caballoblanco));
                    tablogic0->insertar(x,y,"Cb");
                    tablogic2->insertar(x,y,"Cb");
                }else if(x==2){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tablogic0->insertar(x,y,"Ab");
                    tablogic1->insertar(x,y,"Ab");
                }else if(x==7){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(alfilblanco));
                    tablogic0->insertar(x,y,"Ab");
                    tablogic2->insertar(x,y,"Ab");
                }else if(x==3){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tab1[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tablogic0->insertar(x,y,"Tb");
                    tablogic1->insertar(x,y,"Tb");
                }else if(x==6){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tab2[x][y]->setPixmap(QPixmap::fromImage(torreblanco));
                    tablogic0->insertar(x,y,"Tb");
                    tablogic2->insertar(x,y,"Tb");
                }else if(x==4){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(reyblanco));
                    tablogic0->insertar(x,y,"Tb");
                }else if(x==5){
                    tab0[x][y]->setPixmap(QPixmap::fromImage(damablanco));
                    tablogic0->insertar(x,y,"Db");
                }
            }
        }
    }

    /*lo agregamos al scrollpane*/
    ui->tablero0->setWidget(fondo0);
    ui->tablero1->setWidget(fondo1);
    ui->tablero2->setWidget(fondo2);

    tablogic0->insertar(3,3,"u");

    std::cout<<"Mostrando Columnas del tablero 0"<<std::endl;
    tablogic0->recorrerColumnas();
    std::cout<<"Mostrando Filas del tablero 0"<<std::endl;
    tablogic0->recorrerFilas();
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

        /*validamos que tenga los datos correctos*/
        if(arreglocoordenada.length()-1 != 2){
            QMessageBox::information(this,"Error","Debes ingresar una coordenada valida.");
        }else{
            QString ficha = arreglocoordenada.at(0); //ficha = "p"

            bool bFicha;
            if(jugador1){
                /*turno del jugador 1 fichas negras*/

                /*validando que sea una ficha correcta*/
                if(ficha== "R"){

                }else if(ficha=="D"){

                }else if(ficha=="T"){

                }else if(ficha=="A"){

                }else if(ficha=="C"){

                }else if(ficha=="P"){
                    QString nFicha = ficha+"n";
                    QByteArray bnficha = nFicha.toLatin1();
                    char *charbnficha = bnficha.data();

                    QString destino = arreglocoordenada.at(2);
                    QString dx = destino.at(0);
                    QString dy = destino.at(1);
                    int x = dx.toInt();
                    int y = dy.toInt();
                    bool prueba = tablogic0->moverpeon(charbnficha,x,y);
                    if(prueba){
                        ui->lblerror->setText("si");
                    }else{
                        ui->lblerror->setText("ban");
                    }
                }else{
                    ui->lblerror->setText("Pieza invalida.");
                }
                ui->lblturnoactual->setText("El Tato");


                /*primero validar si hay fichas en existencia*/


                /*al final se cambia el lblturnoactual por el nombre del siguiente jugador
                 * y el bool jugador1 cambia a false.
                 * */
            }else{
                /*turno del jugador 2 fichas blancas*/

                /*validando que sea una ficha correcta*/



                /*al final se cambia el lblturnoactual por el nombre del siguiente jugador
                 * y el bool jugador1 cambia a true.
                 * */
            }//fin turno
            //ui->listamovimientos->addItem(nFicha);

            //QString tablero = arreglocoordenada.at(1);

            /*en "destino" se almacena la coordenada destino,
             *se separa la coordenada en (x,y)
             * */

        }
    }
}//fin boton movimiento

//for(int i=0;i<arreglocoordenada.length(); i++){
    /*recorro el arreglo y agrego los item*/
    //ui->listamovimientos->addItem(arreglocoordenada.value(i));
//}
