//
// Created by badetitou on 13/01/16.
//

#ifndef LEPENTE_MAIN_H
#define LEPENTE_MAIN_H

    #define NB_LIGNE 19
    #define NB_COLONNE 19
    int verificationEgalite(int plateau[NB_LIGNE][NB_COLONNE]);
    int  verificationGagner(int plateau[NB_LIGNE][NB_COLONNE], int coordX,int coordY,int joueurCourant);
    void afficherPlateau(int pateau[NB_LIGNE][NB_COLONNE]);
#endif //LEPENTE_MAIN_H
