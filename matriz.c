/**********************************************************************
* Baseado no código disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* Aqui se implementa o número do tipo "MATRIZ"
*
* numero.h definiu a interface do "número_t virtual"
* que é usada aqui
* ********************************************************************/
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "matriz.h"

static  Numero_pt copia_ (Numero_t const * const  me);

static  Numero_pt atribui_ (Numero_t const * const  me,
							         Numero_t       * const  outro) ;

static  Numero_pt soma_  (Numero_t const * const  me,
								   Numero_t const * const  outro,
							       Numero_t       * const  res);

static  Numero_pt subt_  (	Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt mult_  ( Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt divd_  ( Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt ac_soma_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_subt_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_mult_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_divd_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  int	compara_ 	(Numero_t const * const  me,
							 Numero_t const * const  outro);

static  char * imprime_  (Numero_t const * const  me);

static  void destroi_ (Numero_t   *   me);



/*---------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de MeuDouble*
 * -------------------------------------------------------------------*/
static  Matriz_pt Copia_ (Matriz_t const * const  me);

static  Matriz_pt Atribui_ (Matriz_t const * const  me,
							     Matriz_t       * const  outro) ;

static  Matriz_pt Soma_  (Matriz_t const * const  me,
							   Matriz_t const * const  outro,
							   Matriz_t       * const  res);

static  Matriz_pt Subt_  (Matriz_t const * const  me,
							   Matriz_t const * const  outro,
							   Matriz_t       * const  res);

static  Matriz_pt Mult_  ( Matriz_t const * const  me,
								Matriz_t const * const  outro,
								Matriz_t       * const  res);

static  Matriz_pt Divd_  ( Matriz_t const * const  me,
								Matriz_t const * const  outro,
								Matriz_t       * const  res);

static  Matriz_pt Ac_Soma_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  Matriz_pt Ac_Subt_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  Matriz_pt Ac_Mult_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  Matriz_pt Ac_Divd_ (Matriz_t       * const  me,
								 Matriz_t const * const  outro);

static  int	Compara_ 	    (Matriz_t const * const  me,
							 Matriz_t const * const  outro);

static  char *      Imprime_  (Matriz_t const * const  me);

static  void        Destroi_ (Matriz_t  *   me);

/* ------------------------------------------------------- */

static double  Modulo_ (Matriz_t   const * const me);

static void Get_ (Matriz_t  const * const me, double *ptMat);

static void Set_ (Matriz_t       * const me,
			double                valorMatriz,);

static int GetTam_ (Matriz_t     const * const me,);

static double GetMat_ (Matriz_t  const * const me);

static double Transpor_ (Matriz_t const * const me,
                          Matriz_t * const outro);

static double Reverse_horizontal_ (Matriz_t const * const me,
                                   Matriz_t * const outro);

static double Reverse_vertical_ (Matriz_t const * const me,
                                 Matriz_t * const outro);

static double Acrescenta_linha_ (Matriz_t * const me);

static double Acrescenta_coluna_ (Matriz_t * const me);

 /*---------------------------------------------*
 * implementação do construtor                  *
 * ---------------------------------------------*/
Matriz_pt Matriz_constroi (Matriz_pt  me, int tamanho,
                                         double mat);
{
    static struct NumeroVtbl const vtbl = {
        &copia_,
        &atribui_,
        &soma_,
        &subt_,
        &mult_,
        &divd_,
        &ac_soma_,
        &ac_subt_,
        &ac_mult_,
        &ac_divd_,
        &compara_,
        &imprime_,
        &destroi_,
     };

         me = (Matriz_pt) Num_constroi ((Numero_pt) me);

         me->super.metodo = &vtbl;

     static struct Matriz_Interface_st const interface = {
        &Copia_,
        &Atribui_,
        &Soma_,
        &Subt_,
        &Mult_,
        &Divd_,
        &Ac_Soma_,
        &Ac_Subt_,
        &Ac_Mult_,
        &Ac_Divd_,
        &Compara_,
        &Imprime_,
        &Destroi_,
        &Modulo_,
        &Get_,
        &Set_,
        &GetTam_,
        &GetMat_,
        &Transpor_,
        &Reverse_horizontal_,
        &Reverse_vertical_,
        &Acrescenta_coluna_,
        &Acrescenta_linha_,

     };

     me->Metodo = &interface;

	me->valor = (double *) malloc ((tamanho[0]*tamanho[1])*sizeof(double));
	if (me->valor == NULL)
	{	/*erro!!! não conseguiu alocar */
	    printf ("Erro na alocação de memória em Num_Constroi");
	    printf ("Nao alocou o valor double");
	    exit (1);
	}

	int k, i, j = 0;
	for(i=0, i<tamanho[0], i++){
        for(j=0, j<tamanho[1], j++){
            me->valor[i][j] = mat[k];
            k++;
        }
	}
    return (me);
}

 /*---------------------------------------------*
 * ---------------------------------------------*/


static inline
void Get_ (Matriz_t  const * const me, double *ptMat)

{
	static int i, j = 0;
	for(i=0, i<me->tam[0], i++){
        for(j=0, j<me->tam[1], j++){
            *ptMat[i][j] = me->valor[i][j];
        }
	}
}

static inline
void Set_ (Matriz_t       * const me,
			double                valorMatriz,)

{
	static int i, j = 0;
	for(i=0, i<me->tam[0], i++){
        for(j=0, j<me->tam[1], j++){
            me->valor[i][j] = valorMatriz;
        }
	}
}

static inline
int GetTam_ (Matriz_t     const * const me,)
{
	return(me->tam);
}


static inline
double GetMat_ (Matriz_t  const * const me)
{
    static int i, j = 0;
	for(i=0, i<me->tam[0], i++){
        for(j=0, j<me->tam[1], j++){
                return(me->valor[i][j]);
        }
	}
}


static
double  Modulo_ (Matriz_t  const * const me)
{
    static int i, j = 0;
    static double modulo[tam[0]];
    static double maiorMod = 0;
    for(i=0, i<(me->tam[0]), i++){
        for(j=0, j<(me->tam[1]), j++){
            modulo[i] += abs(me->valor[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
    if (i == 0){
        maiorMod = modulo[i]};
    if (vet[i] > maior){
        maiorMod = modulo[i];}}

    return(maiorMod);
}

static
double Transpor_ (Matriz_t const * const me, Matriz_t * const outro)
{
    static int i, j = 0;
    for(i=0, i<(me->tam[0]), i++){
        for(j=0, j<(me->tam[1]), j++){
                outro->valor[j][i] = me->valor[i][j];
        }}
    return ((Matriz_pt)outro);
}

static
double Reverse_horizontal_ (Matriz_t const * const me, Matriz_t * const outro)
{
    static int i, j = 0;
    static int troca = (me->tam[0]);
    for(i=0, i<(me->tam[0]), i++){
        for(j=0, j<(me->tam[1]), j++){
                outro->valor[troca][j] = me->valor[i][j];
        }troca--;}
    return ((Matriz_pt)outro);
}

static
double Reverse_vertical_ (Matriz_t const * const me, Matriz_t * const outro)
{
    static int i, j = 0;
    for(i=0, i<(me->tam[0]), i++){
        static int troca = (me->tam[1]);
        for(j=0, j<(me->tam[1]), j++){
                outro->valor[i][troca] = me->valor[i][j];
                troca--;
        }}
    return ((Matriz_pt)outro);
}

static
double Acrescenta_linha_ (Matriz_t * const me);
{
    static int i, j = 0;
    me->tam[0] += 1;
    for(i=0, i<(me->tam[0]), i++){
        for(j=0, j<(me->tam[1]), j++){
            me->valor[(me->tam[0])][j] = 0;
        }}
    return ((Matriz_pt)me);
}

static
double Acrescenta_coluna_ (Matriz_t * const me);
{
    static int i, j = 0;
    me->tam[1] += 1;
    for(i=0, i<(me->tam[0]), i++){
        for(j=0, j<(me->tam[1]), j++){
            me->valor[i][(me->tam[0])] = 0;
        }}
    return ((Matriz_pt)me);
}

/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/
static inline
Matriz_pt Copia_ (Matriz_t const * const  me)
{
	return ( (Matriz_pt)
	          copia_ ((Numero_pt) me));
}

 static
 Numero_pt copia_ (Numero_t const * const  me)
{
	assert (me != NULL);
	Numero_pt outro = NULL;
	outro = (Numero_pt) Matriz_constroi
							((Matriz_pt) outro,
							  me->tam, me->mat);
	return outro;
}

/*-----------------------------------------------------------------*/
static inline
Matriz_pt Atribui_(Matriz_t const * const me,
					  Matriz_t       * const  outro )
{
	return ( (Matriz_pt)
	          atribui_ ((Numero_pt) me,
								 (Numero_pt) outro));
}

static
 Numero_pt atribui_ (Numero_t const * const  me,
						  Numero_t       * const  outro)
 {
	 Set_((Matriz_pt) outro,
                GetTam_((Matriz_pt) me));

	 return (Numero_pt) outro;
 }
/*-----------------------------------------------------------------*/
static inline
Matriz_pt Soma_  ( Matriz_t const * const  me,
						   Matriz_t const * const  outro,
						   Matriz_t       * const  res)
{
	return ( (Matriz_pt)
	          soma_ ((Numero_pt) me,
					 (Numero_pt) outro,
					 (Numero_pt) res));
}

static  Numero_pt soma_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
    static int i, j = 0;
	Set_((Matriz_pt) res,
	             for(i=0, i<GetTam_(Matriz_pt(me)), i++){
                    for(j=0, j<GetTam_(Matriz_pt(me)), j++){
                         (GetMat_((Matriz_pt)me) + GetMat_((Matriz_pt)outro));
                        }});
    return (Numero_pt) res;
}


/*-----------------------------------------------------------------*/
static inline
Matriz_pt Subt_  (      Matriz_t const * const  me,
						   Matriz_t const * const  outro,
						   Matriz_t       * const  res)
{
	return ( (Matriz_pt)
	          subt_ ((Numero_pt) me,
							  (Numero_pt) outro,
							  (Numero_pt) res));
}
static  Numero_pt subt_  (	Numero_t const * const  me,
								    Numero_t const * const  outro,
								    Numero_t       * const  res)
{
        static int i, j = 0;
		Set_((Matriz_pt) res,
	             for(i=0, i<GetTam_(Matriz_pt(me)), i++){
                    for(j=0, j<GetTam_(Matriz_pt(me)), j++){
                         (GetMat_((Matriz_pt)me) - GetMat_((Matriz_pt)outro));
                        }});
		return (Numero_pt) res;
}

/*-----------------------------------------------------------------*/
static inline
Matriz_pt Mult_  ( Matriz_t const * const  me,
						   Matriz_t const * const  outro,
						   Matriz_t       * const  res)
{
	return ( (Matriz_pt)
	          mult_ ((Numero_pt) me,
									  (Numero_pt) outro,
									  (Numero_pt) res));
}

static  Numero_pt mult_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
        static int i, j = 0;
		Set_((Matriz_pt) res,
	             for(i=0, i<GetTam_(Matriz_pt(me)), i++){
                    for(j=0, j<GetTam_(Matriz_pt(me)), j++){
                         (GetMat_((Matriz_pt)me) * GetMat_((Matriz_pt)outro));
                        }});
        return ( (Numero_pt) res);
}

/*-----------------------------------------------------------------*/
static inline
Matriz_pt Divd_  ( Matriz_t const * const  me,
						   Matriz_t const * const  outro,
						   Matriz_t       * const  res)
{
	return ( (Matriz_pt)
	          divd_ ((Numero_pt) me,
                     (Numero_pt) outro,
                     (Numero_pt) res));
}

static  Numero_pt divd_  (	Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
        static int i, j = 0;
		Set_((Matriz_pt) res,
	             for(i=0, i<GetTam_(Matriz_pt(me)), i++){
                    for(j=0, j<GetTam_(Matriz_pt(me)), j++){
                         (GetMat_((Matriz_pt)me) / GetMat_((Matriz_pt)outro));
                        }});
        return ( (Numero_pt) res);
}

/*-----------------------------------------------------------------*/
static inline
Matriz_pt Ac_Soma_  ( Matriz_t  * const  me,
						 Matriz_t const * const  outro)
{
	return ( (Matriz_pt)
	          ac_soma_ ((Numero_pt) me,
                        (Numero_pt) outro));
}

static  Numero_pt ac_soma_  (Numero_t       * const  me,
                             Numero_t const * const  outro)
{
    static int i, j = 0;
	Set_((Matriz_pt) me,
	             for(i=0, i<GetTam_(Matriz_pt(me)), i++){
                    for(j=0, j<GetTam_(Matriz_pt(me)), j++){
                         (GetMat_((Matriz_pt)me) + GetMat_((Matriz_pt)outro));
                        }})

	return ((Numero_pt) me);
}

/*-----------------------------------------------------------------*/
static inline
Matriz_pt Ac_Subt_  ( Matriz_t  * const  me,
						 Matriz_t const * const  outro)
{
    return ( (Matriz_pt)
              ac_subt_ ((Numero_pt) me,
                        (Numero_pt) outro));
}


static  Numero_pt ac_subt_  (Numero_t       * const  me,
								  Numero_t const * const  outro)
{
    static int i, j = 0;
	Set_((Matriz_pt) me,
	             for(i=0, i<GetTam_(Matriz_pt(me)), i++){
                    for(j=0, j<GetTam_(Matriz_pt(me)), j++){
                         (GetMat_((Matriz_pt)me) - GetMat_((Matriz_pt)outro));
                        }});

	return ((Numero_pt) me);
}

/*-----------------------------------------------------------------*/
static inline
Matriz_pt Ac_Mult_  ( Matriz_t  * const  me,
						 Matriz_t const * const  outro)
{
	return ( (Matriz_pt)
	          ac_mult_ ((Numero_pt) me,
                        (Numero_pt) outro));
}


static  Numero_pt ac_mult_  (Numero_t       * const  me,
                             Numero_t const * const  outro)
{
    static int i, j = 0;
    Set_((Matriz_pt) me,
	             for(i=0, i<GetTam_(Matriz_pt(me)), i++){
                    for(j=0, j<GetTam_(Matriz_pt(me)), j++){
                         (GetMat_((Matriz_pt)me) * GetMat_((Matriz_pt)outro));
                        }});

	 return ( (Numero_pt) me);
}

/*-----------------------------------------------------------------*/
static inline
Matriz_pt Ac_Divd_  ( Matriz_t  * const  me,
						 Matriz_t const * const  outro)
{
	return ( (Matriz_pt)
	          ac_divd_ ((Numero_pt) me,
									     (Numero_pt) outro));
}


static  Numero_pt ac_divd_  (Numero_t       * const  me,
								  Numero_t const * const  outro)
{
    static int i, j = 0;
    Set_((Matriz_pt) me,
	             for(i=0, i<GetTam_(Matriz_pt(me)), i++){
                    for(j=0, j<GetTam_(Matriz_pt(me)), j++){
                         (GetMat_((Matriz_pt)me) / GetMat_((Matriz_pt)outro));
                        }});
	 return ( (Numero_pt) me);}

/*-----------------------------------------------------------------*/
static inline
int Compara_  ( Matriz_t const * const  me,
				Matriz_t const * const  outro)
{
	return ( compara_ ((Numero_pt) me,
                       (Numero_pt) outro));
}

static  int	compara_ 	(Numero_t const * const  me,
                         Numero_t const * const  outro)
{
	if( Modulo_((Matriz_pt)me) > Modulo_((Matriz_pt)outro) )
	{ return (1);}
	else if( Modulo_((Matriz_pt)me) < Modulo_((Matriz_pt)outro) )
	{  return (-1);};

	return(0);
}

/*-----------------------------------------------------------------*/
static inline
char * Imprime_  ( Matriz_t const * const  me)
{
	return ( imprime_ ((Numero_pt) me));
}
static  char * imprime_  (Numero_t const * const  me)
{
    static char buffer[50];

    sprintf(buffer, "%l ", GetMat((Matriz_pt)me));

	return buffer;
}

 /*---------------------------------------------*
 * implementação do destrutor                   *
 * ---------------------------------------------*/
 /*-----------------------------------------------------------------*/
static inline
void Destroi_  ( Matriz_t  *   me)
{
	  destroi_ ((Numero_t *)  me);
}
static void destroi_ (Numero_t *  me)
{
	/* primeiro destroi o valor double */
	free (((Matriz_pt) me)->valor);
	/*... e só agora destroi-se o número virtual da classe base */
	free ((Numero_t *) me);
}
