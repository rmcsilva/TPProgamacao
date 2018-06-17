#ifndef UI_H
#define UI_H
#include "guitarras.h"
#include "clientes.h"
#include "alugueres.h"

void mainMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int *diaAtual, int *mesAtual, int *anoAtual);
void guitarrasMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int diaAtual, int mesAtual, int anoAtual);
void clientesMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int diaAtual, int mesAtual, int anoAtual);
void alugueresMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int *diaAtual, int *mesAtual, int *anoAtual);
void alteraData(int *dia, int *mes, int *ano);
void printDataLogo(int dia, int mes, int ano);
void printSeparador();
int scanfInteiro();
#endif
