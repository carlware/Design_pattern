/***********listHandler.h ***********/

#ifndef LISTHANDLER_H
#define LISTHANDLER_H

#include"list/list.h"

typedef struct {

         bool(*canHandle)(ImplType);
        List*(*createList)();
         void(*freeList)(List*);
         void(*swim)(List*, int, isLess);
         void(*sink)(List*, int, isLess);
   const auto(*listDeleteMaxElement)(List*, isLess);
   const auto(*sortedListDeleteMaxElement)(List*);
          int(*listGetSize)(List*);
   const auto(*listGetItem)(List*, const int);
        List*(*sortedListInsertItem)(List*, const auto,
                                                 compareTo);
         void(*listInsertItem)(List*, const auto);
   const auto(*listDeleteItem)(List*, int);
   const auto(*listDeleteLastItem)(List*);
   const auto(*listDeleteFirstItem)(List*);
          int(*linearSearch)(const auto, List*, size_t,
                                                 compareTo);
          int(*binarySearch)(const auto, List*, size_t,
                                                 compareTo);
         void(*selectionSort)(List *, size_t, isLess);
         void(*insertionSort)(List*, size_t, isLess);
         void(*quickSort)(List *, size_t, compareTo);
                                // compareTo for stable sort
         void(*mergeSort)(List*, size_t, isLess);
         void(*swap)(List*, int, int);
}ListHandler;

typedef struct{

  ListHandler *handler;
}ListRtti;

/*
  "config.c" lookup below 2 global symbols created in impl 
  handlers, before linking time, so "extern" keyword
*/
extern ListHandler arrayImplHandler;
extern ListHandler linkedListImplHandler;

/*
  "virtualImplyLayer.c" lookup below global symbol created 
  in "config.c", before linking time, so "extern" keyword
*/
extern ListHandler *listHandlers[];

#endif
