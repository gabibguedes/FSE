# Exercicio 3 - FSE

Implementação do [exercicio 3 de FSE](https://gitlab.com/fse_fga/exercicios/exercicio-3-i2c/). O exercício é a implementação do protocolo de comunicação I2C de uma Raspberry Pi conectada a um Sensor de Pressão, Umidade e Temperatura modelo BME280 e um Display LCD de 16x2 caracteres.

O exercicio será dividido em 2 entregas, o desenvolvimento do medidor de temperaturas em Python e em C.

## Programa em Python

O programa lê as 3 grandezas fornecidas pelo sensor BME280 (Temperatura, Umidade e Pressão) e apresenta o resultado no display, atualizando os dados a cada 1 segundo.

A implementação do programa encontra-se na pasta `py/` do repositório.

### Dependências

O programa utiliza das bibliotecas smbus2 e RPi.bme280 para se comunicar com o sensor. Para instalar as bibliotecas execute o comando abaixo.

```sh
pip3 install -r py/requirements.txt
```

### Como rodar

Para executar o programa rode o comando abaixo:

```sh
python3 py/main.py
```

O programa entrará no loop de execução atualizando os dados do display a cada segundo até que seja interrompido.

<!-- ## Programa em C
### Como rodar

O programa utiliza de Makefile com cross-compiling, é necessário inicialmente ajustar o caminho do compilador utilizado na variável `CC` do Makefile. Com o compilador correto, para compilar o programa basta utilizar o comando abaixo:

```sh
make
```

A compilação gera o arquivo binário executável em `bin/bin`. Esse arquivo deve ser transferido para a Raspberry Pi para ser executado na placa. -->