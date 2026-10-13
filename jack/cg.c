#include "defs.h"
#include "data.h"
#include "decl.h"
#include <stdlib.h>
#include <stdio.h>

// Tableau des registres disponibles
// et de leurs noms
static int freereg[4];
static char *reglist[4] = {"%r8", "%r9", "%r10", "%r11"};

// Mettre tous les registres libres
void freeall_registers() {
    freereg[0] = freereg[1] = freereg[2] = freereg[3] = 1;
}

// Alloue un registre libre. Renvoie l'id du
// reg. Meurs si aucun libre
static int alloc_register() {
    for (int i=0; i<4; i++) {
        if (freereg[i]) {
            freereg[i] = 0;
            return i;
        }
    }
    fprintf(stderr, "Aucun registre disponible!\n");
    exit(1);
}

// Libère un registre
// Erreur si déjà libre
static int free_register(int reg) {
    if (freereg[reg] != 0) {
        fprintf(stderr, "Erreur pour libérer le registre %d\n", reg);
        exit(1);
    }
    freereg[reg] = 1;
}

// Print out the assembly preamble
void cgpreamble()
{
  freeall_registers();
  fputs(
	"\t.text\n"
	".LC0:\n"
	"\t.string\t\"%d\\n\"\n"
	"printint:\n"
	"\tpushq\t%rbp\n"
	"\tmovq\t%rsp, %rbp\n"
	"\tsubq\t$16, %rsp\n"
	"\tmovl\t%edi, -4(%rbp)\n"
	"\tmovl\t-4(%rbp), %eax\n"
	"\tmovl\t%eax, %esi\n"
	"\tleaq	.LC0(%rip), %rdi\n"
	"\tmovl	$0, %eax\n"
	"\tcall	printf@PLT\n"
	"\tnop\n"
	"\tleave\n"
	"\tret\n"
	"\n"
	"\t.globl\tmain\n"
	"\t.type\tmain, @function\n"
	"main:\n"
	"\tpushq\t%rbp\n"
	"\tmovq	%rsp, %rbp\n",
  Outfile);
}

// Print out the assembly postamble
void cgpostamble()
{
  fputs(
	"\tmovl	$0, %eax\n"
	"\tpopq	%rbp\n"
	"\tret\n",
  Outfile);
}

// Enregistre un intlit sur un registre
// Renvoie le num du reg
int cgload(int value) {
    int r = alloc_register();
    fprintf(Outfile, "\tmovq\t$%d, %s\n", value, reglist[r]);
    return r;
}

int cgadd(int r1, int r2) {
    fprintf(Outfile, "\taddq\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r1);
    return r2;
}

int cgsub(int r1, int r2) {
    fprintf(Outfile, "\tsubq\t%s, %s\n", reglist[r2], reglist[r1]);
    free_register(r2);
    return r1;
}

int cgmul(int r1, int r2) {
    fprintf(Outfile, "\timulq\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r1);
    return r2;
}

int cgdiv(int r1, int r2) {
    fprintf(Outfile, "\tidivq\t%s, %s\n", reglist[r2], reglist[r1]);
    free_register(r2);
    return r1;
}