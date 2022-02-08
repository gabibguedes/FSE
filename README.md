# Exercicio 1 - FSE

Implementação do [exercicio 1 de FSE](https://gitlab.com/fse_fga/exercicios/exercicio-1-uart). O exercício é a implementação da comunicação de uma Raspberry Pi com um Arduino, utilizando da UART e do protocolo de comunicação estabelecido em aula para o envio e recebimento de inteiros, floats e strings.

## Como rodar

O programa utiliza de Makefile com cross-compiling, é necessário inicialmente ajustar o caminho do compilador utilizado na variável `CC` do Makefile. Com o compilador correto, para compilar o programa basta utilizar o comando abaixo:

```sh
make
```

A compilação gera o arquivo binário executável em `bin/bin`. Esse arquivo deve ser transferido para a Raspberry Pi para ser executado na placa.