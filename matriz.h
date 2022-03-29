/**********************************************************************
* Baseado no código disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* Aqui se apresenta a interface do número do tipo "MATRIZ"
*
* numero.h definiu a interface do "número_t virtual"
* ********************************************************************/

#ifndef MATRIZ_H
#define MATRIZ_H

#include "numero.h" /*a interface da classe básica */

struct Matriz_Interface_st;

 struct Matriz_st {
    struct Numero_st super;

    struct Matriz_Interface_st const *  Metodo;

    unsigned int *tam;

    double **valor;
}

typedef struct Matriz_st *Matriz_pt;
typedef struct Matriz_st  Matriz_t;

Matriz_pt Matriz_constroi (Matriz_pt  me, int tamanho, double mat)

struct Matriz_Interface_st {
	Matriz_pt (*copia)	(Matriz_t const * const me);

    Matriz_pt (*atribui)	(Matriz_t const * const  me,
							 Matriz_t       * const  outro);

    Matriz_pt (*soma)	(Matriz_t const * const  me,
							 Matriz_t const * const  outro,
							 Matriz_t       * const res);

    Matriz_pt (*subt)	(Matriz_t const * const  me,
							 Matriz_t const * const  outro,
							 Matriz_t       * const res);

    Matriz_pt (*mult)	(Matriz_t const * const  me,
							 Matriz_t const * const  outro,
							Matriz_t        * const res);

    Matriz_pt (*divd)	(Matriz_t const * const  me,
							 Matriz_t const * const  outro,
							 Matriz_t       * const res);

    Matriz_pt (*ac_soma)	(Matriz_t       * const  me,
							     Matriz_t const * const  outro);

    Matriz_pt (*ac_subt)	(Matriz_t       * const  me,
							     Matriz_t const * const outro);

    Matriz_pt (*ac_mult)	(Matriz_t       * const  me,
							     Matriz_t const * const outro);

    Matriz_pt (*ac_divd)	(Matriz_t        * const  me,
							     Matriz_t const * const outro);

    int			(*compara)	(Matriz_t const * const  me,
							 Matriz_t const * const  outro);

    char *      (*imprime)  (Matriz_t const * const  me);

    void        (*destroi)  (Matriz_t       *        me);
    /*------------------------------------------------------*/
    void       (*get     ) (Matriz_t  const * const me,
							double               * ptReal,
	                        double 				 * ptImag);

	void   	   (*set     ) (Matriz_t        * const me,
	                          double             valorReal,
	                          double 		     valorImag);

    int        (*gettam  ) (Matriz_t     const * const me,);

    double     (*getmat  ) (Matriz_t  const * const me);

    double     (*transpor) (Matriz_t const * const me,
                             Matriz_t * const outro);

    double     (*reverse_horizontal) (Matriz_t const * const me,
                                       Matriz_t * const outro);

    double     (*reverse_vertical) (Matriz_t const * const me,
                                     Matriz_t * const outro);

    double     (*acrescenta_linha) (Matriz_t * const me);

    double     (*acrescenta_coluna) (Matriz_t * const me);

    double  (*modulo) (Matriz_t   const * const me);

    /*------------------------------------------------------*/
};

typedef struct Matriz_Interface_st *Matriz_Interface_pt;

#endif /* Matriz_H */
