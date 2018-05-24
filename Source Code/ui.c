#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

void mainMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int *totalClientesBanidos,int diaAtual, int mesAtual, int anoAtual){
  //TODO: Implementar a mudança de data
  int option=0;

  do {
    printLogo();
    printf("Gerir:\n1-Guitarras\n2-Clientes\n3-Alugueres\n4-Sair\n>");
    scanf("%d",&option);
    switch (option) {
      case 1:
        guitarrasMenu(listaClientes, listaGuitarras, totalGuitarras);
        break;
      case 2:
        clientesMenu(listaClientes, listaGuitarras, totalGuitarras);
        break;
      case 3:
        alugueresMenu(listaClientes, listaGuitarras, totalGuitarras, totalClientesBanidos,diaAtual, mesAtual, anoAtual);
        break;

      case 4:
        break;

      default:
        printf("Opcao errada!\n");
    }
  } while(option!=4);

}

void guitarrasMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras){
  int option=0;
  printLogo();
  do {
    printf("Guitarras:\n"
      "1-Adicionar uma guitarra ao stock da loja\n"
      "2-Mostrar historico de alugueres de uma guitarra\n"
      "3-Listar todas as guitarras\n"
      "4-Listar guitarras alugadas\n"
      "5-Voltar ao menu anterior\n>");
    scanf("%d",&option);
    switch (option) {
      case 1:
        *listaGuitarras=adicionaGuitarra(*listaGuitarras, totalGuitarras);
        break;
      case 2:
        listarHistoricoAluguerGuitarra(*listaClientes, *listaGuitarras, *totalGuitarras);
        break;
      case 3:
        listarGuitarras(*listaGuitarras, *totalGuitarras);
        break;
      case 4:
        listarGuitarrasAlugadas(*listaGuitarras, *totalGuitarras);
        break;
      case 5:
        break;

      default:
        printf("Opcao errada!\n");
    }
  } while(option!=5);
}

void clientesMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras){
  int option=0;
  printLogo();
  do {
    printf("Clientes:\n"
      "1-Adicionar um novo cliente\n"
      "2-Remover um cliente\n"
      "3-Mostrar estado de um dado cliente\n"
      "4-Listar clientes ativos\n"
      "5-Listar clientes banidos\n"
      "6-Voltar ao menu anterior\n>");
    scanf("%d",&option);
    switch (option) {
      case 1:
        *listaClientes=adicionaCliente(*listaClientes);
        break;
      case 2:
        *listaClientes=removeCliente(*listaClientes);
        break;
      case 3:
        mostraCliente(*listaClientes);
        break;
      case 4:
        listarClientesAtivos(*listaClientes);
        break;
      case 5:
        break;
      case 6:
        break;
      default:
        printf("Opcao errada!\n");
    }
  } while(option!=6);
}

void alugueresMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int *totalClientesBanidos, int diaAtual, int mesAtual, int anoAtual){
  int option=0;
  do {
    printLogo();
    printf("Alugueres:\n"
      "1-Criar um novo aluguer\n"
      "2-Concluir um aluguer\n"
      "3-Lista de alugueres a decorrer\n"
      "4-Voltar ao menu anterior\n>");
    scanf("%d",&option);
    switch (option) {
      case 1:
        criarAluguer(*listaClientes, *listaGuitarras, *totalGuitarras, diaAtual, mesAtual, anoAtual);
        break;
      case 2:
        *listaClientes=concluiAluguer(*listaClientes, totalClientesBanidos, diaAtual, mesAtual, anoAtual);
        break;
      case 3:
        listarAlugueresDecorrer(*listaClientes);
        break;
      case 4:

        break;
      default:
        printf("Opcao errada!\n");
    }
  } while(option!=4);
}
void printLogo(){
  printf(
"                           ____         ___\n"
"                         ,' __ ``.._..''   `.\n"
"                         `.`. ``-.___..-.    :\n"
" ,---..____________________>\\          _,'_  |\n"
"| ---- :Guitarras p' Aluguer/|:.:.:.:.|-|(\\  |\n"
" `-:._,:_|_|_|_|_|_|_|_|_|_|_|.:.:.:.:|-|(/  |\n"
"                        _.' )   ____  '-'    ;\n"
"                       (    `-''  __``-'    /\n"
"                        ``-....-''  ``-..-''\n");
}

void printSeparador(){
  printf("-----------------------------------------------------\n");
}
