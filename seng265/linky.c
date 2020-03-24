#include <stdio.h>
#include <stdlib.h>
#include "emalloc.h"
#include "linky.h"
#include <string.h>

//this file contains functions relating linked lists. This was used with kwoc3.c linky.c and emalloc.c

// function accepts the first element in the linked list and frees nodes all nodes used in the linked list
void freeNodes(word_node *head) {
     word_node *new;

     while (head != NULL) {
        new = head;
        new = new->next;
        free(new->info);
        free(new);
     }


     free(head);
}



word_node* remove_node(word_node *head, int e, int wc) {


  if (head == NULL){
    return NULL ;
  }

  word_node* new_h = head;
  //free and return
  if (e == 0 || wc == 1){
     new_h = head->next;
     free(head);
     return new_h;
  }


  int k = 0;
  word_node* prev;

  while(k < e){
    prev = head;
    head = head-> next;
    k++;
    
    
    
   }
  prev->next = head->next;

  head = NULL;
  free(head);
  return new_h;
}




//this function adds a node to the linked list
word_node* addNode(word_node* prev){

  word_node* new = (word_node*)emalloc(sizeof(word_node));

  if (prev != NULL){
    prev->next = new;
  }

  return new;
  
  }
