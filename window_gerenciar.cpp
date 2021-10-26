#include "window_gerenciar.h"
#include "ui_window_gerenciar.h"

window_gerenciar::window_gerenciar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_gerenciar)
{
    ui->setupUi(this);
}

window_gerenciar::~window_gerenciar()
{
    delete ui;
}
