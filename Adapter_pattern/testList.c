/************************* testList.c *****************/
#include"list/list.h"


bool equal (const void * key, const void *item){
  if( *((int *)key) == *((int *)item) ){
    return true;
  }else{
    return false;
  }
}

bool less (const void * key, const void *item){
  if( *((int *)key) < *((int *)item) ){
    return true;
  }else{
    return false;
  }
}


int compare(const void *key, const void *item){
  if( *((int *)key) == *((int *)item) ){
    return 0;
  }else if((int *)key < (int *)item){
    return -1;
  }else{
    return 1;
  }
}

int main(int argc, char*argv[]){


  /*
  List *arrayList = createList();

  int *item = NULL;
  srand(time(NULL));
  for(int input = 10; input > 0; input--){
    item = malloc(sizeof(int));
    *item = rand();
    insertItem(arrayList, item);
  }
  item = (int  *)getItem(arrayList, 0); // Returns (const void *)
  printf("First item: %d\n", *item);

  printf("\nSize of list: %d\n", getSize(arrayList));

  fprintf(stdout, "About to call delete\n");
  int *item1 = deleteItem(arrayList, 3);
  fprintf(stdout, "Item to be deleted:%p\n", item1);
  free(item1); // User's responsibility to avoid leak, after calling deleteItem()
  printf("One item deleted \n");

  printf("\nSize of list: %d\n", getSize(arrayList));

  printf("Index found after linear search: %d\n",
         lSearch( item, arrayList, getSize(arrayList), equal) );

  printf("Item found after Binary search: %d\n",
         *(int *)(bSearch(item, arrayList, getSize(arrayList), compare) ));



  printf("\nBefore insertion sorting\n");
  for(int index =0; index < getSize(arrayList); index++){
    printf("Element: %d \n", *((const int *)getItem(arrayList, index) ));
  }

  callInsertionSort(arrayList, getSize(arrayList), less);
  //callMergeSort(arrayList, getSize(arrayList), less);
  printf("\nAfter sorting\n");
  for(int index =0; index < getSize(arrayList); index++){
    printf("Element: %d \n", *((const int *)getItem(arrayList, index)));
  }


  freeList(arrayList);  // User is responsible to free list, before stop using list
  */
  List *linkedList = createList(LINKED_LIST_IMPL);

  int *item = NULL;
  srand(time(NULL));
  for(int input = 10; input > 0; input--){
    item = malloc(sizeof(int));
    *item = rand();
    printf("testList() - item to insert: %d\n", *item);
    insertItem(linkedList, item);
  }
  printf("testList() - Search last item index: %d\n", lSearch( item, linkedList, getSize(linkedList), compare) );

  for(int index=0; index <10; index++){
    const int *item = getItem(linkedList, index);
    printf("testList() - got item:%d\n", *item);
  }
  printf("testList() - Delete item with index 0\n");
  item = deleteItem(linkedList, 0);
  for(int index=0; index < 9; index++){
    const int *item = getItem(linkedList, index);
    printf("testList() - After delete got item:%d with index:%d\n", *item, index);
  }

  printf("testList() - Search deleted item index: %d\n", lSearch( item, linkedList, getSize(linkedList), compare) );
  printf("testList() - Item to be deleted:%d\n", *(int *)item);
  free(item);

  freeList(linkedList);
}