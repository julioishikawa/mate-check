#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pieces.h"

// Função recursiva para imprimir os passos restantes de um segmento do movimento do Cavalo.
// Parâmetros:
//   steps     - Número de passos restantes a serem impressos.
//   direction - String que indica a direção (ex: "Cima", "Direita", etc.)
void printKnightSegmentRecursive(int steps, const char *direction) {
    if (steps <= 0)  // Condição base: se não há mais passos, encerra a recursão.
        return;
        
    // Imprime a direção do movimento
    printf("%s\n", direction);
    
    // Chama a função recursivamente para imprimir o próximo passo (steps - 1)
    printKnightSegmentRecursive(steps - 1, direction);
}

// Função recursiva para imprimir os dois segmentos do movimento do Cavalo.
// Parâmetros:
//   seg            - Índice do segmento atual (0 para o primeiro, 1 para o segundo).
//   segment1Steps  - Número de passos do primeiro segmento (geralmente 2).
//   segment2Steps  - Número de passos do segundo segmento (geralmente 1).
//   primaryDir     - Direção do primeiro segmento.
//   secondaryDir   - Direção do segundo segmento.
void printKnightMovementRecursive(int seg, int segment1Steps, int segment2Steps,
                                  const char *primaryDir, const char *secondaryDir) {
    if (seg >= 2)  // Condição base: se ambos os segmentos já foram impressos, encerra a recursão.
        return;
    
    // Determina o número de passos e a direção para o segmento atual
    int steps = (seg == 0) ? segment1Steps : segment2Steps;
    const char *direction = (seg == 0) ? primaryDir : secondaryDir;
    
    // Imprime os passos do segmento atual utilizando a função recursiva
    printKnightSegmentRecursive(steps, direction);
    
    // Chama recursivamente para imprimir o próximo segmento (incrementa o índice)
    printKnightMovementRecursive(seg + 1, segment1Steps, segment2Steps, primaryDir, secondaryDir);
}

// Função para movimentar o Cavalo.
// O Cavalo inicia na posição b1 e move-se em "L" (2 em uma direção e 1 na outra).
void moveKnight(void) {
    // Define a posição inicial fixa do Cavalo (b1)
    const char knightStartCol = 'b';
    const int knightStartRow = 1;
    char input[100];         // Buffer para entrada do usuário
    char knightDestCol;      // Coluna de destino
    int knightDestRow;       // Linha de destino
    int validMove = 0;       // Flag para indicar se o movimento informado é válido

    // Loop para solicitar e validar a posição de destino do Cavalo
    do {
        printf("\nMovimento do Cavalo (inicia em b1)\n");
        printf("Digite a posicao de destino para o Cavalo (ex: c3): ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Tenta extrair a coluna e a linha da entrada
            if (sscanf(input, " %c%d", &knightDestCol, &knightDestRow) != 2) {
                knightDestCol = '\0';
                knightDestRow = -1;
            }
            // Converte a coluna para minúsculo para padronizar a comparação
            knightDestCol = tolower(knightDestCol);
        }
        // Verifica se a posição está dentro dos limites válidos do tabuleiro (colunas a-h, linhas 1-8)
        if (knightDestCol < 'a' || knightDestCol > 'h' ||
            knightDestRow < 1 || knightDestRow > 8) {
            printf("\nPosicao invalida. As colunas devem estar entre a-h e as linhas entre 1-8.\n");
            continue;  // Reinicia o loop se a posição for inválida
        }
        // Verifica se o Cavalo está tentando permanecer na posição inicial (b1)
        if (knightDestCol == knightStartCol && knightDestRow == knightStartRow) {
            printf("\nMovimento invalido. O Cavalo deve sair de sua posicao inicial.\n");
            continue;  // Reinicia o loop se o movimento for inválido
        }
        // Calcula a diferença entre a posição de destino e a posição inicial
        int deltaRow = knightDestRow - knightStartRow;
        int deltaCol = knightDestCol - knightStartCol;
        // Verifica se o movimento do Cavalo é válido (movimento em "L":
        // 2 casas em uma direção e 1 casa na outra)
        if ((abs(deltaRow) == 2 && abs(deltaCol) == 1) ||
            (abs(deltaRow) == 1 && abs(deltaCol) == 2))
            validMove = 1;
        else
            printf("\nMovimento invalido para o Cavalo. Ele deve mover-se em 'L' (2 em uma direcao e 1 na outra).\n");
    } while (!validMove);  // Repete enquanto o movimento não for válido

    // Após a validação, recalcula as diferenças para determinar os segmentos do movimento
    int deltaRow = knightDestRow - knightStartRow;
    int deltaCol = knightDestCol - knightStartCol;
    int segment1Steps, segment2Steps;  // Segmentos do movimento: primeiro (2 passos) e segundo (1 passo)
    const char *primaryDir = "";       // Direção do primeiro segmento (2 passos)
    const char *secondaryDir = "";     // Direção do segundo segmento (1 passo)

    // Define os segmentos do movimento com base nas diferenças:
    // Se a variação na linha for 2, o movimento principal (2 passos) é vertical;
    // caso contrário, é horizontal.
    if (abs(deltaRow) == 2) {
        segment1Steps = 2;         // Primeiro segmento: 2 passos (vertical)
        segment2Steps = 1;         // Segundo segmento: 1 passo (horizontal)
        primaryDir = (deltaRow > 0) ? "Cima" : "Baixo";       // Se deltaRow positivo, vai "Cima"; se negativo, "Baixo"
        secondaryDir = (deltaCol > 0) ? "Direita" : "Esquerda"; // Se deltaCol positivo, vai "Direita"; se negativo, "Esquerda"
    } else {
        segment1Steps = 2;         // Primeiro segmento: 2 passos (horizontal)
        segment2Steps = 1;         // Segundo segmento: 1 passo (vertical)
        primaryDir = (deltaCol > 0) ? "Direita" : "Esquerda";   // Se deltaCol positivo, vai "Direita"; se negativo, "Esquerda"
        secondaryDir = (deltaRow > 0) ? "Cima" : "Baixo";         // Se deltaRow positivo, vai "Cima"; se negativo, "Baixo"
    }

    // Exibe a movimentação do Cavalo utilizando recursão para imprimir ambos os segmentos
    printf("\nMovimentacao do Cavalo:\n");
    // Chama a função recursiva que imprime os segmentos (inicia com seg = 0)
    printKnightMovementRecursive(0, segment1Steps, segment2Steps, primaryDir, secondaryDir);
}
