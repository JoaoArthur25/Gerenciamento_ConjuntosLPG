#include <stdio.h>

#define LIN 8
#define COL 10

// pontos feitos: 1, 2, 3, 6, 7
// pontos a fazer: 4, 5, 8, main chimbica

int criarConjunto(int *contador) {
    if (*contador >= LIN) {
        printf("Nao ha mais espaco para novos conjuntos.\n");
        return 0;
    }
    (*contador)++;
    return 1; 
}

void inserirValoresConjunto(int matriz[LIN][COL], int indiceConjunto, int contador) {
    if (indiceConjunto < 0 || indiceConjunto >= contador) {
        printf("Indice de conjunto invalido.\n");
        return;
    }

    printf("Insira valores para o conjunto %d:\n", indiceConjunto);
    int inicio = 0;
    while (inicio < COL && matriz[indiceConjunto][inicio] != 0) {
        inicio++;
    }

    for (int i = inicio; i < COL; i++) {
        printf("Valor [%d]: ", i);
        scanf("%d", &matriz[indiceConjunto][i]);

        if (matriz[indiceConjunto][i] == 0) {
            printf("Entrada encerrada pelo usuário.\n");
            break;
        }
    }
}

void excluirConjunto(int *contador, int matriz[LIN][COL], int indiceConjunto) {
    if (*contador == 0) {
        printf("Nao ha conjuntos para excluir.\n");
        return;
    }
    if (indiceConjunto < 0 || indiceConjunto >= *contador) {
        printf("Indice de conjunto invalido.\n");
        return;
    }

    for (int i = indiceConjunto; i < (*contador - 1); i++) {
        for (int j = 0; j < COL; j++) {
            matriz[i][j] = matriz[i + 1][j];
        }
    }

    (*contador)--;
}

void mostrarTodosConjuntos(const int matriz[LIN][COL], int contador) {
    printf("\nConteudo da matriz (%d conjuntos usados):\n", contador);
    for (int i = 0; i < contador; i++) {
        printf("Conjunto %d: ", i + 1);
        for (int j = 0; j < COL; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void mostrarConjunto(const int matriz[LIN][COL], int indiceConjunto) {
    printf("\nConteudo do cojunto (%d):\n", indiceConjunto);
    for (int i = 0; i < COL; i++) {
        printf("%d ", matriz[indiceConjunto][i]);
    }
}

int main(void) {
    int matriz[LIN][COL] = {0};
    int contadorLinha = 0;

    if (criarConjunto(&contadorLinha)) inserirValoresConjunto(matriz, 0, contadorLinha);
    if (criarConjunto(&contadorLinha)) inserirValoresConjunto(matriz, 1, contadorLinha);

    mostrarTodosConjuntos(matriz, contadorLinha);
    
    mostrarConjunto(matriz, 1);

    return 0;
}

