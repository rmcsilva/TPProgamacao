#include "alugueres.h"
#include "guitarras.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>


void preencheGuitarra(ptrGuitarra guitarra, int id){
  guitarra->id=id;
  guitarra->estado = DISPONIVEL;
  printf("Introduza o nome da guitarra\n");
  scanf(" %[^\n]s", guitarra->nome);

  printf("Introduza o preco do aluguer por dia\n");
  scanf(" %d", &guitarra->precoAluguerDia);

  printf("Introduza o valor da guitarra\n");
  scanf(" %d", &guitarra->valor);
}

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

void listarGuitarras(ptrGuitarra guitarras, int total){
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

//Devolve um ID unico para as guitarras
int devolveID(ptrGuitarra listaGuitarras, int total){
  int id;
  do {
    printf("Introduza o ID da nova guitarra:\n");
    scanf(" %d", &id);
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

int verificaGuitarrasDisponiveis(ptrGuitarra listaGuitarras, int total){
  int count=0;
  for(int i=0; i<total; i++){
    if(listaGuitarras[i].estado==DISPONIVEL)
      count++;
  }
  return count;
}
