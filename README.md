# CoroteSort
---
## Como Compilar?

<details>
 <summary><h3>Linux</h3></summary>

#### Pré-requisitos
1. **Git:** Para clonar o projeto.
2. **Compilador C++:** Pode ser o GCC ou outro que funcione com o CMake.
3. **CMake:** Instale o CMake para a compilação.

#### Passos para Compilar e Executar
```bash
# 1. Clone o repositório e entre na pasta
git clone https://github.com/Largyrixa/CoroteSort.git
cd CoroteSort

# 2. Crie a pasta de build e configure o projeto
mkdir build && cd build
cmake ..

# 3. Compile e execute o projeto
make && cd ..
./build/bin/CoroteSort
```

</details>

<details>
 <summary><h3>Windows</h3></summary>

#### Pré-requisitos

1.  **Git:** Essencial para clonar o projeto. Baixe em [git-scm.com](https://git-scm.com/download/win).
2.  **Compilador C++:** A extensão precisa de um compilador para funcionar. Instale **uma** das opções abaixo:
    * **(Mais fácil)** **Visual Studio Build Tools:** Instale o "Visual Studio Community 2022" (como na Opção 1 do guia anterior), garantindo que a carga de trabalho **"Desenvolvimento para desktop com C++"** esteja selecionada. Você não precisará usar a interface do Visual Studio, apenas o compilador que vem com ele.
    * **(Alternativa)** **MinGW-w64:** Siga as instruções para instalar o MinGW-w64 via MSYS2 (como na Opção 2 do guia anterior) e adicione-o ao PATH do sistema.
3.  **Visual Studio Code:** Baixe em [code.visualstudio.com](https://code.visualstudio.com/).
4.  **Extensões do VS Code:** Dentro do VS Code, vá até a aba de Extensões (Ctrl+Shift+X) e instale:
    * `CMake Tools` (da Microsoft)
    * `C/C++` (da Microsoft)

#### Passos para Compilar e Executar

1.  **Clonar e Abrir o Projeto:**
    * Clone o repositório usando o Git.
    * Abra o **VS Code** e vá em `File > Open Folder...` para abrir a pasta raiz do projeto (`CoroteSort`).

2.  **Selecionar o Compilador (Kit):**
    * Logo após abrir a pasta, a extensão CMake Tools deve mostrar uma notificação na parte inferior da tela, perguntando se você deseja configurar o projeto. Clique em `Yes`.
    * Em seguida, ela pedirá para você "Select a Kit". Uma lista suspensa aparecerá no topo com os compiladores que ela encontrou no seu sistema.
    * Selecione o compilador que você instalou (ex: `Visual C++ Build Tools` ou `GCC for MinGW-w64`).
    * *Se nenhuma notificação aparecer, pressione `Ctrl+Shift+P` para abrir a Paleta de Comandos, digite `CMake: Select a Kit` e pressione Enter.*

3.  **Configurar e Compilar (Build):**
    * Após selecionar o Kit, a extensão irá configurar o projeto automaticamente (equivalente a `cmake ..`). Você verá o progresso no painel "Output".
    * Na **barra de status azul** na parte inferior do VS Code, você verá vários botões. Clique no botão **`[Build]`**.
    * Isso irá compilar todo o projeto (equivalente a `cmake --build .`).

4.  **Executar o Programa:**
    * Na mesma barra de status, clique no **ícone de Play** (▶️) ou no botão que diz `[Run]`.
    * A extensão irá compilar o projeto (se houver mudanças) e depois executar o `CoroteSort.exe`. A saída do seu programa aparecerá no Terminal Integrado do VS Code.

5.  **(Opcional) Depurar:**
    * Para depurar o código (usar breakpoints, inspecionar variáveis), clique no **ícone de inseto (🐞)** ao lado do botão de Play.
</details>