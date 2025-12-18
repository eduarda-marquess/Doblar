#include "login.h"
#include "Clic.h"
#include <stdio.h>
#include <string.h>

void cadastrarUsuario() {
    char user[50], pass[50];
    Clic_clearScreen();
    Clic_setFgColor(Clic_color_CIAN);
    Clic_printBox(40, 8);
    Clic_move(2, 5); printf("--- CADASTRO ---");
    
    Clic_move(4, 5); printf("Novo Usuario: "); scanf("%s", user);
    Clic_move(5, 5); printf("Senha: "); scanf("%s", pass);

    FILE *arq = fopen("usuarios.txt", "a");
    if (arq) {
        fprintf(arq, "%s %s 0\n", user, pass);
        fclose(arq);
        Clic_move(7, 5); printf("Cadastrado com sucesso!");
    }
    Clic_keyCapture();
}

bool realizarLogin(char *usuarioLogado) {
    char user[50], pass[50], fUser[50], fPass[50];
    int fScore;
    Clic_clearScreen();
    Clic_setFgColor(Clic_color_YELLOW);
    Clic_printBox(40, 8);
    Clic_move(2, 5); printf("--- LOGIN DOBLAR ---");

    Clic_move(4, 5); printf("Usuario: "); scanf("%s", user);
    Clic_move(5, 5); printf("Senha: "); scanf("%s", pass);

    FILE *arq = fopen("usuarios.txt", "r");
    if (!arq) return false;

    while (fscanf(arq, "%s %s %d", fUser, fPass, &fScore) != EOF) {
        if (strcmp(user, fUser) == 0 && strcmp(pass, fPass) == 0) {
            strcpy(usuarioLogado, fUser);
            fclose(arq);
            return true;
        }
    }
    fclose(arq);
    return false;
}

void exibirScores() {
    Clic_clearScreen();
    printf("--- RANKING DE VITORIAS ---\n");
    FILE *arq = fopen("usuarios.txt", "r");
    char user[50], pass[50];
    int score;
    if (arq) {
        while (fscanf(arq, "%s %s %d", user, pass, &score) != EOF) {
            printf("%s: %d vitorias\n", user, score);
        }
        fclose(arq);
    }
    printf("\nPressione qualquer tecla...");
    Clic_keyCapture();
}