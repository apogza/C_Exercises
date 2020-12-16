#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int list_size = 200;
const int max_data_value = 50;

struct node
{
  int data;
  struct node *prev;
  struct node *next;
};

typedef struct node Node;
typedef Node *List;

Node *create_node (int number)
{
  Node *new_node = malloc (sizeof(Node));

  new_node->data = number;

  return new_node;
}

int get_rand_number (int min, int max)
{
  return min + rand() % (max - min);
}

List create_list ()
{
  List result = NULL;

  for (int i = 0; i < 200; i++)
    {
      Node *new_node = create_node (get_rand_number (0, 50));

      if (result == NULL)
        {
          result = new_node;
        }
      else
        {
          new_node->next = result;
          result->prev = new_node;

          result = new_node;
        }
    }

  return result;
}

void remove_duplicates (List *list, int max_value)
{
  // use an array as a table to keep track of elements
  // we have already encountered

  int *hash_table = calloc (max_value, sizeof(int));

  Node *current_node = (*list);

  while (current_node != NULL)
    {
      int current_value = current_node->data;

      if (hash_table[current_value] > 0)
        {
          Node* prev = current_node->prev;
          Node* next = current_node->next;

          if (prev != NULL)
            {
              prev->next = next;
            }

          if (next != NULL)
            {
              next->prev = prev;
            }

          free(current_node);
          current_node = next;
        }
      else
        {
          hash_table[current_value] = 1;
          current_node = current_node->next;
        }
    }

  free (hash_table);
}

void print_list (List list)
{
  Node *current_node = list;

  while (current_node != NULL)
    {
      printf ("%d ", current_node->data);
      current_node = current_node->next;
    }

  printf ("\n");

}

int main ()
{
  srand (time(NULL));

  List list = create_list ();
  printf("Initial list:\n");
  print_list (list);


  remove_duplicates (&list, max_data_value);

  printf("\nAfter removing duplicates:\n");
  print_list (list);
  printf("\nDone!\n");

  return 0;
}
