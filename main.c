#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define TAMANHO_MAX 100

char mapa[TAMANHO_MAX][TAMANHO_MAX];
int visitado[TAMANHO_MAX][TAMANHO_MAX];
int linhas, colunas;

typedef struct {
    int x, y;
} Posicao;

typedef struct {
    Posicao posicoes[TAMANHO_MAX * TAMANHO_MAX];
    int frente, tras;
} Fila;

void inicializar_fila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
}

int esta_vazia(Fila *f) {
    return f->frente == f->tras;
}

void enfileirar(Fila *f, Posicao pos) {
    f->posicoes[f->tras++] = pos;
}

Posicao desenfileirar(Fila *f) {
    return f->posicoes[f->frente++];
}

void imprimir_mapa() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (visitado[i][j]) {
                printf(" ");
            } else {
                printf("%c", mapa[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

Posicao encontrar_mais_proximo_nao_explorado(int x, int y) {
    Fila f;
    inicializar_fila(&f);
    int temp_visitado[TAMANHO_MAX][TAMANHO_MAX] = {0};
    enfileirar(&f, (Posicao){x, y});
    temp_visitado[x][y] = 1;

    while (!esta_vazia(&f)) {
        Posicao pos = desenfileirar(&f);

        if (!visitado[pos.x][pos.y] && mapa[pos.x][pos.y] == ' ') {
            return pos;
        }

        int direcoes[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; i++) {
            int novo_x = pos.x + direcoes[i][0];
            int novo_y = pos.y + direcoes[i][1];
            if (novo_x >= 0 && novo_x < linhas && novo_y >= 0 && novo_y < colunas && !temp_visitado[novo_x][novo_y]) {
                enfileirar(&f, (Posicao){novo_x, novo_y});
                temp_visitado[novo_x][novo_y] = 1;
            }
        }
    }

    return (Posicao){x, y};
}

int mover_robo(int x, int y) {
    if (x < 0 || x >= linhas || y < 0 || y >= colunas) {
        return 0;
    }

    if (mapa[x][y] == 'D') {
        printf("Alvo alcançado\n");
        return 1;
    }

    visitado[x][y] = 1;

    if (x > 0 && (mapa[x-1][y] == ' ' || mapa[x-1][y] == 'D') && !visitado[x-1][y]) {
        printf("cima\n");
        mapa[x][y] = ' ';
        x -= 1;
    } else if (x < linhas-1 && (mapa[x+1][y] == ' ' || mapa[x+1][y] == 'D') && !visitado[x+1][y]) {
        printf("baixo\n");
        mapa[x][y] = ' ';
        x += 1;
    } else if (y > 0 && (mapa[x][y-1] == ' ' || mapa[x][y-1] == 'D') && !visitado[x][y-1]) {
        printf("esquerda\n");
        mapa[x][y] = ' ';
        y -= 1;
    } else if (y < colunas-1 && (mapa[x][y+1] == ' ' || mapa[x][y+1] == 'D') && !visitado[x][y+1]) {
        printf("direita\n");
        mapa[x][y] = ' ';
        y += 1;
    } else {
        Posicao mais_proximo = encontrar_mais_proximo_nao_explorado(x, y);
        if (mais_proximo.x == x && mais_proximo.y == y) {
            return 0;
        }
        x = mais_proximo.x;
        y = mais_proximo.y;
    }

    if (mapa[x][y] == 'D') {
        printf("Alvo alcançado\n");
        return 1;
    }

    mapa[x][y] = '@';
    imprimir_mapa();
    usleep(200000);

    return mover_robo(x, y);
}

int main() {
    FILE *arquivo = fopen("mapa1.txt", "r");

    linhas = 0;
    while (fgets(mapa[linhas], TAMANHO_MAX, arquivo)) {
        colunas = strlen(mapa[linhas]);
        if (mapa[linhas][colunas-1] == '\n') {
            mapa[linhas][colunas-1] = '\0';
            colunas--;
        }
        linhas++;
    }
    fclose(arquivo);

    int inicio_x = -1, inicio_y = -1;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (mapa[i][j] == '@') {
                inicio_x = i;
                inicio_y = j;
                break;
            }
        }
        if (inicio_x != -1) break;
    }

    memset(visitado, 0, sizeof(visitado));

    imprimir_mapa();
    mover_robo(inicio_x, inicio_y);
    return 0;
}