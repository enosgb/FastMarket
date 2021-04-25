#include "window_pagamento.h"
#include "ui_window_pagamento.h"

window_pagamento::window_pagamento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_pagamento)
{
    ui->setupUi(this);
}

window_pagamento::~window_pagamento()
{
    delete ui;
}
