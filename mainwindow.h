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
    void crear_grafico(int n);
    QString nombre_correcto(QString pieza);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
