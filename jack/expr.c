#include "defs.h"
#include "data.h"
#include "decl.h"
#include <stdio.h>
#include <stdlib.h>

static int OpPrec[] = {0, 10, 10, 20, 20, 0};

// Vérifie qu'on a une opération et renvoie sa prio
static int op_precedence(int tokentype) {
    int prec = OpPrec[tokentype];
    if (prec == 0) {
        fprintf(stderr, "Erreur de syntaxe ligne %d, token %d\n", Line, tokentype);
        exit(1);
    }
    return prec;
}

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

// // Renvoie un AST dont la racine est * ou /
// struct ASTnode *multiplicative_expr() {
//     struct ASTnode *left, *right;
//     int tokentype;

//     // On obtient le premier intlit normalement
//     left = primary();
    
//     tokentype = Token.token;
//     if (tokentype == T_EOF) {
//         return left;
//     }

//     while (tokentype == T_STAR || tokentype == T_SLASH) {

//         // On scanne le prochain
//         scan(&Token);
//         // On met a droite le prochain intlit (car mult haute priorité)
//         right = primary();

//         left = mkastnode(arithop(tokentype), left, right, 0);

//         tokentype = Token.token;
//         if (tokentype == T_EOF) break;
//     }

//     return left;
// }

// // Renvoie un AST donc la racine est + ou -
// struct ASTnode *additive_expr() {
//     struct ASTnode *left, *right;
//     int tokentype;

//     left = multiplicative_expr();

//     tokentype = Token.token;
//     if (tokentype == T_EOF) return left;

//     while (1) {
//         scan(&Token);
//         right = multiplicative_expr();

//         left = mkastnode(arithop(tokentype), left, right, 0);

//         tokentype = Token.token;
//         if (tokentype == T_EOF) break;
//     }

//     return left;
// }

// Renvoie un AST dont la racine est une op binaire
// ptp est la prio de l'ancien op
struct ASTnode* binexpr(int ptp) {
    struct ASTnode *left, *right;
    int tokentype;

    // Obtient l'intlit de gauche
    // Scan le prochain token dans la foulée
    left = primary();

    tokentype = Token.token;
    if (tokentype == T_EOF) {
        return left;
    }

    // On rentre dans l'arbre si la prio est plus forte que
    // la précédente
    while (op_precedence(tokentype) > ptp) {
        // On obtient le prochain token
        scan(&Token);

        // On construit le SAD avec notre prio actuelle
        right = binexpr(OpPrec[tokentype]);

        left = mkastnode(arithop(tokentype), left, right, 0);

        tokentype = Token.token;
        if (tokentype == T_EOF) {
            return left;
        }
    }

    return left;
}