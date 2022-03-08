# Trabalho 1 - FSE

**Aluna:** Gabriela Barrozo Guedes

**Matricula:** 16/0121612

Implementação do [trabalho 1 de FSE](https://gitlab.com/fse_fga/trabalhos-2021_2/trabalho-1-2021-2). O trabalho consiste na implementação de um sistema embarcado de um forno, que deve fazer o controle de um resistor e uma ventoinha de acordo com os dados recebidos dos sensores de temperatura.


## Como rodar

O programa utiliza de Makefile, e foi desenvolvido para ser compilado e executado em uma Raspiberry Pi. Para compilar o programa basta utilizar o comando abaixo:

```sh
make
```

A compilação gera o arquivo binário executável em `bin/bin`. Esse arquivo pode ser executado com o comando abaixo.

```sh
make run
```

## Instruções

O programa iniciará com um menu, onde será possível fazer os ajustes das grandezas Kp, Ki, Kd, o modo inicial de execução (Terminal, Curva de Reflow ou Potenciometro) e caso esteja no modo de terminal será possível ajustar a temperatura inicial.

Ao começar a executar a interação com o usuário passa a ser pelo dashboard.

