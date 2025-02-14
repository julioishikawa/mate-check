#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pieces.h"

// Função recursiva para imprimir cada passo do movimento da Torre.
// Parâmetros:
//   steps     - Número de passos restantes para imprimir.
//   direction - Direção do movimento ("Cima", "Baixo", "Direita" ou "Esquerda").
void printRookStepsRecursive(int steps, const char *direction) {
    // Caso base: se não há mais passos, encerra a recursão.
    if (steps <= 0)
        return;
    
    // Imprime a direção de um passo do movimento.
    printf("%s\n", direction);
    
    // Chama a função recursivamente para o próximo passo.
    printRookStepsRecursive(steps - 1, direction);
}

// Função para movimentar a Torre.
// A Torre inicia na posição a1 e move-se apenas na mesma linha ou coluna.
void moveRook(void) {
    // Posição inicial fixa da Torre (coluna 'a' e linha 1)
    const char rookStartCol = 'a';
    const int rookStartRow = 1;
    
    // Variáveis para armazenar a posição de destino informada pelo usuário.
    char rookDestCol;
    int rookDestRow;
    int validMove = 0; // Flag para indicar se o movimento é válido.
    char input[100];   // Buffer para entrada do usuário.

    // Loop para solicitar e validar a posição de destino da Torre.
    do {
        printf("\nMovimento da Torre (inicia em a1)\n");
        printf("Digite a posicao de destino para a Torre (ex: h1): ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Tenta extrair um caractere (coluna) e um número (linha) da entrada.
            if (sscanf(input, " %c%d", &rookDestCol, &rookDestRow) != 2) {
                rookDestCol = '\0';
                rookDestRow = -1;
            }
            // Converte a coluna para minúsculo para padronizar a entrada.
            rookDestCol = tolower(rookDestCol);
        }
        // Verifica se a posição está dentro dos limites válidos do tabuleiro.
        if (rookDestCol < 'a' || rookDestCol > 'h' ||
            rookDestRow < 1 || rookDestRow > 8)
            printf("\nPosicao invalida. As colunas devem estar entre a-h e as linhas entre 1-8.\n");
        // A Torre deve mover-se apenas na mesma coluna ou na mesma linha.
        else if (rookDestCol != rookStartCol && rookDestRow != rookStartRow)
            printf("\nMovimento invalido. A Torre deve mover-se apenas na mesma coluna ou na mesma linha.\n");
        // Verifica se o movimento não é nulo (não permanecer na mesma posição).
        else if (rookDestCol == rookStartCol && rookDestRow == rookStartRow)
            printf("\nMovimento invalido. A Torre deve sair de sua posicao inicial.\n");
        else
            validMove = 1; // Movimento válido.
    } while (!validMove);

    // Determina a direção e o número de passos do movimento.
    const char *direction;
    int steps;
    // Se a coluna de destino for igual à coluna inicial, o movimento é vertical.
    if (rookDestCol == rookStartCol) {
        // Define a direção vertical: "Cima" se o destino estiver acima, "Baixo" se estiver abaixo.
        direction = (rookDestRow - rookStartRow > 0) ? "Cima" : "Baixo";
        // Número de passos é a diferença absoluta entre as linhas.
        steps = abs(rookDestRow - rookStartRow);
    } else {
        // Caso contrário, o movimento é horizontal.
        // Define a direção horizontal: "Direita" se o destino estiver à direita, "Esquerda" se estiver à esquerda.
        direction = (rookDestCol - rookStartCol > 0) ? "Direita" : "Esquerda";
        // Número de passos é a diferença absoluta entre as colunas.
        steps = abs(rookDestCol - rookStartCol);
    }

    // Exibe os passos do movimento da Torre utilizando a função recursiva.
    printf("\nMovimentacao da Torre:\n");
    printRookStepsRecursive(steps, direction);
}
