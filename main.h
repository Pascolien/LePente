//
// Created by badetitou on 13/01/16.
//

#ifndef LEPENTE_MAIN_H
#define LEPENTE_MAIN_H

    #define NB_LIGNE 19
    #define NB_COLONNE 19

    int verificationEgalite(int [NB_LIGNE][NB_COLONNE]);
    int verificationGagner(int [NB_LIGNE][NB_COLONNE], int ,int ,int );
    void afficherPlateau(int [NB_LIGNE][NB_COLONNE]);
    int executerPrise(int[NB_LIGNE][NB_COLONNE], int, int , int);

#endif //LEPENTE_MAIN_H
