/********************** list.h ********************/

/*
   List is an ordered collection of homogenuous type elements(unique or duplicate).
   List is not designed to have collection of heterogenuous type elements
   All elements in a List are related.
   List is mutable
   Each element has a position.
   If an element is deleted, then still the remaining elements sit in new order.

   Array implementation of List
   Linked implementation of List
*/

#ifndef LIST_H /* Header guard */
#define LIST_H
#include"type.h"

/****************** Interface - start  ********/

 /*
   To ensure Encapsulation(i.e., maintain invariants of 
   array & linked list representation)
   So, Just provide the `List` declartion, to avoid mis-use 
   of `List`
 */
 typedef struct List List;
 typedef enum {ARRAY_IMPL, LINKED_LIST_IMPL}ImplType;


 typedef int (*compareTo)(const auto, const auto);
 typedef bool (*isLess)(const auto, const auto);
 typedef bool (*isEqual)(const auto, const auto);

List* createList(ImplType);
      void freeList(List*);
      void swim(List*, int, isLess);
      void sink(List*, int, isLess);
const auto deleteMax(List*, isLess);
const auto sortDeleteMax(List*);
       int getSize(List*);
const auto getItem(List*, const int);
     List* sortInsertItem(List*, const auto, compareTo);
      void insertItem(List*, const auto);
const auto deleteItem(List*, int);
const auto deleteLastItem(List*);
const auto deleteFirstItem(List*);
       int lSearch(const auto, List*, size_t, compareTo);
       int bSearch(const auto, List*, size_t, compareTo);
      void callSelectionSort(List*, size_t, isLess);
      void callInsertionSort(List*, size_t, isLess);
      void callQuickSort(List*, size_t, compareTo);
      void callMergeSort(List*, size_t, isLess);
      void swap(List*, int, int);
/****************** Interface - end  ********/
#endif
