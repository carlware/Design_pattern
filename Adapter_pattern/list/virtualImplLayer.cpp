#include "list/listHandler.h"

/*****Private symbol - start *****************/
static ListHandler * findListImplHandler(ImplType);
/*****Private symbol - end   *****************/


/***** User interface - start *************/
List* createList(ImplType implType){

  ListHandler *handler =  findListImplHandler(implType);

  if(handler != NULL){

    List *list = handler->createList();
    return list;
  }
  fprintf(stderr,
      "createList() - No implementation for this feature\n"
         );
  return NULL;

}


void freeList(List *list){
  /*
    Since the address of the first member in 'list' is 
    guaranteed to be the address of the entire object of 
    type 'ListRtti':
   */
  ((ListRtti *)list)->handler->freeList(list);
}


void swim(List *list, int parentIndex, isLess less){

    ((ListRtti *)list)->handler->swim(list, parentIndex,
                                                   less);

}


void sink(List *list, int index, isLess less){

    ((ListRtti *)list)->handler->sink(list, index, less);
}


const auto deleteMax(List *list, isLess less){

    return ((ListRtti *)list)->handler->
                       listDeleteMaxElement(list, less);
}

const auto sortDeleteMax(List *list){

    return ((ListRtti *)list)->handler->
                       sortedListDeleteMaxElement(list);
}


int getSize(List *list){

    return ((ListRtti *)list)->
                            handler->listGetSize(list);
}


const auto getItem(List *list, const int index){

    return ((ListRtti *)list)->handler->
                              listGetItem(list, index);
}


List* sortInsertItem(List *list, const auto item,
                                    compareTo compare){

  //fprintf(stdout, "In sortInsertItem() \n");
  return ((ListRtti *)list)->handler->
             sortedListInsertItem(list, item, compare);
}


void insertItem(List *list, const void *item){

    ((ListRtti *)list)->handler->
                            listInsertItem(list, item);
}

const auto deleteItem(List *list, int listIndex){

    return ((ListRtti *)list)->handler->
                      listDeleteItem(list, listIndex);
}


const auto deleteLastItem(List *list){

    return ((ListRtti *)list)->handler->
                             listDeleteLastItem(list);
}


const auto deleteFirstItem(List *list){

    return ((ListRtti *)list)->handler->
                            listDeleteFirstItem(list);
}


int lSearch(const auto key, List *list, size_t size,
                                   compareTo compare){

    return ((ListRtti *)list)->handler->
               linearSearch(key, list, size, compare);
}


int bSearch(const auto key, List *list, size_t size,
                                   compareTo compare){

    return ((ListRtti *)list)->handler->
               binarySearch(key, list, size, compare);
}

void callInsertionSort(List *list, size_t size,
                                         isLess less){

  ((ListRtti *)list)->handler->
                      insertionSort(list, size, less);
}

void callQuickSort(List *list, size_t size,
                                   compareTo compare){

  ((ListRtti *)list)->handler->
                       quickSort(list, size, compare);
}

void callSelectionSort(List *list, size_t size,
                                         isLess less){

  ((ListRtti *)list)->handler->
                      selectionSort(list, size, less);
}

void callMergeSort(List *list, size_t size,
                                         isLess less){

    ((ListRtti *)list)->handler->
                          mergeSort(list, size, less);
}

void swap(List *list, int i, int j){

    ((ListRtti *)list)->handler->swap(list, i, j);
}

/***** User interface -end *************/


/*****Private symbol - start *****************/
static ListHandler * findListImplHandler(ImplType
                                           implType){

  ListHandler *implHandler = NULL;
  int handlerIndex = 0;
  while(listHandlers[handlerIndex] !=NULL){

    implHandler = listHandlers[handlerIndex];
    if( implHandler->canHandle(implType) ){
      return implHandler;
    }
    handlerIndex++;
  }
  return NULL;
}
/*****Private symbol - end *****************/
