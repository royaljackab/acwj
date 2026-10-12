#pragma once

// Tokens
enum {
    T_EOF,
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_INTLIT
};

// AST noeuds
enum { 
    A_ADD,
    A_SUBTRACT,
    A_MULTIPLY,
    A_DIVIDE,
    A_INTLIT
};

// Token structure
struct token {
    int token;
    int intvalue;
};

// Abstract Syntax Tree structure
struct ASTnode {
    int op; // "Opération" à exécuté sur ce noeud
    struct ASTnode *left; // Enfants droits et gauches
    struct ASTnode *right;
    int intvalue; // Pour les intlit
};
