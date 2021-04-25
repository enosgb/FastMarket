#ifndef WINDOW_GERENCIARESTOQUE_H
#define WINDOW_GERENCIARESTOQUE_H
#include "connect.h"
#include <QTableWidget>
#include <QDialog>

namespace Ui {
class window_gerenciarEstoque;
}

class window_gerenciarEstoque : public QDialog
{
    Q_OBJECT

public:
    explicit window_gerenciarEstoque(QWidget *parent = nullptr);
    ~window_gerenciarEstoque();

    Conexao con;

private slots:


    void on_btn_limpar_clicked();

    void on_btn_gravarProduto_clicked();

    void on_tb_gerenciarProdutos_currentChanged(int index);

    void on_tw_geProdutos_itemSelectionChanged();

    void on_btn_geGravar_clicked();

    void on_btn_geExcluir_clicked();

    void on_btn_geBuscar_clicked();

private:
    Ui::window_gerenciarEstoque *ui;
};

#endif // WINDOW_GERENCIARESTOQUE_H
