#include "clientes.h"
#include "ficheiros.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

ptrCliente adicionaCliente(ptrCliente listaClientes){
  int nifTmp;
  //Verifica se o cliente já existe
  do{
    printf("Introduza o NIF do novo cliente\n");
    nifTmp = scanfInteiro();
    //Se listaClientes tiver vazio não é necessario verificar
    if(listaClientes==NULL) break;
    //Verifica se o cliente já existe
    if(verificaCliente(listaClientes, nifTmp))
      printf("O cliente com o NIF %d já existe\n", nifTmp);
    else
      break;
  }while(1);

  ptrCliente tmp = malloc(sizeof(cliente));
  if(tmp==NULL){
    printf("Erro de alocacao de memoria!!\n");
    return listaClientes;
  }

  printf("Introduza o nome do novo cliente: \n");
  scanf(" %[^\n]s\n", tmp->nome);

  tmp->nif = nifTmp;
  tmp->nAlugueresAtual = 0;
  tmp->nAlugueresTotal = 0;
  tmp->nEntregasAtrasadas = 0;
  tmp->nEntregasDanificadas = 0;
  tmp->prox=NULL;
  tmp->alugueres=NULL;

  //Verifica se é o primeiro nó da lista
  if(listaClientes==NULL){
    listaClientes=tmp;
    return listaClientes;
  }
  ptrCliente listaTmp = listaClientes;
  //Procura ultimo cliente
  while (listaTmp->prox!=NULL) listaTmp=listaTmp->prox;
  //Insere no fim da lista ligada
  listaTmp->prox=tmp;

  return listaClientes;
}


ptrCliente removeCliente(ptrCliente listaClientes){
  if(listaClientes==NULL){
    printf("Não existem clientes!\n\n");
    return listaClientes;
  }
  int nifTmp;
  printf("Introduza o nif do cliente a remover:\n");
  nifTmp = scanfInteiro();

  ptrCliente clienteAtual,clienteAnterior=NULL;
  clienteAtual = listaClientes;
  //Procura o cliente
  while(clienteAtual!=NULL && clienteAtual->nif!=nifTmp){
    clienteAnterior=clienteAtual;
    clienteAtual=clienteAtual->prox;
  }
  //Verifica se existe
  if(clienteAtual==NULL){
    printf("O cliente não existe\n\n");
    return listaClientes;
  }

  //Verifica se tem alugueres
  if (clienteAtual->nAlugueresTotal>0) {
    //Verifica se tem alugueres a decorrer
    if(clienteAtual->nAlugueresAtual>0){
      printf("O cliente ainda tem guitarras em sua posse!\nDeseja continuar? 1-Sim  0-Nao\n");
      int option;
      option = scanfInteiro();
      if(option==0){
        printf("Operação cancelada\n\n");
        return listaClientes;
      }
    }
    ptrAluguer aluguerAtual, aluguerAnterior=NULL;
    aluguerAtual=clienteAtual->alugueres;
    //Apaga todos os alugueres associados ao cliente
    while(aluguerAtual!=NULL){
      aluguerAtual->guitarra->estado=DISPONIVEL;
      aluguerAnterior=aluguerAtual;
      aluguerAtual=aluguerAtual->prox;
      free(aluguerAnterior);
    }
  }
  //Se a lista só tive um nó então o anterior está a null
  if(clienteAnterior==NULL)
    listaClientes=clienteAtual->prox;
  else
    clienteAnterior->prox = clienteAtual->prox;
  free(clienteAtual);
  printf("Cliente removido com sucesso!\n\n");
  return listaClientes;
}


ptrCliente banirCliente(ptrCliente listaClientes, int nif, int motivo){
  ptrCliente clienteAtual,clienteAnterior=NULL;
  clienteAtual = listaClientes;
  //Procura o cliente
  while(clienteAtual!=NULL && clienteAtual->nif!=nif){
    clienteAnterior=clienteAtual;
    clienteAtual=clienteAtual->prox;
  }
  //Verifica se tem alugueres
  if (clienteAtual->nAlugueresTotal>0) {
    ptrAluguer aluguerAtual, aluguerAnterior=NULL;
    aluguerAtual=clienteAtual->alugueres;
    //Apaga todos os alugueres associados ao cliente
    while(aluguerAtual!=NULL){
      aluguerAtual->guitarra->estado=DISPONIVEL;
      aluguerAnterior=aluguerAtual;
      aluguerAtual=aluguerAtual->prox;
      free(aluguerAnterior);
    }
  }

  adicionaClienteBanido(clienteAtual->nome, clienteAtual->nif, motivo);
  //Se a lista só tive um nó então o anterior está a null
  if(clienteAnterior==NULL)
    listaClientes=clienteAtual->prox;
  else
    clienteAnterior->prox = clienteAtual->prox;
  free(clienteAtual);
  printf("Cliente com o nif %d foi banido ",nif);
  motivo==ATRASO ? printf("por causa de alugueres atrasados!\n\n")
                 : printf("por causa da entrega de guitarras danificadas!\n\n");
  return listaClientes;
}


void mostraCliente(ptrCliente listaClientes){
  if(listaClientes==NULL){
    printf("Não existem clientes!\n\n");
    return;
  }
  int nifTmp;
  printf("Introduza o nif do cliente a mostrar:\n");
  nifTmp = scanfInteiro();

  while(listaClientes != NULL){
    if(listaClientes->nif==nifTmp){
      printf("\nNome do cliente: %s\n", listaClientes->nome);
      printf("Número de guitarras em sua posse: %d\n", listaClientes->nAlugueresAtual);
      printf("Número de alugueres total do cliente: %d\n", listaClientes->nAlugueresTotal);
      printf("Número de entregas atrasadas: %d\n", listaClientes->nEntregasAtrasadas);
      printf("Número de entregas danificadas: %d\n\n", listaClientes->nEntregasDanificadas);
      printSeparador();
      break;
    }
    listaClientes = listaClientes->prox;
  }
  if(listaClientes==NULL){
    printf("\nO cliente não existe!\n\n");
    printSeparador();
  }

}


void listarClientesAtivos(ptrCliente listaClientes){
  if(listaClientes==NULL){
    printf("Não existem clientes!\n\n");
    printSeparador();
    return;
  }
  while(listaClientes != NULL){
    printf("Nome do cliente: %s\n", listaClientes->nome);
    printf("Nif do cliente: %d\n\n", listaClientes->nif);
    printSeparador();
    listaClientes = listaClientes->prox;
  }
}


void listarClientesBanidos(){
  FILE *f;
  f=fopen(NOME_FICHEIRO_CLIENTES_BANIDOS, "rb");
  if(f==NULL){
    printf("Erro ao abrir o ficheiro %s!\n",NOME_FICHEIRO_CLIENTES_BANIDOS);
    printSeparador();
    return;
  }
  clienteBanido clienteBanido;
  while (fread(&clienteBanido, sizeof(clienteBanido), 1, f)==1) {
    printf("Nome do cliente: %s\n", clienteBanido.nome);
    printf("Nif do cliente: %d\n", clienteBanido.nif);
    printf("O cliente foi banido ");
    clienteBanido.motivo==ATRASO ? printf("por causa de alugueres atrasados!\n\n")
                                 : printf("por causa da entrega de guitarras danificadas!\n\n");
    printSeparador();
  }
  fclose(f);
  return;
}


//devolve um se o cliente já existir, devolve 0 caso contrário
int verificaCliente(ptrCliente listaClientes, int nif){
  while (listaClientes!=NULL) {
    if(listaClientes->nif==nif) return 1;
    listaClientes=listaClientes->prox;
  }

  FILE *f;
  f=fopen(NOME_FICHEIRO_CLIENTES_BANIDOS, "rb");
  //Como não há clientes banidos devolve 0
  if(f==NULL) return 0;

  clienteBanido clienteBanido;
  while (fread(&clienteBanido, sizeof(clienteBanido), 1, f)==1)
    if (clienteBanido.nif==nif) return 1;

  fclose(f);

  return 0;
}


//Apaga todos os clientes e os seus alugueres
void freeCliente(ptrCliente* listaClientes){
  if(listaClientes==NULL)
    return;

  ptrCliente tmpClienteAtual = *listaClientes;
  //Ponteiro para cliente auxiliar que vai ser apagado quando se percorre a lista de clientes
  ptrCliente tmpClienteAnt;
  ptrAluguer tmpAluguerAtual= (*listaClientes)->alugueres;
  //Mesma lógica para os alugueres
  ptrAluguer tmpAluguerAnt;

  while (tmpClienteAtual!=NULL) {
    while (tmpAluguerAtual!=NULL) {
      tmpAluguerAnt=tmpAluguerAtual;
      tmpAluguerAtual=tmpAluguerAtual->prox;
      free(tmpAluguerAnt);
    }
    tmpClienteAnt=tmpClienteAtual;
    tmpClienteAtual=tmpClienteAtual->prox;
    free(tmpClienteAnt);
  }
}
