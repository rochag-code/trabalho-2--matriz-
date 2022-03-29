#include <stdio.h>
#include "matriz.h"

int main ()
{

	Matriz_pt ptM1=NULL, ptM2=NULL, ptM3=NULL, ptM4=NULL, ptM5=NULL, ptM6=NULL, ptM7=NULL, ptM8=NULL;


	ptM1 = Matriz_constroi (ptM1, ([3,4]), ([1,2,3,4,5,6,7,8,9,10,11,12]));

	ptM2 = ptM1->Metodo->copia (ptM1);

	printf ("As duas matrizes sao %s %s \n",
				ptM1->Metodo->imprime (ptM1),
				ptM2->Metodo->imprime (ptM2));

    ptM3 = Matriz_constroi (ptM1, ([3,3]), ([0,0,0,0,0,0,0,0,0]));

    ptM3 = ptM2->Metodo->atribui (ptM2, ptM3);
    printf ("ptM3 recebeu o valor de M2 = %s \n",
				ptM3->Metodo->imprime (ptM3));

    ptM3 = ptM1->Metodo->soma(ptM1, ptM2, ptM3);
    printf ("ptM3 recebeu a soma de M1 com M2 = %s \n",
				ptM3->Metodo->imprime (ptM3));

    ptM3 = ptM3->Metodo->subt(ptM3, ptM2, ptM3);
    printf ("ptM3 recebeu a subtracao de M3 com M2 = %s \n",
				ptM3->Metodo->imprime (ptM3));

    ptM3 = ptM1->Metodo->mult(ptM1, ptM2, ptM3);
    printf ("ptM3 recebeu a multiplicacao de M1 com M2 = %s \n",
                 ptM3->Metodo->imprime (ptM3));

    ptM3 = ptM1->Metodo->divd(ptM1, ptM2, ptM3);
    printf ("ptM3 recebeu a divisão de M1 com M2 = %s \n",
                 ptM3->Metodo->imprime (ptM3));

    ptM3 = ptM1->Metodo->ac_soma(ptM3, ptM2);
    printf ("ptM3 foi somado com M2 = %s \n",
				ptM3->Metodo->imprime (ptM3));

    ptM3 = ptM3->Metodo->ac_subt(ptM3, ptM2);
    printf ("ptM3 foi subtraido de M2 = %s \n",
				ptM3->Metodo->imprime (ptM3));

    ptM3 = ptM1->Metodo->ac_mult(ptM3, ptM2);
    printf ("ptM3 foi multiplicado por M2 = %s \n",
                 ptM3->Metodo->imprime (ptM3));

    ptM3 = ptM1->Metodo->ac_divd(ptM3, ptM2);
    printf ("ptM3 foi dividido por M2 = %s \n",
                 ptM3->Metodo->imprime (ptM3));

    if (ptM1->Metodo->compara(ptM2,ptM3)>0)
    {
       printf ("M2 eh maior que M3 \n");
    }
    if (ptM1->Metodo->compara(ptM2,ptM3)<0)
    {
       printf ("M2 eh menor que M3 \n");
    }

    ptM4 = Transpor_(ptM1, ptM2);
    printf("A matriz M1 transposta é: %s \n",
                                ptM4->Metodo->imprime (ptM4));

    ptM5 = Reverse_horizontal_(ptM1, ptM2);
    printf("A matriz M1 com as linhas trocadas é: %s \n",
                                ptM5->Metodo->imprime (ptM5));

    ptM6 = Reverse_vertical_(ptM1, ptM2);
    printf("A matriz M1 com as colunas trocadas é: %s \n",
                                ptM6->Metodo->imprime (ptM6));

    ptM7 = Acrescenta_linha_(ptM1);
    printf("A matriz M1 com uma linha acrescentada é: %s \n"
                                ptM7->Metodo->imprime (ptM7));

    ptM8 = Acrescenta_coluna_(ptM1);
    printf("A matriz M1 com uma coluna acrescentada é: %s \n"
                                ptM8->Metodo->imprime (ptM8));

	ptM1->Metodo->destroi (ptM1);
	ptM2->Metodo->destroi (ptM2);
    ptM3->Metodo->destroi (ptM3);
    ptM4->Metodo->destroi (ptM4);
    ptM5->Metodo->destroi (ptM5);
    ptM6->Metodo->destroi (ptM6);
    ptM7->Metodo->destroi (ptM7);
    ptM8->Metodo->destroi (ptM8);

	return (0);
}
