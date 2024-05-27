

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

typedef enum { false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

float Efloat () { 

  float e = 1.0f;
  float facto = 1.0f;
  float vieux_e=0.0f;
  int n = 1;
  while ( e != vieux_e) 
  //e != vieux_e signifie qu'après le calcul de très petites valeurs, 
  //le compilateur pourrait ignorer ces différences,
  //faisant en sorte que la valeur précédente de e soit égale à la valeur suivante.
  {
    vieux_e = e;
    facto *= n;
    e += 1.0f / facto;
    n++;

  }
  return e;



 }

/*************************************************/

double Edouble () { 
  
  double e = 1.0;
  double facto = 1.0;
  double vieux_e=0.0;
  int n = 1;
  while ( e != vieux_e)
  //e != vieux_e signifie qu'après le calcul de très petites valeurs, 
  //le compilateur pourrait ignorer ces différences,
  //faisant en sorte que la valeur précédente de e soit égale à la valeur suivante.
  {
    vieux_e = e;
    facto *= n;
    e += 1.0f / facto;
    n++;

  }
  return e;
 }
  
/*************************************************/

long double Elongdouble () { 
  long double e
   = 1.0f;
  long double facto = 1.0f;
  long double vieux_e=0.0f;
  int n = 1;
  while ( e != vieux_e)
  //e != vieux_e signifie qu'après le calcul de très petites valeurs, 
  //le compilateur pourrait ignorer ces différences,
  //faisant en sorte que la valeur précédente de e soit égale à la valeur suivante.
  {
    vieux_e = e;
    facto *= n;
    e += 1.0f / facto;
    n++;

  }
  return e; }

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n) {
  float e = Efloat ();
  float y = e - 1.0f;
  printf("float y_0: %f\n", y);

  for (int i = 1 ; i < n ; i ++)
  //Répétez 30 fois et commencez avec i=1, car y0 nous a déjà été montré.
  {
    y = y * i -1.0f;
    printf("float y_%d: %f\n", i, y);
  }
}

/*************************************************/

void afficheYdouble (int n) 
{
  double e = Edouble();
  double y = e - 1.0;
  printf("double y_0: %lf\n", y);

  for (int i = 1 ; i < n ; i ++)
  //Répétez 30 fois et commencez avec i=1, car y0 nous a déjà été montré.
  {
    y = y * i -1.0f;
    printf("double y_%d: %lf\n", i, y);
  }

}

/*************************************************/

void afficheYlongdouble (int n) 
{
  long double e = Elongdouble  ();
  long double y = e - 1.0;
  printf("long double y_0: %Lf\n", y);

  for (int i = 1 ; i < n ; i ++)
  //Répétez 30 fois et commencez avec i=1, car y0 nous a déjà été montré.
  {
    y = y * i -1.0f;
    printf("long double y_%d: %Lf\n", i, y);
  }
}
//Il est évident que l'utilisation de long double permet
//d'afficher avec plus de précision de nombreux chiffres après la virgule.

/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/

//....LOURD ET MALADROIT....

double power_sup0(double x, long n) {
    if (n == 0) return 1.0;
    return x * power_sup0(x, n-1);
}

double power1 (double x, long n) 
{ 
  if (n == 0) return 1.0;
    if (n < 0) return 1.0 / power_sup0(x, -n);
    return power_sup0(x, n);
    
 }



   

/*************************************************/
// IT´ERATIF, PAR n-1
double power2a (double x, long n) {
  double res = 1; 
  double n_t= 0;
  if(n<0) 
    n_t=-n ;
  else n_t=n;
  for (size_t i = 0; i < n_t; i++)
{
  res = res* x;
}
  if(n<0) return 1/res;
   //En tenant compte du cas où x est négatif.
  else return res;
  }
/*************************************************/
 //IT´ERATIF, PAR n-1
double power2b (double x, long n) { 
  double res = 1;
  while (n>0)
  {
    res = res * x;
    n--;
  }
  return res;
   
 }


/*************************************************/
//RECURSIF TERMINAL AVEC SOUS-PROC ´ EDURE, PAR n-1
void pow3(double x, long n, double* r) {
    if (n == 0) {
        return;
    } else {
    // l'utilisation d'un pointeur permet à la fonction pow3 de modifier 
    //la variable locale result à l'intérieur de la fonction power3.
        *r = (*r) * x; 
        pow3(x, n-1, r);  
    }
}

double power3(double x, long n) {
    double result = 1.0;
    pow3(x, n, &result); 
    return result;
}
 

/*************************************************/
//RECURSIF TERMINAL AVEC SOUS-FONCTION, PAR n-1
double pow4(double x, long n, double r) {
    if (n == 0) {
        return r;
    }
    return pow4(x, n - 1, r * x);
}

double power4(double x, long n) {
    double r = 1.0;
    return pow4(x, n, r);
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m
//R´ECURSIF SIMPLE, PAR n/2, MAIS BOURDE
double power5 (double x, long n)
{
    if (n == 0)
         return 1 ;
    else if (n % 2 == 0)
    //Ici, on distingue si n est pair ou non. 
    
              return (power5(x,n/2)*power5(x,n/2)   ) ;
         else return (power5(x,n/2)*power5(x,n/2) *x) ;   
    ////Si n n'est pas pair, après power5(x, n/2) * power5(x, n/2), 
    //il faut multiplier par x lui-même, sans avoir besoin de diviser n par 2.
}

/*************************************************/
//RECURSIF SIMPLE, PAR n/2, OK
double power6(double x, long n) {
    if (n == 0) {
        return 1.0;
    } else {
        double y = power6(x, n / 2);
        if (n % 2 == 0) {  // n est pair
            return y * y;
        } else {  // n est impaire
            return y * y * x;
        }
    }
}


/*************************************************/
//R´ECURSIF SIMPLE, PAR n/2, VARIANTE, OK
double power7 (double x, long n) { 
  
  if (n == 0)
    return 1.0;
  else 
    if (n%2==0)//n est pair
      return power7(x*x,n/2);
    else //n est impair
      return power7(x*x,n/2) * x;
 }

/*************************************************/
//R´ECURSIF SIMPLE, PAR n/2, AVEC SOUS-FONCTION
double pow8(double x,long n,double r)
{
  if(n==0) 
    return r;
  else 
    if (n % 2 == 0) //n est pair
      return pow8(x*x,n/2, r);
    else // n est impair
      return pow8(x*x,n/2, r*x); 
}

double power8 (double x, long n) { 
  return  pow8(x,n,1.0);
  //Appelle la fonction récursive avec une valeur initiale de r égale à 1.0
}

/*************************************************/
void pow9(double x , long n, double *r) 
{
  if (n == 0)
      return;
  else 
      if (n % 2 != 0) // si n est impair
          *r = (*r) * x;
        //dans le pseudocode, r est en entrée-sortie (inout),
        //nous utilisons ici un pointeur pour modifier immédiatement la valeur de r plutôt que de copier une copie.
      pow9(x * x, n / 2, r);//si n est pair
      return ;
    
}
// Fonction principale pour calculer x à la puissance n
double power9 (double x, long n) 
{ 
    double res = 1.0;
    pow9(x, n, &res); //&res = r (pointeur)
    return res;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat
//ITERATIF, PAR n/2
double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}


/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/


int A1(int m, int n) { 
  if(m==0)
    return n+1;
  if(n==0)
    return A1(m-1,1);
  return A1(m-1,A1(m,n-1));
 }

int Ackermann1 (int m ) { 
  if (m ==0 )
    return 1;
  else
    return A1(m-1,1);
 }

/*************************************************/

int A2(int m, int n) { 
    if (m == 0) {
        return n + 1;
    }
    int r = 1;
    for (int i = 0; i <= n; i++) {
        r = A2(m - 1, r);
    }
    return r;
}
/*************************************************/

int Ackermann2 (int m) { 
 return A2(m, 1);
 }

/*************************************************/
// version 3 it´erative en m et r´ecursive en n

int A3(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    if (n == 0) {
        return A3(m - 1, 1);
    }
    return A3(m - 1, A3(m, n - 1));
}

int Ackermann3(int m) {
    return A3(m, 1);
}

/*************************************************/
// version 4  purement it´erative


int A4(int m, int n) {
    while (m != 0) {
        if (n == 0) {
            m--;
            n = 1;
        } else {
            n = A4(m, n - 1);
            m--;
        }
    }
    return n + 1;
}

int Ackermann4(int m) {
    return A4(m, 1);
}

/*************************************************/

// 主函数 Ackermann5

int A5(int m, int n) {
    {
    while (m != 0) {
        if (n == 0) {
            n = 1;
            m--;
        } else {
            n = A5(m, n - 1);
            m--;
        }
    }
    return n + 1;
}
}
int Ackermann5(int m) {
    return A5(m, 1);
}

   
   

/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}

/*************************************************/
int X_iterative(int n) {
  // X_iterative : Calcule la valeur de X de manière itérative
    int x = 2;
    for (int i = 1; i <= n; ++i) {
        x = x + log(x)/log(2);
    }
    return x;
}
/*************************************************/
// X_recursive : Calcule la valeur de X de manière récursive
// n : le nombre d'itérations à effectuer
int X_recursive(int n) {
    if (n == 0) return 2;
    return X_recursive(n - 1) + (int)log2(X_recursive(n - 1));
}

/*************************************************/
// X_recursive_aux : Fonction auxiliaire pour calculer X de manière récursive en utilisant une approche terminale
// n : le nombre d'itérations restantes
// acc : l'accumulateur qui garde la valeur courante de X
int X_recursive_aux(int n, int acc) {
    if (n == 0) return acc;
    return X_recursive_aux(n - 1, acc + (int)log2(acc));
}

int X_recursive_terminal(int n) {
    return X_recursive_aux(n, 2);
}

/*************************************************/
// X_recursive_terminal : Calcule la valeur de X de manière récursive terminale
// n : le nombre d'itérations à effectuer
void X_recursive_terminal_proc(int n, int acc, int *result) {
    if (n == 0) *result = acc;
    else X_recursive_terminal_proc(n - 1, acc + (int)log2(acc), result);
}
/*************************************************/


/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       double x ;
       long double y ;
       float z ;
       
       int cptx ;
  
       long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (false) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (false) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (false) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (false) {  
       

        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e2 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.40Lf \n", Elongdouble()) ; 
        
}

if (false) {  
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            afficheYlongdouble(30) ;
}
        
/******************    power     *******************************/

if (false) {  

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        
        for(i=0 ; i<=10 ; i++)
        printf("Power %d dit que power(2,10) vaut %.0lf \n", i, power(2,10,i) ) ;
        
        printf("\n") ;
      
}
// printf("power1(2, -3) = %f\n", power1(2.5, -3)); 
// printf("power2a(2, -3) = %f\n", power2a(2.5, -3)); 
// printf("power2b(2, 3) = %f\n", power2b(2.5, 3)); 
// printf("power3(2, 3) = %f\n", power3(1.5, 3)); 
// printf("power4(2, 3) = %f\n", power4(1.5, 3)); 
// printf("power5(2, 3) = %f\n", power5(1.5, 3)); 
// printf("power6(2, 3) = %f\n", power5(1.5, 3)); 
// printf("power7(2, 3) = %f\n", power7(1.5, 3)); 
// printf("power8(2, 3) = %f\n", power8(1.5, 3)); 
// printf("power9(2, 3) = %f\n", power9(1.5, 3)); 
if (false) {  

        i=5 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;
       
}
     
if (false) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

/******************    Ackermann    *******************************/
 /*            
if (true) { 

      for(i=1 ; i<=5 ; i++)  // numéro de version
      
      for(j=0 ; j<=5 ; j++)  // test de A(j,0) pour j de 0 à 5
      
      printf("Ack%d(%d) = %d \n", i, j, Ackermann(j,i)) ;
}
*/   
/***********************************************************************/
printf("Iterative: %d\n", X_iterative(100));
printf("Recursive: %d\n", X_recursive(4));
//printf("Recursive: %d\n", X_recursive(100));
printf("Recursive Terminal with Function: %d\n", X_recursive_terminal(4));
//*printf("Recursive Terminal with Function: %d\n", X_recursive_terminal(100));

int result;
X_recursive_terminal_proc(4, 2, &result);
printf("Recursive Terminal with Procedure: %d\n", result);
return 0;
}



