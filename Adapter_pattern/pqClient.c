#include"PriorityQueue/PQ.h"

/*
 A priority queue is an abstract data type which is like a regular
 queue or stack data structure, but where additionally each element
 has a "priority" associated with it. In a priority queue, an element
 with high priority is served before an element with low priority.
 If two elements have the same priority, they are served according
 to their order in the queue.

 While priority queues are often implemented with heaps, they are
 conceptually distinct from heaps. A priority queue is an abstract
 concept like "a list" or "a map"; just as a list can be implemented
 with a linked list or an array, a priority queue can be implemented
 with a heap or a variety of other methods such as an unordered array.
*/

typedef struct{

  const char *firstName;
  const char *lastName;
}PersonDetails;

typedef struct{

  long sinKey;
  PersonDetails value;
}Person;

bool less(const void *item1, const void *item2){

  const Person *person1 = (const Person *)item1;
  const Person *person2 = (const Person *)item2;

  if( person1->sinKey < person2->sinKey ){

    return true;
  }
  return false;
}

int compare(const void *item1, const void *item2){

  const Person *person1 = (const Person *)item1;
  const Person *person2 = (const Person *)item2;

  if( person1->sinKey < person2->sinKey ){

    return -1;
  }else if( person1->sinKey == person2->sinKey ){

    return 0;
  }
  return 1;
}

int main(void){
  PQ *pq= createPQ(PQ_USING_HEAP);

  Person *person = malloc(sizeof(Person));
  person->sinKey = 364222888L;
  (person->value).firstName = "Sham";
  (person->value).lastName = "S";
  insertItemInPQ(pq, person, less);

  person = malloc(sizeof(Person));
  person->sinKey = 365222888L;
  (person->value).firstName = "Tham";
  (person->value).lastName = "T";
  insertItemInPQ(pq, person, less);

  person = malloc(sizeof(Person));
  person->sinKey = 366222888L;
  (person->value).firstName = "Pham";
  (person->value).lastName = "P";
  insertItemInPQ(pq, person, less);

  person = malloc(sizeof(Person));
  person->sinKey = 368222888L;
  (person->value).firstName = "Bham";
  (person->value).lastName = "B";
  insertItemInPQ(pq, person, less);


  person = NULL;
  if(pq == NULL){
    fprintf(stderr, "main() - pq is NULL\n");
  }
  person = deleteItemInPQ(pq, less);
  printf("SIN key is: %ld\n", person->sinKey);
  free(person);
  person = deleteItemInPQ(pq, less);
  printf("SIN key is: %ld\n", person->sinKey);
  free(person);

  freePQ(pq);


}
