#ifndef CONNECT_H
#define CONNECT_H
#include <QtSql>

class Conexao{
public:
    QSqlDatabase bandoDeDados=QSqlDatabase::addDatabase("QSQLITE");
    QString local;
    QString banco;
    Conexao(){
       local=qApp->applicationDirPath();
       banco=local+"/db/FastMarket.db";
       bandoDeDados=QSqlDatabase::addDatabase("QSQLITE");

    }
    void fechar(){
        bandoDeDados.close();
    }
    bool abrir(){
        bandoDeDados.setDatabaseName(banco);

        if(!bandoDeDados.open()){
            return false;
        }else{
            return true;
        }
    }
    bool aberto(){
        if(bandoDeDados.isOpen()){
            return true;
        }else{
            return false;
        }

    }
};

#endif // CONNECT_H
