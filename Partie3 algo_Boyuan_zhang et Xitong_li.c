// binôme : "Boyuan Zhang" <boyuan.zhang@universite-paris-saclay.fr>; 
//          "Xitong Li" <xitong.li@universite-paris-saclay.fr>;  


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef enum { false, true} bool;

typedef struct bloc_image
{ bool quatre ;
struct bloc_image *hg, *hd, *bg, *bd ;
} bloc_image ;
typedef bloc_image *image ;


// Crée une image blanche (un bloc sans sous-blocs).
image Blanc() {
    image img = (image)malloc(sizeof(bloc_image));
    img->quatre = false;
    img->hg = img->hd = img->bg = img->bd = NULL;
    return img;
}

// Crée une image noire (représentée par un pointeur NULL).
image Noir() {
    return NULL; 
}

// Compose une nouvelle image à partir de quatre sous-images données.
image Compose(image i0, image i1, image i2, image i3) {
    image img = (image)malloc(sizeof(bloc_image));
    img->quatre = true;
    img->hg = i0;
    img->hd = i1;
    img->bg = i2;
    img->bd = i3;
    return img;
}

// Affiche la structure d'une image en notation préfixée, 
//où "o" représente blanc, "X" noir, et "(...*)" un bloc composé.
void Affichage(image img) {
    if (img == NULL) {
        printf("X");
    } else if (!img->quatre) {
        printf("o");
    } else {
        printf("(");
        Affichage(img->hg);
        Affichage(img->hd);
        Affichage(img->bg);
        Affichage(img->bd);
        printf("*");
        printf(")");
    }
}

// Affiche la structure d'une image en indiquant la profondeur de chaque élément.

void AffichageProfondeurBis(image img, int profon) {
    if (img == NULL) {
        printf("X%d ", profon);
    } else if (!img->quatre) {
        printf("o%d ", profon);
    } else {
        AffichageProfondeurBis(img->hg, profon + 1);
        AffichageProfondeurBis(img->hd, profon + 1);
        AffichageProfondeurBis(img->bg, profon + 1);
        AffichageProfondeurBis(img->bd, profon + 1);
        
        printf("*%d",profon );
    }
}
// Fonction auxiliaire pour `AffichageProfondeurBis`, 
//initiant la profondeur à 0.
void AffichageProfondeur(image img) {
    AffichageProfondeurBis(img, 0);
}



// Détermine si une image est entièrement noire.

bool EstNoire(image img) {
    if (img == NULL) {
    return true;
    }
    if (!img->quatre) {
        return false;
    }
    return EstNoire(img->hg) && EstNoire(img->hd) && EstNoire(img->bg) && EstNoire(img->bd);
}
// Détermine si une image est entièrement blanche.

bool EstBlanche(image img) {
    if (img == NULL) {
    return false;
    }
    if (!img->quatre) {
    return true;
    }
    return EstBlanche(img->hg) && EstBlanche(img->hd) 
    && EstBlanche(img->bg) && EstBlanche(img->bd);
}
// Calcule l'aire noire d'une image, avec 1 représentant entièrement noire et 0 entièrement blanche.

double Aire(image img) {
    if (img == NULL) return 1.0;

    if (!img->quatre) return 0.0;

    double aire_hg = Aire(img->hg);
    double aire_hd = Aire(img->hd);
    double aire_bg = Aire(img->bg);
    double aire_bd = Aire(img->bd);

    return (aire_hg + aire_hd + aire_bg + aire_bd) / 4.0;
}
// Calcule l'aire noire d'une image, avec 1 représentant entièrement noire et 0 entièrement blanche.

image TriangleBD(int p) {
    if (p == 0) {
        return Blanc();
    } else {
        image moins_profond = TriangleBD(p - 1);
        return Compose(moins_profond, moins_profond, moins_profond, Noir());
    }
}
// Modifie une image pour arrondir son aire à noir ou blanc basé sur une profondeur spécifique.

void Arrondit(image *img, int p) {
    if (p <= 0) {
        
        double aire = Aire(*img);
       
        if (aire >= 0.5) {
            *img = Noir();
       } else {
        *img = Blanc(); 
        }
        } 
        else if ((*img)->quatre) {
        
        Arrondit(&((*img)->hg), p - 1);
        Arrondit(&((*img)->hd), p - 1);
        Arrondit(&((*img)->bg), p - 1);
        Arrondit(&((*img)->bd), p - 1);
    if ((EstNoire((*img)->hg) && EstNoire((*img)->hd) && EstNoire((*img)->bg) && EstNoire((*img)->bd)) ||
        (EstBlanche((*img)->hg) && EstBlanche((*img)->hd) && EstBlanche((*img)->bg) && EstBlanche((*img)->bd))) {
        bool allBlack = EstNoire((*img)->hg);
        *img = allBlack ? Noir() : Blanc();
    }
}
}

// Compare deux images pour déterminer si elles représentent le même dessin.

bool MemeDessin(image img1, image img2) {
    if (img1 == NULL && img2 == NULL) {
        return true;
    }
   
    if ((img1 == NULL && img2 != NULL) || (img1 != NULL && img2 == NULL)) {
        return false;
    }
    
    if (!img1->quatre && !img2->quatre) {
        return true;
    }
  
    if ((img1->quatre && !img2->quatre) || (!img1->quatre && img2->quatre)) {
        return false;
    }
   
    return MemeDessin(img1->hg, img2->hg) &&
           MemeDessin(img1->hd, img2->hd) &&
           MemeDessin(img1->bg, img2->bg) &&
           MemeDessin(img1->bd, img2->bd);
}

// Modifie deux images pour obtenir leur union et intersection.

void InterUnion(image *img1, image *img2) {
    if (*img1 == NULL || *img2 == NULL) {
        if (*img1 == NULL && *img2 != NULL) {
            *img1 = Blanc(); 
        } else if (*img2 == NULL && *img1 != NULL) {
            *img2 = *img1; 
            *img1 = Blanc(); 
        }
        return;
    }

    if (!(*img1)->quatre && !(*img2)->quatre) {
        return;
    }

    if ((*img1)->quatre && !(*img2)->quatre) {
        *img2 = Compose(Blanc(), Blanc(), Blanc(), Blanc());
    } else if (!(*img1)->quatre && (*img2)->quatre) {
        *img1 = Compose(Blanc(), Blanc(), Blanc(), Blanc());
    }
   
    InterUnion(&((*img1)->hg), &((*img2)->hg));
    InterUnion(&((*img1)->hd), &((*img2)->hd));
    InterUnion(&((*img1)->bg), &((*img2)->bg));
    InterUnion(&((*img1)->bd), &((*img2)->bd));
}

//question 4 version1
// Lit une image à partir de l'entrée 
image StrToImage(char* str , int* i){
    char s=str[*i];
    switch (s) {
        case 'o':
            *i = *i -1;
            return Blanc();
        case 'X':
        *i = *i -1;
            return Noir(); 
        case '*':
            
            *i = *i -1;
            image i3 = StrToImage(str,i);
            image i2 = StrToImage(str,i);
            image i1 = StrToImage(str,i);
            image i0 = StrToImage(str,i);;
            return Compose(i0, i1, i2, i3);
        
        default:
            printf("input false!");
            return NULL; 
        }

    
}
    //int len=strlen(str);
    /*for(int i=len-1;i>0 ;i--){
            s=str[i]
            switch (s) {
                case 'o':
                    return Blanc();
                case 'X':
                    return Noir();
                case '*':
                    {
                        image i0 = Lecture();
                        image i1 = Lecture();
                        image i2 = Lecture();
                        image i3 = Lecture();
                        return Compose(i0, i1, i2, i3);
                }
            default:
                return NULL; 
        }
}*/
image Lecture() {
    char c = getchar();
    char str[100] = "";
    int i= 0;
    while(c != '!'){
        str[i] =c;
        c = getchar();
        i++;
    }
    str[i] = '\0';
    printf("%s\n",str);
    i = i - 1;
    return StrToImage(str,&i);
    }
    
    



// Détermine si une image représente un damier et calcule sa hauteur.

int EstDamier(image img, int *hauteur) {
    if (img == NULL) {
        return 0; 
    }
    
    if (!img->quatre) {
        return 0; 
    }

    if (img->hg != NULL && img->hg->quatre == false && // o
        img->hd == NULL && img->bg == NULL && // XX
        img->bd != NULL && img->bd->quatre == false) { // o
        *hauteur = 1;
        return 1;
    }

    int hauteurHg, hauteurHd, hauteurBg, hauteurBd;
    int damierHg = EstDamier(img->hg, &hauteurHg);
    int damierHd = EstDamier(img->hd, &hauteurHd);
    int damierBg = EstDamier(img->bg, &hauteurBg);
    int damierBd = EstDamier(img->bd, &hauteurBd);

    if (damierHg && damierHd && damierBg && damierBd &&
        hauteurHg == hauteurHd && hauteurHg == hauteurBg && hauteurHg == hauteurBd) {
        *hauteur = hauteurHg + 1;
        return 1;
    }

    return 0;
}

int CompteDamiers(image img) {
    if (img == NULL) {
        return 0;
    }

    int hauteur = 0;
    if (EstDamier(img, &hauteur)) {
        return 1 + CompteDamiers(img->hg) + CompteDamiers(img->hd) +
                   CompteDamiers(img->bg) + CompteDamiers(img->bd);
    }

    return CompteDamiers(img->hg) + CompteDamiers(img->hd) +
           CompteDamiers(img->bg) + CompteDamiers(img->bd);
}




int main() {
    
    image imgBlanc = Blanc();
    image imgNoir = Noir();
    image imgCompose = Compose(imgBlanc, imgNoir, imgBlanc, imgNoir);
    image imgCompose1 = Compose(imgBlanc, imgBlanc, imgBlanc, imgNoir);

    
    printf("Affichage:\n");
    Affichage(imgCompose);
    printf("\n");

    
    printf("AffichageProfondeur:\n");
    AffichageProfondeur(imgCompose);
    printf("\n");

    if (EstBlanche(imgBlanc)) {
    printf("L'image est blanche.\n");
    } else {
    printf("L'image n'est pas blanche.\n");
    }


    if (EstNoire(imgBlanc)) {
        printf("L'image est noire.\n");
    } else {
        printf("L'image n'est pas noire.\n");
    }
    
    printf("Entrez une representation d'image quadtree (comme: o, X, (oXoX*), etc.):\n");
    //test fonction 4
    image img = Lecture();


    printf("Affichage de l'image lue:\n");
    Affichage(img);
    printf("\n");


    printf("Affichage de la profondeur de l'image lue:\n");
    AffichageProfondeur(img);
    printf("\n"); 

    printf("(ex;o, X, (oXoX*), etc.):\n");
    image imG = Lecture();

    printf("le graphique est:\n");
    Affichage(imG);
    printf("\n");



    image img1 = NULL; 
    printf("Aire(img1) = %f (approcher a 1.0)\n", Aire(img1));

    image img2 = imgBlanc; 
    printf("Aire(img2) = %f (approcher a 0)\n", Aire(img2));
  

    image img3 = imgCompose1; 
    printf("Aire(img3) = %f (approcher a 0.25)\n", Aire(img3));
    
    for (int p = 0; p <= 3; p++) {
        image img = TriangleBD(p);
        printf("TriangleBD(%d):\n", p);
        Affichage(img);
        printf("\n");
        Aire(img); 
        
    }
    image imgTest = Compose(Compose(Noir(), Blanc(), Noir(), Noir()),
    Compose(Noir(), Blanc(), Blanc(), Noir()),
    Compose(Blanc(), Blanc(), Noir(), Blanc()),
    Compose(Noir(), Blanc(), Noir(), Noir()));

    printf("image initial:\n");
    Affichage(imgTest);
    printf("\n");

  
    Arrondit(&imgTest, 2);

    printf("image d'amelioreration:\n");
    Affichage(imgTest);
    printf("\n");

    image img11 = Compose(Noir(), Compose(Blanc(), Blanc(), Blanc(), Blanc()), Blanc(), Noir());
    image img22 = Compose(Compose(Noir(), Noir(), Noir(), Noir()), Blanc(), Noir(), Compose(Blanc(), Blanc(), Blanc(), Blanc()));

    if (MemeDessin(img11, img22)) 
    {
    printf("meme dessin\n");
    } else {
    printf("les deux sont differents");
    }

   
    image img111 = Compose(Blanc(), Noir(), Compose(Noir(), Blanc(), Noir(), Blanc()), Noir());
    image img222 = Compose(Noir(), Compose(Blanc(), Noir(), Blanc(), Noir()), Blanc(), Noir());

    printf("initial image1:\n");
    Affichage(img111);
    printf("\n");
    
    printf("initial image2:\n");
    Affichage(img222);
    printf("\n");

    InterUnion(&img111, &img222);

    printf("jiao image1:\n");
    Affichage(img111);
    printf("\n");

    printf("bing image2:\n");
    Affichage(img222);
    printf("\n");
    return 0;
   

    image img20 = Compose(Blanc(), Noir(), Noir(), Blanc());

    image img4 = Compose(
                Compose(Blanc(), Noir(), Noir(), Blanc()),
                Compose(Blanc(), Noir(), Noir(), Blanc()),
                Compose(Blanc(), Noir(), Noir(), Blanc()),
                Compose(Blanc(), Noir(), Noir(), Blanc())
            );
    int count = CompteDamiers(img4);
    printf("Number of checkerboards: %d\n", count);

return 0;

}
