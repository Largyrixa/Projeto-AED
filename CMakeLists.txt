cmake_minimum_required(VERSION 3.14)
project(CoroteSort)

# C++ Standard corrigido para C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Configurações para não compilar exemplos e jogos do raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG "5.0" # Sugestão: usar uma tag de versão específica
  GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

# Adicionar os arquivos fonte
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

# Declarando o executável
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
)

# Adicionando os diretórios de include (src e a nova pasta include)
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Linkando com a biblioteca raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Setando a definição de pré-processador para o caminho dos assets
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")