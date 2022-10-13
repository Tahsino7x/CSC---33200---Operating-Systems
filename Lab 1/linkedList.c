#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node* next;
};

// Insert node
void insert(struct Node** head, int new_data) 
{
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); // allocate memory based on node size
  struct Node* last = *head; 

  new_node->data = new_data;
  new_node->next = NULL;

    if (*head == NULL) 
    {
        *head = new_node;
        return;
    }

  while (last->next != NULL) 
    last = last->next;

  last->next = new_node;
  return;
}

// Delete a node
void delete(struct Node** head, int val) 
{
  struct Node *temp = *head, *prev;
  if (temp != NULL && temp->data == val) 
  {
    *head = temp->next;
    free(temp);
    return;
  }
  // Find the value to be deleted
  while (temp != NULL && temp->data != val) 
  {
    prev = temp;
    temp = temp->next;
  }

  // If the value is not present
  if (temp == NULL) 
    return;

  // Remove the node
  prev->next = temp->next;
  free(temp);
}

// search linked list
int search(struct Node** head, int val) 
{
  struct Node* current = *head;
  while (current != NULL) 
  {
    if (current->data == val) 
        return 1;
    current = current->next;
  }
  return 0;
}

// Sort the linked list
void sort(struct Node** head) 
{
    struct Node *current = *head, *index = NULL;
    int temp;

    if (head == NULL) 
        return;
    else 
        while (current != NULL)  // index points to the node next to current
        {
            index = current->next;
            while (index != NULL) 
            {
                if (current->data > index->data) 
                {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
        index = index->next;
            }
    current = current->next;
        }
  }

// traverse the linked list
void traverseList(struct Node* node) 
{
  while (node != NULL) 
  {
    printf("%d ", node->data);
    node = node->next;
  }
  printf("\n");
}


int main() 
{
  struct Node* head = NULL; // set the head pointer to null
  insert(&head, 6);
  insert(&head, 2);
  insert(&head, 4);
  insert(&head, 5);
  insert(&head, 1);

  printf("traverse linked list: ");
  traverseList(head);

  delete(&head, 4);  // delete 4 from list
  traverseList(head);

  int val = 2;
  if (search(&head, val)) 
    printf("\n%d is found", val);
  else 
    printf("\n%d is not found", val);

  val = 4;
  if (search(&head, val)) 
    printf("\n%d is found", val);
  else 
    printf("\n%d is not found", val);
  
  sort(&head);
  printf("\nSorted List: ");
  traverseList(head);
}