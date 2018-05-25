#ifndef ALUGUERES_H
#define ALUGUERES_H
#include "guitarras.h"
typedef struct aluguer aluguer, *ptrAluguer;

//Constantes alugueres
#define MAXIMO_DIAS_MES 31
#define GUITARRAS_CARAS 500
#define MINIMO_GUITARRAS_BARATAS 6
#define MAXIMO_ALUGUERES_DECORRER 5
#define MAXIMO_DIAS_ALUGUER 7
#define MULTA 10

//Constantes banir
#define MAXIMO_GUITARRAS_DANIFICADAS 3
#define MAXIMO_DIAS_ATRASO 20

//Constantes estado estrutura aluguer
#define DECORRER 0
#define ENTREGUE 1
#define ENTREGA_DANIFICADA 2

struct aluguer{
  ptrGuitarra guitarra;
  int estado;
  //Data inicio
  int diaInicio;
  int mesInicio;
  int anoInicio;
  //Data entrega
  int diaEntrega;
  int mesEntrega;
  int anoEntrega;
  //TODO: dias de atraso
  ptrAluguer prox;
};

void limiteAluguer(int diaAtual, int mesAtual, int anoAtual);
int calculaDiasAtraso(int diaInicio, int mesInicio, int anoInicio, int diaEntrega, int mesEntrega, int anoEntrega);
int calculaValorAluguer(int diasAlugados,int diasAtrasados,int estado, int precoAluguerDia, int valorGuitarra);
#endif
