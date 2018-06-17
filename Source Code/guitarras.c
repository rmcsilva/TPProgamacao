#include "clientes.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

ptrGuitarra adicionaGuitarra(ptrGuitarra guitarras, int *total){
  ptrGuitarra tmp;
  tmp=realloc(guitarras, sizeof(guitarra)*(*total+1));
  if(tmp==NULL){
    printf("Erro de alocacao de memoria!!\n");
    return guitarras;
  }
  guitarras=tmp;
  //Garante um ID único
  int id = devolveID(guitarras,*total);
  preencheGuitarra(&guitarras[*total], id);
  (*total)++;
  return guitarras;
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
  idTmp = scanfInteiro();
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


void listarGuitarras(ptrGuitarra guitarras, int total){
  if(total==0){
    printf("Não existem guitarras!!\n\n");
    printSeparador();
    return;
  }

  for(int i=0; i<total; i++){
    printf("Nome da guitarra: %s\n", guitarras[i].nome);
    printf("Estado: ");
    //Verifica se está indesponível
    if(guitarras[i].estado)
      guitarras[i].estado==ALUGADA ? printf("Alugada\n") : printf("Danificada\n");
    else
      printf("Disponivel\n");

    printf("ID da guitarra: %d\n", guitarras[i].id);
    printf("Preco do aluguer da guitarra por dia: %d\n", guitarras[i].precoAluguerDia);
    printf("Valor da Guitarra: %d\n\n", guitarras[i].valor);
    printSeparador();
  }
}


void listarGuitarrasAlugadas(ptrGuitarra guitarras, int total){
  if(guitarras==NULL){
    printf("Não existem guitarras!!\n\n");
    printSeparador();
    return;
  }
  printf("Guitarras Alugadas:\n");
  for(int i=0; i<total; i++){
    if(guitarras[i].estado==ALUGADA){
      printf("Nome da guitarra: %s\n", guitarras[i].nome);
      printf("ID da guitarra: %d\n", guitarras[i].id);
      printf("Preco do aluguer da guitarra por dia: %d\n", guitarras[i].precoAluguerDia);
      printf("Valor da Guitarra: %d\n\n", guitarras[i].valor);
      printSeparador();
    }
  }
}


void listarGuitarrasDisponiveis(ptrGuitarra guitarras, int total){
  if(guitarras==NULL){
    printf("Não existem guitarras!!\n\n");
    printSeparador();
    return;
  }
  printf("Guitarras disponiveis:\n");
  for(int i=0; i<total; i++){
    if(guitarras[i].estado==DISPONIVEL){
      printf("Nome da guitarra: %s\n", guitarras[i].nome);
      printf("ID da guitarra: %d\n", guitarras[i].id);
      printf("Preco do aluguer da guitarra por dia: %d\n", guitarras[i].precoAluguerDia);
      printf("Valor da Guitarra: %d\n\n", guitarras[i].valor);
      printSeparador();
    }
  }
}


void preencheGuitarra(ptrGuitarra guitarra, int id){
  guitarra->id=id;
  guitarra->estado = DISPONIVEL;
  printf("Introduza o nome da guitarra\n");
  scanf(" %[^\n]s", guitarra->nome);

  printf("Introduza o preco do aluguer por dia\n");
  guitarra->precoAluguerDia = scanfInteiro();

  printf("Introduza o valor da guitarra\n");
  guitarra->valor = scanfInteiro();
}


//Devolve um ID unico para as guitarras
int devolveID(ptrGuitarra listaGuitarras, int total){
  int id;
  do {
    printf("Introduza o ID da nova guitarra:\n");
    id = scanfInteiro();
    //Se a lita das guitarras estiver vazia não é preciso verificar
    if (listaGuitarras==NULL) {
      return id;
    }
    if (devolveIndexGuitarra(listaGuitarras, total, id) != -1)
      printf("Já existe uma guitarra com o ID %d!\n", id);
    else
      return id;
  } while(1);
}


//devolve -1 se não existir
int devolveIndexGuitarra(ptrGuitarra listaGuitarras, int total, int id){
  for(int i=0; i<total; i++){
    if(listaGuitarras[i].id==id)
      return i;
  }
  return -1;
}


//Devolve o número de guitarras disponiveis
int verificaGuitarrasDisponiveis(ptrGuitarra listaGuitarras, int total){
  int count=0;
  for(int i=0; i<total; i++){
    if(listaGuitarras[i].estado==DISPONIVEL)
      count++;
  }
  return count;
}
