#include"PriorityQueue/PQ.h"

typedef struct {

  bool (*canHandle)(PQImplType);
  PQ*(*createPQ)();
  void(*freePQ)(PQ *);
   int(*isEmptyPQ)(PQ *);
  void(*insertItemInPQ)(PQ *, void *, isLess);
  void(*insertSortedItemInPQ)(PQ *, void *, compareTo);
 void*(*deleteItemInPQ)(PQ *, isLess);
   PQ*(*heapSort)(PQ *, isLess);
}PQImplHandler;

typedef struct{
  PQImplHandler *handler;
}PQRtti;

extern PQImplHandler maxHeapHandlerForPQ;
extern PQImplHandler sortedArrayHandlerForPQ;
extern PQImplHandler arrayHandlerForPQ;

extern PQImplHandler *pqHandlerList[];