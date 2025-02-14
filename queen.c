#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pieces.h"

// Função recursiva para imprimir cada passo do movimento da Rainha.
// Parâmetros:
//   steps         - Quantidade de passos restantes para imprimir.
//   verticalDir   - Direção vertical ("Cima" ou "Baixo"). Se não houver movimento vertical, será uma string vazia.
//   horizontalDir - Direção horizontal ("Direita" ou "Esquerda"). Se não houver movimento horizontal, será uma string vazia.
void printQueenStepsRecursive(int steps, const char *verticalDir, const char *horizontalDir) {
    // Caso base: se não há passos restantes, encerra a recursão.
    if (steps <= 0)
        return;
    
    // Se houver movimento em ambas as direções (diagonal),
    // imprime ambas separadas por vírgula.
    if (verticalDir[0] != '\0' && horizontalDir[0] != '\0')
        printf("%s, %s\n", verticalDir, horizontalDir);
    // Se o movimento for apenas vertical, imprime a direção vertical.
    else if (verticalDir[0] != '\0')
        printf("%s\n", verticalDir);
    // Se o movimento for apenas horizontal, imprime a direção horizontal.
    else if (horizontalDir[0] != '\0')
        printf("%s\n", horizontalDir);
    
    // Chama a função recursivamente para imprimir o próximo passo.
    printQueenStepsRecursive(steps - 1, verticalDir, horizontalDir);
}

// Função para movimentar a Rainha.
// A Rainha inicia na posição d1 e pode mover-se horizontalmente, verticalmente ou diagonalmente.
void moveQueen(void) {
    // Define a posição inicial da Rainha (coluna 'd' e linha 1)
    const char queenStartCol = 'd';
    const int queenStartRow = 1;
    
    // Variáveis para armazenar a posição de destino fornecida pelo usuário.
    char queenDestCol;
    int queenDestRow;
    // Flag para indicar se o movimento informado é válido.
    int validMove = 0;
    // Buffer para armazenar a entrada do usuário.
    char input[100];

    // Loop para solicitar e validar a entrada do usuário até que um movimento válido seja informado.
    do {
        printf("\nMovimento da Rainha (inicia em d1)\n");
        printf("Digite a posicao de destino para a Rainha (ex: g4): ");
        // Lê a entrada do usuário.
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Tenta extrair a coluna e a linha da entrada.
            if (sscanf(input, " %c%d", &queenDestCol, &queenDestRow) != 2) {
                // Se a extração falhar, define valores inválidos.
                queenDestCol = '\0';
                queenDestRow = -1;
            }
            // Converte a coluna para minúsculo para garantir consistência.
            queenDestCol = tolower(queenDestCol);
        }
        // Verifica se a posição informada está dentro dos limites válidos do tabuleiro (colunas a-h e linhas 1-8).
        if (queenDestCol < 'a' || queenDestCol > 'h' ||
            queenDestRow < 1 || queenDestRow > 8) {
            printf("\nPosicao invalida. As colunas devem estar entre a-h e as linhas entre 1-8.\n");
        } else {
            // Calcula a diferença entre a posição de destino e a posição inicial.
            int deltaRow = queenDestRow - queenStartRow;
            int deltaCol = queenDestCol - queenStartCol;
            // Verifica se o movimento é válido:
            // A Rainha pode mover-se na mesma linha (horizontal),
            // na mesma coluna (vertical) ou na diagonal (quando |deltaRow| == |deltaCol|).
            if (!((queenDestRow == queenStartRow) || (queenDestCol == queenStartCol) ||
                  (abs(deltaRow) == abs(deltaCol))))
                printf("\nMovimento invalido. A Rainha deve mover-se horizontalmente, verticalmente ou diagonalmente.\n");
            // Impede que a Rainha permaneça na posição inicial.
            else if (queenDestRow == queenStartRow && queenDestCol == queenStartCol)
                printf("\nMovimento invalido. A Rainha deve sair de sua posicao inicial.\n");
            else
                validMove = 1; // Movimento válido.
        }
    } while (!validMove);

    // Calcula as diferenças entre a posição de destino e a posição inicial.
    int deltaRow = queenDestRow - queenStartRow;
    int deltaCol = queenDestCol - queenStartCol;
    // Variável para armazenar o número de passos que a Rainha deverá mover.
    int steps;
    // Variáveis para armazenar as direções vertical e horizontal do movimento.
    const char *verticalDir = "";
    const char *horizontalDir = "";

    // Determina a direção e o número de passos do movimento com base na posição de destino:
    // Se a Rainha mover-se somente na horizontal (mesma linha).
    if (queenDestRow == queenStartRow) {
        steps = abs(deltaCol); // Número de colunas a percorrer.
        horizontalDir = (deltaCol > 0) ? "Direita" : "Esquerda";
    }
    // Se a Rainha mover-se somente na vertical (mesma coluna).
    else if (queenDestCol == queenStartCol) {
        steps = abs(deltaRow); // Número de linhas a percorrer.
        verticalDir = (deltaRow > 0) ? "Cima" : "Baixo";
    }
    // Caso contrário, o movimento é diagonal (|deltaRow| == |deltaCol|).
    else {
        steps = abs(deltaRow);  // O número de passos é o valor absoluto de deltaRow (ou deltaCol, já que são iguais).
        verticalDir = (deltaRow > 0) ? "Cima" : "Baixo";
        horizontalDir = (deltaCol > 0) ? "Direita" : "Esquerda";
    }

    // Imprime os passos do movimento da Rainha utilizando a função recursiva.
    printf("\nMovimentacao da Rainha:\n");
    printQueenStepsRecursive(steps, verticalDir, horizontalDir);
}