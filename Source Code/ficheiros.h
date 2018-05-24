#ifndef FICHEIROS_H
#define FICHEIROS_H
#include "alugueres.h"
#include "clientes.h"
#include "guitarras.h"

#define NOME_FICHEIRO_GUITARRAS "guitarras.txt"
#define NOME_FICHEIRO_CLIENTES "clientes.txt"
#define NOME_FICHEIRO_CLIENTES_BANIDOS "clientesBanidos.bin"

ptrGuitarra importaGuitarras(ptrGuitarra listaGuitarras, int *total);
ptrCliente importaClientes(ptrCliente listaClientes,ptrGuitarra listaGuitarras, int total);
void importaTotalClientesBanidos(int *totalClientesBanidos);
void adicionaClienteBanido(int *totalClientesBanidos, char nome[100], int nif, int motivo);
void exportaDados(ptrCliente listaClientes,ptrGuitarra listaGuitarras, int total);
#endif
