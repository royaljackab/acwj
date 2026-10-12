#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

// Pour un AST, interprète son opération et renvoie la valeur finale
int interpretAST(struct ASTnode *n) {
    int leftval, rightval;

    // On obtient la valeur droite et gauche
    if (n->left) {
        leftval = interpretAST(n->left);
    }
    if (n->right) {
        rightval = interpretAST(n->right);
    }

    switch (n->op) {
        case A_ADD: return leftval + rightval;
        case A_SUBTRACT: return leftval - rightval;
        case A_MULTIPLY: return leftval * rightval;
        case A_DIVIDE: return leftval / rightval;
        case A_INTLIT: return n->intvalue;
        default:
            fprintf(stderr, "Opérateur AST inconnu %d\n", n->op);
            exit(1);
    }        
}