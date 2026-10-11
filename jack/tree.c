#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

// Construit et renvoie un noeud AST générique
struct ASTnode *mkastnode(int op, struct ASTnode* left, struct ASTnode *right, int intvalue) {
    struct ASTnode *n;

    // Allocation d'un nouveau noeud
    n = (struct ASTnode*) malloc(sizeof(struct ASTnode));
    if (n == NULL) {
        fprintf(stderr, "Impossible de malloc dans mkastnode()\n");
        exit(1);
    }

    n->op = op;
    n->left = left;
    n->right = right;
    n->intvalue = intvalue;

    return n;
}

// Construit et renvoie un noeud AST feuille
struct ASTnode *mkastleaf(int op, int intvalue) {
    return mkastnode(op, NULL, NULL, intvalue);
}

// Construit et renvoie un noeud AST avec un seul enfant
struct ASTnode* mkastunary(int op, struct ASTnode *left, int intvalue) {
    return mkastnode(op, left, NULL, intvalue);
}