/*

========== Agenda Multiusuário ==========

*/

#include <stdio.h>
#include "agenda.h"
#include "usuario.h"

int main() {
    //dados
    int opcao = 0;

    while (true) {
        //menu inicial
        do {
            printf("\n---MENU---\n");
            printf("[1] - Primeiro Acesso.\n");
            printf("[2] - Acessar a Agenda.\n");
            printf("[3] - Sair.\n");
            printf("OPCAO: ");
            scanf("%d", &opcao);
            //error
            if (opcao < 1 || opcao > 3)
                printf("ERROR: opcao invalida! Tente novamente.\n");
        } while (opcao < 1 || opcao > 3);

        //primeiro acesso
        if (opcao == 1) {
            cadastrar_usuario();
        } 
        // acessar a agenda
        else if (opcao == 2) {
            autenticar_usuario();
        } 
        //sai do programa
        else {
            printf("\nObrigado por usar nosso sistema.\n");
            break;
        }
    }

    return 0;
}
