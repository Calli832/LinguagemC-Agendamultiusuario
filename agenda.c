/*

========== Agenda Multiusuário ==========

*/

//ARQUIVO DE IMPLEMENTACAO
#include "agenda.h"
#include <stdio.h>
#include <string.h>

//FUNCAO AUXILIAR QUE VERIFICA SE O CONTATO PERTENCE AO USUARIO
bool verificar_contato(int id_contato, int id_usuario) {
    //dados
    FILE* arquivo_contatos = fopen(ARQ_AGENDA, "rb");
    Contato contato;
    bool resultado = false;

    if (arquivo_contatos != NULL) {
        //procura pelo contato
        while (fread(&contato, sizeof(Contato), 1, arquivo_contatos) != 0) {
            //verifica se o contato pertence ao usuario
            if (contato.id_contato == id_contato) {
                if (contato.id_usuario == id_usuario)
                    resultado = true;

                break;
            }
        }

        //fecha o arquivo
        fclose(arquivo_contatos);
    } else {
        printf("ERROR: nao foi possivel obter os dados do arquivo! Por favor, contacte o desenvolvedor.\n");
    }

    return resultado;
}


void menu_agenda(Usuario usuario) {
    //dados
    int opcao = 0;
    int id_contato_alterar = 0;

    //cabecalho
    printf("\nAgenda de <%s>\n", usuario.nome);

    while (true) {
        //menu
        do {
            printf("\n---MENU---\n");
            printf("[1] - Novo Contato.\n");
            printf("[2] - Alterar Contato.\n");
            printf("[3] - Listar Contatos.\n");
            printf("[4] - Consultar Contatos.\n");
            printf("[0] - Sair.\n");
            printf("OPCAO: ");
            scanf("%d", &opcao);
            //error
            if (opcao < 0 || opcao > 4)
                printf("ERROR: opcao invalida! Tente novamente.\n");
        } while (opcao < 0 || opcao > 4);
        
        //novo contato
        if (opcao == 1) {
            printf("\n---ADICIONAR CONTATO---\n");
            cadastrar_contato(usuario.id);
        }
        //alterar contato
        else if (opcao == 2) {
            printf("\n---ALTERAR CONTATOS---.\n");
            printf("Informe o id do contato que deseja alterar: ");
            scanf("%d", &id_contato_alterar);

            //verifica se o contato pertence ao usuario
            if (verificar_contato(id_contato_alterar, usuario.id)) {
                alterar_contato(id_contato_alterar);
            } else {
                printf("ERROR: Contato nao pertence ao usuario ou nao existe!\n");
            }
        }

        //listar contatos
        else if (opcao == 3) {
            printf("\n---LISTAR CONTATOS---\n");
            listar_contatos(usuario.id);
        }
        //consultar contatos
        else if (opcao == 4) {
            printf("\n---CONSULTAR CONTATO PELO NOME\n");
            consultar_contatos(usuario.id);
        }
        //sair
        else if (opcao == 0) {
            printf("\nAVISO: Ate a proxima!\n");
            break;
        }
    }
}

void listar_contatos(int id_usuario) {
    //abre o arquivo de usuarios para leitura
    FILE* arquivo_contatos = fopen(ARQ_AGENDA, "rb");
    Contato contato;
    int flag_existem_contatos = 0;

    if (arquivo_contatos == NULL) {
        printf("\nERROR: nao foi possivel obter os dados do arquivo! Por favor, contacte o desenvolvedor.\n");
    } else {
        //lista os contatos
        while (fread(&contato, sizeof(Contato), 1, arquivo_contatos) != 0) {
            //verifica se o contato pertence ao usuario
            if (contato.id_usuario == id_usuario) {
                printf("\n|ID Contato: %d | Nome: %s | Telefone: %s | E-mail: %s |",
                contato.id_contato, contato.nome, contato.telefone, contato.email);
                printf("\n------------------------------------------------------------------------------");
                flag_existem_contatos = 1;
            }
        }

        //exibe um aviso caso nao tenham contatos cadastrados
        if (!flag_existem_contatos)
            printf("\n\nAVISO: nao existem contatos cadastrados para este usuario.\n\n");
        else
            printf("\n\n");

        //fecha o arquivo
        fclose(arquivo_contatos);
    }
}

void cadastrar_contato(int id_usuario) {
    //abre o arquivo para insercao de um novo contato
    FILE* arquivo_contatos = fopen(ARQ_AGENDA, "a+b");
    Contato contato;
    int id = 0;
    long int tamanho_arquivo = 0;

    if (arquivo_contatos == NULL) {
        printf("ERROR: nao foi possivel obter os dados do arquivo! Por favor, contacte o desenvolvedor.\n");
    } else {
        //pega o tamanho do arquivo e retorna o valor da divisao para inserir o id do contato
        fseek(arquivo_contatos, 0, SEEK_END); // seek to end of file
        tamanho_arquivo = ftell(arquivo_contatos); // get current file pointer
        fseek(arquivo_contatos, 0, SEEK_SET); //volta para o inicio do arquivo

        id = tamanho_arquivo/sizeof(Contato);

        //limpa o buffer
        while (getchar() != '\n');
        
        //pega os dados
        contato.id_usuario = id_usuario;
        contato.id_contato = id + 1;
               
        printf("Nome: ");
        fgets(contato.nome, 50, stdin);
        //tira o enter do final
        contato.nome[strlen(contato.nome) - 1] = '\0'; //string termina com este caracter

        printf("Telefone: ");
        fgets(contato.telefone, 15, stdin);
        //tira o enter do final
        contato.telefone[strlen(contato.telefone) - 1] = '\0';

        printf("Email: ");
        fgets(contato.email, 30, stdin);
        //tira o enter do final
        contato.email[strlen(contato.email) - 1] = '\0';

        //adiciona no arquivo
        fwrite(&contato, sizeof(contato), 1, arquivo_contatos);

        //fecha o arquivo
        fclose(arquivo_contatos);
    }
}

void alterar_contato(int id_contato) {
    //abre o arquivo para insercao de um novo contato
    FILE* arquivo_contatos = fopen(ARQ_AGENDA, "r+b");
    Contato contato;
    int posicao_arquivo = 0;

    if (arquivo_contatos == NULL) {
        printf("ERROR: nao foi possivel obter os dados do arquivo! Por favor, contacte o desenvolvedor.\n");
    } else {
        //pega o tamanho do arquivo e retorna o valor da divisao para inserir o id do contato
        while (fread(&contato, sizeof(contato), 1, arquivo_contatos) != 0) {
            if (contato.id_contato == id_contato)
                break;
            posicao_arquivo++;
        }

        //limpa o buffer
        while (getchar() != '\n');
        
         /* Ciro: não mostra os dados do contato (Interface: -0.5) */

        //pega os dados              
        printf("Nome: ");
        fgets(contato.nome, 50, stdin);
        //tira o enter do final
        contato.nome[strlen(contato.nome) - 1] = '\0'; //string termina com este caracter

        printf("Telefone: ");
        fgets(contato.telefone, 15, stdin);
        //tira o enter do final
        contato.telefone[strlen(contato.telefone) - 1] = '\0';

        printf("Email: ");
        fgets(contato.email, 30, stdin);
        //tira o enter do final
        contato.email[strlen(contato.email) - 1] = '\0';

        //posiciona o curso para fazer a alteraca
        fseek(arquivo_contatos, posicao_arquivo*sizeof(Contato), SEEK_SET); //volta para o inicio do arquivo

        //adiciona no arquivo
        fwrite(&contato, sizeof(contato), 1, arquivo_contatos);

        //fecha o arquivo
        fclose(arquivo_contatos);
    }
}

void consultar_contatos(int id_usuario) {
    //dados
    FILE* arquivo_contatos = fopen(ARQ_AGENDA, "rb");
    char nome[51];
    Contato contato;
    int flag_existem_contatos = 0;

    if (arquivo_contatos == NULL)
        printf("ERROR: nao foi possivel obter os dados do arquivo! Por favor, contacte o desenvolvedor.\n");
    else {
        //limpa o buffer
        while (getchar() != '\n');
        
        //pega os dados              
        printf("Nome: ");
        fgets(nome, 50, stdin);

        //tira o enter do final
        nome[strlen(nome) - 1] = '\0';

        //lista os contatos
        while (fread(&contato, sizeof(Contato), 1, arquivo_contatos) != 0) {
            //verifica se o contato pertence ao usuario
            if ((contato.id_usuario == id_usuario) && (strstr(contato.nome, nome) != NULL)) {
                printf("\n|ID Contato: %d | Nome: %s | Telefone: %s | E-mail: %s |",
                contato.id_contato, contato.nome, contato.telefone, contato.email);
                printf("\n------------------------------------------------------------------------------");
                flag_existem_contatos = 1;
            }
        }

        //exibe um aviso caso nao tenham contatos cadastrados
        if (!flag_existem_contatos)
            printf("\n\nAVISO: nao existem contatos cadastrados para este usuario.\n\n");
        else
            printf("\n\n");

        //fecha o arquivo
        fclose(arquivo_contatos);        
    }
}