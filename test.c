//
// Created by badetitou on 13/01/16.
//


#include "main.h"

int testEgalite(int plateau[NB_LIGNE][NB_COLONNE]){
    int i, j;
    for (i = 0;i<NB_LIGNE; ++i){
        for (j = 0;j<NB_COLONNE;++j){
            plateau[i][j] = 1;
        }
    }
    return verificationEgalite(plateau);
}