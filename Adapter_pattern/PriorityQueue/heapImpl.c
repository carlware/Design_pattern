#include"PriorityQueue/PQHandler.h"


#define PQ_FIRST_ITEM_INDEX 1
/********************* Repr-start *********************/

typedef struct PQ{

  PQRtti rtti;
  List *list;
}PQ;

/********************* Repr-end ***********************/

static void listInsertItemInPQ(List *, void *, isLess);
static void *SwapDeleteLastItemInPQ(List *, isLess);
static PQ * sortMaxHeap(PQ *, isLess);
static PQ *makeBottomUpMaxHeap(PQ *, isLess);
/*********************Usage - start *******************/

bool MaxHeapCanHandle(PQImplType implType){
  if(implType == PQ_USING_HEAP){
    return true;
  }
  return false;
}


PQ* createMaxHeapForPQ(void){

  //printf("createMaxHeapForPQ() - Enter\n");
  PQ *pq = malloc(sizeof(PQ));
  pq->list = createList(ARRAY_IMPL);
  (pq->rtti).handler = &maxHeapHandlerForPQ;

  void *noUseItem = NULL;
  //printf("Before insertItem()\n");
  insertItem(pq->list, noUseItem);// first array element is unused in PQ

  return pq;
}


void freeMaxHeapForPQ(PQ *pq){

  //printf("freeMaxHeapForPQ() - Enter\n");
  if(pq != NULL){
    freeList(pq->list); //free(NULL) is no-op(ISO-IEC 9899, section 7.20.3.2 )
    free(pq);
  }
}

int isEmptyMaxHeapForPQ(PQ *pq){

  //printf("isEmptyMaxHeapForPQ() - Enter\n");
  if(pq == NULL){

    fprintf(stderr, "isEmptyMaxHeapForPQ() - NULL is passed\n");
    return -1;
  }
  if(getSize(pq->list) - 1 == 0){
    return 1;
  }
  return 0;
}


void insertMaxHeapItemForPQ(PQ *pq, void *item, isLess less){

  //printf("insertMaxHeapItemForPQ() - Enter\n");
  listInsertItemInPQ(pq->list, item, less);
}

void* delMaxHeapItemForPQ(PQ *pq, isLess less){

  //printf("delMaxHeapItemForPQ() - Enter\n");
  int empty = isEmptyMaxHeapForPQ(pq);
  if(empty == -1){

    fprintf(stderr, "delMaxHeapItemForPQ() - NULL PQ is passed\n");
    return NULL;
  }else if(empty){

    fprintf(stderr, "delMaxHeapItemForPQ() - PQ is empty \n");
    return NULL;
  }

  void *maxElement = SwapDeleteLastItemInPQ(pq->list, less);

  if(maxElement == NULL){
    fprintf(stdout, "PQ is empty\n");
    return NULL;
  }
  return maxElement;
}


PQ* heapSortMinHeap(PQ *pq, isLess less){

  PQ *maxHeap = makeBottomUpMaxHeap(pq, less);
  return sortMaxHeap(maxHeap, less);

}

/**********************Usage - end ********************/


/**********************Helper function - start **********/
static PQ* sortMaxHeap(PQ *maxHeap, isLess less){

  int listLastIndex = getSize(maxHeap->list)-1;
  while(listLastIndex > 1){

    swap(maxHeap->list, PQ_FIRST_ITEM_INDEX, listLastIndex--);
    sink(maxHeap->list, PQ_FIRST_ITEM_INDEX, less);
  }
  PQ *minHeap = maxHeap;
  return minHeap;
}


static PQ *makeBottomUpMaxHeap(PQ *pq, isLess less){

  int sizeOfList = getSize(pq->list);
  int parentIndex = (sizeOfList-1)/2;

  for(;parentIndex >= 1;parentIndex--){
    sink(pq->list, parentIndex, less);
  }
  return pq;
}

static void listInsertItemInPQ(List *arrayList, void *newItem, isLess less){

  insertItem(arrayList, newItem);
  int lastElementIndex = getSize(arrayList)-1;
  printf("last index is: %d\n", lastElementIndex);
  swim(arrayList, lastElementIndex, less);

}


static void *SwapDeleteLastItemInPQ(List *list, isLess less){

  int firstIndex = PQ_FIRST_ITEM_INDEX;
  int lastIndex = getSize(list)-1;
  if(lastIndex > PQ_FIRST_ITEM_INDEX){
    swap(list, firstIndex, lastIndex);
  }
  void *maxItem = (void *)deleteLastItem(list);
  sink(list, PQ_FIRST_ITEM_INDEX, less);
  return maxItem;
}

/**********************Helper function - end *************/
PQImplHandler maxHeapHandlerForPQ ={
  MaxHeapCanHandle,
  createMaxHeapForPQ,
  freeMaxHeapForPQ,
  isEmptyMaxHeapForPQ,
  insertMaxHeapItemForPQ,
  NULL,
  delMaxHeapItemForPQ,
  heapSortMinHeap
};