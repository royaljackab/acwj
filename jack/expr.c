#include "defs.h"
#include "data.h"
#include "decl.h"
#include <stdio.h>
#include <stdlib.h>

int arithop(int tok) {
    switch (tok) {
        case T_PLUS:
            return A_ADD;
        case T_MINUS:
            return A_SUBTRACT;
        case T_STAR:
            return A_MULTIPLY;
        case T_SLASH:
            return A_DIVIDE;
        case T_INTLIT:
            return A_INTLIT;
        default:
            fprintf(stderr, "Caractère inconnu dans arithop() ligne %d\n", Line);
            exit(1);
    }
}

// Parse un facteur primaire et renvoie son noeud AST
// Scanne également le prochain token
static struct ASTnode *primary(void) {
    struct ASTnode *n;

    // Pour un INTLIT, on crée un noeuf feuille AST
    // et on scan le prochain token.
    // Sinon on envoie une erreur
    switch(Token.token) {
        case T_INTLIT:
            n = mkastleaf(A_INTLIT, Token.intvalue);
            scan(&Token);
            return n;
        default:
            fprintf(stderr, "Erreur de syntaxe ligne %d\n", Line);
            exit(1);
    }
}

// Renvoie un AST dont la racine est une opération binaire
struct ASTnode *binexpr() {
    struct ASTnode *n, *left, *right;
    int nodetype;

    // Récupère le premier littéral et scanne le suivant
    n = primary();

    // Si plus de tokens, on renvoie le gauche
    if (Token.token == EOF) {
        return left;
    }

    // Conversion du token en noeud type
    nodetype = arithop(Token.token);

    // Prochain token
    scan(&Token);

    // On obtient par récursion le sous-arbre droit
    right = binexpr();

    n = mkastnode(nodetype, left, right, 0);
    return n;
}
