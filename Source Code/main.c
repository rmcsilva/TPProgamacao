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
  ptrGuitarra listaGuitarras=NULL;
  ptrCliente listaClientes=NULL;

  printf("Introduza a data do progama!\n");
  alteraData(&dia,&mes,&ano);
  //Importa estrutras dos ficherios de texto para memória
  listaGuitarras=importaGuitarras(listaGuitarras,&totalGuitarras);
  listaClientes=importaClientes(listaClientes,listaGuitarras, totalGuitarras);
  mainMenu(&listaClientes, &listaGuitarras, &totalGuitarras, &dia, &mes, &ano);
  //Exporta estrutras da memória para os ficherios de texto
  exportaDados(listaClientes, listaGuitarras, totalGuitarras);
  //Elimina estruturas da memmória
  freeCliente(&listaClientes);
  free(listaGuitarras);
  return 0;
}
