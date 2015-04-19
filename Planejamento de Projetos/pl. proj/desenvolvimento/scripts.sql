create database personalize;

CREATE TABLE categoria_produto (
	codigo integer NOT NULL PRIMARY KEY AUTOINCREMENT,
	descricao varchar(30) NOT NULL
)

CREATE TABLE produto (
	codigo integer NOT NULL PRIMARY KEY AUTOINCREMENT,
	descricao varchar(30) NOT NULL,
	codigo_categoria integer NOT NULL,
	fotos varchar(25)[],
)

CREATE TABLE personalizacao_produto (

	codigo_produto integer NOT NULL PRIMARY KEY,

)

create table endereco(
	cpf_cnpj not null constraint pk_endereco primary key, foreign key  
	logradouro varchar(15) not null,
	bairro varchar(15) not null,
	numero varchar(5) not null,
	cidade varchar(30) not null,
	cep varchar(10) not null
);
