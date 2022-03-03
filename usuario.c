/*

========== Agenda Multiusuário ==========

*/

//ARQUIVO DE IMPLEMENTACAO
#include "usuario.h"
#include "agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool usuario_existe(const char *login, Usuario *usuario) {
    //dados
    FILE* arquivo_usuarios = fopen(ARQ_USUARIO, "rb");
    Usuario usuario_corrente;
    bool resultado = false;

    if (arquivo_usuarios == NULL)
        printf("\nERROR: problemas ao abrir o arquivo de [%s]! Contate o desenvolvedor.\n", ARQ_USUARIO);
    else {
        //procura os usuarios
        while (fread(&usuario_corrente, sizeof(Usuario), 1, arquivo_usuarios) != 0) {
            //verifica se o login do usuario e igual ao informado
            if (strcmp(usuario_corrente.login, login) == 0) {
                *usuario = usuario_corrente;
                resultado = true;
                break;
            }
        }

        //fecha o arquivo
        fclose(arquivo_usuarios);
    }
    

    return resultado;
}

void cadastrar_usuario(void) {
    //dados
    FILE* arquivo_usuarios = NULL;
    Usuario usuario;
    Usuario tmp_usuario;
    int opcao = 0;

    //captura os dados
    do {
        //limpa o buffer
        while (getchar() != '\n');
        
        //dados
        printf("\n---CADASTRO---\n");
        printf("Login: ");
        fgets(usuario.login, 20, stdin);
        printf("Nome: ");
        fgets(usuario.nome, 50, stdin);

        //retirar o \n do final da string
        usuario.login[strlen(usuario.login) - 1] = '\0';
        usuario.nome[strlen(usuario.nome) - 1] = '\0';
        
        //mini menu
        printf("\nDeseja continuar?\n");
        printf("[1] - Cadastrar.\n");
        printf("[0] - Cancelar.\n");
        printf("OPCAO: ");
        scanf("%d", &opcao);

        //error
        if (opcao != 0 && opcao != 1)
            printf("ERROR: opcao invalida! Tente novamente.\n");
        else if (usuario_existe(usuario.login, &usuario))
            printf("ERROR: usuario ja cadastrado! Tente novamente.\n");
    } while ((opcao != 0 && opcao != 1) || (usuario_existe(usuario.login, &usuario)));

    if (opcao == 1) {
        arquivo_usuarios = fopen(ARQ_USUARIO, "a+b");

        if (arquivo_usuarios == NULL)
            printf("\nERROR: problema ao abrir o arquivo [%s]! Contate o desenvolvedor.\n", ARQ_USUARIO);
        else {
            // posiciona o curso para o fim do arquivo
            if (fseek(arquivo_usuarios, -sizeof(Usuario), SEEK_END) != 0) {
                //ler o ultimo registro para poder atualizar o id
                fread(&tmp_usuario, sizeof(Usuario), 1, arquivo_usuarios);
                usuario.id = tmp_usuario.id + 1;
            } else {
                usuario.id = 0;
            }

            //grava o usuario
            fwrite(&usuario, sizeof(Usuario), 1, arquivo_usuarios);
            printf("INFO: Cadastrado com sucesso!\n");
            
            //envia para a tela da agenda
            menu_agenda(usuario);

            //fecha o arquivo
            fclose(arquivo_usuarios);
        }
    }
}

void autenticar_usuario(void) {
    //dados
    Usuario usuario;
    
    //limpa o buffer
    while (getchar() != '\n');
    
    //ler os dados
    printf("\n---LOGIN---\n");
    printf("Login: ");
    fgets(usuario.login, 20, stdin);

    //tira o enter do final
    usuario.login[strlen(usuario.login) - 1] = '\0';

    //autentica
    if (usuario_existe(usuario.login, &usuario)) {
        menu_agenda(usuario);
    } else {
        printf("\nERROR: Acesso negado.\n");
    }
}