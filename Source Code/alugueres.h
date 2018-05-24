#ifndef ALUGUERES_H
#define ALUGUERES_H
#include "guitarras.h"
#include "clientes.h"

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
//TODO:Completar

void criarAluguer(ptrCliente listaClientes, ptrGuitarra listaGuitarras, int totalGuitarras, int diaAtual, int mesAtual, int anoAtual);
ptrCliente concluiAluguer(ptrCliente listaClientes, int diaAtual, int mesAtual, int anoAtual);
void limiteAluguer(int diaAtual, int mesAtual, int anoAtual);
void listarAlugueresDecorrer(ptrCliente listaClientes);
int calculaDiasAtraso(int diaInicio, int mesInicio, int anoInicio, int diaEntrega, int mesEntrega, int anoEntrega);
#endif
