#include "clientes.h"
#include "ficheiros.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

ptrCliente adicionaCliente(ptrCliente listaClientes){
  int nifTmp;
  //Verifica se o cliente já existe
  //TODO: Verificar nos clientes banidos!!
  do{
    printf("Introduza o NIF do novo cliente\n");
    scanf(" %d", &nifTmp);
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
  //TODO:REVER
  if(listaClientes==NULL){
    printf("Não existem clientes!\n\n");
    return listaClientes;
  }
  int nifTmp;
  printf("Introduza o nif do cliente a remover:\n");
  scanf(" %d", &nifTmp);

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
      scanf(" %d",&option);
      if(option==0){
        printf("Operação cancelada\n\n");
        return listaClientes;
      }
    }
    ptrAluguer aluguerAtual, aluguerAnterior=NULL;
    aluguerAtual=clienteAtual->alugueres;
    //Apaga todos os alugueres associados ao cliente
    //TODO:TESTARRR
    while(aluguerAtual!=NULL){
      aluguerAtual->guitarra->estado=DISPONIVEL;
      aluguerAnterior=aluguerAtual;
      aluguerAtual=aluguerAtual->prox;
      free(aluguerAtual);
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

ptrCliente banirCliente(ptrCliente listaClientes,int *totalClientesBanidos, int nif, int motivo){
  //TODO: Atualizar o ficheiro binários
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
    //TODO:TESTARRR
    while(aluguerAtual!=NULL){
      aluguerAtual->guitarra->estado=DISPONIVEL;
      aluguerAnterior=aluguerAtual;
      aluguerAtual=aluguerAtual->prox;
      free(aluguerAtual);
    }
  }

  adicionaClienteBanido(totalClientesBanidos, clienteAtual->nome, clienteAtual->nif, motivo);
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

//devolve um se o cliente já existir, devolve 0 caso contrário
int verificaCliente(ptrCliente listaClientes, int nif){
  //TODO: Falta verificar nos clientes banidos
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


//BASE MAIS QUE COMPLETA ADPTAR GERAL
void mostraTudoETodos(ptrCliente listaClientes){
  ptrAluguer tmp;

  while(listaClientes != NULL){
    printf("Nome do cliente: %s\n", listaClientes->nome);
    printf("Nif do cliente: %d\n", listaClientes->nif);
    printf("Número de alugueres total do cliente: %d\n", listaClientes->nAlugueresTotal);
    printf("Número de alugueres atual do cliente: %d\n", listaClientes->nAlugueresAtual);
    printf("Número de entregas atrasadas: %d\n", listaClientes->nEntregasAtrasadas);
    printf("Número de entregas danificadas: %d\n", listaClientes->nEntregasDanificadas);
    tmp=listaClientes->alugueres;
    while (tmp != NULL) {
      printf("Data de inicio: %d\\%d\\%d\n",
            tmp->diaInicio, tmp->mesInicio, tmp->anoInicio);

      //Verifica se já foi entregue
      printf("Estado do aluguer: ");
      if(tmp->estado){
        tmp->estado==ENTREGUE ? printf("Entregue\n") : printf("Entregue danificado\n");
        printf("Data da entrega: %d\\%d\\%d\n"
            ,tmp->diaEntrega, tmp->mesEntrega, tmp->anoEntrega);
      }else{
        printf("A decorrer\n");
        //TODO: data prevista de entrega
      }
      tmp = tmp->prox;
    }
    puts("");
    listaClientes = listaClientes->prox;
  }
}

void mostraCliente(ptrCliente listaClientes){
  if(listaClientes==NULL){
    printf("Não existem clientes!\n\n");
    return;
  }
  int nifTmp;
  printf("Introduza o nif do cliente a mostrar:\n");
  scanf(" %d", &nifTmp);
  //TODO:Fazer introduzir novamente se não exister cliente?

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

void listarHistoricoAluguerGuitarra(ptrCliente listaClientes, ptrGuitarra listaGuitarras, int total){
  int idTmp, count=0;

  if(listaGuitarras==NULL){
    printf("Não existem guitarras!!\n\n");
    printSeparador();
    return;
  }

  if(listaClientes==NULL){
    printf("Não existem clientes!\n\n");
    printSeparador();
    return;
  }

  printf("Introduza o id da guitarra que deseja procurar o historico:\n");
  scanf(" %d", &idTmp);
  if(devolveIndexGuitarra(listaGuitarras, total, idTmp) == -1){
    printf("A guitarra não existe!!\n");
    printSeparador();
    return;
  }
  while (listaClientes!=NULL) {
    ptrAluguer tmpAluguer=listaClientes->alugueres;
    while (tmpAluguer!=NULL) {
      if(tmpAluguer->guitarra->id==idTmp && tmpAluguer->estado>0){
        //Para verificar se a guitarra tem historico
        count++;
        printf("Cliente %s, nif:%d \n",listaClientes->nome, listaClientes->nif);
        printf("Data de inicio do emprestimo: %d/%d/%d\n", tmpAluguer->diaInicio, tmpAluguer->mesInicio, tmpAluguer->anoInicio);
        printf("Data final do emprestimo: %d/%d/%d\n", tmpAluguer->diaEntrega, tmpAluguer->mesEntrega, tmpAluguer->anoEntrega);
        int diasAtraso=calculaDiasAtraso(tmpAluguer->diaInicio, tmpAluguer->mesInicio, tmpAluguer->anoInicio, tmpAluguer->diaEntrega, tmpAluguer->mesEntrega, tmpAluguer->anoEntrega);
        //TODO: Banir cliente se dias de atraso exceder a 20?
        diasAtraso==0 ? printf("Emprestimo concluido sem dias de atraso!\n\n") : printf("Emprestimo concluido com %d dias de atraso!!\n\n", diasAtraso);
        printSeparador();
      }
      tmpAluguer=tmpAluguer->prox;
    }
    listaClientes=listaClientes->prox;
  }

  if(count==0){
    printf("A guitarra com o id %d, ainda não tem historico!\n\n", idTmp);
    printSeparador();
  }

  return;
}

void freeCliente(ptrCliente* listaClientes){
  if(listaClientes==NULL)
    return;

  ptrCliente tmpClienteAtual = *listaClientes;
  ptrCliente tmpClienteAnt;
  ptrAluguer tmpAluguerAtual= (*listaClientes)->alugueres;
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
