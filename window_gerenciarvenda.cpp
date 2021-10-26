#include "window_gerenciarvenda.h"
#include "ui_window_gerenciarvenda.h"
#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QDir>
#include <QDesktopServices>

window_gerenciarVenda::window_gerenciarVenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window_gerenciarVenda)
{
    ui->setupUi(this);

    QDate data_ini = QDate::currentDate();
    ui->deInicial->setDate(data_ini);
    ui->deFinal->setDate(data_ini);

    ui->twProdutosVendas->horizontalHeader()->setVisible(true);
    ui->twProdutosVendas->setColumnCount(5);
    QStringList cabecalho1={"Movimentação","Produto","Quantidade","Vlr.Und","Total"};
    ui->twProdutosVendas->setHorizontalHeaderLabels(cabecalho1);
    ui->twProdutosVendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->twProdutosVendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twProdutosVendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twProdutosVendas->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->twVendas->horizontalHeader()->setVisible(true);
    ui->twVendas->setColumnCount(6);
    QStringList cabecalho2={"Id","Data","Hora","Usuário","Total","T.Pag"};
    ui->twVendas->setHorizontalHeaderLabels(cabecalho2);
    ui->twVendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->twVendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twVendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twVendas->setEditTriggers(QAbstractItemView::NoEditTriggers);

    con.abrir();
    int linhas=0;
    QSqlQuery query;
    query.prepare("select * from tb_vendas");
    query.exec();
    query.first();
    do{
        ui->twVendas->insertRow(linhas);
        ui->twVendas->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
        ui->twVendas->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
        ui->twVendas->setItem(linhas,2,new QTableWidgetItem(query.value(2).toString()));
        ui->twVendas->setItem(linhas,3,new QTableWidgetItem(query.value(3).toString()));
        ui->twVendas->setItem(linhas,4,new QTableWidgetItem(query.value(4).toString()));
        ui->twVendas->setItem(linhas,5,new QTableWidgetItem(query.value(5).toString()));
        linhas++;
    }while(query.next());
    con.fechar();
}

window_gerenciarVenda::~window_gerenciarVenda()
{
    delete ui;
}

void window_gerenciarVenda::on_twVendas_itemSelectionChanged()
{
    ui->twProdutosVendas->setRowCount(0);
    ui->twProdutosVendas->clear();


    con.abrir();
    int linhas=0;
    QSqlQuery query;
    query.prepare("select id_movimentacao,produto,quantidade,valor_unitario,valor_total from tb_produtosVendidos where id_venda="+ui->twVendas->item(ui->twVendas->currentRow(),0)->text());
    query.exec();
    query.first();
    do{
        ui->twProdutosVendas->insertRow(linhas);
        ui->twProdutosVendas->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
        ui->twProdutosVendas->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
        ui->twProdutosVendas->setItem(linhas,2,new QTableWidgetItem(query.value(2).toString()));
        ui->twProdutosVendas->setItem(linhas,3,new QTableWidgetItem(query.value(3).toString()));
        ui->twProdutosVendas->setItem(linhas,4,new QTableWidgetItem(query.value(4).toString()));
        linhas++;
    }while(query.next());
    con.fechar();
}

void window_gerenciarVenda::on_btnBuscarVendas_clicked()
{
    ui->twVendas->setRowCount(0);
    con.abrir();
    int linhas=0;
    QSqlQuery query;
    query.prepare("select * from tb_vendas where data_venda between '"+ui->deInicial ->text()+"' and  '"+ui->deFinal->text()+"'");
    query.exec();
    query.first();
    do{
        ui->twVendas->insertRow(linhas);
        ui->twVendas->setItem(linhas,0,new QTableWidgetItem(query.value(0).toString()));
        ui->twVendas->setItem(linhas,1,new QTableWidgetItem(query.value(1).toString()));
        ui->twVendas->setItem(linhas,2,new QTableWidgetItem(query.value(2).toString()));
        ui->twVendas->setItem(linhas,3,new QTableWidgetItem(query.value(3).toString()));
        ui->twVendas->setItem(linhas,4,new QTableWidgetItem(query.value(4).toString()));
        ui->twVendas->setItem(linhas,5,new QTableWidgetItem(query.value(5).toString()));
        linhas++;
    }while(query.next());
    con.fechar();
}

void window_gerenciarVenda::on_btn_todasVendas_clicked()
{

}

void window_gerenciarVenda::on_btn_gerarPdf_clicked()
{
    QString nome=QDir::currentPath()+"/"+ui->twVendas->item(ui->twVendas->currentRow(),0)->text()+"_vendas.pdf";

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(nome);

    QPainter painter;
    if(!painter.begin(&printer)){
        qDebug() << "Erro ao abrir PDF";
        return;
    }
    int linha = 250;
    int salto = 20;

    painter.drawPixmap(25,25,QPixmap(":/imagens/fastmarket-logo.jpg"));

    painter.drawText(25,200,"ID:"+ui->twVendas->item(ui->twVendas->currentRow(),0)->text());
    painter.drawText(150,200,"Data:"+ui->twVendas->item(ui->twVendas->currentRow(),1)->text());
    painter.drawText(25,350,"Valor Total ");

    painter.drawText(25,225,+"Qtd");
    painter.drawText(70,225,+"Produto");
    painter.drawText(200,225,+"Vlr.Unitário");

    for(int i = 0;i<ui->twProdutosVendas->rowCount();i++){
        painter.drawText(25,linha,ui->twProdutosVendas->item(i,2)->text());
        painter.drawText(70,linha,ui->twProdutosVendas->item(i,1)->text());
        painter.drawText(200,linha,+"R$ "+ui->twProdutosVendas->item(i,3)->text());
        linha+=salto;
    }

    painter.drawText(200,350," R$ "+ui->twVendas->item(ui->twVendas->currentRow(),4)->text());

    printer.newPage();

    painter.drawText(25,25,"Relatório fastmarket Ok");

    painter.end();

    QDesktopServices::openUrl(QUrl("file:///"+nome));

}
