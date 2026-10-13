#include "defs.h"
#include <stdio.h>
#include <string.h>
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <stdlib.h>
#include <errno.h>

// Initialisation des variables globales
static void init() {
    Line = 1;
    Putback = '\n';
}

// Affiche un usage en cas d'erreur
static void usage(char* prog) {
    fprintf(stderr, "Usage: %s <inline>\n", prog);
    exit(1);
} 

// List of printable tokens
char *tokstr[] = {"+", "-", "*", "/", "intlit"};

int main(int argc, char* argv[]) {
    struct ASTnode *n;
    
    if (argc != 2) {
        usage(argv[0]);
    }

    if ((Infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Impossible d'ouvrir %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    if ((Outfile = fopen("out.s", "w")) == NULL) {
        fprintf(stderr, "Impossible de créer out.s: %s\n", strerror(errno));
        exit(1);
    }

    scan(&Token);
    n = binexpr(0);
    printf("Résultat final : %d\n", interpretAST(n));
    exit(0);
}