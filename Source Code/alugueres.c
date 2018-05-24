#include "clientes.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

void criarAluguer(ptrCliente listaClientes, ptrGuitarra listaGuitarras, int totalGuitarras, int diaAtual, int mesAtual, int anoAtual){
  //TODO:FALTA VERIFICACOES
  if(listaClientes==NULL){
    printf("Não existem clientes!\n\n");
    return;
  }
  if(listaGuitarras==NULL){
    printf("Não existem guitarras!\n\n");
    return;
  }
  //Verifca se há guitarras disponiveis;
  if(verificaGuitarrasDisponiveis(listaGuitarras, totalGuitarras)==0){
    printf("Não existem guitarras disponiveis!\n\n");
    return;
  }
  int nifTmp;
  ptrCliente clienteAtual=listaClientes;
  listarClientesAtivos(listaClientes);
  printf("Introduza o nif do cliente que deseja criar o aluguer: \n");
  scanf(" %d",&nifTmp);
  //Encontra o cliente com o nif indicado
  while (clienteAtual!=NULL && clienteAtual->nif!=nifTmp) {
    clienteAtual=clienteAtual->prox;
  }
  if(clienteAtual==NULL){
    printf("O cliente não existe\n\n");
    return;
  }
  //Verifca se ao realizar o aluguer atual é ultrupassado o maximo de alugueresa a decorrer
  if(clienteAtual->nAlugueresAtual>MAXIMO_ALUGUERES_DECORRER-1){
    printf("O cliente já tem o máximo de guitarras alugadas permitido!!\n\n");
    return;
  }

  listarGuitarrasDisponiveis(listaGuitarras, totalGuitarras);
  int idTmp;
  printf("Introduza o ID da lista de guitarras a alugar:\n");
  scanf(" %d", &idTmp);
  int index=-1;
  //Procura o indice da guitarra no vetor
  for(int i=0; i<totalGuitarras; i++){
    //Verifica se existe e se é possivel alugar
    if(listaGuitarras[i].id==idTmp && listaGuitarras[i].estado==0){
      index=i;
      break;
    }
  }
  //verifica se o indice está correto
  if(index == -1){
    printf("ID da guitarra inválido!\n");
    return;
  }
  int alugueresConcluidos = clienteAtual->nAlugueresTotal - clienteAtual->nAlugueresAtual;
  if(listaGuitarras[index].valor>GUITARRAS_CARAS && alugueresConcluidos<MINIMO_GUITARRAS_BARATAS){
    printf("O cliente ainda tem de concluir mais %d alugueres de guitarras baratas até poder alugar guitarras caras!!\n\n", MINIMO_GUITARRAS_BARATAS-alugueresConcluidos);
    return;
  }
  //Cria o aluguer
  ptrAluguer tmp = malloc(sizeof(aluguer));
  if(tmp==NULL){
    printf("Erro de alocacao de memoria!!\n");
    return;
  }
  //Atualiza estados
  clienteAtual->nAlugueresAtual++;
  clienteAtual->nAlugueresTotal++;
  listaGuitarras[index].estado=ALUGADA;
  //Preenche a temporaria com os dados
  tmp->guitarra = &listaGuitarras[index];
  tmp->estado=DECORRER;
  tmp->diaInicio=diaAtual;
  tmp->mesInicio=mesAtual;
  tmp->anoInicio=anoAtual;
  tmp->prox=NULL;
  limiteAluguer(diaAtual,mesAtual,anoAtual);

  int valorAluguer= MAXIMO_DIAS_ALUGUER * listaGuitarras[index].precoAluguerDia;
  printf("Valor máximo previsto do aluguer: %d$\n\n", valorAluguer);

  //Verifica se não existem alugueres
  if(clienteAtual->alugueres==NULL){
    clienteAtual->alugueres=tmp;
    return;
  }
  ptrAluguer listaTmp = clienteAtual->alugueres;
  //Procura o ultimo aluguer
  while (listaTmp->prox!=NULL) listaTmp=listaTmp->prox;
  //Coloca o aluguer na ultima posição
  listaTmp->prox=tmp;
  return;
}

void limiteAluguer(int diaAtual, int mesAtual, int anoAtual){
  diaAtual += MAXIMO_DIAS_ALUGUER;
  if(diaAtual > MAXIMO_DIAS_MES){
    diaAtual -= MAXIMO_DIAS_MES;
    if(mesAtual > 12){
      mesAtual=1;
      anoAtual++;
    }else{
      mesAtual++;
    }
  }
  printf("Data limite para entrega do aluguer: %d/%d/%d\n",diaAtual, mesAtual, anoAtual);
}

void listarAlugueresDecorrer(ptrCliente listaClientes){
  if(listaClientes==NULL){
    printf("Não existem clientes!\n\n");
    return;
  }
  //Procura clientes todos
  while (listaClientes!=NULL) {
    ptrAluguer tmp=listaClientes->alugueres;

    if(listaClientes->nAlugueresAtual>0)
      printf("Cliente %s, NIF:%d\n\n",listaClientes->nome, listaClientes->nif);

    while(tmp!=NULL){
      if(tmp->estado==DECORRER){
        printf("Guitarra %s, ID:%d\n",tmp->guitarra->nome, tmp->guitarra->id);
        printf("Data de inicio do aluguer: %d/%d/%d\n",tmp->diaInicio, tmp->mesInicio, tmp->anoInicio);
        limiteAluguer(tmp->diaInicio, tmp->mesInicio, tmp->anoInicio);
        puts("");
      }
      tmp=tmp->prox;
    }
    printSeparador();
    listaClientes=listaClientes->prox;
  }
}

int calculaDiasAtraso(int diaInicio, int mesInicio, int anoInicio, int diaEntrega, int mesEntrega, int anoEntrega){
  int diasAtrasados, totalDiasInicio, totalDiasEntrega;
  //TODO:Banir cliente
  if(anoInicio!=anoEntrega){
    return 365;
  }

  //Reduzir tudo a dias
  totalDiasInicio = diaInicio + MAXIMO_DIAS_MES * mesInicio;
  totalDiasEntrega = diaEntrega + MAXIMO_DIAS_MES * mesEntrega;

  diasAtrasados = totalDiasEntrega - totalDiasInicio;

  diasAtrasados -= MAXIMO_DIAS_ALUGUER;

  if (diasAtrasados<0){
    return 0;
  }else{
    return diasAtrasados;
  }
}


ptrCliente concluiAluguer(ptrCliente listaClientes,int *totalClientesBanidos, int diaAtual, int mesAtual, int anoAtual){
  //TODO: Implementar data
  //TODO: Mostrar listas
  //printf("Concluir aluguer:\n1-Usar a data atual\n2-Indicar outra data\n>");
  int diaEntrega=diaAtual, mesEntrega=mesAtual, anoEntrega=anoAtual;
  int nifTmp;
  printf("Introduza o nif do cliente que deseja concluir o aluguer: \n");
  scanf(" %d",&nifTmp);
  ptrCliente clienteAtual=listaClientes;
  //Encontra o cliente com o nif indicado
  while (clienteAtual!=NULL && clienteAtual->nif!=nifTmp) {
    clienteAtual=clienteAtual->prox;
  }
  if(clienteAtual==NULL){
    printf("O cliente não existe\n\n");
    return listaClientes;
  }
  if(clienteAtual->nAlugueresAtual==0){
    printf("O cliente não tem alugueres a decorrer!\n\n");
    return listaClientes;
  }

  int idTmp;
  //TODO: Imprimir lista guitarras está na função a cima
  printf("Introduza o ID da lista de guitarras alugadas ao cliente:\n");
  scanf(" %d", &idTmp);

  ptrAluguer aluguerTmp = clienteAtual->alugueres;
  while (aluguerTmp!=NULL) {
    if(aluguerTmp->guitarra->id==idTmp && aluguerTmp->estado==DECORRER){
      //encontra o aluguer que ainda está a decorrer com o ID da guitarra indicado
      break;
    }
    aluguerTmp=aluguerTmp->prox;
  }
  if(aluguerTmp==NULL){
    printf("O cliente não tem nenhum aluguer atual com a guitarra de ID %d!\n", idTmp);
    return listaClientes;
  }

  //reduzir a dias
  int diasAlugados = diaEntrega * mesEntrega - aluguerTmp->diaInicio * aluguerTmp->mesInicio;
  //Verificar se a data esta bem introduzida
  if(diasAlugados<0){
    printf("Erro! Verifique a data de entrega do aluguer!!\n");
    return listaClientes;
  }

  int diasAtrasados=calculaDiasAtraso(aluguerTmp->diaInicio, aluguerTmp->mesInicio, aluguerTmp->anoInicio, diaEntrega, mesEntrega, anoEntrega);
  if(diasAtrasados>MAXIMO_DIAS_ATRASO){
    //Bane o cliente
    return banirCliente(listaClientes, totalClientesBanidos, nifTmp, ATRASO);
  }else if (diasAtrasados>0){
    clienteAtual->nEntregasAtrasadas++;
  }

  int estado;
  printf("Verifique o estado da guitarra:\n1-Perfeitas Condicoes\n2-Danificada\n>");
  scanf(" %d",&estado);
  if (estado==1) {
    //Atualizar o estado do aluguer
    aluguerTmp->estado=ENTREGUE;
    //altera estado da guitarra para disponivel, pois está em boas condicoes
    aluguerTmp->guitarra->estado=DISPONIVEL;
  }else if(estado==2) {
    //Atualizar o estado do aluguer
    aluguerTmp->estado=ENTREGA_DANIFICADA;
    //altera estado da guitarra para danificada
    aluguerTmp->guitarra->estado=DANIFICADA;
    clienteAtual->nEntregasDanificadas++;
    //Bane o cliente
    if(clienteAtual->nEntregasDanificadas>MAXIMO_GUITARRAS_DANIFICADAS){
      return banirCliente(listaClientes, totalClientesBanidos, nifTmp, GUITARRAS_DANIFICADAS);
    }
  }else{
    printf("Estado invalido!!\n\n");
  }

  //Reduz o numero de alugueres a decorrer
  clienteAtual->nAlugueresAtual--;
  //Atualiza os dados da entrega do aluguer
  aluguerTmp->diaEntrega=diaEntrega;
  aluguerTmp->mesEntrega=mesEntrega;
  aluguerTmp->anoEntrega=anoEntrega;

  int total = calculaValorAluguer(diasAlugados, diasAtrasados, aluguerTmp->guitarra->estado, aluguerTmp->guitarra->precoAluguerDia, aluguerTmp->guitarra->valor);
  printf("O valor total do aluguer é %d!\n", total);
  return listaClientes;
}

int calculaValorAluguer(int diasAlugados,int diasAtrasados,int estado, int precoAluguerDia, int valorGuitarra){
  int total=0;
  //Se a guitarra estiver danificada o seu valor é acrescentado ao total
  if(estado==DANIFICADA)
    total += valorGuitarra;

  if(diasAlugados>0){
    //Casa nao haja dias atrasados o resultado não é influenciado por é somado 0
    total += diasAlugados*precoAluguerDia + diasAtrasados*MULTA;
  }else{
    //casos o dia de entrega seja igual ao dia de aluguer
    total += precoAluguerDia;
  }
  return total;
}
