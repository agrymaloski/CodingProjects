#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "emalloc.h"
#include "linky.h"

//linky.c contains all linked list functions
//emalloc.c contains safe calls to malloc


//Aleah Grymaloski V00909691
//This program searches for key words (a key word does not appear in the excempt files)
//it stores word info as a linked list of structs
//words will print with their corresponding sentance, line number
//an astricks symbol will print next to a word if it was repeated more than once in a sentance



//this function accepts a word and word length and wi
int check_dash(char* word, int length){

    int i = 0;
    int flag = 0;

    while(i<length){

      //if double dash return
      if(word[i]=='-'){
        flag++;
        if (word[i+1] =='-'){
          return 1;

        }

        flag = 0;
      }
      i++;
    }

    if(word[i-1] == '-'){
      return 1;
    }

    return 0;

}



//this function formats the output so each word and the following sentance have length 2 more than the
//length of the longest word
char* format_output(char* word, int longest, int length){


      while(length< longest){
        word[length] = ' ';
        length++;
      }
      word[length] = '\0';
      return word;

  }



//this function accepts all word info (key word, line number, sentance, and word
//length and returns a pointer to the struct containing this info
keyWord* createWord(char *line, char *word, int line_count, int length){

      keyWord* key = NULL;

      key = (keyWord*)emalloc(sizeof(keyWord));

      if (key == NULL){
        free(key);
        return NULL;
      }
      char low_temp[40];
      int p = 0;

      while(p < length){

        low_temp[p] = tolower(word[p]);
          p++;
        }
        low_temp[p] = '\0';
        strcpy(key->word, low_temp);

        key->line = line_count;
        strcpy(key->sentance, line);
        key->length = length;

        key->flag = 0;
        key->seen = 0;

      return key;
}


//function will take in size and ptr to array and initialize that array
int initialize(char *array, int size){
    if(size == 0){
        return 0;
    }
    int i = 0;
    while(i<size){
        *array = '\0';
        array++;
        i++;
    }

    return 1;
  }



//searches for key word and returns 1 if no key word
int checkWord(char* word, FILE *wordFile, int length){
    rewind(wordFile);

    char temp[40];
    char lower[40];
    int result = 0;
    int k = 0;

    while(k<length){
      lower[k] = tolower(word[k]);
      k++;
    }
    lower[k] = '\0';

    while(fscanf(wordFile, "%s", temp)!= EOF){
      result =  strcmp(temp, lower);

      if (result == 0){
        return 1;
      }
    }
    return 0;
}




//Function accepts an address to a string and the length of the string
//to upper changes letters to uppercase and returns the modified string
char* toUpper(char* word ,int length){
    int i = 0;

    while(i < length){
      word[i] = toupper(word[i]);
      i++;
    }

  return word;
}


//function accepts an address to a string and the length of the string
//and changes letters to all lowercase
char* toLower(char* word ,int length){
  int i = 0;
  while(i < length){
    word[i] = tolower(word[i]);
    i++;
  }

  return word;
}



int main (int argc, char *argv[]){


  FILE *exempt_file;
  FILE *input_file;


  int file_flag = 0;
  char ee[] = "-e";


  //open text file (given through command line)
  if (strcmp(argv[1],ee) == 0){
    exempt_file  = fopen(argv[2], "r");
    input_file = fopen(argv[3], "r");

  }else if (argc >= 4){
    exempt_file  = fopen(argv[3], "r");
    input_file = fopen(argv[1], "r");

  }else{

  // no excempt words file
    input_file = fopen(argv[1], "r");
    exempt_file  = NULL;
    file_flag = 1;
  }

  int word_count = 0;
  int line_count = 0;
  char character = fgetc(input_file);
  char sentance[100];
  int head_flag = 0;
  word_node* head = NULL;
  word_node* current = NULL;
  word_node* prev = NULL;
  int longest_word = 0;
  int length = 0;
  char* repeat_array[100];
  int repeat_flag = 0;
  int total_wc = 0;
  int o = 0;
  int i = 0;
  //read sentance line by line

  while(character != EOF){
    line_count++;

    //forms sentance char by char from input file
    int k = 0;
    while (character != '\n'){
      sentance[k] = character;
      character = fgetc(input_file);
      k++;
    }
    sentance[k] = '\0';


    //create temp string for tokenizing
    char tok[100];
    strncpy(tok, sentance, 100);


    //split words using strtok, copy into array of words
    char *tok_ptr = strtok(tok, " ");
    word_count = 0;
    while (tok_ptr != NULL){
        repeat_flag = 0;

        //if word is a key word!
        int word_result = 0;

        if (file_flag == 0){

          int dd = 0;
          while(tok_ptr[dd] != '\0'){
              dd++;
          }
          word_result = checkWord(tok_ptr, exempt_file, dd);
        }

        if (word_result == 0){
            o = 0;

            //check to see if the word was repeated in the sentance, if yes, turn flag on
            while (o < word_count && repeat_flag == 0 ){

              //if word is repeated set flag on
              if (strcmp(repeat_array[o], tok_ptr) == 0){
                repeat_flag = 1;
              }
              o++;
            }

            if (repeat_flag == 1){
                //if word was repeated, iterate thorugh list and flag the repeated word!
                word_node* corona = head;
                int difference = total_wc + o -1;

                while (difference > 0){

                    corona = corona -> next;
                    difference--;
                }
                corona->info->flag = 1;

            //if word was not flagged, print word like normal
            }else{

                //loop that gets the length of the word
                length = 0;
                while(tok_ptr[length] != '\0'){
                    length++;
                }

                //creates the longest word!
                if (length + 2 > longest_word){
                    longest_word = length + 2;
                }


                //if word doesnt contain dashes
                if (check_dash(tok_ptr, length) == 0){

                    //if first word
                    if (head_flag == 0){
                        current = addNode(NULL);
                    }else{
                        current = addNode(prev);
                    }

                    //fill word into into the node
                    repeat_array[word_count] = tok_ptr;
                    current->info = createWord(sentance, tok_ptr, line_count, length);
                    word_count++;
                    prev = current;

                    //if first element in the list
                    if(head_flag == 0){
                        head = current;
                        head_flag = 1;
                    }
                }

            }
            repeat_flag = 0;

        }//end of key word if statement

        tok_ptr = strtok(NULL, " ");
    }//end of sentance loop (token word array)

    total_wc = word_count + total_wc;

    //initialize array
    k = 0;
    while(k<100){
        repeat_array[k] = NULL;
        k++;
    }

    character = fgetc(input_file);

      initialize(sentance, 100);

    }//end of big character loop


    word_node* greatest;
    word_node* curr;


    if (head != NULL){
        greatest = head;
        curr = head->next;
    }

    int element = 0;
    repeat_flag = 0;
    o=0;


    //print words in alphebetical order using selection sort algorithm
    while(total_wc > 0){

      while(total_wc -1 > i){

        if(strcmp(greatest->info->word, curr->info->word) > 0){
          greatest = curr;
          element = i+1;

        }else if(strcmp(greatest->info->word, curr->info->word) ==  0){

          if(curr->info->line < greatest->info->line){
            greatest = curr;
            element = i + 1;
          }

        }

        curr = curr->next;
        i++;
    }


    char* word_temp = toUpper(greatest->info->word, greatest->info->length);

    if(greatest->info->flag == 0){

      printf("%s%s (%d)\n", format_output(word_temp, longest_word, greatest->info->length) , greatest->info->sentance, greatest->info->line);

    }else{
          printf("%s%s (%d*)\n", format_output(word_temp, longest_word, greatest->info->length) , greatest->info->sentance, greatest->info->line);
    }

    word_node* temp_head = head;


    if(total_wc != 1){

      if (element == 0){
        greatest = head->next;
        curr = greatest->next;
      }else{
        greatest = head;

      }
    }

    //remove printed element from the list
    head = remove_node(head, element, total_wc);


    if (element != 0 && total_wc != 1){
      curr = temp_head->next;
    }

    element = 0;
    i = 0;
    total_wc--;
  }

  //frees all nodes in the linked list
  freeNodes(head);


  if(file_flag == 0){
      fclose(exempt_file);

  }
  fclose(input_file);

  return 0;

}// end of main loop
