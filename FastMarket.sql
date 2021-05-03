create database FastMarket;

use FastMarket;

drop table tb_produto;

create table tb_produto
(
	id_produto int not null auto_increment,
    produto varchar(30) not null,
    id_fornecedor double not null,
    qtd_estoque int not null,
    valor_compra real not null,
    valor_venda real not null,
    primary key(id_produto)
);

create table tb_produtosVendidos
(
	id_movimentacao int not null auto_increment,
    id_venda int not null,
    produto varchar(30),
    quantidade int not null,
    valor_unitario real not null,
    valor_total real not null,
    primary key(id_movimentacao)
);

create table tb_usuarios
(
	id_usuario int not null auto_increment,
    username varchar(30) not null,
    nome_user varchar(30) not null,
    senha_user varchar(30) not null,
	fone_user varchar(14) not null,
    acesso_user int(1) not null,
    primary key (id_usuario)
);

create table tb_vendas
(
	id_venda int not null auto_increment,
    data_venda varchar(10) not null,
    hora_venda varchar(10) not null,
    id_usuario int not null,
    valor_total real not null,
    tipoPagamento varchar(14),
    primary  key(id_venda)
);
