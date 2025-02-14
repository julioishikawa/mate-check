#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pieces.h"

// Função recursiva para exibir os passos do movimento do Bispo
// Parâmetros:
//   steps      - Número de passos restantes a serem exibidos.
//   verticalDir   - String representando a direção vertical ("Cima" ou "Baixo").
//   horizontalDir - String representando a direção horizontal ("Direita" ou "Esquerda").
void moveBishopRecursive(int steps, const char *verticalDir, const char *horizontalDir) {
    // Condição base: se não houver mais passos para imprimir, encerra a recursão.
    if (steps <= 0)
        return;
    
    // Imprime o passo atual com as direções definidas.
    printf("%s, %s\n", verticalDir, horizontalDir);
    
    // Chama a função recursivamente, decrementando o contador de passos.
    moveBishopRecursive(steps - 1, verticalDir, horizontalDir);
}

// Função para movimentar o Bispo.
// O Bispo inicia na posição c1 e deve mover-se na diagonal.
void moveBishop(void) {
    // Define a posição inicial fixa do Bispo.
    const char bishopStartCol = 'c';
    const int bishopStartRow = 1;
    
    // Variáveis para armazenar a posição de destino informada pelo usuário.
    char bishopDestCol;
    int bishopDestRow;
    int validMove = 0;  // Flag que indica se o movimento informado é válido.
    char input[100];    // Buffer para armazenar a entrada do usuário.

    // Loop para solicitar e validar a posição de destino do Bispo.
    do {
        printf("Movimento do Bispo (inicia em c1)\n");
        printf("Digite a posicao de destino para o Bispo (ex: a3): ");
        
        // Lê a entrada do usuário.
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Tenta extrair a coluna e a linha da entrada.
            if (sscanf(input, " %c%d", &bishopDestCol, &bishopDestRow) != 2) {
                // Se a extração falhar, define valores inválidos.
                bishopDestCol = '\0';
                bishopDestRow = -1;
            }
            // Converte a coluna para minúsculo para padronizar a comparação.
            bishopDestCol = tolower(bishopDestCol);
        }
        
        // Verifica se a posição está dentro dos limites válidos do tabuleiro.
        if (bishopDestCol < 'a' || bishopDestCol > 'h' ||
            bishopDestRow < 1 || bishopDestRow > 8)
            printf("\nPosicao invalida. As colunas devem estar entre a-h e as linhas entre 1-8.\n\n");
        // Verifica se o Bispo não está permanecendo na posição inicial.
        else if (bishopDestCol == bishopStartCol && bishopDestRow == bishopStartRow)
            printf("\nMovimento invalido. O Bispo deve sair de sua posição inicial.\n\n");
        // Verifica se o movimento é diagonal: a diferença absoluta entre linhas deve ser igual à diferença absoluta entre colunas.
        else if (abs(bishopDestRow - bishopStartRow) != abs(bishopDestCol - bishopStartCol))
            printf("\nMovimento invalido. O Bispo deve mover-se na diagonal.\n\n");
        else
            // Se todas as condições forem satisfeitas, o movimento é válido.
            validMove = 1;
    } while (!validMove);  // Repete o loop enquanto o movimento não for válido.

    // Determina a direção vertical com base na diferença das linhas.
    // Se a linha de destino é maior que a linha inicial, o movimento é "Cima", caso contrário, "Baixo".
    const char *verticalDir = (bishopDestRow - bishopStartRow > 0) ? "Cima" : "Baixo";
    
    // Determina a direção horizontal com base na diferença das colunas.
    // Se a coluna de destino é maior que a coluna inicial ('c'), o movimento é "Direita", caso contrário, "Esquerda".
    const char *horizontalDir = (bishopDestCol - bishopStartCol > 0) ? "Direita" : "Esquerda";
    
    // Calcula o número de passos que o Bispo deve dar.
    // Como o movimento é diagonal, a quantidade de passos é a diferença absoluta entre as linhas.
    int steps = abs(bishopDestRow - bishopStartRow);

    // Exibe os passos do movimento do Bispo utilizando a função recursiva.
    printf("\nMovimentacao do Bispo:\n");
    moveBishopRecursive(steps, verticalDir, horizontalDir);
}