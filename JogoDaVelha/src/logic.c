#include "logic.h"
#include <stdbool.h>

/* ----- Inicializa o tabuleiro com todas as posições "desocupadas" (' '). ----- */
void InitBoard(Board *b)
{
  for (int i = 0; i < 9; i++)
  {
    b->info[i] = ' ';
  }
}

/* ------ Checa se um jogador ganhou a partida ou se houve empate. ----- */
char BoardState(Board b)
{
  // Matriz de possíveis vitórias conforme as posições ocupadas.
  const int wins[8][3] = {
      {0, 1, 2}, // Linha 1
      {3, 4, 5}, // Linha 2
      {6, 7, 8}, // Linha 3
      {0, 3, 6}, // Coluna 1
      {1, 4, 7}, // Coluna 2
      {2, 5, 8}, // Coluna 3
      {0, 4, 8}, // Diagonal principal
      {2, 4, 6}  // Diagonal secundária
  };

  // Loop que percorre as possibilidades de vitória.
  for (int i = 0; i < 8; i++)
  {

    int s1 = wins[i][0];
    int s2 = wins[i][1];
    int s3 = wins[i][2];

    if (b.info[s1] == 'X' && b.info[s1] == b.info[s2] && b.info[s2] == b.info[s3])
    {
      return 'X';
    }
    else if (b.info[s1] == 'O' && b.info[s1] == b.info[s2] && b.info[s2] == b.info[s3])
    {
      return 'O';
    }
  }

  // Verifica se há espaços disponíveis no tabuleiro.
  for (int i = 0; i < 9; i++)
  {
    if (b.info[i] == ' ')
    {
      return 'N';
    }
  }

  // Caso todos os espaços estejam ocupados, deu empate.
  return 'E';
}

/* ------ Realiza um movimento do jogador atual. ----- */
bool MakeMove(Board *b, int x, int y, char player){

  // Conversão de coordenada 2D para 1D (vetor 0-8)
  int pos = y * 3 + x;

  // Verifica se a posição do tabuleiro é válida.
  if (pos >= 0 && pos < 9 && b->info[pos] == ' ')
  {
    // O jogador ocupa a posição e a função retorna 'true'.
    b->info[pos] = player;
    return true;
  }

  // Em caso inválido, retorna falso.
  return false;
}

/* ----- Retorna o conteúdo de uma célula ----- */
char GetBoardCell(Board b, int x, int y){
  
  int pos = y * 3 + x;

  if (pos >= 0 && pos < 9)
  {
    return b.info[pos];
  }

  // Retorna '?' se as coordenadas são inválidas.
  return '?';
}

