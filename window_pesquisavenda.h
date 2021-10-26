#ifndef WINDOW_PESQUISAVENDA_H
#define WINDOW_PESQUISAVENDA_H

#include "window_novavenda.h"
#include "funcoes_globais.h"
#include <QMessageBox>
#include "variaveis_globais.h"
#include <connect.h>

#include <QDialog>

namespace Ui {
class window_pesquisaVenda;
}

class window_pesquisaVenda : public QDialog
{
    Q_OBJECT

public:
    explicit window_pesquisaVenda(QWidget *parent = nullptr);
    ~window_pesquisaVenda();

    Conexao con;
    static QString retIdVenda;

private slots:
    void on_btn_PeBuscar_clicked();

    void on_tw_PeProdutos_itemSelectionChanged();

    void on_btn_PeSelecionarItem_clicked();


private:
    Ui::window_pesquisaVenda *ui;
};

#endif // WINDOW_PESQUISAVENDA_H
