/*** CLIC is a library for creating Command Line Interfaces in the C language. ***/
/**
 * Paulo Regis M. Sousa
 */
#ifndef CLIC_H
#define CLIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <sys/ioctl.h>

#define Clic_symbol_HLINE "\u2501"
#define Clic_symbol_VLINE "\u2503"
#define Clic_symbol_CORNER_TL "\u250f"
#define Clic_symbol_CORNER_TR "\u2513"
#define Clic_symbol_CORNER_BL "\u2517"
#define Clic_symbol_CORNER_BR "\u251b"
#define Clic_symbol_ARROW "\u2192"
#define Clic_symbol_ARROW_RETURN "\u21b3"
#define Clic_symbol_T_SIDE_L "\u2523"
#define Clic_symbol_T_SIDE_R "\u252b"
#define Clic_symbol_T_UP "\u2533"
#define Clic_symbol_T_DOWN "\u253b"
#define Clic_symbol_CROSS "\u254b"
#define Clic_symbol_TREE_POINTS "\u2026"
#define Clic_symbol_SAD "\u0001f641"
#define Clic_symbol_SMILE "\u1f642"
#define Clic_symbol_BLOCK "\u2588"
#define Clic_symbol_DIAG "\u2572"
#define Clic_symbol_CDIAG "\u2571"

typedef enum Clic_color {
	Clic_color_BLACK     = 0,
	Clic_color_GRAY      = 8,
    Clic_color_RED       = 9,
	Clic_color_GREEN     = 10,
	Clic_color_YELLOW    = 11,
	Clic_color_MAGENTA   = 13,
	Clic_color_CIAN      = 14,
	Clic_color_WHITE     = 15,
	Clic_color_BLUE      = 39,
	Clic_color_ORANGE    = 208,
	Clic_color_LIGHTGRAY = 248
} Clic_color;

typedef enum Clic_key {
	Clic_key_TAB = 9,   
    Clic_key_ENTER = 10,
    Clic_key_SPACE = 32,
    Clic_key_NUMBER_0 = 48,
    Clic_key_NUMBER_9 = 57,
	Clic_key_ARROW_UP = 65,
	Clic_key_ARROW_DOWN = 66,
	Clic_key_ARROW_RIGHT = 67,
	Clic_key_ARROW_LEFT = 68,
	Clic_key_LETTER_A = 97,
	Clic_key_LETTER_Z = 122,
	Clic_key_DELETE = 127
} Clic_key;

/* ---------------- COLOR ---------------- */

/**
 * Redefine a cor do terminal para o padrão.
 */
#define Clic_resetColor() printf("\e[m")

/**
 * Define a cor do texto (primeiro plano) no terminal.
 * @param color Cor a ser usada no texto.
 */
#define Clic_setFgColor(color) printf("\e[38;5;%dm", color)

/**
 * Define a cor de fundo no terminal.
 * @param color Cor a ser usada como fundo.
 */
#define Clic_setBgColor(color) printf("\e[48;5;%dm", color)


/* ---------------- MOVIMENT ---------------- */

/**
 * Move o cursor para a linha e coluna especificadas.
 * @param line Número da linha.
 * @param column Número da coluna.
 */
#define Clic_move(line, column) printf("\e[%d;%dH", line, column)

/**
 * Move o cursor para cima um número especificado de linhas.
 * @param lines Número de linhas para mover para cima.
 */
#define Clic_moveUp(lines) printf("\e[%dA", lines)

/**
 * Move o cursor para baixo um número especificado de linhas.
 * @param lines Número de linhas para mover para baixo.
 */
#define Clic_moveDown(lines) printf("\e[%dB", lines)

/**
 * Move o cursor para a direita um número especificado de colunas.
 * @param columns Número de colunas para mover à direita.
 */
#define Clic_moveRight(columns) printf("\e[%dC", columns)

/**
 * Move o cursor para a esquerda um número especificado de colunas.
 * @param columns Número de colunas para mover à esquerda.
 */
#define Clic_moveLeft(columns) printf("\e[%dD", columns)

/**
 * Move o cursor para o início das próximas linhas.
 * @param lines Número de linhas para mover para baixo.
 */
#define Clic_moveDownBegin(lines) printf("\e[%dE", lines)

/**
 * Move o cursor para o início das linhas anteriores.
 * @param lines Número de linhas para mover para cima.
 */
#define Clic_moveUpBegin(lines) printf("\e[%dF", lines)

/**
 * Move o cursor para uma coluna específica.
 * @param column Número da coluna.
 */
#define Clic_moveToColumn(column) printf("\e[%dG", column)

/**
 * Move o cursor para o início da linha atual.
 */
#define Clic_moveToBegin() printf("\e[1G")

/**
 * Salva a posição atual do cursor.
 */
#define Clic_saveCursorPosition() printf("\e7")

/**
 * Restaura o cursor para a última posição salva.
 */
#define Clic_restoreCursorPosition() printf("\e8")


/* ---------------- CLEAR ---------------- */

/**
 * Limpa toda a tela do terminal.
 */
#define Clic_clearScreen() printf("\e[2J\e[1;1H")

/**
 * Limpa a linha atual do terminal.
 */
#define Clic_clearLine() printf("\e[2K")


/* ---------------- AUXILIARY ---------------- */

/**
 * Quebra a linha atual e move para a próxima.
 */
#define Clic_breakLine() printf("\n")

/**
 * Obtém a largura da janela do terminal.
 * @return Largura da janela em caracteres.
 */
int Clic_getScreenWidth();

/**
 * Obtém a altura da janela do terminal.
 * @return Altura da janela em caracteres.
 */
int Clic_getScreenHeight();

/**
 * Captura o código da tecla pressionada.
 * @return Código da tecla pressionada.
 */
int Clic_keyCapture();

/**
 * Move o cursor para a última linha e coluna do terminal.
 * Útil para corrigir problemas de desenho na tela.
 */
void Clic_fixDraw();


/* ---------------- PRINT ---------------- */

/**
 * Desenha um símbolo.
 * @param symbol Símbolo a ser desenhado.
 */
#define Clic_printSymbol(symbol) printf("%s", symbol)

/**
 * Desenha uma linha horizontal com largura especificada.
 * @param width Largura da linha.
 */
#define Clic_printHLine(width) for (int i=0; i<width; i++) Clic_printSymbol(Clic_symbol_HLINE)

/**
 * Desenha uma linha vertical com altura especificada.
 * @param height Altura da linha.
 */
#define Clic_printVLine(height) for (int i=0; i<height; i++) printf(Clic_symbol_VLINE "\e[1D\e[1B")

/**
 * Desenha uma linha horizontal de blocos.
 * @param width Largura da linha.
 */
#define Clic_printHBlockLine(width) for (int i=0; i<width; i++) printf(" ")

/**
 * Desenha uma linha vertical de blocos.
 * @param height Altura da linha.
 */
#define Clic_printVBlockLine(height) for (int i=0; i<height; i++) printf(" \e[1D\e[1B")

/**
 * Desenha uma caixa com largura e altura especificadas.
 * @param width Largura da caixa.
 * @param height Altura da caixa.
 */
void Clic_printBox(int width, int height);

#endif /* CLIC_H */