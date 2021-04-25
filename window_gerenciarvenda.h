#ifndef WINDOW_GERENCIARVENDA_H
#define WINDOW_GERENCIARVENDA_H
#include "connect.h"
#include <QDialog>

namespace Ui {
class window_gerenciarVenda;
}

class window_gerenciarVenda : public QDialog
{
    Q_OBJECT

public:
    explicit window_gerenciarVenda(QWidget *parent = nullptr);
    ~window_gerenciarVenda();
    Conexao con;

private slots:
    void on_twVendas_itemSelectionChanged();

    void on_btnBuscarVendas_clicked();

private:
    Ui::window_gerenciarVenda *ui;
};

#endif // WINDOW_GERENCIARVENDA_H
