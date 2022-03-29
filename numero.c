/**********************************************************************
* Baseado no c�digo disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* numero.c implementa a interface do "n�mero virtual"
*
* Um n�mero complexo, um n�mero racional, um n�mero real,
* um n�mero inteiro, um n�mero em ponto flutuante, um quaternion,
* um octonion, um big_num, um ponto_fixo, ....
* todos s�o inst�ncias "reais" do "n�mero virtual"
*
* Todos ser�o "filhos" de "n�mero" na �rvore de heran�a
* ********************************************************************/
#include  <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "numero.h"


/*--------------------------------------------------------------------
*  prot�tipos das fun��es virtuais do Numero_t
* Note que s�o fun��es que s�o implementadas apenas localmente
* (terminadas com "_"). S�o fun��es "static"  (tem escopo
* limitado ao arquivo objeto criado a partir daqui e n�o ser�o linkadas
*  com outros .obj. Elas s�o declaradas aqui porque precisamos delas
*  para atribuirmos seus respectivos endere�os nos campos da vtbl (tabela
*  de fun��es virtuais) apontada por metodo (que � o primeiro campo de
*  Numero_t)
* ------------------------------------------------------------------*/

static  Numero_pt Num_copia_ (Numero_t const * const   me);

static  Numero_pt Num_atribui_ (Numero_t const * const   me,
							    Numero_t       * const   outro) ;

static  Numero_pt Num_soma_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_subt_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_mult_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_divd_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_ac_soma_  (Numero_t       * const    me,
							     Numero_t const * const    outro    );

static  Numero_pt Num_ac_subt_  (Numero_t       * const    me,
							     Numero_t const * const    outro );

static  Numero_pt Num_ac_mult_  (Numero_t       * const    me,
							     Numero_t const * const    outro );

static  Numero_pt Num_ac_divd_  (Numero_t       * const    me,
							     Numero_t const * const    outro );

static  int	Num_compara_ 	(Numero_t const * const    me,
							 Numero_t const * const    outro );

static  char * Num_imprime_  (Numero_t const * const    me);

static  void   Num_destroi_  (Numero_t  *     me);


/* --------------------------------------------------------------*
 * implementa��o do construtor                                   *
 * O construtor N�O fica dentro da tabela de fun��es             *
 * virtuais porque n�o h� atributos a serem "constru�dos"        *
 * para os "Numeros" na classe base. Se houvessem, faria sentido *
 * termos uma implementa��o de construtor inicial.               *
 * --------------------------------------------------------------*/
  Numero_pt Num_constroi (Numero_pt  me)
{
	/* aloca dinamicamente uma area de memoria para um Numero_t */
	me = (Numero_t *) malloc (sizeof(Numero_t));
	if (me == NULL)
	{	/*erro!!! n�o conseguiu alocar */
	    printf ("Erro na aloca��o de mem�ria em Num_Constroi");
	    exit (1);
	}

	/* tabela de fun��es virtuais da classe Numero_t *
	 * Esta tabela est�tica ser� compartilhada por todos os n�meros */

    static struct NumeroVtbl const vtbl = {
        &Num_copia_,
        &Num_atribui_,
        &Num_soma_,
        &Num_subt_,
        &Num_mult_,
        &Num_divd_,
        &Num_ac_soma_,
        &Num_ac_subt_,
        &Num_ac_mult_,
        &Num_ac_divd_,
        &Num_compara_,
        &Num_imprime_,
        &Num_destroi_
     };
     me->metodo = &vtbl; /*  metodo agora aponta para a vtbl de Numero_t */

	/* ------------------------------------------------------------
	 * quando implementarmos o "meu_float", valor apontar� para float
     * quando implementarmos o racional,   valor apontar� para
     * um vetor com dois "long int"
     * quando implementarmos o complexo,   valor apontar� para
     * um vetor com dois "double"
     * quando implementarmos o quaternion, valor apontar� para
     * um vetor com quatro "double"
     * Por isso, cada tipo espec�fico de n�mero terminar� de implementar
     * o seu construtor....
     *---------------------------------------------------------------*/
     return (me);
}





/*--------------------------------------------------------------------
*  implementa��es das fun��es virtuais do Numero_t
* Note que s�o fun��es que s�o implementadas apenas localmente
* (terminadas com "_"). S�o fun��es "static"  (tem escopo
* limitado ao arquivo objeto criado a partir daqui e n�o ser�o linkadas
*  com outros .obj. Elas s�o implementadas aqui porque precisamos delas
*  para a compila��o do c�digo..... mas se espera que
*  "nunca, jamais" venham a ser "EXECUTADAS".
*  As fun��es que ser�o executadas s�o as fun��es similares a estas
*  dos tipos de n�mero que s�o "filhos" do "Numero_t"
*  (real, inteiro, ponto_fixo, complexo, bignum, hipercomplexo...)
* ------------------------------------------------------------------*/

static inline Numero_pt Num_copia_ (Numero_t const * const    me)
{
	assert (0);
	printf ("%p",(void *)me);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_atribui_ (Numero_t const * const    me,
									  Numero_t       * const    outro)
{
	assert (0);  /* fun��o virtual ... nunca deve ser chamada */
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;  /*fa�o retorno para evitar erro de
	                            compila��o */
}

static inline Numero_pt Num_soma_  (Numero_t const * const    me,
									Numero_t const * const    outro,
									Numero_t       * const    res)
{
	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_subt_  (Numero_t const * const    me,
									Numero_t const * const    outro,
									Numero_t       * const    res)
{
	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_mult_  (Numero_t const * const    me,
									Numero_t const * const    outro,
									Numero_t       * const    res)
{
	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);

	return (Numero_pt) NULL;
}

static inline Numero_pt Num_divd_  (Numero_t const * const    me,
									Numero_t const * const    outro,
									Numero_t       * const    res)
{
	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_ac_soma_  (Numero_t       * const    me,
									   Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_ac_subt_  (Numero_t       * const    me,
									   Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_ac_mult_  (Numero_t       * const    me,
									   Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;
}

static inline Numero_pt Num_ac_divd_  (Numero_t       * const    me,
									   Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (Numero_pt) NULL;
}


static inline int	Num_compara_ 	(Numero_t const * const    me,
									 Numero_t const * const    outro)
{
	assert (0);
	printf ("%p %p",(void *)me, (void *)outro);
	return (0);
}


static inline char * Num_imprime_  (Numero_t const * const    me)
{
	assert (0);
	printf ("%p",(void *)me);
	return (char *) NULL;
}

/* --------------------------------------------------*
 * implementa��o do destrutor                        *
                                     *
 * --------------------------------------------------*/
static inline void Num_destroi_ (Numero_t * me)
{
	/* *free (me); */
}
