#include <stdio.h>

#define LIN 8
#define COL 10

// ---------- helpers internos (estáticos) ----------
static int tamanhoConjunto(const int linha[COL]) {
    int n = 0;
    while (n < COL && linha[n] != 0) n++;
    return n;
}

static int contem(const int linha[COL], int valor) {
    if (valor == 0) return 0; 
    for (int i = 0; i < COL && linha[i] != 0; i++) {
        if (linha[i] == valor) return 1;
    }
    return 0;
}

static void limparLinha(int linha[COL]) {
    for (int j = 0; j < COL; j++) linha[j] = 0;
}

static void copiarLinha(const int src[COL], int dst[COL]) {
    for (int j = 0; j < COL; j++) dst[j] = src[j];
}

// ---------- 1. criar ----------
int criarConjunto(int *contador) {
    if (*contador >= LIN) {
        printf("Nao ha mais espaco para novos conjuntos.\n");
        return 0;
    }
    (*contador)++;
    printf("\n-> Conjunto criado. Indice: %d\n", *contador - 1);
    return 1;
}

// ---------- 2. inserir ----------
void inserirValoresConjunto(int matriz[LIN][COL], int indiceConjunto, int contador) {
    if (contador == 0) {
        printf("Nao ha conjuntos para inserir valores.\n");
        return;
    }
    if (indiceConjunto < 0 || indiceConjunto >= contador) {
        printf("\n-> Conjunto %d nao foi criado!\n", indiceConjunto);
        return;
    }

    printf("Insira valores para o conjunto %d (0 encerra):\n", indiceConjunto);

    int inicio = 0;
    while (inicio < COL && matriz[indiceConjunto][inicio] != 0) inicio++;

    for (int i = inicio; i < COL; i++) {
        printf("Valor [%d]: ", i);
        int v;
        if (scanf("%d", &v) != 1) {
            printf("Entrada invalida. Encerrando insercao.\n");
            break;
        }
        matriz[indiceConjunto][i] = v;
        if (v == 0) {
            printf("Entrada encerrada pelo usuario.\n");
            break;
        }
    }
}

// ---------- 3. excluir ----------
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
    
    for (int j = 0; j < COL; j++) matriz[*contador - 1][j] = 0;

    (*contador)--;
    printf("Conjunto %d removido. Agora ha %d conjunto(s).\n", indiceConjunto, *contador);
}

// ---------- 4. uniao ----------
int uniaoConjuntos(int matriz[LIN][COL], int contador, int a, int b) {
    if (contador >= LIN) {
        printf("Nao ha espaço para armazenar o resultado da uniao.\n");
        return -1;
    }
    if (a < 0 || a >= contador || b < 0 || b >= contador) {
        printf("Indices invalidos para uniao.\n");
        return -1;
    }
    int destino = contador; 
    limparLinha(matriz[destino]);

    int k = 0;

    // adiciona elementos unicos do conjunto A
    for (int i = 0; i < COL && matriz[a][i] != 0; i++) {
        int v = matriz[a][i];
        if (v != 0 && !contem(matriz[destino], v)) {
            if (k >= COL - 1) { 
                printf("Aviso: capacidade do conjunto estourada; alguns elementos foram ignorados.\n");
                break;
            }
            matriz[destino][k++] = v;
        }
    }
    // adiciona elementos unicos do conjunto B
    for (int i = 0; i < COL && matriz[b][i] != 0; i++) {
        int v = matriz[b][i];
        if (v != 0 && !contem(matriz[destino], v)) {
            if (k >= COL - 1) {
                printf("Aviso: capacidade do conjunto estourada; alguns elementos foram ignorados.\n");
                break;
            }
            matriz[destino][k++] = v;
        }
    }
    // termina com 0
    if (k < COL) matriz[destino][k] = 0;

    printf("Uniao feita: resultado em indice %d.\n", destino);
    return destino;
}

// ---------- 5. interseccao ----------
int intersecConjuntos(int matriz[LIN][COL], int contador, int a, int b) {
    if (contador >= LIN) {
        printf("Nao ha espaço para armazenar o resultado da interseccao.\n");
        return -1;
    }
    if (a < 0 || a >= contador || b < 0 || b >= contador) {
        printf("Indices invalidos para interseccao.\n");
        return -1;
    }
    int destino = contador; 
    limparLinha(matriz[destino]);

    int k = 0;
    for (int i = 0; i < COL && matriz[a][i] != 0; i++) {
        int v = matriz[a][i];
        if (v != 0 && contem(matriz[b], v) && !contem(matriz[destino], v)) {
            if (k >= COL - 1) {
                printf("Aviso: capacidade do conjunto estourada; alguns elementos foram ignorados.\n");
                break;
            }
            matriz[destino][k++] = v;
        }
    }
    if (k < COL) matriz[destino][k] = 0;

    printf("Interseccao feita: resultado em indice %d.\n", destino);
    return destino;
}

// ---------- 6. mostrar ----------
void mostrarConjunto(const int matriz[LIN][COL], int indiceConjunto, int contador) {
    if (indiceConjunto < 0 || indiceConjunto >= contador) {
        printf("Indice de conjunto invalido.\n");
        return;
    }
    printf("\nConteudo do conjunto (%d): ", indiceConjunto);
    for (int i = 0; i < COL; i++) {
        printf("%d ", matriz[indiceConjunto][i]);
    }
    printf("\n");
}

// ---------- 7. mostrar todos ----------
void mostrarTodosConjuntos(const int matriz[LIN][COL], int contador) {
    printf("\nConteudo da matriz (%d conjunto(s) usados):\n", contador);
    for (int i = 0; i < contador; i++) {
        printf("Conjunto %d: ", i); 
        for (int j = 0; j < COL; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// ---------- 8. buscar ----------
void buscarValores(int matriz[LIN][COL], int contador) {
    if (contador == 0){
        printf("E necessario criar um conjunto antes de utilizar essa funcao.\n");
        return;
    }

    int valor, encontrado = 0;
    printf("Digite qual valor deseja buscar: ");
    if (scanf("%d", &valor) != 1) {
        printf("Entrada invalida.\n");
        return;
    }

    printf("\nConjuntos que contem o valor %d:\n", valor);
    for (int i = 0; i < contador; i++){
        for (int j = 0; j < COL && matriz[i][j] != 0; j++){
            if (matriz[i][j] == valor){
                printf("-> Conjunto %d\n", i);
                encontrado = 1;
                break;
            }
        }
    }
    if (!encontrado){
        printf("O valor buscado nao existe em nenhum conjunto.\n");
    }
}

// ---------- main ----------
int main(void) {
    int matriz[LIN][COL] = {0};
    int contadorLinha = 0, opcao = 0, indiceConjunto = 0;

    do {
        printf("\n-- Gerenciamento de conjuntos --\n");
        printf("\n-- Menu --\n");
        printf("1- Criar um novo conjunto vazio\n");
        printf("2- Inserir dados em um conjunto\n");
        printf("3- Remover um conjunto\n");
        printf("4- Fazer a uniao entre dois conjuntos (resultado em nova linha)\n");
        printf("5- Fazer a interseccao entre dois conjuntos (resultado em nova linha)\n");
        printf("6- Mostrar um conjunto\n");
        printf("7- Mostrar todos os conjuntos\n");
        printf("8- Fazer busca por um valor\n");
        printf("9- Sair do programa\n");
        printf("\nDigite a opcao que deseja selecionar: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Encerrando.\n");
            break;
        }

        switch (opcao){
            case 1: {
                criarConjunto(&contadorLinha);
            } break;

            case 2: {
                if (contadorLinha == 0) {
                    printf("Crie um conjunto antes (opcao 1).\n");
                    break;
                }
                printf("Digite o indice do conjunto para inserir valores (0 a %d): ", contadorLinha - 1);
                if (scanf("%d", &indiceConjunto) != 1) { printf("Entrada invalida.\n"); break; }
                inserirValoresConjunto(matriz, indiceConjunto, contadorLinha);
            } break;

            case 3: {
                if (contadorLinha == 0) {
                    printf("Nao ha conjuntos para remover.\n");
                    break;
                }
                printf("Digite o indice do conjunto a excluir (0 a %d): ", contadorLinha - 1);
                int idx;
                if (scanf("%d", &idx) != 1) { printf("Entrada invalida.\n"); break; }
                excluirConjunto(&contadorLinha, matriz, idx);
            } break;

            case 4: {
                if (contadorLinha < 2) {
                    printf("Crie ao menos dois conjuntos para fazer a uniao.\n");
                    break;
                }
                if (contadorLinha >= LIN) {
                    printf("Sem espaco para salvar o resultado da uniao. Exclua algum conjunto primeiro.\n");
                    break;
                }
                int a, b;
                printf("Digite os indices dos dois conjuntos para uniao (0 a %d): ", contadorLinha - 1);
                if (scanf("%d %d", &a, &b) != 2) { printf("Entrada invalida.\n"); break; }
                int idxRes = uniaoConjuntos(matriz, contadorLinha, a, b);
                if (idxRes >= 0) {
                    contadorLinha++; 
                    mostrarConjunto(matriz, idxRes, contadorLinha);
                }
            } break;

            case 5: { // interseccao
                if (contadorLinha < 2) {
                    printf("Crie ao menos dois conjuntos para fazer a interseccao.\n");
                    break;
                }
                if (contadorLinha >= LIN) {
                    printf("Sem espaco para salvar o resultado da interseccao. Exclua algum conjunto primeiro.\n");
                    break;
                }
                int a, b;
                printf("Digite os indices dos dois conjuntos para interseccao (0 a %d): ", contadorLinha - 1);
                if (scanf("%d %d", &a, &b) != 2) { printf("Entrada invalida.\n"); break; }
                int idxRes = intersecConjuntos(matriz, contadorLinha, a, b);
                if (idxRes >= 0) {
                    contadorLinha++; 
                    mostrarConjunto(matriz, idxRes, contadorLinha);
                }
            } break;

            case 6: {
                if (contadorLinha == 0) {
                    printf("Nao ha conjuntos para mostrar.\n");
                    break;
                }
                printf("Digite o indice do conjunto que deseja mostrar (0 a %d): ", contadorLinha - 1);
                if (scanf("%d", &indiceConjunto) != 1) { printf("Entrada invalida.\n"); break; }
                mostrarConjunto(matriz, indiceConjunto, contadorLinha);
            } break;

            case 7:
                mostrarTodosConjuntos(matriz, contadorLinha);
                break;

            case 8:
                buscarValores(matriz, contadorLinha);
                break;

            case 9:
                printf("Programa fechado com sucesso.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 9);

    return 0;
}
