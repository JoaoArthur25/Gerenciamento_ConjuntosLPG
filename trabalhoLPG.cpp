#include <stdio.h>

#define LIN 8
#define COL 10

// pontos feitos: 1, 2, 3, 6, 7, 8
// pontos a fazer: 4, 5, main so precisa das funcoes 4 e 5

int criarConjunto(int *contador) {
    if (*contador >= LIN) {
        printf("Nao ha mais espaco para novos conjuntos.\n");
        return 0;
    }
    (*contador)++;
    printf("\n->Conjunto criado. Indice: %d\n", *contador - 1);
    return 1; 
}

void inserirValoresConjunto(int matriz[LIN][COL], int indiceConjunto, int contador) {
    if (contador == 0) {
        printf("Nao ha conjuntos para inserir valores.\n");
        return;
    }
    if (indiceConjunto < 0 || indiceConjunto >= contador) {
        printf("\n->Conjunto %d não foi criado!\n", indiceConjunto);
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

void mostrarConjunto(const int matriz[LIN][COL], int indiceConjunto) {
    printf("\nConteudo do cojunto (%d):\n", indiceConjunto);
    for (int i = 0; i < COL; i++) {
        printf("%d ", matriz[indiceConjunto][i]);
    }
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

void buscarValores(int matriz[LIN][COL], int contador) {
    int valor, encontrado = 0;

    if (contador == 0){
        printf("É necessário criar um conjunto antes de utilizar essa função");
        return;
    }

    printf("Digite qual valor deseja buscar: ");
    scanf("%d", &valor);

    printf("\nConjuntos que contem o valor %d:\n", valor);

    for (int i = 0; i < contador; i++){
        for (int j = 0; j < COL; j++){
            if (matriz[i][j] == valor){
                printf("-> Conjunto %d\n", i);
                encontrado = 1;
                break;
            }
        }
    }

    if (encontrado == 0){
        printf("O valor que deseja buscar não existe em nenhum conjunto\n");
    }
}


int main(void) {
    int matriz[LIN][COL] = {0};
    int contadorLinha = 0, opcao = 0, indiceConjunto = 0;

    do {
        printf("\n--Gerenciamento de conjuntos--\n");
        printf("\n--Menu--\n");
        printf("1- Criar um novo conjunto vazio\n");
        printf("2- Inserir dados em um conjunto\n");
        printf("3- Remover um conjunto\n");
        printf("4- Fazer a união entre dois conjuntos\n");
        printf("5- Fazer a intersecção entre dois conjuntos\n");
        printf("6- Mostrar um conjunto\n");
        printf("7- Mostrar todos os conjuntos\n");
        printf("8- Fazer busca por um valor\n");
        printf("9- Sair do programa\n");
        printf("\nDigite a opção que deseja selecionar: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                criarConjunto(&contadorLinha);
                break;
            case 2:
                printf("Digite o índice do conjunto o qual deseja inserir valores (0 a %d): ", contadorLinha - 1);
                scanf("%d", &indiceConjunto);
                inserirValoresConjunto(matriz, indiceConjunto, contadorLinha);
                break;
            case 3:
                printf("Digite o índice do conjunto o qual deseja inserir excluir valores (0 a %d): ", contadorLinha - 1);
                scanf("%d", &indiceConjunto);
                excluirConjunto(&contadorLinha, matriz, indiceConjunto);
                break;
            case 4: 
                //fun;
                break;
            case 5: 
                //fun;
                break;
            case 6: 
                printf("Digite o índice do conjunto o qual deseja mostrar: ");
                scanf("%d", &indiceConjunto);
                mostrarConjunto(matriz, indiceConjunto);
                break;    
            case 7:
                mostrarTodosConjuntos(matriz, contadorLinha);
                break;
            case 8:
                buscarValores(matriz, contadorLinha);
                break;
            case 9:
                printf("Programa fechado com sucesso\n");
                break;
            default:
                printf("Digite novamente uma das opções\n");
                break;
            }
        } while (opcao != 9);

    return 0;
}

