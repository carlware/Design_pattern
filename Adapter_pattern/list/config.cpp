#include"list/listHandler.h"

ListHandler *listHandlers[] ={

  &arrayImplHandler,
  &linkedListImplHandler,
  NULL // to indicate end of array
};
