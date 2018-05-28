#include "clientes.h"
#include "ficheiros.h"
#include "ui.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  //TODO:REVER alocações de memoria
  //TODO: Melhorar estruras de dados, ordenar por id / nif
  //TODO: Bug nas datas, mês de dezembro porque muda de ano!
  int dia, mes, ano;
  int totalGuitarras=0;
  int totalClientesBanidos=0;
  ptrGuitarra listaGuitarras=NULL;
  ptrCliente listaClientes=NULL;

  printf("Introduza a data do progama!\n");
  alteraData(&dia,&mes,&ano);

  listaGuitarras=importaGuitarras(listaGuitarras,&totalGuitarras);
  listaClientes=importaClientes(listaClientes,listaGuitarras, totalGuitarras);
  importaTotalClientesBanidos(&totalClientesBanidos);
  mainMenu(&listaClientes, &listaGuitarras, &totalGuitarras, &totalClientesBanidos, &dia, &mes, &ano);
  exportaDados(listaClientes, listaGuitarras, totalGuitarras);
  //Elimina estruturas
  freeCliente(&listaClientes);
  free(listaGuitarras);
  return 0;
}
