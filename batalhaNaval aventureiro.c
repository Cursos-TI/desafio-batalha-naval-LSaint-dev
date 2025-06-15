#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída.

// Constantes para o Tabuleiro e Navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// --- Protótipos das Funções ---
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// Função para tentar posicionar um navio e retornar se foi possível
// Retorna 1 se o navio foi posicionado com sucesso, 0 caso contrário.
// Tipo de direcao: 0=horizontal, 1=vertical, 2=diagonal principal (++), 3=diagonal secundária (+-)
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                    int linha_inicio, int coluna_inicio, int direcao);

int main() {
    printf("--- Batalha Naval - MateCheck: Nivel Aventureiro ---\n\n");

    // Criar um Tabuleiro 10x10: Matriz inicializada com 0s (água).
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // Todas as posições começam como água.
        }
    }

    // Posicionar Quatro Navios:

    // Navio 1: Horizontal
    // Coordenadas iniciais (linha 2, coluna 1)
    if (!posicionarNavio(tabuleiro, 2, 1, 0)) { // 0 = horizontal
        printf("Falha ao posicionar Navio 1. Verifique limites ou sobreposicao.\n");
        return 1;
    }

    // Navio 2: Vertical
    // Coordenadas iniciais (linha 0, coluna 5)
    if (!posicionarNavio(tabuleiro, 0, 5, 1)) { // 1 = vertical
        printf("Falha ao posicionar Navio 2. Verifique limites ou sobreposicao.\n");
        return 1;
    }

    // Navio 3: Diagonal Principal (linha e coluna aumentam)
    // Coordenadas iniciais (linha 3, coluna 3)
    if (!posicionarNavio(tabuleiro, 3, 3, 2)) { // 2 = diagonal principal (++)
        printf("Falha ao posicionar Navio 3. Verifique limites ou sobreposicao.\n");
        return 1;
    }

    // Navio 4: Diagonal Secundária (linha aumenta, coluna diminui)
    // Coordenadas iniciais (linha 1, coluna 8)
    if (!posicionarNavio(tabuleiro, 1, 8, 3)) { // 3 = diagonal secundária (+-)
        printf("Falha ao posicionar Navio 4. Verifique limites ou sobreposicao.\n");
        return 1;
    }

    // Exibir o Tabuleiro
    printf("Tabuleiro de Batalha Naval com Navios Diagonais:\n");
    exibirTabuleiro(tabuleiro);

    printf("\n--- Nivel Aventureiro da Batalha Naval Concluido! ---\n");

    return 0; // Indica que o programa foi executado com sucesso.
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

// Tenta posicionar um navio no tabuleiro.
// Retorna 1 se o navio foi posicionado com sucesso, 0 caso contrário (limite ou sobreposição).
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                    int linha_inicio, int coluna_inicio, int direcao) {
    int r, c; // Variáveis para linha e coluna temporárias

    // --- 1. Validação de Limites e Sobreposição ---
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
            c = coluna_inicio - i; // Coluna diminui
        }

        // Valida se a posição calculada está dentro dos limites do tabuleiro.
        if (r < 0 || r >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO) {
            printf("Erro: Navio fora dos limites do tabuleiro em (%d,%d).\n", linha_inicio, coluna_inicio);
            return 0; // Fora dos limites
        }

        // Valida se a posição já está ocupada por outro navio.
        if (tabuleiro[r][c] == NAVIO) {
            printf("Erro: Sobreposicao de navios em (%d,%d).\n", r, c);
            return 0; // Sobreposição
        }
    }

    // --- 2. Posicionamento do Navio (se a validação passou) ---
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

    return 1; // Navio posicionado com sucesso.
}