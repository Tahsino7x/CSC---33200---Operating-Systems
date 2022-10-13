#include<stdio.h>
#include<stdlib.h>

// structure for Circular Linked List
struct Node
{
   int data;
   struct Node *next;
};

void insert(struct Node** head, int data)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    
    // if its the first node being entered
    if(*head == NULL){
        *head = newNode;
        (*head)->next = *head;
        return;
    }
    struct Node* curr = *head;

    // traverse till last node in LL
    while(curr->next != *head){
        curr = curr->next;
    }
    curr->next = newNode;
    // assign this new node's next as current head
    newNode->next = *head;
}

// traverse the linked list
void traverseList(struct Node* head)
{
    if(head == NULL)
        return;
    
    struct Node* temp = head;
    
    do{
        printf("%d ", temp->data);
        temp = temp->next;
        
    }while(temp!=head);
    printf("\n");
}

// search linked list
int search(struct Node** head, int val) 
{
   if(head == NULL)
      return 0;

    struct Node *current = *head;

     while(current->next != *head) 
     {
      if(current->data == val) 
         return 1;
      current = current->next;
   }

   if(current->data == val)
      return 1;

  return 0;
}

// sort the linked list
void sort(struct Node** head) 
{
    //Current will point to head  
    struct Node *current = *head, *index = NULL;  
    int temp;  
    if(head == NULL) 
        printf("List is empty");  

    else 
    {  
        do{  
//Index will point to node next to current  
        index = current->next;  
        while(index != *head) 
        {  
    //If current node is greater than index data, swaps the data  
        if(current->data > index->data) 
        {  
        temp =current->data;  
        current->data= index->data;  
        index->data = temp;  
        }  
        index= index->next;  
        }  
    current =current->next;  
        }while(current->next != *head);   
    }  
}

// Delete a node
void delete(struct Node** head, int val) 
{
     if (head == NULL)
        return;
  
    // Find the required node
    struct Node *curr = *head, *prev;
    while (curr->data != val) 
    {
        if (curr->next == *head)
            break;
        prev = curr;
        curr = curr->next;
    }
  
    // Check if node is only node
    if (curr->next == *head) 
    {
        head = NULL;
        free(curr);
        return;
    }
  
    // If more than one node, check if it is first node
    if (curr == *head) 
    {
        prev = *head;
        while (prev->next != *head)
            prev = prev->next;
        *head = curr->next;
        prev->next = *head;
        free(curr);
    }
  
    // check if node is last node
    else if (curr->next == *head && curr == *head) 
    {
        prev->next = *head;
        free(curr);
    }
    else 
    {
        prev->next = curr->next;
        free(curr);
    }
}

int main(){
    
    // first node will be null at creation    
    struct Node* head = NULL;
    insert(&head, 6);
    insert(&head, 2);
    insert(&head, 4);
    insert(&head, 5);
    insert(&head, 1);

    printf("traverse linked list: ");
    traverseList(head);

    delete(&head, 4); // delete 4 from list
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