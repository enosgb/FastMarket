#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QIcon cadeado_aberto;
    QIcon cadeado_fechado;


private slots:
    void on_btn_bloqueio_clicked();

    void on_btn_novaVenda_clicked();

    void on_actionEstoque_triggered();

    void on_actionUsu_rios_triggered();

    void on_actionVendas_triggered();

    void on_actionSAIR_triggered();

    void on_actionSobre_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
