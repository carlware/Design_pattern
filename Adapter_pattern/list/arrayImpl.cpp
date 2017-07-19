/***************** arrayImpl.c **************/


#include"list/listHandler.h"

/*
  typedefs are always "local to a file".
  'ListResizeOperation' type is used only in array 
  implementation
*/
typedef enum {DOUBLE_THE_LIST, HALF_THE_LIST}
                              ListResizeOperation;


/* Symbols not visible to Linker - start */
static List* resizeList(List *,
                             ListResizeOperation);
/*static int bSearchRecur(const void *,
             const void**, int, int, compareTo);*/
static int bSearchIter(const auto keyPtr,
        const auto arrayDptr, int, int, compareTo);

static void insSort(List *, size_t, isLess);
static void sSort(List *, size_t, isLess);
static void merge(const auto leftListDptr,
  const auto rightListDptr, int, int, int, isLess);
static void mSort(const void **, const auto dptr,
                                 int, int, isLess);
static void qSort(List *, int, int, compareTo);
static  int partition(List *, int, int, compareTo);
static const void* delMaxListElem(const void **,
                                   size_t, isLess);
/************** Symbols - end ********************/


/***********  Representation - start *************
Public symbol with restricted access to its details
*/
typedef struct List{

  ListRtti rtti;
  const void *arrayDptr;
  /* For housekeeping - Array enhancement/shrink */
  int lastItemPosition;
  int size;
}List;

#define INITIAL_LIST_SIZE 50
#define FIRST_ITEM_INDEX 0
/**************** Representation - end ************/



/*********** Public symbols - start ***************/
bool canArrayImplHandle(ImplType implType){
  if(implType == ARRAY_IMPL){
    return true;
  }else{
    return false;
  }
}

List *arrayCreate(void){

    List *list = malloc(sizeof(List));
    if(list != NULL){

      list->arrayDptr = malloc(INITIAL_LIST_SIZE*sizeof(
                                          const auto));
      if(list->array != NULL){

      /* Is it safe to initialise zeroes to  array of  pointers? */
        list->array = memset(list->array, 0, INITIAL_LIST_SIZE*sizeof(void *));
        list->lastItemPosition = -1;
        list->size = INITIAL_LIST_SIZE;
        (list->rtti).handler = &arrayImplHandler;
      }else{
        free(list);
        list = NULL;
      }
    }

    return list;
}

void arrayFree(List *list){

  if(list != NULL){
    if(list->array != NULL){
      int index = 0;
      while( index <= list->lastItemPosition){
        free((void *)list->array[index++]);
      }
      free((void **)list->array);
    }else{
      fprintf(stderr, "Invalid list sent to freeList()\n");
    }
    free(list);
  }
}


int arrayGetSize(List *list){
  if(list != NULL){
    return list->lastItemPosition + 1;
  }else{
    fprintf(stderr, "List is NULL\n ");
    return -1;
  }
}

const void *arrayDeleteItem(List *arrayList, int listIndex){

  if(arrayList == NULL){
    fprintf(stderr, "Invalid list \n");
    return NULL;
  }
  const void *returnElement = NULL;
  if(listIndex < arrayGetSize(arrayList)){
    returnElement= arrayList->array[listIndex];
  }else{
    fprintf(stderr, "Invalid index\n");
    exit(EXIT_FAILURE);
  }

  /* Delete operation - O(n) operation */
  for(int accumulator = listIndex; accumulator <= arrayList->lastItemPosition; accumulator++){
    arrayList->array[accumulator] = arrayList->array[accumulator + 1];
  }

  arrayList->lastItemPosition--;

  /* House keeping - Half the list */
  if(arrayList->size > INITIAL_LIST_SIZE){ /* Minimum size maintained */
    if((arrayList->lastItemPosition + 1) == ((arrayList->size)/2)){
      arrayList = resizeList(arrayList, HALF_THE_LIST);
      if(arrayList == NULL){
        fprintf(stderr, "deleteItem() - Unable to allocate memory \n");
        exit(1);
      }
    }
  }
  return returnElement; /* User must free this element*/
}


const void * arrayDeleteLastItem(List *arrayList){

  return arrayDeleteItem(arrayList, arrayList->lastItemPosition);
}


const void *arrayDeleteFirstItem(List *arrayList){

  return arrayDeleteItem(arrayList, FIRST_ITEM_INDEX);
}


void arraySwap(List *list, int i, int j){

  const void **array = list->array;

  const void *tempPointer = array[i];
  array[i] = array[j];
  array[j] = tempPointer;
}
void arraySwim(List *list, int index, isLess less){

  const void **array = list->array;
  while(index > 1 &&  less(array[index/2], array[index]) ){
    arraySwap(list, index/2, index);
    index/=2;
  }
}


void arraySink(List *list, int parentIndex, isLess less){

  const void **array = list->array;
  while( 2*parentIndex <= list->lastItemPosition ){

    int childIndex = 2*parentIndex;
    if( childIndex < list->lastItemPosition && //larger child
                (less(array[childIndex], array[childIndex+1])) ){
      childIndex = childIndex + 1;
    }
    if(!less(array[parentIndex], array[childIndex])) break;
    arraySwap(list, parentIndex, childIndex);
    parentIndex = childIndex;
  }
}

const void *arrayDeleteMaxElement(List *list, isLess less){
  if(list != NULL){

    const void *maxElement= delMaxListElem(list->array, arrayGetSize(list), less);
    list->lastItemPosition--;
    return maxElement;
  }else{
    fprintf(stderr, "listDeleteMaxElement() - NULL is passed\n");
  }
  return NULL;
}


const void *sortedArrayDeleteMaxElement(List *list){
  if(list != NULL){

    const void *maxElement= arrayDeleteLastItem(list);
    return maxElement;
  }else{
    fprintf(stderr, "sortedListDeleteMaxElement() - NULL is passed\n");
  }
  return NULL;
}

const void *arrayGetItem(List *list, const int index){

  if((index >=0) && (index < arrayGetSize(list))){

    return (const void *)list->array[index];
  }else{
    return NULL;
  }
}


void arrayInsertItem(List *arrayList, const void *newItem){

  //fprintf(stdout, "In arrayInsertItem()\n");
  if(arrayList == NULL){
    fprintf(stderr, "listInsertItem() -Invalid list \n");
    return;
  }
  /* House keeping - Enhance the array */
  if(arrayList->lastItemPosition + 1 == arrayList->size){
    arrayList = resizeList(arrayList, DOUBLE_THE_LIST);
    if(arrayList == NULL){
      fprintf(stderr, "insertItem() - Unable to allocate memory \n");
      exit(1);
    }
  }

  /* Insert new element - O(1) operation */
  arrayList->array[++(arrayList->lastItemPosition)] = newItem;
}

List * sortedArrayInsertItem(List *arrayList, const void *newItem, compareTo compare){

  if(arrayList == NULL){
    fprintf(stderr, "sortedArrayInsertItem() -Invalid list \n");
    return NULL;
  }

  List *newlist = arrayCreate();

  /* Insert new element - O(n) operation */
  int oldIndex =0;
  for(; oldIndex < arrayGetSize(arrayList); oldIndex++){
    //fprintf(stdout, "sortedArrayInsertItem()-Before calling compare()\n");
    if( compare(newItem, arrayList->array[oldIndex]) > 0){

      //fprintf(stdout, "Insering old item\n");
      arrayInsertItem(newlist, arrayList->array[oldIndex]);
      arrayList->array[oldIndex] = NULL;
    }else{
      break;
    }

  }//end for-loop
  //fprintf(stdout, "Inserting newitem\n");
  arrayInsertItem(newlist, newItem);

  for(;oldIndex < arrayGetSize(arrayList); oldIndex++){
    //fprintf(stdout,"Inserting remaining old item\n");
    arrayInsertItem(newlist, arrayList->array[oldIndex]);
    arrayList->array[oldIndex] = NULL;
  }
  arrayFree(arrayList);
  arrayList = newlist;

  //fprintf(stdout, "new list size:%d\n", arrayGetSize(arrayList));
  return arrayList;
}


/**************Searching & Sorting -start **************/
int arrayLinearSearch(const void *keyItem, List *list, size_t listSize, compareTo compare){

  if(list != NULL && (listSize > 0)){
    const void ** array = list->array;
    for(int index =0; index < listSize; index++){

      if(compare(keyItem, array[index] ) == 0){

        return index;
      }
    }
  }
  return -1;
}


int arrayBinarySearch(const void *key, List *list, size_t listSize, compareTo compare){

  if(list != NULL && (listSize > 0)){
    return bSearchIter(key, list->array, 0, listSize-1, compare);
    //return bSearchRecur(key, list->array, 0, listSize-1, compare);
  }
  return -1;
}

void arraySelectionSort(List *list, size_t listSize, isLess less){

  if(list != NULL && (listSize > 0)){

    sSort(list, listSize, less);
  }
}

void arrayInsertionSort(List *list, size_t listSize, isLess less){

  if(list!=NULL && (listSize > 0)){
    insSort(list, listSize, less);
  }
}

void arrayQuickSort(List *list, size_t listSize, compareTo compare){

  if(list != NULL && (listSize > 0)){
    qSort(list, 0, listSize-1, compare);
  }
}

void arrayMergeSort(List *list, size_t listSize, isLess less){

  if(list != NULL){

    const void **aux = malloc(arrayGetSize(list) * sizeof(void*)); //Auxillary for shadow copy
    if(aux != NULL){
      //printf("Size of list: %d\n", listSize);
      mSort(list->array, aux, 0, listSize-1, less);
    }else{

      fprintf(stderr, "mergeSort() - Malloc failure");
      exit(EXIT_FAILURE);
    }
  }else{

    fprintf(stderr, "mergeSort() - List is NULL");
  }
}

/**************Searching & Sorting -end **************/



/****************Public symbols - end *******************/
/* Private symbols - start - Not visible to Linker****/
static void qSort(List *list, int low, int high, compareTo compare){

  if(high <= low){
    return; // no partition for sub array of size 1
  }
  int pivotIndex = partition(list, low, high, compare);
  qSort(list, low, pivotIndex-1, compare);
  qSort(list, pivotIndex+1, high, compare);
}

static int partition(List *list, int low, int high, compareTo compare){

  int pivot = low;
  int leftIndex = low + 1;
  int rightIndex = high;
  const void **array = list->array;

  while(true){

    while( leftIndex < high  && (compare(array[leftIndex], array[pivot]) < 0) ){
      leftIndex++; // move right as long as a[leftIndex] < a[pivot]
    }

    while( rightIndex > pivot && (compare(array[pivot], array[rightIndex])  < 0) ){
      rightIndex--; // move left as long as a[rightIndex] > a[pivot]
    }

    if(leftIndex >= rightIndex){
      break; // partition is done
    }
    if( compare(array[leftIndex], array[rightIndex]) == 0 ){
      leftIndex++; rightIndex--;
      continue; //stable sort
    }
    arraySwap(list, leftIndex, rightIndex);
  }
  if( compare(array[pivot], array[rightIndex]) != 0 ){
    arraySwap(list, pivot, rightIndex); // pivot element is positioned(once) with stable sort
  }
  return rightIndex;
}

static void mSort(const void **array, const void **aux, int low, int high, isLess less){

  if(high <= low) return;
  int mid = (low + high)/2;

  mSort(array, aux, low, mid, less);
  mSort(array, aux, mid+1, high, less);
  merge(array, aux, low, mid, high, less);
}

static void merge(const void **array, const void **aux, int low, int mid, int high, isLess less){

  for(int index = low; index <= high; index++){
    aux[index] = array[index]; //Shallow copy
    //printf("Each record: %s\n",(char *)aux[index]);
  }
  //printf("Low-%d, Mid-%d, High-%d\n", low, mid, high);
  int leftIndex = low; int rightIndex = mid+1;
  //printf("leftIndex-%d, rightIndex-%d\n", leftIndex, rightIndex);

  for(int index = low; index <= high; index++){

    if(leftIndex > mid)     /* left array exhausted */  array[index] = aux[rightIndex++];
    else if(rightIndex > high) /*Right array exhausted*/ array[index] = aux[leftIndex++];
    else if( less(aux[rightIndex], aux[leftIndex]) )    array[index] = aux[rightIndex++];
    else                                                array[index] = aux[leftIndex++];
  }
}


static int bSearchIter(const void *key, const void **array, int lowerBound, int upperBound, compareTo compare){

  int mid =0;
  while(lowerBound <= upperBound){

    mid = (lowerBound + upperBound)/2;
    if(compare(key, array[mid]) == 0){

      return mid;
    }else if(compare(key, array[mid]) < 0){

      upperBound = mid-1;
    }else if(compare(key, array[mid]) > 0){

      lowerBound = mid+1;
    }
  }/* end while */

  return -1;
}

/*static int bSearchRecur(const void *key, const void **array, int lowerBound, int upperBound, compareTo compare){

  if(lowerBound > upperBound) return -1;

  int mid = (lowerBound + upperBound)/2;

  if(compare(key, array[mid]) == 0){

    return mid;
  }else if(compare(key, array[mid]) < 0){

    return bSearchRecur(key, array, lowerBound, mid-1, compare);
  }else { // compare() > 0

    return bSearchRecur(key, array, mid+1, upperBound, compare);
  }
}*/

static const void *delMaxListElem(const void **array, size_t size, isLess less){

  if(size >0){

    const void *maxElement = array[0];
    int maxElementIndex = 0;
    printf("size of list: %d\n", size);
    for(int index = 1; index < size; index++){
      if( less(maxElement, array[index]) ){
        maxElement = array[index];
        maxElementIndex = index;
      }
    }

    for(int index = maxElementIndex; index < size-1; index++){
      array[index] = array[index+1];// Rearrange array
    }

    return (void *)maxElement;
  }else{
    return NULL;
  }
}

static void sSort(List *list, size_t listSize, isLess less){

  for(int sortedBoundaryIndex = 0; sortedBoundaryIndex < (long long)listSize; sortedBoundaryIndex++){

    int minItemIndex = sortedBoundaryIndex;
    for(int unSortedBoundaryIndex = sortedBoundaryIndex +1; unSortedBoundaryIndex < (long long)listSize; unSortedBoundaryIndex++){

      if( less(list->array[unSortedBoundaryIndex], list->array[minItemIndex])){
        minItemIndex = unSortedBoundaryIndex;
      }
    }
    arraySwap(list, sortedBoundaryIndex, minItemIndex);
  }// end for-loop
}


static void insSort(List *list, size_t listSize, isLess less){

  for(int sortedBoundaryIndex = -1; sortedBoundaryIndex < (long long)listSize - 1; sortedBoundaryIndex++){
    /*
      -1 mean sorted pool is yet to form.
       0 mean first element is in sorted pool
    */

    for(int unSortedElementIndex = sortedBoundaryIndex + 1; unSortedElementIndex > 0; unSortedElementIndex--){
      /* Within this loop, sorted pool does not exist, as new element is being compared*/
      if(less(list->array[unSortedElementIndex], list->array[unSortedElementIndex-1])){
        arraySwap(list, unSortedElementIndex, unSortedElementIndex-1);
      }else{
        break; //If the unsorted element is > or ==, no swap, Stable sort
      }
    }
  }
}

/* resizeList() is not visible to Linker (ld) */
static List *resizeList(List *list, ListResizeOperation opType){

  if(opType == DOUBLE_THE_LIST){

    list->array = realloc(list->array, 2*(list->size)*sizeof(void *));
    if(list->array == NULL){ return NULL; }
    list->lastItemPosition = list->lastItemPosition;;
    list->size = 2*(list->size);
  }else if(opType == HALF_THE_LIST){

    list->array = realloc(list->array, ((list->size)/2)*sizeof(void *));
    if(list->array == NULL){ return NULL; }
    list->lastItemPosition = list->lastItemPosition;
    list->size = (list->size)/2;
  }

  return list;
}
/************* helper symbols - end  ************/

/* config.c requires below symbol */
ListHandler arrayImplHandler = {
  canArrayImplHandle,
  arrayCreate,
  arrayFree,
  arraySwim,
  arraySink,
  arrayDeleteMaxElement,
  sortedArrayDeleteMaxElement,
  arrayGetSize,
  arrayGetItem,
  sortedArrayInsertItem,
  arrayInsertItem,
  arrayDeleteItem,
  arrayDeleteLastItem,
  arrayDeleteFirstItem,
  arrayLinearSearch,
  arrayBinarySearch,
  arraySelectionSort,
  arrayInsertionSort,
  arrayQuickSort,
  arrayMergeSort,
  arraySwap,
};
