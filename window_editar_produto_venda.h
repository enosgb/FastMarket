#ifndef WINDOW_EDITAR_PRODUTO_VENDA_H
#define WINDOW_EDITAR_PRODUTO_VENDA_H

#include <QDialog>

namespace Ui {
class window_editar_produto_venda;
}

class window_editar_produto_venda : public QDialog
{
    Q_OBJECT

public:
    explicit window_editar_produto_venda(QWidget *parent = nullptr);
    ~window_editar_produto_venda();

private slots:
    void on_btn_veEditarOk_clicked();

    void on_btn_veEditarCancelar_clicked();

private:
    Ui::window_editar_produto_venda *ui;
};

#endif // WINDOW_EDITAR_PRODUTO_VENDA_H
