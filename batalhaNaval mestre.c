#include <stdio.h>

// Constantes para o Tabuleiro e Navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5 // Valor para áreas afetadas por habilidades

// Constantes para as Matrizes de Habilidade
#define TAMANHO_HABILIDADE_MATRIZ 7 // Matrizes de habilidade 7x7

// Protótipos das Funções
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// Função para tentar posicionar um navio e retornar se foi possível
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                    int linha_inicio, int coluna_inicio, int direcao);

// Função para construir a matriz de habilidade Cone
void construirHabilidadeCone(int matrizHabilidade[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ]);

// Função para construir a matriz de habilidade Cruz
void construirHabilidadeCruz(int matrizHabilidade[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ]);

// Função para construir a matriz de habilidade Octaedro
void construirHabilidadeOctaedro(int matrizHabilidade[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ]);

// Função para aplicar a habilidade no tabuleiro principal
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int matrizHabilidade[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ],
                       int linha_origem, int coluna_origem);


int main() {
    printf("--- Batalha Naval - Mestre ---\n\n");

    // Definir o Tabuleiro: 10x10 inicializado com 0s (água).
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Posicionar Quatro Navios 
    // Navio 1: Horizontal (2,1)
    if (!posicionarNavio(tabuleiro, 2, 1, 0)) {
        printf("Erro ao posicionar Navio 1. Encerrando.\n"); return 1;
    }
    // Navio 2: Vertical (0,5)
    if (!posicionarNavio(tabuleiro, 0, 5, 1)) {
        printf("Erro ao posicionar Navio 2. Encerrando.\n"); return 1;
    }
    // Navio 3: Diagonal Principal (3,3)
    if (!posicionarNavio(tabuleiro, 3, 3, 2)) {
        printf("Erro ao posicionar Navio 3. Encerrando.\n"); return 1;
    }
    // Navio 4: Diagonal Secundária (1,8)
    if (!posicionarNavio(tabuleiro, 1, 8, 3)) {
        printf("Erro ao posicionar Navio 4. Encerrando.\n"); return 1;
    }

    // Criar Matrizes de Habilidade
    int habilidadeCone[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ];
    int habilidadeCruz[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ];
    int habilidadeOctaedro[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ];

    // Construir as formas das habilidades
    construirHabilidadeCone(habilidadeCone);
    construirHabilidadeCruz(habilidadeCruz);
    construirHabilidadeOctaedro(habilidadeOctaedro);

    // Integrar Habilidades ao Tabuleiro: Definir pontos de origem e aplicar.
    printf("\n--- Aplicando Habilidade: CONE (origem no topo do cone, centralizada) ---\n");
    aplicarHabilidade(tabuleiro, habilidadeCone, 2, 4);

    printf("\n--- Aplicando Habilidade: CRUZ (origem no centro) ---\n");
    aplicarHabilidade(tabuleiro, habilidadeCruz, 6, 2);

    printf("\n--- Aplicando Habilidade: OCTAEDRO (origem no centro) ---\n");
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 8, 7);

    // Exibir o Tabuleiro com Habilidades
    printf("\nTabuleiro Final com Navios e Habilidades:\n");
    // Chamada da função de exibição.
    exibirTabuleiro(tabuleiro);

    printf("\n--- Nivel Mestre da Batalha Naval Concluido! Parabens! ---\n");

    return 0;
}

// Exibe o tabuleiro de Batalha Naval no console, com os valores numéricos.
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
            // Exibe o valor numérico diretamente.
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

int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                    int linha_inicio, int coluna_inicio, int direcao) {
    int r, c;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        r = linha_inicio;
        c = coluna_inicio;

        if (direcao == 0) { // Horizontal
            c = coluna_inicio + i;
        } else if (direcao == 1) { // Vertical
            r = linha_inicio + i;
        } else if (direcao == 2) { // Diagonal Principal (linha++, coluna++)
            r = linha_inicio + i;
            c = coluna_inicio + i;
        } else if (direcao == 3) { // Diagonal Secundária (linha++, coluna--)
            r = linha_inicio + i;
            c = coluna_inicio - i;
        }

        if (r < 0 || r >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO) {
            printf("Erro: Navio fora dos limites do tabuleiro em (%d,%d).\n", linha_inicio, coluna_inicio);
            return 0;
        }

        if (tabuleiro[r][c] == NAVIO) {
            printf("Erro: Sobreposicao de navios em (%d,%d).\n", r, c);
            return 0;
        }
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        r = linha_inicio;
        c = coluna_inicio;

        if (direcao == 0) { // Horizontal
            c = coluna_inicio + i;
        } else if (direcao == 1) { // Vertical
            r = linha_inicio + i;
        } else if (direcao == 2) { // Diagonal Principal (linha++, coluna++)
            r = linha_inicio + i;
            c = coluna_inicio + i;
        } else if (direcao == 3) { // Diagonal Secundária (linha++, coluna--)
            r = linha_inicio + i;
            c = coluna_inicio - i;
        }
        tabuleiro[r][c] = NAVIO;
    }

    return 1;
}

// Constrói a matriz de habilidade em forma de Cone (apontando para baixo).
void construirHabilidadeCone(int matrizHabilidade[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ]) {
    int centro = TAMANHO_HABILIDADE_MATRIZ / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            matrizHabilidade[i][j] = 0;

            if (j >= centro - i && j <= centro + i) {
                matrizHabilidade[i][j] = 1;
            }
        }
    }
}

// Constrói a matriz de habilidade em forma de Cruz.
void construirHabilidadeCruz(int matrizHabilidade[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ]) {
    int centro = TAMANHO_HABILIDADE_MATRIZ / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            matrizHabilidade[i][j] = 0;

            if (i == centro || j == centro) {
                matrizHabilidade[i][j] = 1;
            }
        }
    }
}

// Constrói a matriz de habilidade em forma de Octaedro (losango).
void construirHabilidadeOctaedro(int matrizHabilidade[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ]) {
    int centro = TAMANHO_HABILIDADE_MATRIZ / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {
            matrizHabilidade[i][j] = 0;

            // abs(i - centro) + abs(j - centro) <= centro
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matrizHabilidade[i][j] = 1;
            }
        }
    }
}

// Aplica a matriz de habilidade ao tabuleiro principal, centrando-a na origem.
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int matrizHabilidade[TAMANHO_HABILIDADE_MATRIZ][TAMANHO_HABILIDADE_MATRIZ],
                       int linha_origem, int coluna_origem) {

    int offset_linha = TAMANHO_HABILIDADE_MATRIZ / 2;
    int offset_coluna = TAMANHO_HABILIDADE_MATRIZ / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE_MATRIZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_MATRIZ; j++) {

            if (matrizHabilidade[i][j] == 1) {
                int tabuleiro_linha = linha_origem + (i - offset_linha);
                int tabuleiro_coluna = coluna_origem + (j - offset_coluna);

                if (tabuleiro_linha >= 0 && tabuleiro_linha < TAMANHO_TABULEIRO &&
                    tabuleiro_coluna >= 0 && tabuleiro_coluna < TAMANHO_TABULEIRO) {

                    if (tabuleiro[tabuleiro_linha][tabuleiro_coluna] != NAVIO) {
                        tabuleiro[tabuleiro_linha][tabuleiro_coluna] = HABILIDADE;
                    }
                }
            }
        }
    }
}