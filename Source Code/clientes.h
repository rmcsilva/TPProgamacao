#ifndef CLIENTES_H
#define CLIENTES_H
#include "guitarras.h"
typedef struct cliente cliente, *ptrCliente;
typedef struct aluguer aluguer, *ptrAluguer;

//Contantes motivo para cliente banido
#define ATRASO 0
#define GUITARRAS_DANIFICADAS 1

//Constantes estrutura aluguer
#define DECORRER 0
#define ENTREGUE 1
#define ENTREGA_DANIFICADA 2

struct cliente{
  char nome[100];
  int nif;
  int nAlugueresTotal;
  int nAlugueresAtual;
  int nEntregasAtrasadas;
  int nEntregasDanificadas;
  ptrAluguer alugueres;
  ptrCliente prox;
};

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

typedef struct clienteBanido{
  char nome[100];
  int nif;
  int motivo;
}clienteBanido, *ptrClienteBanido;

//Métodos clientes
ptrCliente adicionaCliente(ptrCliente listaClientes);
ptrCliente removeCliente(ptrCliente listaClientes);
ptrCliente banirCliente(ptrCliente listaClientes,int *totalClientesBanidos, int nif, int motivo);
void listarClientesAtivos(ptrCliente listaClientes);
int verificaCliente(ptrCliente listaClientes, int nif);
void mostraCliente(ptrCliente listaClientes);
void freeCliente(ptrCliente* listaClientes);
//Métodos Guitarras
void listarHistoricoAluguerGuitarra(ptrCliente listaClientes, ptrGuitarra listaGuitarras, int total);
#endif
