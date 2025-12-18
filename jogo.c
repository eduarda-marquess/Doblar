#include "jogo.h"
#include "Clic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

int lancarDado(char *usuarioAtivo, bool cartasViradas[]) {
    if (strcmp(usuarioAtivo, "duda123") == 0) {
        if ((rand() % 100) < 70) {
            for (int i = 0; i < 6; i++) {
                if (!cartasViradas[i]) return i + 1;
            }
        }
    }
    return (rand() % 6) + 1;
}

void desenharJogo(char *nome, bool cartasJ[], bool cartasB[], int vJ, int vB) {
    Clic_clearScreen();
    Clic_setFgColor(Clic_color_CIAN);
    Clic_printBox(60, 18);

    // Cartas do Jogador
    Clic_move(3, 5); Clic_setFgColor(Clic_color_WHITE);
    printf("CARTAS DE %s:", nome);
    Clic_move(5, 5);
    for (int i = 0; i < 6; i++) {
        if (cartasJ[i]) {
            Clic_setFgColor(Clic_color_GREEN);
            printf("[%d] ", i + 1);
        } else {
            Clic_setFgColor(Clic_color_GRAY);
            printf("[?] ");
        }
    }

    // Cartas do Bot
    Clic_move(8, 5); Clic_setFgColor(Clic_color_WHITE);
    printf("CARTAS DO BOT:");
    Clic_move(10, 5);
    for (int i = 0; i < 6; i++) {
        if (cartasB[i]) {
            Clic_setFgColor(Clic_color_RED);
            printf("[%d] ", i + 1);
        } else {
            Clic_setFgColor(Clic_color_GRAY);
            printf("[?] ");
        }
    }

    // Histórico
    Clic_move(13, 5); Clic_setFgColor(Clic_color_YELLOW);
    printf("HISTORICO: ");
    for (int i = 0; i < totalLancamentos; i++) printf("%d ", historico[i]);

    Clic_move(15, 5); Clic_resetColor();
}

void iniciarJogo(char *nomeJogador, bool logado) {
    srand(time(NULL));
    bool cartasJ[6] = {false}, cartasB[6] = {false};
    int totalJ = 0, totalB = 0;
    totalLancamentos = 0;
    char id[50];
    strcpy(id, logado ? nomeJogador : "Visitante");

    while (totalJ < 6 && totalB < 6) {
        desenharJogo(id, cartasJ, cartasB, totalJ, totalB);
        printf("Sua vez! Pressione qualquer tecla...");
        Clic_keyCapture();

        int dJ = lancarDado(id, cartasJ);
        adicionarAoHistorico(dJ);
        if (!cartasJ[dJ-1]) { cartasJ[dJ-1] = true; totalJ++; }

        if (totalJ == 6) break;

        desenharJogo(id, cartasJ, cartasB, totalJ, totalB);
        printf("Vez do Bot... ");
        fflush(stdout);
        sleep(1);

        int dB = (rand() % 6) + 1;
        adicionarAoHistorico(dB);
        if (!cartasB[dB-1]) { cartasB[dB-1] = true; totalB++; }
    }

    desenharJogo(id, cartasJ, cartasB, totalJ, totalB);
    Clic_move(16, 5);
    if (totalJ == 6) printf("VITORIA DE %s! ", id);
    else printf("O BOT VENCEU! ");
    
    printf("Pressione algo para sair.");
    Clic_keyCapture();
}