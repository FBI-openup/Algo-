// binôme : "Boyuan Zhang" <boyuan.zhang@universite-paris-saclay.fr>; 
//          "Xitong Li" <xitong.li@universite-paris-saclay.fr>;  

#include <stdio.h>
#include <stdlib.h>


/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then


//computer pour les 2 type de malloc
int malloc_cpt_liste = 0;     
int *cs = &malloc_cpt_liste;
int malloc_cpt_listedelistes = 0;
int *cps = &malloc_cpt_listedelistes;

typedef enum { FALSE, TRUE} bool;


/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
      //*cs -= 1;
      //*cps -= 1;
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

/*************************************************/
/*                                               */
/*          IMPLANTATION DE FONCTION             */
/*                                               */
/*************************************************/
//   LI XITONG ET ZHANG BOYUAN <MIAGE>


bool UnPlusDeuxEgalTrois(Liste L)
{ 
    int i1 = 0; // Premier élément de la liste
    int i2 = 0; // Deuxième élément de la liste
    int i3 = 0; // Troisième élément de la liste
    // Vérifie si la liste n'est pas vide et assigne la valeur du premier élément à i1
    if (!estVide(L)) i1 = premier(L);
    // Vérifie si le deuxième élément existe et l'assigne à i2
    if (!estVide(suite(L))) i2 = premier(suite(L));
    // Vérifie si le troisième élément existe et l'assigne à i3
    if (!estVide(suite(suite(L)))) i3 = premier(suite(suite(L)));
    // Retourne vrai si la somme des deux premiers éléments est égale au troisième
    return i1 + i2 == i3;
}

bool Croissante(Liste L)
{ 
    // Vérifie si la liste est vide ou si elle n'a qu'un seul élément
    if (estVide(L) || estVide(suite(L)))
        return TRUE; // Une liste vide ou avec un seul élément est considérée comme croissante
    else 
        // Compare le premier élément avec le deuxième
        if (premier(L) < premier(suite(L)))
            // Si le premier élément est inférieur au deuxième, continue la vérification avec le reste de la liste
            return Croissante(suite(L));
        else
            // Si le premier élément est supérieur ou égal au deuxième, la liste n'est pas croissante
            return FALSE;
}


int Recursive_NombreMemePosition(Liste L1, Liste L2)
{ 
    // Vérifie si l'une des listes est vide
    if (estVide(L1) || estVide(L2))
        return 0; // Si l'une des listes est vide, retourne 0
    else
        // Compare les premiers éléments des deux listes
        if (premier(L1) == premier(L2))
            // Si les premiers éléments sont égaux, incrémente le compteur et continue la récursion
            return 1 + Recursive_NombreMemePosition(suite(L1), suite(L2));
        else
            // Si les premiers éléments sont différents, continue la récursion sans incrémenter le compteur
            return Recursive_NombreMemePosition(suite(L1), suite(L2));
}


int iteratif_NombreMemePosition(Liste L1,Liste L2)
    { 
        int cpt=0;
        // Boucle tant que les deux listes ne sont pas vides
        while (!estVide(L1) && !estVide(L2))
        {
            if (premier(L1) == premier(L2))
            {
                cpt++;
                L2=suite(L2);
                L1=suite(L1);
            }
            else
            {
                L2=suite(L2);
                L1=suite(L1);
            }
        }
        return cpt;
    }   

// SF_NMP : Sous-fonction récursive pour calculer le nombre d'éléments égaux dans les mêmes positions
int  SF_NMP(Liste L1,Liste L2, int res)
{
    if (estVide(L1) || estVide(L2))
            return res;
    if (premier(L1) == premier(L2)) res++;
    return SF_NMP(suite(L1),suite(L2),res);             
}
// sous_fonction_NombreMemePosition : Fonction principale pour initier le calcul récursif
int sous_fonction_NombreMemePosition(Liste L1,Liste L2)
{   
    int res = 0;
    return SF_NMP(L1,L2,res);
    
} 

// SP_NMP : Sous-procédure récursive pour calculer le nombre d'éléments égaux dans les mêmes positions
void  SP_NMP(Liste L1,Liste L2,int *res)
{
    if (estVide(L1) || estVide(L2))
            return;
    if (premier(L1) == premier(L2))
        {
        (*res)++;
        }
    SP_NMP(suite(L1),suite(L2),res);
                
}
// sous_procedure_NombreMemePosition : Fonction principale pour initier le calcul récursif
int sous_procedure_NombreMemePosition(Liste L1,Liste L2)
{   
    int res = 0;
    SP_NMP(L1,L2,&res);
    return res;
} 


// AjouteDevantPremierZero : Ajoute un élément devant le premier zéro dans une liste
Liste AjouteDevantPremierZero(Liste L1, int x)
{
    // Vérifie si la liste est vide
    if (estVide(L1))
        return NULL; // Retourne NULL si la liste est vide
    else
        // Vérifie si le premier élément de la liste est zéro
        if (premier(L1) == 0)
            // Ajoute x devant le premier zéro trouvé et retourne la nouvelle liste
            return ajoute(x, L1);
        else
            // Si le premier élément n'est pas zéro, continue la recherche dans le reste de la liste
            return ajoute(premier(L1), AjouteDevantPremierZero(suite(L1), x));
}



Liste FonctVireDernier(Liste L1)
//recursif
{   

    if (estVide(L1)||estVide(suite(L1)))
        return NULL;
    else
        return ajoute(premier(L1),FonctVireDernier(suite(L1)));
} 



// FonctVireDernier_iter : Supprime le dernier élément d'une liste de manière itérative
Liste FonctVireDernier_iter(Liste L) {
    
    // Vérifie si la liste est vide ou si elle n'a qu'un seul élément
    if (L == NULL || L->suivant == NULL) {
        return NULL; // Retourne NULL dans ces cas
    }

    // Crée une nouvelle tête de liste
    Liste newHead = (Liste)malloc(sizeof(Bloc));
    if (newHead == NULL) {
        exit(EXIT_FAILURE); // Gestion d'erreur pour malloc
    }

    // Initialise les pointeurs pour parcourir les listes
    Liste currentNew = newHead;
    Liste currentOld = L;

    // Parcourt la liste jusqu'à l'avant-dernier élément
    while (currentOld->suivant != NULL) {
        currentNew->nombre = currentOld->nombre; // Copie l'élément
        currentOld = currentOld->suivant; // Avance dans l'ancienne liste

        // Si l'élément suivant n'est pas le dernier, crée un nouvel élément dans la nouvelle liste
        if (currentOld->suivant != NULL) {
            currentNew->suivant = (Liste)malloc(sizeof(Bloc));
            if (currentNew->suivant == NULL) {
                exit(EXIT_FAILURE); // Gestion d'erreur pour malloc
            }
            currentNew = currentNew->suivant;
        }
    }

    // Marque la fin de la nouvelle liste
    currentNew->suivant = NULL;

    return newHead; // Retourne la nouvelle liste sans le dernier élément
}





//------------------------------------------------------//
//recursif out
// ADDZ : Ajoute un élément x devant le dernier zéro trouvé dans une liste, en utilisant un pointeur booléen pour marquer si un zéro a déjà été trouvé
void ADDZ(Liste *L1, int x, bool *vu) {
    if (estVide(*L1)) {
        // Si la liste est vide, ajoute l'élément x et marque vu comme FALSE
        *L1 = ajoute(x, *L1);
    } else {
        // Traite d'abord le reste de la liste de manière récursive
        if (suite(*L1) != NULL) {
            ADDZ(&((*L1)->suivant), x, vu);
        }
        
        // Vérifie si le premier élément est zéro et si aucun zéro n'a été traité auparavant
        if (premier(*L1) == 0 && !*vu) {
            // Ajoute x devant le dernier zéro trouvé
            *L1 = ajoute(x, *L1);
            *vu = TRUE; // Marque qu'un zéro a été trouvé et traité
        }
    }
}

// AjouteDevantDernierZero : Ajoute un élément x devant le dernier zéro dans une liste
Liste AjouteDevantDernierZero(Liste L1, int x) {
    bool vu = FALSE; // Initialise un indicateur pour suivre si un zéro a été trouvé
    ADDZ(&L1, x, &vu); // Appelle la fonction récursive ADDZ
    return L1; // Retourne la liste modifiée
}




//------------------------------------------------------//
//recursif terminal
// AjouteDevantDernierZeroAux : Fonction auxiliaire pour ajouter un élément x devant le dernier zéro dans une liste
void AjouteDevantDernierZeroAux(Liste *L, Liste *precedent, Liste *dernierZeroPrecedent, int x) {
    if (estVide(*L)) {
        // Si on atteint la fin de la liste, effectue l'insertion
        if (dernierZeroPrecedent != NULL) {
            // Si un zéro a été trouvé, insère x devant ce zéro
            (*dernierZeroPrecedent)->suivant = ajoute(x, (*dernierZeroPrecedent)->suivant);
        } else {
            // Si aucun zéro n'a été trouvé dans la liste
            if (precedent == NULL) { // Si la liste est initialement vide
                empile(x, L);
            } else {
                // Insère x à la fin de la liste
                (*precedent)->suivant = ajoute(x, NULL);
            }
        }
        return;
    }

    // Met à jour le pointeur vers le précédent zéro si le nombre actuel est zéro
    if ((*L)->nombre == 0) {
        dernierZeroPrecedent = precedent;
    }

    // Appel récursif pour le reste de la liste
    AjouteDevantDernierZeroAux(&(*L)->suivant, L, dernierZeroPrecedent, x);
}

// AjouteDevantDernierZero_ter : Fonction principale pour ajouter un élément x devant le dernier zéro dans une liste
void AjouteDevantDernierZero_ter(Liste *L, int x) {
    // Appelle la fonction auxiliaire avec des pointeurs initiaux à NULL
    AjouteDevantDernierZeroAux(L, NULL, NULL, x);
}



//------------------------------------------------------//
//iteratif
// AjouteDevantDernierZero_iter : Ajoute un élément x devant le dernier zéro trouvé dans une liste, en utilisant une approche itérative
void AjouteDevantDernierZero_iter(Liste *L, int x) {
    // Si la liste est vide, ajoute simplement x et retourne
    if (estVide(*L)) {
        empile(x, L);
        return;
    }

    // Initialise les pointeurs pour parcourir la liste
    Liste courant = *L;
    Liste precedent = NULL;
    Liste dernierZeroPrecedent = NULL;

    // Parcourt la liste pour trouver la position du dernier zéro
    while (courant != NULL) {
        if (courant->nombre == 0) {
            dernierZeroPrecedent = precedent; // Met à jour le pointeur si un zéro est trouvé
        }
        precedent = courant; // Met à jour le pointeur précédent
        courant = courant->suivant; // Passe à l'élément suivant
    }

    // Si aucun zéro n'est trouvé et que le premier élément n'est pas zéro, ajoute x à la fin
    if (dernierZeroPrecedent == NULL && (*L)->nombre != 0) {
        precedent->suivant = ajoute(x, NULL);
    } else {
        // Sinon, insère x devant le dernier zéro trouvé
        if (dernierZeroPrecedent == NULL) { // Si le premier élément est zéro
            empile(x, L);
        } else {
            dernierZeroPrecedent->suivant = ajoute(x, dernierZeroPrecedent->suivant);
        }
    }
}




//----------------------------------------------------------------------

// Tic : Modifie une liste en supprimant le premier groupe de zéros et en ajoutant un zéro avant chaque groupe de non-zéros
void Tic(Liste *L1) {
    // Vérifie si la liste est vide
    if (estVide(*L1)) {
        return;
    }

    Liste temp = NULL; // Liste temporaire pour stocker les modifications
    bool firstZeroGroupPassed = FALSE; // Indicateur pour le premier groupe de zéros
    bool addZeroBeforeNonZero = TRUE;  // Indicateur pour ajouter un zéro avant les non-zéros

    // Parcourt la liste
    while (!estVide(*L1)) {
        int currentVal = premier(*L1); // Valeur actuelle

        // Si la valeur actuelle est zéro
        if (currentVal == 0) {
            // Si c'est le premier groupe de zéros
            if (!firstZeroGroupPassed) {
                // Marque le premier groupe de zéros comme passé
                firstZeroGroupPassed = TRUE;
                addZeroBeforeNonZero = FALSE; // Ne plus ajouter de zéro avant les non-zéros

                // Supprime tous les zéros consécutifs
                while (!estVide(suite(*L1))) {
                    if (premier(*L1) == 0)
                        depile(L1);
                    else
                        break;
                }
                continue;
            }
        } else {
            // Si c'est un non-zéro et qu'il faut ajouter un zéro avant
            if (addZeroBeforeNonZero == TRUE) {
                empile(0, &temp); // Ajoute un zéro dans la liste temporaire
            }
        }

        // Ajoute la valeur actuelle dans la liste temporaire
        empile(currentVal, &temp);

        // Supprime l'élément actuel de la liste originale
        depile(L1);
    }

    // Réinitialise la liste originale et la remplit avec les éléments de la liste temporaire
    initVide(L1);
    while (!estVide(temp)) {
        empile(premier(temp), L1);
        depile(&temp);
    }
}


/*************************************************/
/*                                               */
/*           Permutation                         */
/*                                               */
/*************************************************/

//définition de Type ListeDeListes
typedef struct OuterBloc {
    Liste innerHead;  //pointer vers le début de element-Liste 
    struct OuterBloc *suivant;
} OuterBloc;

typedef OuterBloc *ListeDeListes;


//Parce que estVide ne peut vérifier que si la liste est NULL, 
//nous écrivons un estVideListeDeListes pour vérifier si elle est NULL.
bool estVideListeDeListes(ListeDeListes l) {
    return l == NULL;
}

//meme pour premier
Liste premierListeDeListes(ListeDeListes L) {
    if (estVideListeDeListes(L)) return NULL;
    return L->innerHead;
}

//meme pour suite
ListeDeListes suiteListeDeListes(ListeDeListes L) {
    if (estVideListeDeListes(L)) return NULL;
    return L->suivant;
}
//Étant donné que seuls les ajouts nécessitent la méthode malloc, 
//nous devons intégrer le décompte dans les nouveaux ajouts, 
//et également écrire un ajout avec un compteur pour listeDelistes.
Liste ajouteListe(int x, Liste l) {
    *cs += 1;
    Liste nouveau = (Liste) malloc(sizeof(Bloc));
    if (nouveau == NULL) {
        exit(EXIT_FAILURE);//Si la mémoire ne peut pas être malloc, quittez le programme
    }
    nouveau->nombre = x;
    nouveau->suivant = l;
    return nouveau;
}
ListeDeListes ajouteListeDeListes(Liste innerList, ListeDeListes outerList) {
    *cps += 1;
    ListeDeListes nouveau = (ListeDeListes) malloc(sizeof(OuterBloc));

    if (nouveau == NULL) {
        //Si la mémoire ne peut pas être malloc, quittez le programme
        exit(EXIT_FAILURE);
    }
    nouveau->innerHead = innerList; 
    nouveau->suivant = outerList; 
    return nouveau;
 }


ListeDeListes depileListeDeListe(ListeDeListes *L){
    ListeDeListes temp = *L;
    *L = suiteListeDeListes(*L);
    free(temp);
}

/*
void empileListeDeListe(Liste l, ListeDeListes *L){
    *L = ajouteListeDeListes(l, *L);
}
*/

// Ajoute En Tete Toute Liste
// AETTL( 6, [[3,7,9],[2],[4,8],[]] ) -> [[6,3,7,9],[6,2],[6,4,8],[6]]
ListeDeListes AETTL(int x, ListeDeListes L) {
    if (estVideListeDeListes(L)) {
        return L;
    } else {
        return ajouteListeDeListes(ajouteListe(x, L->innerHead), AETTL(x, L->suivant));
    }
}

// Ajoute Toute Position
// ATP( 4, [5,7,9] ) ->[[4,5,7,9],[5,4,7,9],[5,7,4,9],[5,7,9,4]]
ListeDeListes ATP(int x, Liste L) {
    if (estVide(L)) {
        return ajouteListeDeListes(ajouteListe(x, NULL), NULL);
    } else {
        return ajouteListeDeListes(ajouteListe(x, L), AETTL(premier(L), ATP(x, suite(L))));
    }
} 


// Concat ( [a,b,c], [x,y,z] ) -> [a,b,c,x,y,z]
Liste Concat (Liste L1,Liste L2){
    if(estVide(L1)){
         return L2;
    }else if(estVide(L2)){
        return L1;
    }else return ajouteListe( premier(L1), Concat( suite(L1), L2 ) );
}

//Concat pour liste de liste
ListeDeListes ConcatListeDeListes (ListeDeListes L1,ListeDeListes L2){
    if(estVideListeDeListes(L1)) return L2;
    else return ajouteListeDeListes( premierListeDeListes(L1), ConcatListeDeListes(suiteListeDeListes(L1), L2));
}

 // Ajoute Toute Liste Toute Position
    // ATLTP( 4, [[5,7,9],[2],[3,8],[]] )
    // -> [[4,5,7,9],[5,4,7,9],[5,7,4,9],[5,7,9,4],[4,2],[2,4],[4,3,8],[3,4,8],[3,8,4],[4]]
ListeDeListes ATLTP (int x,ListeDeListes L) {
    if(estVideListeDeListes(L)) 
        return ajouteListeDeListes(NULL, NULL);
    else{
        //Liste tmp = premierListeDeListes(L);
        //depileListeDeListe(&L);
        //return ConcatListeDeListes(ATP(x, tmp), ATLTP(x, L));
        return ConcatListeDeListes(ATP(x,premierListeDeListes(L)),ATLTP(x,suiteListeDeListes(L)));
        }
    }

//n Permutations prend en argument un entier n et rend la liste des permutations de [1..n].
//Par exemple, Permutations(3) rendra [ [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1] ]
ListeDeListes Permutations(int n){
    if (n==0)return ajouteListeDeListes(NULL, NULL);
    else return ATLTP(n, Permutations (n-1));
}



/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/



void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}


void affiche_liste_de_liste_rec(ListeDeListes l){
    if(estVideListeDeListes(l)){
        printf("\n");
    }else{
        poup(premierListeDeListes(l));
        affiche_liste_de_liste_rec(suiteListeDeListes(l));
    }
}

int main(int argc, char** argv)
{
    // Liste l ;

    //     initVide (&l) ;

    //       poup(l) ;

    //          empile(4, &l) ;

    //       poup(l) ;

    //          empile(5, &l) ;
    //          empile(6, &l) ;
    //          empile(7, &l) ;
    //          empile(8, &l) ;
    //          empile(9, &l) ;

    //       poup(l) ;

        // VireDernier_rec  (&l) ;
        // VireDernier_iter (&l) ;
    //     depile(& l) ;

    //       poup(l) ;

    // VideListe(&l);
    
    Liste L = NULL;
    Liste L1 = NULL;
    Liste L2 = NULL;
    // test de Croissant
    if(FALSE){
        if (Croissante(L)) {
            printf("vrai\n");
        } 
        else {
            printf("faux\n");
        }
    }
    
    empile(3,&L); 
    empile(2,&L); 
    empile(1,&L); 

    empile(3,&L1); 
    empile(2,&L1); 
    empile(0,&L1); 
    empile(1,&L1); 


    empile(2,&L2); 
    empile(2,&L2); 

    affiche_iter(L);
    affiche_iter(L1);
    affiche_iter(L2);

    //test UnPlusDeuxEgalTrois
    if(FALSE){
        if (UnPlusDeuxEgalTrois(L)) {
            printf("1 + 2 == 3\n");
        } else {
            printf("1 + 2 != 3\n");
        }
        }
    //test NombreMemePosition 
    if(FALSE){
        printf("%d",Recursive_NombreMemePosition(L1,L));
        printf("%d",iteratif_NombreMemePosition(L1,L));
        printf("%d",sous_fonction_NombreMemePosition(L1,L2));
        printf("%d",sous_procedure_NombreMemePosition(L1,L));
    }
    // teste Tic et AjouteDevantDernierZero 
    if(FALSE){
        Liste maListe;
        initVide(&maListe);
        // creation de la liste [3, 7, 2, 0, 0, 0, 8, 9, 0, 0, 2, 1]
        empile(1, &maListe);
        empile(2, &maListe);
        empile(0, &maListe);
        empile(0, &maListe);
        empile(9, &maListe);
        empile(8, &maListe);
        empile(0, &maListe);
        empile(0, &maListe);
        empile(0, &maListe);
        empile(2, &maListe);
        empile(7, &maListe);
        empile(3, &maListe);
        
        printf("Liste avant Tic : ");
        affiche_iter(maListe);
        Liste maListe1 = NULL;
        empile(0, &maListe1);
        poup(FonctVireDernier_iter(maListe));
        
        Liste maListe2 = maListe;
        
        poup(maListe);
        Liste maListe3;
        initVide(&maListe3);
        // creation de la liste [3, 7, 2, 0, 0, 0, 8, 9, 0, 0, 2, 1]
        empile(1, &maListe3);
        empile(2, &maListe3);
        empile(0, &maListe3);
        empile(0, &maListe3);
        empile(9, &maListe3);
        empile(8, &maListe3);
        empile(0, &maListe3);
        empile(0, &maListe3);
        empile(0, &maListe3);
        empile(2, &maListe3);
        empile(7, &maListe3);
        empile(3, &maListe3);

        Tic(&maListe);
        poup(maListe);
        printf("Liste après Tic :");
        printf("expected :0 3 0 7 0 2 8 9 0 5 0 0 2 1 ");

        printf("Liste après AjouteDevantDernierZero : ");
        printf("expected : 3 7 2 0 0 0 8 9 0 5 0 2 1 ");
        printf("----------------------------------------");
        poup(maListe2);
        printf("resultat on trouve");
        poup(AjouteDevantDernierZero(maListe2,5));
        printf("----------------------------------------");
        poup(maListe3);
        AjouteDevantDernierZero_ter(&maListe3, 5);
        // AjouteDevantDernierZero_iter(&maListe3,5);
        poup(maListe3);
        // affiche_iter(AjouteDevantDernierZero_t(5, maListe3));
    }
    
    //test Permutations
    if(TRUE){
        printf("Permutations %d:\n", 2);
        ListeDeListes l = Permutations(2);
        affiche_liste_de_liste_rec(l);
        printf("\n");
        printf("nombre de malloc pour liste =  %d",malloc_cpt_liste);
        printf("\n");
        printf("nombre de malloc pour liste de liste = %d",malloc_cpt_listedelistes);
        printf("\n");
        }
}


