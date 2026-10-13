#pragma once

#include "defs.h"
#ifndef extern_
    #define extern_ extern
#endif

#include <stdio.h>

extern_ int          Line; // Compteur de ligne
extern_ int          Putback; // Caractère a retourner si on est allé trop loin
extern_ FILE        *Infile; // Pointeur vers le fichier
extern_ struct token Token; // Token le plus récent scanné
extern_ FILE         *Outfile;