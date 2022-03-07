# Trabalho 1 - FSE

Implementação do [trabalho 1 de FSE](https://gitlab.com/fse_fga/trabalhos-2021_2/trabalho-1-2021-2).


### Como rodar

O programa utiliza de Makefile, é necessário inicialmente ajustar o caminho do compilador utilizado na variável `CC` do Makefile ou importar o projeto para ser compilado na Raspiberry. Com o compilador correto, para compilar o programa basta utilizar o comando abaixo:

```sh
make
```

A compilação gera o arquivo binário executável em `bin/bin`. Esse arquivo deve ser transferido para a Raspberry Pi para ser executado na placa.

Se o programa já estiver sendo compilado na placa, para executa-lo basta utilizar o comando abaixo:

```sh
make run
```