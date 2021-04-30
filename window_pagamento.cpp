#include "window_pagamento.h"
#include "ui_window_pagamento.h"

window_pagamento::window_pagamento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_pagamento)
{
    ui->setupUi(this);

    if(!con.abrir()){

    }

    ui->cb_tipoPagamento->addItem("Dinheiro");
    ui->cb_tipoPagamento->addItem("Cartão");
}

window_pagamento::~window_pagamento()
{
    delete ui;
}

void window_pagamento::on_btn_cancelar_clicked()
{
    variaveis_globais::statusPagamento = false;
    close();
}

void window_pagamento::on_btn_confirmar_clicked()
{
    variaveis_globais::statusPagamento = true;
    close();
}
