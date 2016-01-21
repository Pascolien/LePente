//
// Created by badetitou on 09/01/2016.
//

#include <stdio.h>
#include <string.h>
#include "main.h"
#include "test.h"

typedef struct {
    int x;
    int y;
} Direction;

Direction directions[] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; // C'est valeur correspondent a  NORD | NORD-EST | EST | SUD-EST | SUD | SUD-OUEST | OUEST | NORD-OUEST


Direction victoire[5];


void initialiserPlateau(int[NB_LIGNE][NB_COLONNE]);
void demandeCoordonnees(int[NB_LIGNE][NB_COLONNE], int*,int*);
void afficherPlateauVictoire(int[NB_LIGNE][NB_COLONNE], int, int, int);
int estDansVictoire(int, int);

int main(int argc, char *argv[]){
    int joueurCourant = 1; // Joueur courant represente soit par un 0 (joueur 1) soit par un 1 (joueur 2)
    int resultat = 0; // Vaut 0 si le jeu continue, 1 si le joueur 1 a gagne, 2 si le joueur 2 a gagne, 3 si y a egalite
    int nbPrisesJ1 = 0, nbPrisesJ2 = 0, prise; // Nombres de prises par le joueur 1 puis le joueur 2
    int coordX, coordY; // Stocke les coordonnees entrees par le joueur courant
    int plateau[NB_LIGNE][NB_COLONNE];

    if (argc > 1) {
	    if (strcmp(argv[1], "--test") == 0) {
		    if (testEgalite(plateau))
			    printf("--> Egalite fonctionne\n");
		    else
			    printf("xx> Egalite NE fonctionne PAS\n");
		    if (testVictoireHorizontal(plateau)) 
			    printf("--> victoireHorizontal fonctionne\n");
		    else
			   printf("xx> victoireHorizontal NE fonctionne PAS\n");
		    if (testVictoireVertical(plateau))
			    printf("--> victoireVertical fonctionne\n");
		    else
			   printf("xx> victoireVertical NE fonctionne PAS\n");
		    if (testVictoireDiagoDroite(plateau))
			    printf("--> victoireDiagoDroite fonctionne\n");
		    else
			   printf("xx> victoireDiagoDroite NE fonctionne PAS\n");
		    if (testVictoireDiagoGauche(plateau))
			    printf("--> victoireDiagoGauche fonctionne\n");
		    else
			   printf("xx> victoireDiagoGauche NE fonctionne PAS\n");
            if (testPrise(plateau) == 16)
                printf("--> prise fonctionne\n");
            else
                printf("xx> prise NE fonctionne PAS\n");
	    } else {
		    printf("Usage : ./a.out\nParamétre : \n\t--test : permet de tester l'ensemble des fonctionnalitees du jeu\n");
	    }
    } else {


        initialiserPlateau(plateau); // Action permettant d'initialiser toutes les cases du plateau a  0

        while (resultat == 0 && nbPrisesJ1 < 10 && nbPrisesJ2 < 10) {
            afficherPlateau(plateau);
            printf("Nombre de prises du Joueur 1: %d\nNombre de prises du Joueur 2 : %d\n", nbPrisesJ1, nbPrisesJ2);
            demandeCoordonnees(plateau, &coordX, &coordY); // Demande des coordonnees valides a  l'utilisateur

            printf("--> coordX : %d, coordY %d\n", coordX, coordY);


            if (coordX != -1) { // Il n'y a pas d'abandon
                plateau[coordX][coordY] = joueurCourant;

                printf("--> Pion placé \n");

                resultat = verificationGagner(plateau, coordX, coordY, joueurCourant);

                printf("--> Verification Gagner OK \n");

                if (resultat == 0) {
                    printf("--> executerPrise : start\n");
                    prise = executerPrise(plateau, coordX, coordY, joueurCourant);
                    printf("--> executerPrise : done\n");
                    if (prise > 0) {
                        if (joueurCourant == 0) {
                            nbPrisesJ1 += prise;
                        } else {
                            nbPrisesJ2 += prise;
                        }
                    } else {
                        printf("--> VerificationEgalite : start\n");
                        resultat = verificationEgalite(plateau);
                        printf("--> VerificationEgalite : done\n");
			if (resultat != 0) {
				resultat = 3;
			}
		    }
		    joueurCourant = joueurCourant % 2 + 1;
		}
	    } else {
		    resultat = joueurCourant % 2 + 1;
	    }
	}
	if (coordX == -1){
		if (resultat == 1){
			afficherPlateau(plateau);
			printf("Le joueur 1 a gagne par abandon\n");
		} else { 
			afficherPlateau(plateau);
			printf("Le joueur 2 a gagne par abandon\n");
		}
	}
	else if (nbPrisesJ1 >= 10) {
		afficherPlateau(plateau);
		printf("Joueur 1 a gagne (nombre de pion pris : %d)\n", nbPrisesJ1);
	} else if (nbPrisesJ2 >= 10){
		afficherPlateau(plateau);
		printf("Joueur 2 a gagne (nombre de pion pris : %d)\n", nbPrisesJ2);
	} else if (resultat == 1) {
		afficherPlateauVictoire(plateau, coordX, coordY, resultat);
		printf("Joueur 1 a gagne\n");
	} else if (resultat == 2) {
		afficherPlateauVictoire(plateau, coordX, coordY, resultat);
		printf("Joueur 2 a gagne\n");
	} else {
		afficherPlateau(plateau);
		printf("Egalite\n");
	}
    }
    return 0;
}

void afficherPlateauVictoire(int plateau[NB_LIGNE][NB_COLONNE], int coordX, int coordY, int resultat){
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
				if (resultat  == 1 && estDansVictoire(coordX,coordY)){
					printf("\033[35mo  ");
				} else {
					printf("o  ");
				}
			} else {
				if (resultat  == 2 && estDansVictoire(coordX,coordY)){
					printf("\033[35mx  ");
				} else {
					printf("x  ");
				}
			}
			printf("\033[0m");
		}
		printf("\n");
	}

}

int estDansVictoire(int coordX, int coordY){
	int resultat = 0;
	int i = 0;
	while (resultat == 0 && i < 5){
		if (victoire[i].x == coordX && victoire[i].y == coordY){
			resultat = 1;
		}
	}
	return resultat;
}

int executerPrise(int plateau[NB_LIGNE][NB_COLONNE], int coordX, int coordY, int joueurCourant){
    int prise = 0,i, joueurAdverse = joueurCourant %2 + 1;
    for (i = 0;i<8;++i){
        if(coordX + directions[i].x * 3 >= 0 && coordX + directions[i].x * 3 < NB_LIGNE && coordY + directions[i].y * 3 >= 0 && coordY + directions[i].y * 3 < NB_COLONNE // On ne sort pas du tablea
           && plateau[coordX + directions[i].x * 3][coordY + directions[i].y * 3] == joueurCourant    // Le pion a  trois cases est notre pion
           && plateau[coordX + directions[i].x][coordY + directions[i].y] == joueurAdverse  //Que le premier pion et le second appartiennent a  l'adversaire
           && plateau[coordX + directions[i].x * 2][coordY + directions[i].y * 2] == joueurAdverse){ // Alors
            plateau[coordX + directions[i].x][coordY + directions[i].y] = 0;
            plateau[coordX + directions[i].x * 2][coordY + directions[i].y * 2] = 0;
            prise += 2;
        }
    }
    return prise;
}

int verificationEgalite(int plateau[NB_LIGNE][NB_COLONNE]){
    int i = 0, j, resultat;
    resultat = 1;
    while (resultat && i < NB_LIGNE){
        j = 0;
        while (resultat && j < NB_COLONNE){
            resultat = plateau[i][j] != 0;
            ++j;
        }
        ++i;
    }
    return resultat;
}



int verificationGagner(int plateau[NB_LIGNE][NB_COLONNE], int coordX, int coordY, int joueurCourant){
    int i = 0;
    int n = 0;
    victoire[0].x = coordX;
    victoire[0].y = coordY;
    while(i<4 && n < 5) {
        int j = 1;
        n = 1;
        while (n < 5
               && coordX + directions[i].x*j < NB_LIGNE
               && coordX + directions[i].x*j >= 0
               && coordY + directions[i].y*j < NB_COLONNE
               && coordY + directions[i].y*j >= 0
               && plateau[coordX + directions[i].x*j][coordY + directions[i].y*j] == joueurCourant) {
    		victoire[n].x = coordX + directions[i].x * j;
    		victoire[n].y = coordY + directions[i].y * j;
		++n;
		++j;
        }
        j = -1;
        while (n < 5
               && coordX + directions[i].x*j < NB_LIGNE
               && coordX + directions[i].x*j >= 0
               && coordY + directions[i].y*j < NB_COLONNE
               && coordY + directions[i].y*j >= 0
               && plateau[coordX + directions[i].x*j][coordY + directions[i].y*j] == joueurCourant) {
    		victoire[n].x = coordX + directions[i].x * j;
    		victoire[n].y = coordY + directions[i].y * j;
		++n;
		--j;
        }
        ++i;
    }
    if (n == 5){
        n = joueurCourant;
    } else {
        n = 0;
    }
    return n;
}


void demandeCoordonnees(int plateau[NB_LIGNE][NB_COLONNE], int* coordX,int* coordY){
	int testSscanf = 0;
    char buffer[255];
    do{
        printf("Donner les coordonnees de votre coup sous le format coordonneesX,coordonneesY : \n");
        fgets(buffer, 255, stdin);
        testSscanf = sscanf(buffer,"%d,%d",coordX,coordY);
        *coordX = *coordX - 1;
        *coordY = *coordY - 1;
    } while (testSscanf == 0 || (((*coordX<0 || *coordX>=NB_LIGNE) || (*coordY<0 || *coordY>=NB_COLONNE) || plateau[*coordX][*coordY] != 0) && (*coordX != -1 && *coordY != -1)));
}


void afficherPlateau(int plateau[NB_LIGNE][NB_COLONNE]){
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

void initialiserPlateau(int plateau[NB_LIGNE][NB_COLONNE]){
    int i, j;
    for (i = 0;i<NB_LIGNE;++i){
        for (j = 0;j<NB_COLONNE;++j){
            plateau[i][j] = 0;
        }
    }
}
