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

//Constantes banir clientes
#define MAXIMO_GUITARRAS_DANIFICADAS 3
#define MAXIMO_DIAS_ATRASO 20

//Constantes para o estado da estrutura aluguer
#define DECORRER 0
#define ENTREGUE 1
#define ENTREGA_DANIFICADA 2

struct aluguer{
  ptrGuitarra guitarra;
  int estado;
  //Data do inicio do aluguer
  int diaInicio;
  int mesInicio;
  int anoInicio;
  //Data da entrega do aluguer
  int diaEntrega;
  int mesEntrega;
  int anoEntrega;
  ptrAluguer prox;
};

void limiteAluguer(int diaAtual, int mesAtual, int anoAtual);
int calculaDias(int dia, int mes, int ano);
int calculaDiasAtraso(int diaInicio, int mesInicio, int anoInicio, int diaEntrega, int mesEntrega, int anoEntrega);
int calculaValorAluguer(int diasAlugados,int diasAtrasados,int estado, int precoAluguerDia, int valorGuitarra);
#endif
