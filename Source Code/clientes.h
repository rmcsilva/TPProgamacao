#ifndef CLIENTES_H
#define CLIENTES_H
#include "guitarras.h"
#include "alugueres.h"
typedef struct cliente cliente, *ptrCliente;

//Contantes para o motivo do cliente banido
#define ATRASO 0
#define GUITARRAS_DANIFICADAS 1

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

typedef struct clienteBanido{
  char nome[100];
  int nif;
  int motivo;
}clienteBanido, *ptrClienteBanido;

//Métodos clientes
ptrCliente adicionaCliente(ptrCliente listaClientes);
ptrCliente removeCliente(ptrCliente listaClientes);
ptrCliente banirCliente(ptrCliente listaClientes, int nif, int motivo);
void listarClientesAtivos(ptrCliente listaClientes);
void listarClientesBanidos();
int verificaCliente(ptrCliente listaClientes, int nif);
void mostraCliente(ptrCliente listaClientes);
void freeCliente(ptrCliente* listaClientes);
//Métodos Alugueres
ptrCliente criarAluguer(ptrCliente listaClientes, ptrGuitarra listaGuitarras, int totalGuitarras, int diaAtual, int mesAtual, int anoAtual);
ptrCliente concluiAluguer(ptrCliente listaClientes, int diaAtual, int mesAtual, int anoAtual);
void listarAlugueresDecorrer(ptrCliente listaClientes);
int devolveAlugueresDecorrer(ptrCliente listaClientes);
//Métodos Guitarras
void listarHistoricoAluguerGuitarra(ptrCliente listaClientes, ptrGuitarra listaGuitarras, int total);
#endif
