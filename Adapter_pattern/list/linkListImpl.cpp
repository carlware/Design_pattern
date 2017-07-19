/**********linkedListImpl.c ***********/


#include"list/listHandler.h"


/***************** Representation - start ******************/

  /* Private structure */
  typedef struct DListNode{
    const void *item;
    struct DListNode *next;
    struct DListNode *prev;
  }Node;



  /*
    Reason to introduce 'List' type:

    Problem 1:
     Say, user code has 'x' and 'y' pointing to the same shopping list that is built using 'Node' type.
     Some part of user code update list with new item using 'x'
     'y' is not in sync with this updation
        Node *x = someCreatedList;
        Node *y = x;
        Node *z = malloc(sizeof(Node));
        z->next = x;
        x = z; //y misses that reference.
    Solution:
     Maintain a List type, whose job is to point to head(first node) of the list.
     User code will go via reference of List type


    Problem 2:
     It make sense to have references of 'Node' type pointing to NULL
     Applying operation[insertItem()] on NULL pointer will cause runtime errors
    Solution:
     Run operations over List type because it does not make sense to have reference of SList type pointing to NULL.

    To solve problem1 & problem2, here is 'List' type
  */



  /* Public structure with restricted access to user */

  typedef struct List{

    ListRtti rtti;
    Node *head;
    int size; /*size attribute is not part of list definition,
               but quick way to help user code */
  }List;
#define SENTINEL_NODE_DATA_ITEM (void *)0

/************ Representation - end *************/


/******Private symbol - start - Not visible to linker *****/
static Node* createNode(const void *);
static void addNextNode(Node *, const void *);
static void addPrevNode(Node *, const void *);
/******Helper function - end ******************/



/****Public symbols - start **********/

bool canLinkedListImplHandle(ImplType implType){

  if(implType == LINKED_LIST_IMPL){
    return true;
  }else{
    return false;
  }
}

List *linkListCreate(){

    /*
      Amidst performing insert/delete operations on 'List',
      To reduce the number of special checks, we designate one node as 'SENTINEL'
      After using sentinel, there will be no NULL assignments/check in code.
    */
    List *list = (List *)malloc(sizeof(List));
    if(list != NULL){

      Node *sentinel = createNode(SENTINEL_NODE_DATA_ITEM);
      list->head = sentinel;
      list->head->next = list->head;
      list->head->prev = list->head;
      list->size = 0;
      (list->rtti).handler = &linkedListImplHandler;
      return list;
    }else{

      return NULL;
    }
}

void linkListFree(List *list){

  if(list != NULL){
    if(list->size > 0){

      int index = 0;
      Node *currentNode, *nextNode;
      currentNode = list->head->next;
      do{
        nextNode = currentNode->next;
        free((void *)currentNode->item);
        free(currentNode);
        currentNode = nextNode;
      }while(++index < list->size);
      return;
    }else{

      return;
    }
  }else{

    fprintf(stderr, "Unable to free()\n");
    return;
  }
}


void linkListSwim(List *list, int index, isLess less){

  return;
}


void linkListSink(List *list, int parentIndex, isLess less){

  return;
}

const void * linkListDeleteMaxElement(List *list, isLess less){

  return NULL;
}


const void* sortedLinkListDeleteMaxElement(List *list){

  return NULL;
}


int linkListGetSize(List *list){

  if(list != NULL){
    return list->size;
  }else{
    fprintf(stderr, "List is NULL\n ");
    return -1;
  }
}

const void *linkListGetItem(List *list, int index){

  //printf("linkListGetItem()- Entered with index:%d\n", index);
  if((index >=0) && (index < list->size)){

    Node *node = list->head->next;
    while(index-- > 0 && (node != list->head)){
      node = node->next;
    }
    return (const void *)node->item;
  }else{

    fprintf(stderr, "Invalid index \n");
    return NULL;
  }
}

/* O(1) operation - insert() operation */
void linkListInsertItem(List *linkedList, const void *newItem){

  //fprintf(stdout, "In linkListInsertItem()\n");
  Node *newNode = createNode(newItem);
  if(linkedList->size == 0){
    fprintf(stdout, "linkListInsertItem() - size is: %d\n", getSize(linkedList));
    linkedList->head->next = linkedList->head->prev = newNode;
    newNode->prev = linkedList->head;
  }else{

    /* Link with current last node in the linked list*/
    newNode->prev = linkedList->head->prev;
    newNode->prev->next = newNode;

    /* Link with Sentinel node */
    linkedList->head->prev = newNode;
  }
  newNode->next= linkedList->head;

  linkedList->size++;

}

List* sortedLinkListInsertItem(List *list, const void *item, compareTo compare){

  if(list == NULL){
    return NULL;
  }
  fprintf(stdout, "item is %d\n", *(int *)item);
  if(getSize(list) == 0){

    fprintf(stdout, "sortedLinkListInsertItem() - size is: %d\n", getSize(list));
    linkListInsertItem(list, item);
  }else if(getSize(list) > 0){

    Node *nodeToSearch = list->head->next;

    int index = 0;
    while(nodeToSearch != list->head){
      if(compare(item, nodeToSearch->item) > 0){

        nodeToSearch = nodeToSearch->next;
        index++;
      }else{
        addNextNode(nodeToSearch, item);
        list->size++;
        return list;
      }
    }
    addPrevNode(list->head, item);
    list->size++;
  }
  return list;
}

       /* O(n) - delete() operation*/
const void *linkListDeleteItem(List *linkedList, int listIndex){


  Node *nodeToDelete = linkedList->head->next;
  int nodeIndex = 0;

  if(listIndex < linkedList->size){

     while(nodeIndex < listIndex){//0
       nodeToDelete = nodeToDelete->next;
       nodeIndex++;
     }
     //printf("linkListDeleteItem()-deleting item:%d\n", *((int *)nodeToDelete->item));
     nodeToDelete->prev->next = nodeToDelete->next;
     nodeToDelete->next->prev = nodeToDelete->prev;

     linkedList->size--;

     const void *item = nodeToDelete->item;
     free(nodeToDelete);
     return item; /* User must delete free(item); */
  }else{

    fprintf(stderr, "linkListDeleteItem() - List is empty");
    return NULL;
  }
}

/* O(1) - deleteLastItem() operation */
const void *linkListDeleteLastItem(List *linkedList){

  if(linkedList->size){

    Node *nodeToDelete = linkedList->head->prev;
    const void *item = nodeToDelete->item;
    nodeToDelete->prev->next = nodeToDelete->next;
    nodeToDelete->next->prev = nodeToDelete->prev;

    free(nodeToDelete);
    return item; /* User must free this item,by casting, free(item) */
  }else{

    return NULL;
  }
}


/* O(1) - deleteFirstItem() operation */
const void *linkListDeleteFirstItem(List *linkedList){

  if(linkedList->size){

    Node *nodeToDelete = linkedList->head->next;
    const void *item = nodeToDelete->item;
    nodeToDelete->next->prev = nodeToDelete->prev;
    nodeToDelete->prev->next = nodeToDelete->next;

    free(nodeToDelete);
    return item; /* User must free this item,by casting, free(item) */
  }else{

    return NULL;
  }
}

int linkListLinearSearch(const void *keyItem, List *list, size_t listSize, compareTo compare){

  //fprintf(stdout, "linkListLinearSearch() - list size: %d\n", listSize);

  Node *nodeToSearch = NULL;
  if(listSize > 0){
    nodeToSearch = list->head->next;
  }else{
    return -1;
  }

  for(int index=0; index < listSize-1; index++){
    if(compare(keyItem, nodeToSearch->item) ==0){
      return index;
    }
    nodeToSearch = nodeToSearch->next;
    //fprintf(stdout, "linkListLinearSearch() - next item:%d\n", *((int *)nodeToSearch->item));
  }
  return -1;
}


int linkListBinarySearch(const void *key, List *list, size_t size, compareTo compare){

  return -1;
}

void linkListSelectionSort(List *list, size_t listSize, isLess less){

}


void linkListInsertionSort(List *list, size_t size, isLess less){

  return;
}


void linkListQuickSort(List *list, size_t size, compareTo compare){

  return;
}

void linkListMergeSort(List *list, size_t size, isLess less){

  return;
}


void linkListSwap(List *list, int i, int j){

  return;
}

/******Public symbols - end *************/


/******Private symbols - start - Not visible to linker*******/

static void addNextNode(Node *node, const void *item){
  Node *newNode = createNode(item);
  newNode->next = node;
  newNode->prev = node->prev;
  node->prev = newNode;
  newNode->prev->next = newNode;
  return;
}

static void addPrevNode(Node *node, const void *item){
  Node *newNode = createNode(item);
  newNode->prev = node->prev;
  newNode->next = node;
  newNode->prev->next = newNode;
  newNode->next->prev = newNode;
  return;
}

static Node *createNode(const void * item){

  Node *newNode= malloc(sizeof(Node));

  newNode->next = newNode;
  newNode->prev = newNode;
  newNode->item = item;

  return newNode;
}

/****Private symbols - end ********/

/* 'config.c' lookup below global symbol */
ListHandler linkedListImplHandler = {

  canLinkedListImplHandle,
  linkListCreate,
  linkListFree,
  linkListSwim,
  linkListSink,
  linkListDeleteMaxElement,
  sortedLinkListDeleteMaxElement,
  linkListGetSize,
  linkListGetItem,
  sortedLinkListInsertItem,
  linkListInsertItem,
  linkListDeleteItem,
  linkListDeleteLastItem,
  linkListDeleteFirstItem,
  linkListLinearSearch,
  linkListBinarySearch,
  linkListSelectionSort,
  linkListInsertionSort,
  linkListQuickSort,
  linkListMergeSort,
  linkListSwap,
};