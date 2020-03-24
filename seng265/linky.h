#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

//this file contains all functions relating to linked lists used with kwoc3.c

typedef struct keyWords{

        int flag;
        int line;
        char word[20];
        char sentance[80];
        int length;
        int seen;

}keyWord;


typedef struct node{

    keyWord *info;
    struct node *next;

}word_node;


void freeNodes(word_node *);
word_node* remove_node(word_node *, int , int );
word_node* addNode(word_node* );

#endif
