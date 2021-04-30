#ifndef WINDOW_PAGAMENTO_H
#define WINDOW_PAGAMENTO_H

#include <QDialog>

#include<connect.h>
#include <QTableWidget>
#include "variaveis_globais.h"

namespace Ui {
class window_pagamento;
}

class window_pagamento : public QDialog
{
    Q_OBJECT

public:
    explicit window_pagamento(QWidget *parent = nullptr);
    ~window_pagamento();

    Conexao con;
    int linhas;
    void resetCampo();
    double calcularTotal(QTableWidget *tw, int coluna);
    static QString global_idProduto,global_descricaoProduto,global_quantidade,global_valorUnitario,global_valorTotal;
    static bool editar;
    void removerLinhas(QTableWidget *tw);

private slots:
    void on_btn_cancelar_clicked();

    void on_btn_confirmar_clicked();

private:
    Ui::window_pagamento *ui;
};

#endif // WINDOW_PAGAMENTO_H
