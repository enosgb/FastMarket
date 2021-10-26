#ifndef WINDOW_GERENCIARUSUARIOS_H
#define WINDOW_GERENCIARUSUARIOS_H

#include <QDialog>

#include "connect.h"

namespace Ui {
class window_gerenciarUsuarios;
}

class window_gerenciarUsuarios : public QDialog
{
    Q_OBJECT

public:
    explicit window_gerenciarUsuarios(QWidget *parent = nullptr);
    ~window_gerenciarUsuarios();

    Conexao con;

private slots:
    void on_btn_novoUsuario_clicked();

    void on_btn_gravaNovoUsuario_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_geUsuarios_itemSelectionChanged();

    void on_btn_geBuscarUsuario_clicked();

    void on_bnt_geGravarUsuario_clicked();

    void on_btn_geExcluirUsuario_clicked();

private:
    Ui::window_gerenciarUsuarios *ui;
};

#endif // WINDOW_GERENCIARUSUARIOS_H
