/**********************************************************************
* Baseado no c�digo disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* numero.h define a interface do "n�mero virtual"
* Um n�mero complexo, um n�mero racional, um n�mero real,
* um n�mero inteiro, um n�mero em ponto flutuante ... todos
* s�o inst�ncias "reais" do "n�mero virtual"
* Estes ser�o "filhos" de "n�mero" na �rvore de heran�a
* ********************************************************************/

#ifndef NUMERO_H
#define NUMERO_H

#include <stdint.h>


 /* declaro agora que "existem as estruturas
  * "NumeroVtbl" e "Numero_st"
  * s� "DECLARO"... elas ser�o DEFINIDAS na implementa��o .....  */
struct NumeroVtbl;
struct Numero_st;

/* --------------------------------------------------------*
 * Finalmente, podemos definir a estrutura "n�mero" ,      *
 * que � a classe virtual b�sica para os tipos num�ricos   *
 * A classe virtual b�sica n�o cont�m valores, s� m�todos  *
 * O ponteiro "metodo" � chamado de vptr na literatura     *
 * --------------------------------------------------------*/
struct Numero_st {
    struct NumeroVtbl const *metodo; /* ptr p/ os m�todos */
} ;
typedef struct Numero_st 	Numero_t;
typedef struct Numero_st 	* Numero_pt;

/*------------------------------------------------------------------*
 *  TABELA DE FUNCOES VIRTUAIS DE "NUMERO"                          *
 * Uma fun��o virtual � uma fun��o que � declarada (mas n�o         *
 * implementada em uma classe base (NO CASO, NUMERO) e redefinida   *
 * pela classe derivada (no caso, poder� ser DOUBLE, RACIONAL,      *
 * COMPLEXO, BIG_NUM, QUATERNION,...).                              *
 *                                                                  *
 * Para declarar uma fun��o como sendo virtual, � preciso associ�-la*
 * com uma entrada da tabela metodo  da classe base.                *
 * A tabela (struct) apontada aqui � conhecida   por                *
 * geralmente por vtbl na literatura. O  ponteiro "metodo" �        *
 * geralmente chamado de vptr.                                      *
 *                                                                  *
 * A redefini��o da fun��o na classe derivada sobrepor-se-� �       *
  * defini��o da respectiva fun��o na classe base.                  *
 *                                                                  *
 * No fundo, a declara��o da fun��o virtual na classe base age      *
 * como uma esp�cie de indicador que especifica uma linha geral de  *
 * a��o e estabelece uma interface de acesso. (exce��o para o       *
 * destrutor, que efetivamente tem que "destruir" o ponteiro para   *
 * a tabela de fun��es virtuais)                                    *
 *                                                                  *
 * A redefini��o da fun��o virtual pela classe derivada especifica  *
 * verdadeiramente IMPLEMENTA as opera��es realmente executadas     *
 * por cada m�todo da tabela.                                       *
 *                                                                  *
 * Quando acessadas normalmente, fun��es virtuais se comportam como *
 * qualquer outro tipo de fun��o membro da classe. Entretanto, o que*
 * torna fun��es virtuais importantes e capazes de suportar         *
 * polimorfismo em tempode execu��o � o seu modo de comportamento   *
 * quando acessado atrav�s de um apontador.                         *
 *                                                                  *
 * Lembre-se que um apontador para a classe base pode ser usado     *
 * para apontar para qualquer classe derivada daquela classe base,  *
 * desde que corretamente convertido ("cast").                      *
 *                                                                  *
 * Quando um apontador base aponta para um objeto derivado que      *
 * cont�m uma fun��o virtual, o programa ir� determina qual vers�o  *
 * daquela fun��o chamar baseada no tipo do objeto apontado .                                          *
 *                                                                  *
 * Assim, quando objetos diferentes s�o apontados, vers�es          *
 * diferentes da fun��o virtual s�o executadas.                     *
 * -----------------------------------------------------------------*/

/* Tabela Virtual de m�todos de "Numero" */
struct NumeroVtbl {
	Numero_pt 	(*copia)	(Numero_t const * const me);

    Numero_pt 	(*atribui)	(Numero_t const * const  me,
							 Numero_t       * const  outro);

    Numero_pt 	(*soma)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							 Numero_t       * const res);

    Numero_pt 	(*subt)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							 Numero_t       * const res);

    Numero_pt 	(*mult)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							Numero_t        * const res);

    Numero_pt 	(*divd)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							 Numero_t       * const res);

    Numero_pt 	(*ac_soma)	(Numero_t       * const  me,
							 Numero_t const * const  outro);

    Numero_pt 	(*ac_subt)	(Numero_t       * const  me,
							 Numero_t const * const outro);

    Numero_pt 	(*ac_mult)	(Numero_t       * const  me,
							 Numero_t const * const outro);

    Numero_pt 	(*ac_divd)	(Numero_t        * const  me,
							 Numero_t const * const outro);

    int			(*compara)	(Numero_t const * const  me,
							 Numero_t const * const  outro);

    char *      (*imprime)  (Numero_t const * const  me);

    void        (*destroi)  (Numero_t       *        me);
};

typedef struct NumeroVtbl * NumeroVtbl_pt;



/*-------------------------------------------------------
 * 	INTERFACE P�BLICA DE Numero_t
 * ------------------------------------------------------*/

/* ----------------------------------------------------------------*
 *  Construtor do Numero_t. � implementado em Numero_c             *
 * O construtor � a primeira fun��o a ser executada                *
 * dentro do construtor de cada tipo de n�mero. � o construtor que *
 * ir� associar a tabela de m�todos adequados a cada tipo de       *
 * numero. Por isso, n�o pode estar dentro da pr�pria tabela de    *
 * m�todos virtuais.                                               *
 * Simetricamente, o destrutor � a �ltima fun��o a ser chamada     *
 * dentro do destrutor de cada tipo de n�mero. Mas, como a tabela  *
 * j� existe, o destrutor pode estar "dentro" dela.                *
 * ----------------------------------------------------------------*/
    Numero_pt	Num_constroi(Numero_pt me);

/* --------------------------------------------------------
 *  As demais fun��es N�O s�o implementadas DE VERDADE em numero.c
 *
 * Isso porque cada tipo de numero tem sua pr�pria implementa��o
 * destas fun��es (atribui��o, c�pia, soma, ...., impress�o)
 *
 * Cada uma destas fun��es tem uma entrada respectiva na
 * vtbl de Numero_t (tabela de fun��es virtuais) que ser� substitu�da na
 * vtbl do "??????"_t especifico, a seu tempo.
 *
 * Cada "???????" tem suas proprias implementa��es de soma, subtra��o, etc...
 * Elas s�o, desta forma, escolhidas em "tempo de execu��o".
 * Assim, fazemos polimorfismo "em tempo de execu��o".
 *
 * A soma de dois racionais � diferente da soma de dois complexos!!
 * Cada racional carrega consigo um ponteiro para a tabela de fun��es
 * que s�o usadas para ele....Cada complexo carrega consigo um ponteiro
 * para as fun��es que s�o usadas para ele. Assim, em  tempo de execu��o,
 * o computador "descobre" qual a fun��o que deve usar para aquele "numero".
 *
 * Isso � diferente dos "templates de macro". Nos "templates de macro"
 * faz�amos "polimorfismo em tempo de compila��o", gerando um arquivo
 * .obj para cada tipo de n�mero diferente.
 * ------------------------------------------------------*/

static inline Numero_pt Num_copia	(Numero_t const * const me) {
 return (  me->metodo->copia(me));
}

static inline Numero_pt Num_atribui(Numero_t const * const  me,
									Numero_t       * const  outro)
{
 return (me->metodo->atribui(me, outro));
}

static inline Numero_pt Num_soma (Numero_t const * const  me,
								  Numero_t const * const  outro,
								  Numero_t       * const res)
{
 return (me->metodo->soma(me, outro, res));
}

static inline Numero_pt Num_subt (Numero_t const * const  me,
								  Numero_t const * const  outro,
								  Numero_t       * const res)
{
 return (me->metodo->subt(me, outro, res));
}

static inline Numero_pt Num_mult (Numero_t const * const  me,
								  Numero_t const * const  outro,
								  Numero_t       * const res)
{
 return (me->metodo->mult(me, outro, res));
}

static inline Numero_pt Num_divd (Numero_t const * const  me,
								  Numero_t const * const  outro,
								  Numero_t       * const res)
{
 return (me->metodo->divd(me, outro, res));
}

static inline Numero_pt Num_ac_soma (Numero_t       * const  me,
									 Numero_t const * const outro)
{
 return (me->metodo->ac_soma(me, outro));
}

static inline Numero_pt Num_ac_subt (Numero_t       * const  me,
									 Numero_t const * const outro)
{
 return (me->metodo->ac_subt(me, outro));
}

static inline Numero_pt Num_ac_mult (Numero_t       * const  me,
									 Numero_t const * const outro)
{
 return (me->metodo->ac_mult(me, outro));
}

static inline Numero_pt Num_ac_divd (Numero_t        * const  me,
									 Numero_t const * const outro)
{
 return (me->metodo->ac_divd(me, outro));
}

static inline int	Num_compara	  ( Numero_t const * const  me,
									Numero_t const * const  outro)
{
 return (me->metodo->compara(me, outro));
}

static inline char * Num_imprime (Numero_t const * const  me)
{
 return (me->metodo->imprime)(me);
}

static inline void  Num_destroi (Numero_t  *   me)
{
  /* (me->metodo->destroi)(me)*/;
}



#endif /* FIM DO NUMERO_H */
