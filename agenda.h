/* agenda.h */

#ifndef _AGENDA_H
#define _AGENDA_H

#include <stdbool.h>
#include "usuario.h"

/* nome do arquivo aonde os contados da agenda sao cadastrados */
#define ARQ_AGENDA "agenda.dat"

/* estrutura que representa um contato da agenda */
typedef struct {
    int id_usuario; // id do usuario da agenda
    int id_contato; // id do contato
    char nome[51]; // nome do contato
    char telefone[16]; // telefone do contato
    char email[31]; // e-mail do contato
} Contato;

/* funcao que recebe o um usuario como argumento e
 * exibe a tela inicial de sua agenda */
void menu_agenda(Usuario);

/* funcao que cadastra um novo contato para o usuario
 * cujo id e fornecido como argumento da funcao */
void cadastrar_contato(int);

/* funcao que recebe como argumento o id de um contato
 * e permite alterar os dados desses contato, caso seu
 * id seja valido */
void alterar_contato(int);

/* funcao que lista todos os contatos de um usuario cujo
 * id e fornecido como argumento */
void listar_contatos(int);

/* funcao que permite consultar por nome os contatos de
 * um usuario cujo id e fornecido como argumento */
void consultar_contatos(int);

#endif