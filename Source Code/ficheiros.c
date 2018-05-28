#include "ficheiros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
ptrGuitarra importaGuitarras(ptrGuitarra listaGuitarras, int *total){
  FILE *f;
  f=fopen(NOME_FICHEIRO_GUITARRAS, "r");
  int id,precoAluguerDia,valor,estado;
  char nome[100];
  if(f==NULL){
    printf("Erro ao abrir o ficheiro %s!\n",NOME_FICHEIRO_GUITARRAS);
    return listaGuitarras;
  }
  ptrGuitarra tmp;
  //TODO:Verificações ordem!
  while (fscanf(f," %d %d %d %d %[^\n]s",&id, &precoAluguerDia, &valor, &estado, nome)==5) {
    //Verifica se o ID é único
    if(devolveIndexGuitarra(listaGuitarras, *total, id) != -1){
      printf("A guitarra com o ID %d no ficheiro %s já existe e vai ser ignorada, por favor verifique o ficheiro!\n", id, NOME_FICHEIRO_GUITARRAS );
      continue;
    }
    tmp=realloc(listaGuitarras, sizeof(guitarra)*(*total+1));
    if(tmp==NULL){
      printf("Erro de alocacao de memoria!!\n");
      return listaGuitarras;
    }
    listaGuitarras=tmp;
    listaGuitarras[*total].id=id;
    listaGuitarras[*total].precoAluguerDia=precoAluguerDia;
    listaGuitarras[*total].valor=valor;
    listaGuitarras[*total].estado=estado;
    strcpy(listaGuitarras[*total].nome, nome);
    (*total)++;
  }
  fclose(f);
  printf("Guitarras importadas com sucesso!\n");
  return listaGuitarras;
}

ptrCliente importaClientes(ptrCliente listaClientes,ptrGuitarra listaGuitarras, int total){
  FILE *f;
  f=fopen(NOME_FICHEIRO_CLIENTES, "r");
  if(f==NULL){
    printf("Erro ao abrir o ficheiro %s!\n",NOME_FICHEIRO_CLIENTES);
    return listaClientes;
  }
  //TODO:ADD VERIFICACOES
  int nif,nAlugueresTotal;
  char nome[100];
  ptrCliente tmpCliente;
  ptrCliente listaTmp;
  ptrAluguer alugueresTmp;
  while (fscanf(f, " %d %d %[^\n]s", &nif, &nAlugueresTotal, nome)==3) {
    //Verifica se o NIF é único, a função devolve 1 se não for
    if(verificaCliente(listaClientes, nif)){
      printf("O cliente com o NIF %d no ficheiro %s já existe e vai ser ignorado, por favor verifique o ficheiro!\n", nif, NOME_FICHEIRO_CLIENTES );
      if(nAlugueresTotal>0){
        int id,estado,diaI,mesI,anoI;
        for(int i=0; i<nAlugueresTotal; i++) {
          fscanf(f, " %d %d %d %d %d",&id, &estado, &diaI, &mesI, &anoI);
          if(estado>0){
            int diaE,mesE,anoE;
            fscanf(f, " %d %d %d",&diaE, &mesE, &anoE);
          }
        }
      }
      continue;
    }


    tmpCliente=malloc(sizeof(cliente));
    if(tmpCliente==NULL){
      printf("Erro de alocacao de memoria!!\n");
      return listaClientes;
    }
    //Preenche
    strcpy(tmpCliente->nome, nome);
    tmpCliente->nif=nif;
    tmpCliente->nAlugueresTotal=nAlugueresTotal;
    tmpCliente->nAlugueresAtual=0;
    tmpCliente->nEntregasAtrasadas=0;
    tmpCliente->nEntregasDanificadas=0;
    tmpCliente->prox=NULL;
    tmpCliente->alugueres=NULL;

    if(nAlugueresTotal>0){
      int id,estado,diaI,mesI,anoI,index;
      for(int i=0; i<nAlugueresTotal; i++) {
        fscanf(f, " %d %d %d %d %d",&id, &estado, &diaI, &mesI, &anoI);
        ptrAluguer tmpAluguer=malloc(sizeof(aluguer));
        if(tmpAluguer==NULL){
          printf("Erro de alocacao de memoria!!\n");
          return listaClientes;
        }
        //index fica a -1 se a guitarra não estiver no vetor
        index=devolveIndexGuitarra(listaGuitarras, total, id);
        //Verifica se a guitarra esta na lista de guitarras
        if(index != -1){
          tmpAluguer->guitarra=&listaGuitarras[index];
        }else{
          printf("A guitarra com o id %d, não está na lista de guitarras!\n",id);
          //Para corrigir a posição no ficheiro
          if(estado>0){
            int diaE,mesE,anoE;
            fscanf(f, " %d %d %d",&diaE, &mesE, &anoE);
          }
          continue;
        }
        tmpAluguer->diaInicio=diaI;
        tmpAluguer->mesInicio=mesI;
        tmpAluguer->anoInicio=anoI;
        tmpAluguer->estado=estado;
        tmpAluguer->prox=NULL;
        if(estado>0){
          int diaE,mesE,anoE;
          fscanf(f, " %d %d %d",&diaE, &mesE, &anoE);
          tmpAluguer->diaEntrega=diaE;
          tmpAluguer->mesEntrega=mesE;
          tmpAluguer->anoEntrega=anoE;
          int diasAtraso=calculaDiasAtraso(tmpAluguer->diaInicio, tmpAluguer->mesInicio, tmpAluguer->anoInicio, tmpAluguer->diaEntrega, tmpAluguer->mesEntrega, tmpAluguer->anoEntrega);
          if(diasAtraso>0)
            tmpCliente->nEntregasAtrasadas+=1;
          if(estado==ENTREGA_DANIFICADA)
            tmpCliente->nEntregasDanificadas+=1;
        }else{
          tmpCliente->nAlugueresAtual+=1;
        }

        //Verifica se é o primeiro aluguer do cliente
        if(tmpCliente->alugueres==NULL){
          tmpCliente->alugueres=tmpAluguer;
          alugueresTmp=tmpCliente->alugueres;
        }else{
          //Coloca o ultimo aluguer
          alugueresTmp->prox=tmpAluguer;
          //avança para o ultimo aluguer
          alugueresTmp=tmpAluguer;
        }
      }
    }
    //Verifica se é o primeiro cliente da lista
    if(listaClientes==NULL){
      listaClientes=tmpCliente;
      listaTmp=listaClientes;
    }else{
      //Não é preciso procurar por todos so clientes pois temos sempre o cliente anterior
      listaTmp->prox=tmpCliente;
      //Avança para o ultimo cliente
      listaTmp=tmpCliente;
    }
  }
  fclose(f);
  printf("Clientes importados com sucesso\n");
  return listaClientes;
}

void exportaDados(ptrCliente listaClientes,ptrGuitarra listaGuitarras, int total){
  FILE *f;
  //Exporta Guitarras
  f=fopen(NOME_FICHEIRO_GUITARRAS, "w");
  //Imprime guitarras
  for(int i=0; i<total; i++){
    fprintf(f, "%d %d %d %d %s\n", listaGuitarras[i].id, listaGuitarras[i].precoAluguerDia, listaGuitarras[i].valor, listaGuitarras[i].estado, listaGuitarras[i].nome);
  }
  fclose(f);

  //Exporta Clientes
  f=fopen(NOME_FICHEIRO_CLIENTES, "w");
  //Imprime clientes
  while (listaClientes!=NULL) {
    ptrAluguer tmpAluguer = listaClientes->alugueres;
    fprintf(f, "%d %d %s\n",listaClientes->nif, listaClientes->nAlugueresTotal, listaClientes->nome);
    while (tmpAluguer != NULL) {
      fprintf(f, "%d %d %d %d %d ",tmpAluguer->guitarra->id, tmpAluguer->estado, tmpAluguer->diaInicio, tmpAluguer->mesInicio, tmpAluguer->anoInicio);
      if(tmpAluguer->estado > 0)
        fprintf(f, "%d %d %d\n", tmpAluguer->diaEntrega, tmpAluguer->mesEntrega, tmpAluguer->anoEntrega);
      else
        fprintf(f, "\n");
      tmpAluguer=tmpAluguer->prox;
    }
    fprintf(f, "\n");
    listaClientes=listaClientes->prox;
  }
  fclose(f);
}

void importaTotalClientesBanidos(int *totalClientesBanidos){
  FILE *f;
  f=fopen(NOME_FICHEIRO_CLIENTES_BANIDOS, "rb");
  if(f==NULL){
    printf("Erro ao abrir o ficheiro %s!\n",NOME_FICHEIRO_CLIENTES_BANIDOS);
    return;
  }
  clienteBanido clienteBanido;
  //Fazer desta forma pois ao guardar o inteiro é facilmente alterável
  while(fread(&clienteBanido, sizeof(clienteBanido), 1, f)==1)
    (*totalClientesBanidos)++;
  //Devolve número total de clientes banidos
  printf("Clientes banidos importados com sucesso\n");
  fclose(f);
  return;
}

void adicionaClienteBanido(int *totalClientesBanidos, char nome[100], int nif, int motivo){
  FILE *f;
  f=fopen(NOME_FICHEIRO_CLIENTES_BANIDOS, "ab");
  if(f==NULL){
    printf("Erro ao abrir o ficheiro %s!\n",NOME_FICHEIRO_CLIENTES_BANIDOS);
    return;
  }
  clienteBanido clienteBanido;
  strcpy(clienteBanido.nome, nome);
  clienteBanido.nif=nif;
  clienteBanido.motivo=motivo;
  //Append abre o ficheiro no final,logo é só adicionar
  if(fwrite(&clienteBanido, sizeof(clienteBanido), 1, f)==1){
    (*totalClientesBanidos)++;
  }else{
    printf("Erro ao adiconar cliente banido no ficheiro %s!\n",NOME_FICHEIRO_CLIENTES_BANIDOS);
  }
  fclose(f);
  return;
}
