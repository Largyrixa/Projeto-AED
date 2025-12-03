cmake_minimum_required(VERSION 3.14)
project(JogoDaVelha)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Configurações para não compilar exemplos e jogos do raylib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES    OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES       OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG "5.5" # Sugestão: usar uma tag de versão específica
  GIT_PROGRESS TRUE
)

set(BUILD_SHARED_LIBRARIES OFF CACHE BOOL "" FORCE)
set(PLATFORM Desktop CACHE STRING "" FORCE)

FetchContent_MakeAvailable(raylib)

# Adicionar os arquivos fonte
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.c")

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
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="assets/")

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

if(EXISTS "${ASSETS_DIR}")
    # Comando que copia a pasta assets para o lado do executável após compilar
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ASSETS_DIR}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
        COMMENT "Copiando assets para o diretório de saída..."
    )
else()
    message(WARNING "Pasta 'assets' não encontrada! O jogo pode não rodar sem ela.")
endif()