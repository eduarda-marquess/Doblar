#include "Clic.h"
#include "login.h"
#include "jogo.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void exibirMenuPrincipal() {
    int opcao = 0;
    char usuarioAtivo[50] = "";
    bool logado = false;

    while (opcao != 5) {
        Clic_clearScreen();
        Clic_setFgColor(Clic_color_ORANGE);
        Clic_printBox(55, 16);
        
        Clic_move(2, 22);
        Clic_setFgColor(Clic_color_YELLOW);
        printf("DOBLAR GAME");

        Clic_move(4, 5); 
        if (logado) {
            Clic_setFgColor(Clic_color_GREEN);
            printf("STATUS: Logado como [%s]", usuarioAtivo);
            if (strcmp(usuarioAtivo, "duda123") == 0) {
                Clic_move(5, 5);
                printf(">> MODO MESTRE ATIVADO <<");
            }
        } else {
            Clic_setFgColor(Clic_color_RED);
            printf("STATUS: Modo Visitante");
        }

        Clic_setFgColor(Clic_color_WHITE);
        Clic_move(7, 10);  printf("1 - Jogar");
        Clic_move(8, 10);  printf("2 - Logar");
        Clic_move(9, 10);  printf("3 - Cadastro");
        Clic_move(10, 10); printf("4 - Score");
        Clic_move(11, 10); printf("5 - Sair");
        
        Clic_move(13, 10); Clic_setFgColor(Clic_color_CIAN);
        printf("Selecione: ");
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); 
            continue;
        }

        if (opcao == 1) iniciarJogo(usuarioAtivo, logado);
        else if (opcao == 2) logado = realizarLogin(usuarioAtivo);
        else if (opcao == 3) cadastrarUsuario();
        else if (opcao == 4) exibirScores();
    }
}