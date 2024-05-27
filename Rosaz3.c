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



image Blanc() {
    image img = (image)malloc(sizeof(bloc_image));
    img->quatre = false;
    img->hg = img->hd = img->bg = img->bd = NULL;
    return img;
}


image Noir() {
    return NULL; 
}


image Compose(image i0, image i1, image i2, image i3) {
    image img = (image)malloc(sizeof(bloc_image));
    img->quatre = true;
    img->hg = i0;
    img->hd = i1;
    img->bg = i2;
    img->bd = i3;
    return img;
}


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

void AffichageProfondeur(image img) {
    AffichageProfondeurBis(img, 0);
}


/*image Lecture() {
    char c = getchar();
    switch (c) {
        case 'o':
            return Blanc();
        case 'X':
            return Noir();
        case '(':
            {
                image i0 = Lecture();
                image i1 = Lecture();
                image i2 = Lecture();
                image i3 = Lecture();
                getchar
                return Compose(i0, i1, i2, i3);
            }
        default:
            return NULL; 
    }
}*/

//4 sous fonction pour memoriser le parcourir avant *
image LectureMemo() {
    char c = getchar();
    switch (c) {
        case 'o':
            return Blanc();
        case 'X':
            return Noir();
        default:
            return NULL; 
    }
}

image Lecture() {
    image i0, i1, i2, i3;

    i0 = LectureMemo();
    i1 = LectureMemo();
    i2 = LectureMemo();
    i3 = LectureMemo();

    char c = getchar();
     switch (c) {
        case 'o':
            return Blanc();
        case 'X':
            return Noir();
        case '*':
            return Compose(i0, i1, i2, i3);
        case '!':
            return NULL
    }

    return NULL;
}

//5
bool EstNoire(image img) {
    if (img == NULL) {
    return true;
    }
    if (!img->quatre) {
        return false;
    }
    return EstNoire(img->hg) && EstNoire(img->hd) && EstNoire(img->bg) && EstNoire(img->bd);
}

bool EstBlanche(image img) {
    if (img == NULL) {
    return false;
    }
    if (!img->quatre) {
    return true;
    }
    return EstBlanche(img->hg) && EstBlanche(img->hd) && EstBlanche(img->bg) && EstBlanche(img->bd);
}
//6
double Aire(image img) {
    if (img == NULL) return 1.0;

    if (!img->quatre) return 0.0;

    double aire_hg = Aire(img->hg);
    double aire_hd = Aire(img->hd);
    double aire_bg = Aire(img->bg);
    double aire_bd = Aire(img->bd);

    return (aire_hg + aire_hd + aire_bg + aire_bd) / 4.0;
}
//7
image TriangleBD(int p) {
    if (p == 0) {
        return Blanc();
    } else {
        image moins_profond = TriangleBD(p - 1);
        return Compose(moins_profond, moins_profond, moins_profond, Noir());
    }
}
//8
void Arrondit(image *img, int p) {
    if (img == NULL || *img == NULL) {
        return; // 为空或为黑色节点，不需要处理
    }

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


//9
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

//10
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


//11
int CompteDamiers(image img) {
    if (img == NULL || !img->quatre) {
        return 0;
    }

    bool tousDamiers = true;
    int count = 0;
    int sousArbres[4] = {
        CompteDamiers(img->hg),
        CompteDamiers(img->hd),
        CompteDamiers(img->bg),
        CompteDamiers(img->bd)
    };

    for (int i = 0; i < 4; i++) {
        if (sousArbres[i] == 0) {
            tousDamiers = false;
            break;
        }
        count += sousArbres[i];
    }
    if (tousDamiers) {
        count++; 
    }

    return count;
}

//12
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

    
    free(imgBlanc);
    free(imgCompose);

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
    //printf("Entrez une representation d'image quadtree (comme: o, X, (oXoX*), etc.):\n");

    //image img = Lecture();


    //printf("Affichage de l'image lue:\n");
    //Affichage(img);
    //printf("\n");


    //printf("Affichage de la profondeur de l'image lue:\n");
    //AffichageProfondeur(img);
    //printf("\n");///

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
   
    int nombreDamiers = CompteDamiers(img111);
    printf("le nombre de sous-arbres qui sont des damiers: %d\n", nombreDamiers);
}
