#include"PriorityQueue/PQHandler.h"

PQImplHandler *pqHandlerList[] = {
  &maxHeapHandlerForPQ,
  &sortedArrayHandlerForPQ,
  &arrayHandlerForPQ,
  NULL
};