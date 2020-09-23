typedef struct list_of_listsT
{
  void *list;
  struct list_of_listsT *next;
} list_of_lists;

typedef struct double_listT
{
  double value;
  struct double_listT *next;
} double_list;

typedef struct neuron_listT
{
  double a;
  struct neuron_listT *next;
} neuron_list;

double_list *init_double_list(int n, double v)
{
  double_list *list = (double_list*) malloc(sizeof(double_list));
  double_list *e = list;
  for (int i=0; i<n-1; ++i)
  {
    e->value = v;
    e->next = (double_list*) malloc(sizeof(double_list));
    e = e->next;
  }
  e->value=v;
  e->next=NULL;
  return list;
}

list_of_lists *init_double_list_of_lists(int l, int n, double v)
{
  list_of_lists *list = (list_of_lists*) malloc(sizeof(list_of_lists));;
  list_of_lists *e = list;
  for (int i=0; i<l-1; i++)
  {
    e->list = init_double_list(n,v);
    e->next = (list_of_lists*) malloc(sizeof(list_of_lists));
    e = e->next;
  }
  e->list = init_double_list(n,v);
  e->next=NULL;
  return list;
}

void free_list(double_list *list)
{
  double_list *elem = list;
  while(elem != NULL)
  {
    double_list *e = elem;
    elem = elem->next;
    free(e);
  }
}

void free_list_of_lists(list_of_lists *list)
{
  list_of_lists *elem = list;
  unsigned int i = 0;
  while(elem != NULL)
  {
    list_of_lists *e = elem;
    free_list(e->list);
    elem = elem->next;
    free(e);
    i++;
  }
  printf("freed %i lists\n", i);
}

unsigned int list_of_lists_len(list_of_lists *list)
{
    list_of_lists *e = list;
    unsigned int i = 0;
    while (e!=NULL)
    {
      e=e->next;
      i++;
    }
    return i;
}

void print_double_list(double_list *list)
{
    double_list *e = list;
    unsigned int i=0;
    while (e!=NULL)
    {
      printf("[%i] : %f\n",i , e->value);
      e=e->next;
      i++;
    }
}

void print_list_of_double_list(list_of_lists *list)
{
    list_of_lists *e = list;
    unsigned int i=0;
    while (e!=NULL)
    {
      printf("list[%i] :\n",i);
      print_double_list(e->list);
      e=e->next;
      i++;
    }
}