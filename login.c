#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "login.h"
#include "Clic.h"

void cadastrarUsuario() {
    char user[50], pass[50];
    Clic_clearScreen();
    Clic_setFgColor(Clic_color_CIAN);
    Clic_printBox(45, 10);
    Clic_move(2, 5); printf("--- CADASTRO ---");
    Clic_move(4, 5); printf("Usuario: "); scanf("%s", user);
    Clic_move(5, 5); printf("Senha: "); scanf("%s", pass);
    FILE *arq = fopen("usuarios.txt", "a");
    if (arq) { fprintf(arq, "%s %s 0\n", user, pass); fclose(arq); }
    Clic_move(7, 5); printf("Sucesso! Tecla para voltar.");
    Clic_keyCapture();
}

bool realizarLogin(char *usuarioLogado) {
    char user[50], pass[50], fUser[50], fPass[50];
    int fScore;
    Clic_clearScreen();
    Clic_setFgColor(Clic_color_YELLOW);
    Clic_printBox(45, 10);
    Clic_move(2, 5); printf("--- LOGIN ---");
    Clic_move(4, 5); printf("Usuario: "); scanf("%s", user);
    Clic_move(5, 5); printf("Senha: "); scanf("%s", pass);
    FILE *arq = fopen("usuarios.txt", "r");
    if (!arq) return false;
    while (fscanf(arq, "%s %s %d", fUser, fPass, &fScore) != EOF) {
        if (strcmp(user, fUser) == 0 && strcmp(pass, fPass) == 0) {
            strcpy(usuarioLogado, fUser); fclose(arq); return true;
        }
    }
    fclose(arq); return false;
}

void exibirScores() {
    FILE *arq = fopen("usuarios.txt", "r");
    char user[50], pass[50];
    int score;

    // Garante que a tela esteja limpa e com cor visível
    Clic_clearScreen();
    Clic_resetColor();
    Clic_setFgColor(Clic_color_MAGENTA);
    
    printf("==========================================\n");
    printf("           RANKING DE JOGADORES           \n");
    printf("==========================================\n\n");
    
    Clic_setFgColor(Clic_color_WHITE);

    if (arq == NULL) {
        printf(" [!] Nenhum usuario cadastrado ainda.\n");
    } else {
        printf("  %-15s | %-10s\n", "JOGADOR", "VITORIAS");
        printf("  ----------------------------\n");

        // O loop lê: string(user) string(pass) inteiro(score)
        while (fscanf(arq, "%s %s %d", user, pass, &score) == 3) {
            printf("  %-15s | %-10d\n", user, score);
        }
        fclose(arq);
    }

    printf("\n\n==========================================\n");
    printf(" [Pressione qualquer tecla para voltar] ");
    
    // Limpeza de buffer para garantir que a tela não feche sozinha
    fflush(stdout);
    getchar(); // Captura o enter da opção 4
    Clic_keyCapture(); // Espera a nova tecla do usuário
}