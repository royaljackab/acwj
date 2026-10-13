#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

// Pour un AST, génère récursivement
// du code assembleur
static int genAST(struct ASTnode *n) {
    int leftreg, rightreg;

    // Valeurs droites et gauches
    if (n->left) leftreg = genAST(n->left);
    if (n->right) rightreg = genAST(n->right);

    switch(n->op) {
        case A_ADD: return cgadd(leftreg, rightreg);
        case A_SUBTRACT: return cgsub(leftreg,rightreg);
        case A_MULTIPLY: return cgmul(leftreg,rightreg);
        case A_DIVIDE: return cgdiv(leftreg,rightreg);
        case A_INTLIT: return cgload(n->intvalue);
        default:
            fprintf(stderr, "Opérateur AST inconnu %d\n", n->op);
            exit(1);
    }
}

void generatecode(struct ASTnode *n) {
    int reg;

    cgpreamble();
    reg = genAST(n);
    cgprintint(reg);
    cgpostamble();
}