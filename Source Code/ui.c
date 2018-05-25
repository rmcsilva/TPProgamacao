#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

void mainMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int *totalClientesBanidos, int *diaAtual, int *mesAtual, int *anoAtual){
  int option=0;

  do {
    printDataLogo(*diaAtual, *mesAtual, *anoAtual);
    printf("Gerir:\n1-Guitarras\n2-Clientes\n3-Alugueres\n4-Alterar data\n5-Sair\n>");
    scanf("%d",&option);
    switch (option) {
      case 1:
        guitarrasMenu(listaClientes, listaGuitarras, totalGuitarras, *diaAtual, *mesAtual, *anoAtual);
        break;
      case 2:
        clientesMenu(listaClientes, listaGuitarras, totalGuitarras, *diaAtual, *mesAtual, *anoAtual);
        break;
      case 3:
        alugueresMenu(listaClientes, listaGuitarras, totalGuitarras, totalClientesBanidos,diaAtual, mesAtual, anoAtual);
        break;

      case 4:
        printf("Introduza a nova data do progama!\n");
        alteraData(diaAtual, mesAtual, anoAtual);
        break;

      case 5:
        break;

      default:
        printf("Opcao errada!\n");
    }
  } while(option!=5);

}

void guitarrasMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int diaAtual, int mesAtual, int anoAtual){
  int option=0;
  printDataLogo(diaAtual, mesAtual, anoAtual);
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

void clientesMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int diaAtual, int mesAtual, int anoAtual){
  int option=0;
  printDataLogo(diaAtual, mesAtual, anoAtual);
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
        listarClientesBanidos();
        break;
      case 6:
        break;
      default:
        printf("Opcao errada!\n");
    }
  } while(option!=6);
}

void alugueresMenu(ptrCliente* listaClientes, ptrGuitarra* listaGuitarras, int *totalGuitarras, int *totalClientesBanidos, int *diaAtual, int *mesAtual, int *anoAtual){
  int option=0;
  do {
    printDataLogo(*diaAtual, *mesAtual, *anoAtual);
    printf("Alugueres:\n"
      "1-Criar um novo aluguer\n"
      "2-Concluir um aluguer\n"
      "3-Lista de alugueres a decorrer\n"
      "4-Voltar ao menu anterior\n>");
    scanf("%d",&option);
    switch (option) {
      case 1:
        *listaClientes=criarAluguer(*listaClientes, *listaGuitarras, *totalGuitarras, totalClientesBanidos, *diaAtual, *mesAtual, *anoAtual);
        break;
      case 2:
        *listaClientes=concluiAluguer(*listaClientes, totalClientesBanidos, *diaAtual, *mesAtual, *anoAtual);
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

void alteraData(int *dia, int *mes, int *ano){
  do{
    printf("Dia: ");
    scanf(" %d", dia);
  }while (*dia<1 || *dia>31);

  do{
    printf("Mes: ");
    scanf(" %d", mes);
  }while (*mes<1 || *mes>12);

  do{
    printf("Ano: ");
    scanf(" %d", ano);
  }while (*ano<1900);
}


void printDataLogo(int dia, int mes, int ano){
  printf(
"                           ____         ___\n"
"                         ,' __ ``.._..''   `.\n"
"                         `.`. ``-.___..-.    :\n"
" ,---..____________________>\\          _,'_  |\n"
"| ---- :Guitarras p' Aluguer/|:.:.:.:.|-|(\\  |\n"
" `-:._,:_|_|_|_|_|_|_|_|_|_|_|.:.:.:.:|-|(/  |\n"
"                        _.' )   ____  '-'    ;\n"
"       %2d/%2d/%4d      (    `-''  __``-'    /\n"
"                        ``-....-''  ``-..-''\n",dia,mes,ano);
}

void printSeparador(){
  printf("-----------------------------------------------------\n\n");
}

void tecla(){
  char ch;
  scanf(" %[^\n]c", &ch);
}
