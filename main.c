//
// Created by badetitou on 09/01/2016.
//

#include <stdio.h>

#define NB_LIGNE 19
#define NB_COLONNE 19

typedef struct {
    int x;
    int y;
} Direction;

Direction directions[] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

void initialiser(int[NB_LIGNE][NB_COLONNE]);
void afficher(int[NB_LIGNE][NB_COLONNE]);
void demandeCoordonnees(int[NB_LIGNE][NB_COLONNE], int*,int*);
int verifEgalite(int[NB_LIGNE][NB_COLONNE]);
int verificationGagner(int[NB_LIGNE][NB_COLONNE], int, int , int);
int verifColonne(int[NB_LIGNE][NB_COLONNE], int, int , int);
int verifLigne(int[NB_LIGNE][NB_COLONNE], int, int , int);
int verifDiagoDroite(int[NB_LIGNE][NB_COLONNE], int, int , int);
int verifDiagoGauche(int[NB_LIGNE][NB_COLONNE], int, int , int);
int executerPrise(int[NB_LIGNE][NB_COLONNE], int, int , int);

int main(){
    int joueurCourant = 0;
    int resultat = 0;
    int nbPriseJ1 = 0, nbPriseJ2 = 0, prise;
    int coordX, coordY;

    int plateau[NB_LIGNE][NB_COLONNE];

    initialiser(plateau);
    while (resultat == 0){
        prise = 0; // Reinitialisation du nombre de prise faite pour le nouveau tour
        afficher(plateau);
        demandeCoordonnees(plateau, &coordX,&coordY);
        if (coordX != -1){
            plateau[coordX][coordY] = joueurCourant + 1;
            resultat = verificationGagner(plateau, coordX, coordY, joueurCourant + 1);
            if (resultat == 0){
                if ((prise = executerPrise(plateau, coordX, coordY, joueurCourant + 1))){
                    if (joueurCourant == 1){
                        nbPriseJ1 += prise;
                    } else {
                        nbPriseJ2 += prise;
                    }
                } else {
                    resultat = verifEgalite(plateau);
                    if (resultat != 0){
                        resultat = 3;
                    }
                }
            }
            joueurCourant = (joueurCourant+1)%2;
        } else {
            resultat = (joueurCourant+1)%2+1;
        }
    }
    afficher(plateau);
    if (resultat == 1){
        printf("Joueur 1 a gagne");
    } else if (resultat == 2){
        printf("Joueur 2 a gagne");
    } else {
        printf("Egalite");
    }
    return 0;
}

int executerPrise(int plateau[NB_LIGNE][NB_COLONNE], int coordX, int coordY, int joueurCourant){
    int prise = 0,i, joueurAdverse = joueurCourant %2 + 1;
    for (i = 0;i<8;++i){
        if(coordX + directions[i].x * 3 >= 0 && coordX + directions[i].x * 3 < NB_LIGNE && coordY + directions[i].y * 3 >= 0 && coordY + directions[i].y * 3 < NB_COLONNE // On ne sort pas du tableau
        && plateau[coordX + directions[i].x * 3][coordY + directions[i].y * 3] == joueurCourant    // Le pion à trois cases est notre pion
           && plateau[coordX + directions[i].x][coordY + directions[i].y] == joueurAdverse  //Que le premier pion et le second appartiennent à l'adversaire
           && plateau[coordX + directions[i].x * 2][coordY + directions[i].y * 2] == joueurAdverse){ // Alors
            plateau[coordX + directions[i].x][coordY + directions[i].y] = 0;
            plateau[coordX + directions[i].x * 2][coordY + directions[i].y * 2] = 0;
            prise += 2;
        }
    }
    return prise;
}

int verifEgalite(int plateau[NB_LIGNE][NB_COLONNE]){
    int i = 0, j = 0, resultat;
    resultat = 1;
    while (resultat && i < NB_LIGNE){
        while (resultat && j < NB_COLONNE){
            resultat = plateau[i][j] == 0;
        }
    }
    return resultat;
}



int verificationGagner(int plateau[NB_LIGNE][NB_COLONNE], int coordX, int coordY, int joueurCourant){
    int resultat = 0;
    if (verifColonne(plateau, coordX, coordY, joueurCourant) == 5
            || verifLigne(plateau, coordX, coordY, joueurCourant) == 5
            || verifDiagoDroite(plateau, coordX, coordY,joueurCourant) == 5
            || verifDiagoGauche(plateau,coordX,coordY,joueurCourant) == 5){
        resultat = joueurCourant;
    }
    return resultat;
}

int verifColonne(int plateau[NB_LIGNE][NB_COLONNE], int coordX, int coordY, int joueurCourant){
    int i = coordY + 1, n = 1;
    while ((n<5) && i < NB_LIGNE && plateau[coordX][i] == joueurCourant){
        ++n;
        ++i;
    }
    i=coordY - 1;
    while (n<5 && i >= 0 && plateau[coordX][i] == joueurCourant){
        ++n;
        --i;
    }
    return n;
}

int verifLigne(int plateau[NB_LIGNE][NB_COLONNE], int coordX, int coordY, int joueurCourant){
    int i = coordX + 1, n =1;
    while ((n<5) && i < NB_LIGNE && plateau[i][coordY] == joueurCourant){
        ++n;
        ++i;
    }
    i=coordX - 1;
    while (n<5 && i >= 0 && plateau[i][coordY] == joueurCourant){
        ++n;
        --i;
    }
    return n;
}

int verifDiagoDroite(int plateau[NB_LIGNE][NB_COLONNE], int coordX, int coordY, int joueurCourant){
    int i = 1, n = 1;
    while ((n<5) && coordX - i >= 0 && coordY + i < NB_LIGNE && plateau[coordX - i][coordY + i] == joueurCourant){
        ++n;
        ++i;
    }
    i= 1;
    while (n<5 && coordX + i <NB_COLONNE && coordY - i >=0 && plateau[coordX + i][coordY - i] == joueurCourant){
        ++n;
        ++i;
    }
    return n;
}

int verifDiagoGauche(int plateau[NB_LIGNE][NB_COLONNE], int coordX, int coordY, int joueurCourant){
    int i = 1, n = 1;
    while ((n<5) && coordX + i < NB_LIGNE && coordY - i >= 0 && plateau[coordX + i][coordY - i] == joueurCourant){
        ++n;
        ++i;
    }
    i= 1;
    while (n<5 && coordX - i >= 0 && coordY + i < NB_COLONNE && plateau[coordX - i][coordY + i] == joueurCourant){
        ++n;
        ++i;
    }
    return n;
}


void demandeCoordonnees(int plateau[NB_LIGNE][NB_COLONNE], int* coordX,int* coordY){
    do{
        printf("Donner les coordonnées de votre coup sous le format coordonneesX,coordonneesY : \n");
        scanf("%d,%d",coordX,coordY);
        *coordX = *coordX - 1;
        *coordY = *coordY - 1;
    } while (((*coordX<0 || *coordX>NB_LIGNE) || (*coordY<0 || *coordY>NB_COLONNE) || plateau[*coordX][*coordY] != 0) && (*coordX != -1 && *coordY != -1));
}


void afficher(int plateau[NB_LIGNE][NB_COLONNE]){
    int i, j;
    printf("   ");
    for (i=1;i<10;++i){
        printf("%d  ",i);
    }
    for (i=10;i<NB_COLONNE + 1;++i){
        printf("%d ",i);
    }
    printf("\n");
    for (i = 0; i < NB_LIGNE; ++i) {
        printf("%d ", i+1);
        if (i < 9){
            printf(" ");
        }
        for (j = 0; j < NB_COLONNE; ++j) {
            if (plateau[i][j] == 0){
                printf(".  ");
            } else if (plateau[i][j] == 1){
                printf("o  ");
            } else {
                printf("x  ");
            }
        }
        printf("\n");
    }
}

void initialiser(int plateau[NB_LIGNE][NB_COLONNE]){
    int i, j;
    for (i = 0;i<NB_LIGNE;++i){
        for (j = 0;j<NB_COLONNE;++j){
            plateau[i][j] = 0;
        }
    }
}