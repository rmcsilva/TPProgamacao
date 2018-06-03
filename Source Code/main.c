#include "clientes.h"
#include "ficheiros.h"
#include "ui.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  //TODO: Acrescentar cliente banido por atraso e guitarras danificadas
  //TODO: Melhorar UI
  //TODO: Testar tudo
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
