/* usuario.h */

#ifndef _USUARIO_H
#define _USUARIO_H
#include <stdbool.h>

/* nome do arquivo aonde os usuarios sao cadastrados */
#define ARQ_USUARIO "usuario.dat"

/* estrutura que representa um usuario */
typedef struct {
    int id; // id do usuario
    char login[21]; // login do usuario
    char nome[51]; // nome do usuario
} Usuario;

/* funcao que cadastra um novo usuario no arquivo e direciona-o
 * para a tela inicial de sua agenda, caso o cadastro tenha sido
 * bem-sucedido */
void cadastrar_usuario(void);

/* funcao que solicita o login do usuario e caso ele seja valido,
 * direciona-o para a tela inicial de sua agenda */
void autenticar_usuario(void);

/* funcao que devolve verdadeiro caso um usuario com o login
 * fornecido como primeiro argumento da funcao ja esteja cadastrado
 * e armazena os dados desse usuario na estrutura cujo endereco
 * e passado como segundo argumento da funcao. Se o usuario nao
 * estiver cadastrado, a funcao devolve falso.
 * Esta funcao deve ser usada pelas funcoes cadastrar_usuario()
 * e autenticar_usuario() */
bool usuario_existe(const char *, Usuario *);

#endif