#include "clientes.h"
#include "ficheiros.h"
#include "ui.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  //TODO:Implementar data inicial(telefone)
  //TODO:REVER alocações de memoria
  //TODO: Melhorar estruras de dados, ordenar por id / nif
  //TODO:Metodo para perguntar nif ou id geral
  //TODO:Implementar ID unico guitarras
  int dia=29, mes=5, ano=2018;
  int totalGuitarras=0;
  int totalClientesBanidos=0;
  ptrGuitarra listaGuitarras=NULL;
  ptrCliente listaClientes=NULL;

  listaGuitarras=importaGuitarras(listaGuitarras,&totalGuitarras);
  listaClientes=importaClientes(listaClientes,listaGuitarras, totalGuitarras);
  importaTotalClientesBanidos(&totalClientesBanidos);
  mainMenu(&listaClientes, &listaGuitarras, &totalGuitarras, &totalClientesBanidos, dia, mes, ano);
  exportaDados(listaClientes, listaGuitarras, totalGuitarras);

  freeCliente(&listaClientes);
  free(listaGuitarras);
  return 0;
}
