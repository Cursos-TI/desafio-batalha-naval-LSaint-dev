#include <stdio.h>

// Constantes para o Tabuleiro e Navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Protótipo da Função de Exibição
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    printf("--- Batalha Naval - MateCheck: Nivel Novato ---\n\n");

    // Representar o Tabuleiro: Matriz 10x10 inicializada com 0s (água).
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Posicionar os Navios
    // Navio 1: Horizontal
    int navio1_linha_inicio = 2;
    int navio1_coluna_inicio = 1;

    // Validação para o Navio 1 (horizontal):
    if (navio1_coluna_inicio + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("ERRO: Navio 1 (horizontal) excede os limites do tabuleiro! Ajuste as coordenadas.\n");
        return 1;
    }

    // Posicionamento do Navio 1 (horizontal).
    for (int j = 0; j < TAMANHO_NAVIO; j++) {
        tabuleiro[navio1_linha_inicio][navio1_coluna_inicio + j] = NAVIO;
    }

    // Navio 2: Vertical
    int navio2_linha_inicio = 0;
    int navio2_coluna_inicio = 5;

    // Validação para o Navio 2 (vertical):
    if (navio2_linha_inicio + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("ERRO: Navio 2 (vertical) excede os limites do tabuleiro! Ajuste as coordenadas.\n");
        return 1;
    }

    // Validação de Sobreposição Simplificada para Navio 2.
    int sobreposicao = 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[navio2_linha_inicio + i][navio2_coluna_inicio] == NAVIO) {
            sobreposicao = 1;
            break;
        }
    }

    if (sobreposicao) {
        printf("ERRO: Navio 2 (vertical) se sobrepoe a outro navio! Ajuste as coordenadas.\n");
        return 1;
    }

    // Posicionamento do Navio 2 (vertical).
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[navio2_linha_inicio + i][navio2_coluna_inicio] = NAVIO;
    }

    // Exibir o Tabuleiro
    printf("Tabuleiro de Batalha Naval:\n");
    exibirTabuleiro(tabuleiro);

    printf("\n--- Nivel Novato da Batalha Naval Concluido! ---\n");

    return 0;
}

// Exibe o tabuleiro de Batalha Naval no console.
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Imprime cabeçalho das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%3d", j);
    }
    printf("\n");

    // Imprime linha separadora
    printf("  +");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("+\n");

    // Loops aninhados para percorrer e exibir cada elemento da matriz.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%3d", tabuleiro[i][j]);
        }
        printf(" |\n");
    }

    // Imprime linha de rodapé
    printf("  +");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("+\n");
}