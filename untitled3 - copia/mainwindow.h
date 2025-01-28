#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Analizar_clicked();

    void on_Abrir_clicked();

    void on_Limpiar_clicked();

    void on_Guardar_clicked();

public slots:
void setTextErrores(QString);

public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
