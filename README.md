# Exercicio 1

Implementação do [exercicio 1 de FSE](https://gitlab.com/fse_fga/exercicios/exercicio-1-uart). O exercício é a implementação da comunicação de uma Raspibery Pi com um arduino, utilizando da UART e do protocolo de comunicação estabelecido em aula para o envio e recebimento de inteiros, floats e strings.

## Como rodar

O programa utiliza de Makefile com cross-compiling, é necessário inicialmente ajustar o caminho do compilador utilizado na variável `CC` do Makefile. Com o compilador correto, para compilar o programa basta utilizar o comando abaixo:

```
make
```

A compilação gera o arquivo binário executável em `bin/bin`. Esse arquivo deve ser transferido para a Raspiberry Pi para ser executado na placa.