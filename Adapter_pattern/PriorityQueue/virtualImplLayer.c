#include"PriorityQueue/PQHandler.h"


static PQImplHandler * findImplHandler(PQImplType implType){

  int handlerIndex = 0;
  PQImplHandler *handler = pqHandlerList[handlerIndex++];
  while( handler!= NULL){
    if(handler->canHandle(implType)){
      return handler;
    }
    handler = pqHandlerList[handlerIndex++];
  }
  return NULL;
}
/***************Interface -start ***************/
PQ *createPQ(PQImplType implType){

  PQImplHandler *handler = findImplHandler(implType);
  if(handler != NULL){
    PQ *pq = handler->createPQ();
    return pq;
  }
  return NULL;
}


void freePQ(PQ *pq){

  ((PQRtti *)pq)->handler->freePQ(pq);
}


int isEmptyPQ(PQ *pq){

  return ((PQRtti *)pq)->handler->isEmptyPQ(pq);
}


void insertItemInPQ(PQ *pq, void *item, isLess less){

  if(((PQRtti *)pq)->handler->insertItemInPQ != NULL){

    ((PQRtti *)pq)->handler->insertItemInPQ(pq, item, less);
  }
}


void insertSortedItemInPQ(PQ *pq, void *item, compareTo compare){

  if( ((PQRtti *)pq)->handler->insertSortedItemInPQ != NULL ){
    ((PQRtti *)pq)->handler->insertSortedItemInPQ(pq, item, compare);
  }
}

void*deleteItemInPQ(PQ *pq, isLess less){

  return ((PQRtti *)pq)->handler->deleteItemInPQ(pq, less);
}


PQ*heapSort(PQ *pq, isLess less){

  if(((PQRtti *)pq)->handler->heapSort != NULL){
    return ((PQRtti *)pq)->handler->heapSort(pq, less);
  }
  fprintf(stderr, "heapSort() - Feature not supported\n");
  return NULL;
}
/***************Interface -end ***************/