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



int testVictoireHorizontal(int plateau[NB_LIGNE][NB_COLONNE]){
	int i, j,  resultat = 0;
	for (i = 0;i<NB_LIGNE;++i){
		for (j = 0; j < NB_COLONNE;++j){
			plateau[i][j] = 0;
		}
	}
	for (i = 1;i< 6 ;++i){
		plateau[5][i-1] = 1;
		plateau[7][i-1] = 2;
		plateau[5][NB_COLONNE - i] = 1;
		plateau[7][NB_COLONNE - i] = 2;

	}
	if (verificationGagner(plateau, 5,0,1) 
			&& verificationGagner(plateau,5,1,1)
			&& verificationGagner(plateau,5,3,1)
			&& verificationGagner(plateau,5,NB_COLONNE-1,1)
			&& verificationGagner(plateau,5,NB_COLONNE-3,1)	
			
			&& verificationGagner(plateau,7,1,2)
			&& verificationGagner(plateau,7,3,2)
			&& verificationGagner(plateau,7,NB_COLONNE-1,2)
			&& verificationGagner(plateau,7,NB_COLONNE-3,2)
			
			){
				resultat = 1;
			}
	return resultat;
}

int testVictoireVertical(int plateau[NB_LIGNE][NB_COLONNE]){
	int i, j,  resultat = 0;
	for (i = 0;i<NB_LIGNE;++i){
		for (j = 0; j < NB_COLONNE;++j){
			plateau[i][j] = 0;
		}
	}
	for (i = 1;i< 6 ;++i){
		plateau[i-1][5] = 1;
		plateau[i-1][7] = 2;
		plateau[NB_LIGNE - i][5] = 1;
		plateau[NB_LIGNE - i][7] = 2;

	}
	if (verificationGagner(plateau, 0,5,1) 
			&& verificationGagner(plateau,1,5,1)
			&& verificationGagner(plateau,3,5,1)
			&& verificationGagner(plateau,NB_LIGNE - 1,5,1)
			&& verificationGagner(plateau,NB_LIGNE - 1,5,1)	
			
			&& verificationGagner(plateau,1,7,2)
			&& verificationGagner(plateau,3,7,2)
			&& verificationGagner(plateau,NB_LIGNE-1,7,2)
			&& verificationGagner(plateau,NB_LIGNE-3,7,2)
			
			){
				resultat = 1;
			}
	return resultat;
}

int testVictoireDiagoDroite(int plateau[NB_LIGNE][NB_COLONNE]){
	int i, j,  resultat = 0;
	for (i = 0;i<NB_LIGNE;++i){
		for (j = 0; j < NB_COLONNE;++j){
			plateau[i][j] = 0;
		}
	}
	for (i = 1;i< 6 ;++i){
		plateau[i-1][i-1] = 1;
		plateau[NB_LIGNE-i][NB_COLONNE-i] = 2;

	}
	if (verificationGagner(plateau, 0,0,1) 
			&& verificationGagner(plateau,1,1,1)
			&& verificationGagner(plateau,2,2,1)
			&& verificationGagner(plateau,3,3,1)
			&& verificationGagner(plateau,4,4,1)	
			
			&& verificationGagner(plateau,NB_LIGNE-1,NB_COLONNE-1,2)
			&& verificationGagner(plateau,NB_LIGNE-2,NB_COLONNE-2,2)
			&& verificationGagner(plateau,NB_LIGNE-3,NB_COLONNE-3,2)
			&& verificationGagner(plateau,NB_LIGNE-4,NB_COLONNE-4,2)
			&& verificationGagner(plateau,NB_LIGNE-5,NB_COLONNE-5,2)
			
			){
				resultat = 1;
			}
	return resultat;
}

int testVictoireDiagoGauche(int plateau[NB_LIGNE][NB_COLONNE]){
	int i, j,  resultat = 0;
	for (i = 0;i<NB_LIGNE;++i){
		for (j = 0; j < NB_COLONNE;++j){
			plateau[i][j] = 0;
		}
	}
	for (i = 1;i< 6 ;++i){
		plateau[i-1][NB_COLONNE-i] = 1;
		plateau[NB_LIGNE-i][i-1] = 2;

	}
	if (verificationGagner(plateau, 0,NB_COLONNE-1,1) 
			&& verificationGagner(plateau,1,NB_COLONNE-2,1)
			&& verificationGagner(plateau,2,NB_COLONNE-3,1)
			&& verificationGagner(plateau,3,NB_COLONNE-4,1)
			&& verificationGagner(plateau,4,NB_COLONNE-5,1)	
			
			&& verificationGagner(plateau,NB_LIGNE-1,0,2)
			&& verificationGagner(plateau,NB_LIGNE-2,1,2)
			&& verificationGagner(plateau,NB_LIGNE-3,2,2)
			&& verificationGagner(plateau,NB_LIGNE-4,3,2)
			&& verificationGagner(plateau,NB_LIGNE-5,4,2)
			
			){
				resultat = 1;
			}
	return resultat;
}

int testPrise(int plateau[NB_LIGNE][NB_COLONNE]){
	int i, j,  resultat = 0;

	for (i = 0;i<NB_LIGNE;++i){
		for (j = 0; j < NB_COLONNE;++j){
			plateau[i][j] = 0;
		}
	}
	for (i = 2;i<9;++i){
		for (j=2;j<9;++j){
			plateau[i][j] = 2;
		}
	}
	for (i = 15;i<19;++i){
		for (j=15;j<19;++j){
			plateau[i][j] = 2;
		}
	}
	plateau[5][5] = 1;
	plateau[5][8] = 1;
	plateau[8][8] = 1;
	plateau[2][8] = 1;
	plateau[2][5] = 1;
	plateau[8][5] = 1;
	plateau[2][2] = 1;
	plateau[5][2] = 1;
	plateau[8][2] = 1;
	resultat = executerPrise(plateau,5,5,1) + executerPrise(plateau,17,17,1);
	return resultat;
}
