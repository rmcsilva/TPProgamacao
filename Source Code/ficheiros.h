#ifndef FICHEIROS_H
#define FICHEIROS_H
#include "clientes.h"

#define NOME_FICHEIRO_GUITARRAS "guitarras.txt"
#define NOME_FICHEIRO_CLIENTES "clientes.txt"
#define NOME_FICHEIRO_CLIENTES_BANIDOS "clientesBanidos.bin"

ptrGuitarra importaGuitarras(ptrGuitarra listaGuitarras, int *total);
ptrCliente importaClientes(ptrCliente listaClientes,ptrGuitarra listaGuitarras, int total);
void exportaDados(ptrCliente listaClientes,ptrGuitarra listaGuitarras, int total);
void adicionaClienteBanido(char nome[100], int nif, int motivo);
#endif
