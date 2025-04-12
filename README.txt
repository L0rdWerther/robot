# Projeto 4 - Simulação de um Robô Móvel Recursivo

## Configuração do projeto

Para executar o programa é necessário indicar na main qual o arquivo de texto que será lido.
Para isso, basta alterar a linha 129 do arquivo main.c para o caminho do arquivo desejado.

Exemplo:

FILE *arquivo = fopen("mapa1.txt", "r");

ou

FILE *arquivo = fopen("mapa2.txt", "r");

## Instruções de Compilação

Para compilar o código, execute o seguinte comando no terminal:

```bash
gcc main.c -o robo_navegador
```

## Instruções de Execução

Depois de compilado, execute o programa com o seguinte comando:

```bash
./robo_navegador
```

## Resumo do Código

Este projeto implementa um robô (@) que navega em um mapa em busca de um destino marcado com 'D'.
O mapa é lido a partir de um arquivo de texto (mapa1.txt e mapa2.txt) e o robô começa na posição marcada com '@'.
O robô se move pelo mapa, marcando as posições visitadas em uma matriz secundária e procurando o destino.

## Estratégia de Movimentação

A estratégia de movimentação do robô é baseada no método de busca em largura (BFS).
O robô verifica as quatro direções possíveis (cima, baixo, esquerda, direita) e se move para a primeira direção válida.
Se todas as direções estiverem bloqueadas ou já visitadas, o robô procura a posição não explorada mais próxima e se move para lá.
O processo continua até que o robô alcance o destino ou não haja mais movimentos possíveis.