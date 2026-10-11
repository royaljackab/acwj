#include "data.h"
#include "defs.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Récupère le prochain caractère de l'input
static int next() {
    int c;

    if (Putback) {
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    if ('\n' == c) Line++;
    return c;
}

// Remettre un caractère non voulu
static void putback(int c) {
    Putback = c;
}

/**
 * Skip l'input qui ne nous interesse pas
 * ie espaces, newlines.
 * Renvoie le premier caractère a traiter
 */
static int skip() {
    int c;

    c = next();
    while (c == ' ' || c == '\n' || c == '\t' || c == '\f' || c == '\r') {
        c = next();
    }
    return c;
}

// Renvoie la position du caractère c
// dans la chaine s, ou -1 si non trouvé
static int chrpos(char* s, int c) {
    char *p;

    p = strchr(s, c);
    return p ? p-s : -1;
}

static int scanint(int c) {
    int k, val = 0;

    while ((k = chrpos("0123456789", c)) >= 0) {
        val = val*10 + k;
        c = next();
    }

    // On lit un caractère non-entier, on le remet
    putback(c);
    return val;
}

/**
 * Scan et renvoie le premier token trouvé dans l'input
 * Renvoie 1 si le token est valide, 0 s'il n'y a plus de tokens
 */
int scan(struct token *t) {
    int c;

    // Skip les espaces
    c = skip();

    // Match le token
    switch (c) {
        case EOF:
            return 0;
        case '+':
            t->token = T_PLUS;
            break;
        case '-':
            t->token = T_MINUS;
            break;
        case '*':
            t->token = T_STAR;
            break;
        case '/':
            t->token = T_SLASH;
            break;
        default:
            // Si c'est un entier, on enregistre
            if (isdigit(c)) {
                t->intvalue = scanint(c);
                t->token = T_INTLIT;
                break;
            }

            printf("Caractère %c non reconnu ligne %d\n", c, Line);
            exit(1);

    }

    // On trouve un token
    return 1;
}