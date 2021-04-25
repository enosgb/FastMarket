#ifndef WINDOW_GERENCIAR_H
#define WINDOW_GERENCIAR_H

#include <QDialog>

namespace Ui {
class window_gerenciar;
}

class window_gerenciar : public QDialog
{
    Q_OBJECT

public:
    explicit window_gerenciar(QWidget *parent = nullptr);
    ~window_gerenciar();

private:
    Ui::window_gerenciar *ui;
};

#endif // WINDOW_GERENCIAR_H
