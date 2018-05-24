#ifndef FICHEIROS_H
#define FICHEIROS_H
#include "alugueres.h"
#include "clientes.h"
#include "guitarras.h"

#define NOME_FICHEIRO_GUITARRAS "guitarras.txt"
#define NOME_FICHEIRO_CLIENTES "clientes.txt"

ptrGuitarra importaGuitarras(ptrGuitarra listaGuitarras, int *total);
ptrCliente importaClientes(ptrCliente listaClientes,ptrGuitarra listaGuitarras, int total);
void exportaDados(ptrCliente listaClientes,ptrGuitarra listaGuitarras, int total);
#endif
