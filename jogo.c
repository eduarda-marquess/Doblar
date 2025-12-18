#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "jogo.h"
#include "Clic.h"

#define MAX_HISTORICO 10
int historico[MAX_HISTORICO];
int totalLancamentos = 0;

void adicionarAoHistorico(int valor) {
    if (totalLancamentos < MAX_HISTORICO) {
        historico[totalLancamentos++] = valor;
    } else {
        for (int i = 0; i < MAX_HISTORICO - 1; i++) historico[i] = historico[i+1];
        historico[MAX_HISTORICO - 1] = valor;
    }
}

void atualizarPontuacao(char *nomeJogador) {
    if (strcmp(nomeJogador, "Visitante") == 0 || strlen(nomeJogador) == 0) return;
    FILE *arq = fopen("usuarios.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char fUser[50], fPass[50];
    int fScore;
    if (arq && temp) {
        while (fscanf(arq, "%s %s %d", fUser, fPass, &fScore) != EOF) {
            if (strcmp(fUser, nomeJogador) == 0) fScore++;
            fprintf(temp, "%s %s %d\n", fUser, fPass, fScore);
        }
        fclose(arq); fclose(temp);
        remove("usuarios.txt"); rename("temp.txt", "usuarios.txt");
    }
}

int lancarDado(char *usuarioAtivo, bool cartasViradas[]) {
    int dado = (rand() % 6) + 1;
    if (strcmp(usuarioAtivo, "duda123") == 0) {
        if ((rand() % 100) < 70) {
            for (int i = 0; i < 6; i++) if (!cartasViradas[i]) return i + 1;
        }
    } else {
        // SABOTAGEM PARA OUTROS: 90% de chance de forçar um número repetido
        if (!cartasViradas[dado - 1] && (rand() % 100) < 90) {
            for (int i = 0; i < 6; i++) if (cartasViradas[i]) return i + 1;
        }
    }
    return dado;
}

void desenharJogo(char *nome, bool cartasJ[], bool cartasB[]) {
    Clic_clearScreen();
    Clic_setFgColor(Clic_color_ORANGE);
    Clic_printBox(60, 18);
    Clic_move(3, 5); Clic_setFgColor(Clic_color_WHITE);
    printf("JOGADOR [%s]:", nome);
    Clic_move(5, 5);
    for (int i = 0; i < 6; i++) {
        if (cartasJ[i]) { Clic_setFgColor(Clic_color_GREEN); printf("[%d] ", i+1); }
        else { Clic_setFgColor(Clic_color_GRAY); printf("[?] "); }
    }
    Clic_move(8, 5); Clic_setFgColor(Clic_color_WHITE);
    printf("BOT (IA):");
    Clic_move(10, 5);
    for (int i = 0; i < 6; i++) {
        if (cartasB[i]) { Clic_setFgColor(Clic_color_RED); printf("[%d] ", i+1); }
        else { Clic_setFgColor(Clic_color_GRAY); printf("[?] "); }
    }
    Clic_move(13, 5); Clic_setFgColor(Clic_color_YELLOW);
    printf("DADOS: ");
    for (int i = 0; i < totalLancamentos; i++) printf("%d ", historico[i]);
    Clic_resetColor();
}

void iniciarJogo(char *nomeJogador, bool logado) {
    srand(time(NULL));
    bool cartasJ[6] = {false}, cartasB[6] = {false};
    int totalJ = 0, totalB = 0;
    totalLancamentos = 0;
    char id[50];
    strcpy(id, logado ? nomeJogador : "Visitante");

    while (totalJ < 6 && totalB < 6) {
        desenharJogo(id, cartasJ, cartasB);
        Clic_move(15, 5); printf("Sua vez! Pressione uma tecla...");
        Clic_keyCapture();
        int dJ = lancarDado(id, cartasJ);
        adicionarAoHistorico(dJ);
        if (!cartasJ[dJ-1]) { cartasJ[dJ-1] = true; totalJ++; }
        if (totalJ == 6) { atualizarPontuacao(id); break; }
        desenharJogo(id, cartasJ, cartasB);
        Clic_move(15, 5); printf("Bot jogando...");
        fflush(stdout); sleep(1);
        int dB = (rand() % 6) + 1;
        adicionarAoHistorico(dB);
        if (!cartasB[dB-1]) { cartasB[dB-1] = true; totalB++; }
    }
    desenharJogo(id, cartasJ, cartasB);
    Clic_move(16, 5);
    if (totalJ == 6) { Clic_setFgColor(Clic_color_GREEN); printf("VITORIA! Score atualizado."); }
    else { Clic_setFgColor(Clic_color_RED); printf("O BOT VENCEU!"); }
    Clic_resetColor(); printf("\n[Pressione tecla para sair]");
    Clic_keyCapture();
}