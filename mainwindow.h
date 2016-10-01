#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnmover_clicked();
    int letra_a_numero(QString letra);
    void crear_grafico_tablero(int n);
    void generar_dot(QString contenido);
    float obtenerAleatorio(int desde, int hasta);
    QString nombre_pieza(int n);
    QString nombre_pieza_error(QString p);
    void jugador_negro(QStringList arreglocoordenada, QString coordenada);
    void jugador_blanco(QStringList arreglocoordenada, QString coordenada);
    bool validar_nombre_pieza(QString p);
    bool validar_camino_alfil(QString p, int actual_x, int actual_y, int destino_x, int destino_y, int tablero);

    void alfil_negro(char* cnficha, int destino_x, int destino_y, int tabdest, QString coordenada);
    void alfil_blanco(char* cnficha, int destino_x, int destino_y, int tabdest, QString coordenada);
    void peon_negro(char* cnficha, int destino_x, int destino_y, int tabdest, QString coordenada);
    void peon_blanco(char* cnficha, int destino_x, int destino_y, int tabdest, QString coordenada);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
