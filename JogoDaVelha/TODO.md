# Arquitetura Do Sistema

**Dificuldade:** Fácil (requer organização)

- [x] Configurar o projeto inicial: Criar o `CMakeLists.txt` para compilar C com Raylib.

- [ ] Criar a `struct Board`

- [ ] Implementar a função `CheckWin(Board b)`: Verifica se alguém ganhou

- [ ] Implementar a função `CheckDraw(Board b)`: Verifica se deu velha

- [ ] Implementar a função `MakeMove(Board b, int x, int y)`: Atualiza o estado da matriz

# IA / Bot

**Dificuldade:** Alta (lógica algorítmica pesada)

- [ ] Definir a `struct Node`: Deve representar um estado do tabuleiro e ter ponteiros para os filhos (jogadas futuras).

- [ ] Criar a função `GetMove(Board b, Dificulty d)`: Utiliza uma versão modificada do minimax, no qual existe uma chance de fazer uma jogada propositalmente ruim (a depender da dificuldade).


# Motor Gráfico (Raylib)

**Dificuldade:** Média (muitos detalhes visuais)

- [ ] Desenhar o Grid (o tabuleiro #) na tela.

- [ ] Criar funções `DrawX(int x, int y)` e `DrawO(int x, int y)` com cores e estilos diferentes (ou ainda com imagens aleatórias pra ficar engraçado sei lakkkk)

- [ ] Criar a tela de "Game Over" (Mostrar quem ganhou e instrução para reiniciar).

- [ ] `Extra`: Adicionar efeitos sonoros para o clique e ao ganhar (e talvez uma música).

# Interação e UI

**Dificuldade:** Média (lógica de estado e interação)

- [ ] Implementar o **Game Loop** principal (While (!WindowShouldClose))

- [ ] Criar o sistema de conversão: Transformar o o clique do mouse em coordenadas da matriz.

- [ ] Criar o **Menu Inicial**: Botões para selecionar a dificuldade e botão "Jogar"

- [ ] Gerenciar os estado do jogo: `MENU`, `PLAYING`, `GAME_OVER`. É ele quem decide quando chamar as funções de desenho ou a IA.

# Gerenciamento de Memória & Limpeza

**Dificuldade:** Fácil (Boas Práticas)

- [ ] Implementar `FreeTree(Node *root)`: Uma função recursiva para dar `free` em todos os nós ta árvore após a jogada da IA (evitar memory leak)

- [ ] Implementar `UnloadResources()`: Chamar `UnloadTexture` e `UnloadSound` antes de fechar o jogo
