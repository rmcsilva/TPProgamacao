#ifndef UI_H
#define UI_H
#include "guitarras.h"
#include "clientes.h"
#include "alugueres.h"

void mainMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int diaAtual, int mesAtual, int anoAtual);
void guitarrasMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras);
void clientesMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras);
void alugueresMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras,int diaAtual, int mesAtual, int anoAtual);
void printLogo();
void printSeparador();
#endif
