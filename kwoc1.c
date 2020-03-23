#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Aleah Grymaloski Feb. 13th 2020
//This program accepts two files, one with lines of text and the other with non-key keyWords
//the program will identify key words and illiminate non-key words
//key words will print in alphebetical order with its corresponding sentance, line number
//an astricks symbol will print if a word is repeated in a sentance, these words will only print once

//struct to store key word info
struct keyWords {

        int flag;
        int line;
        char word[20];
        char sentance[100];
        int seen;
        int length;

};



//function accepts a file and a word. This function reads through the file
//and checks if the word appears in the file. If it does, it is not a key word
//if word is not a key word return 1 else return 0
int checkWord(char word[], FILE *wordFile){
  rewind(wordFile);

  char temp[20];
  int result = 0;
  while(fscanf(wordFile, "%s", temp)!= EOF){

    result =  strcmp(temp, word);
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



//this function formats the output so each word and the following sentance have length 2 more than the
//length of the longest word
char* format_output(char* word, int longest, int length){

    while(length< longest){
      word[length] = ' ';
      length++;
    }
    word[length] = ' ';
  return word;
}



//function will take in size and ptr to array and initialize that array
int initialize_word(char *array, int size){
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





int main (int argc, char *argv[]){

  int longest = 0;
  FILE *exempt_file;
  FILE *input_file;
  char ee[] = "-e";
  int file_flag = 0;


  //read input from command line cases include:
  // input_file -e exempt file
  // input_file
  // -e exempt_file input_file
  if (strcmp(argv[1],ee) == 0){
    exempt_file  = fopen(argv[2], "r");
    input_file = fopen(argv[3], "r");

  }else if (argc >= 4){
    exempt_file  = fopen(argv[3], "r");
    input_file = fopen(argv[1], "r");

  }else{
    input_file = fopen(argv[1], "r");
    exempt_file  = NULL;
    file_flag = 1;

  }


  //error messages for files
  if (input_file == NULL){
     printf("Cannot Open Input File!");
     exit(1);
  }
  if (exempt_file == NULL && file_flag == 0){
     printf("Cannot Open exempt File!");
     exit(1);
  }


  char character = fgetc(input_file);
  char temp[500][20];
  int i = 0;
  struct keyWords info[500];
  int line_count = 0;
  char sentance[100];
  int struct_count = 0;
  int word_count = 0;
  char words[500][20];
  int wordnum = 1;

  //initialize struct values
  i = 0;
  while(i<500){
      info[i].seen = 0;
      info[i].flag = 0;
      info[i].length = 0;
      i++;
  }


  //read file char by char till end of file
  while (character != EOF){
      line_count++;


      //read sentance by sentance from file!
      i = 0;
      while (character !='\n'){
          sentance[i] = character;
          character = fgetc(input_file);
          i++;

      }
      sentance[i] = '\0';

      //tokenize sentance into individual words
      char tok[100];
      strncpy(tok , sentance, 100);
      char *word = strtok(tok, " ");
      char *temp[500];

      i=0;
      while (word != NULL){
            temp[i++] = word;
            word = strtok(NULL, " ");
      }


      i = 0;
      int result = 0;
      wordnum = 0;
      while(temp[i] != NULL){

        //check exempt file for non-key word if exempt file was given (file_flag = 0)
        if (file_flag == 0){
          result = checkWord(temp[i],exempt_file);
        }
        if (file_flag == 1){
          result = 0;
        }
        // if key word result is 0
        if (result == 0){

          int w = struct_count;
          int difference =0 ;
          int fall = wordnum;
          int temp_flag = 0;

          //checks if word is repeated 1 or more times in the sentance
          while(w >= 0 && fall >=0 && temp_flag == 0){

              if (strcasecmp(temp[i], info[w].word) == 0){
                //word was repeated so flag and don't print
                difference = struct_count - w;
                info[struct_count - difference].flag = 1;
                temp_flag = 1;
              }

              fall--;
              w--;
          }

          //add to struct array if key word
         if (temp_flag == 0){

            wordnum++;
            word_count++;
            struct_count++;
            info[struct_count].line = line_count;
            strncpy(info[struct_count].sentance , sentance, 100);
            strncpy(info[struct_count].word, toUpper(temp[i],20),20);

          }

       }
       i++;
    }


    i = 0;
    int count = 0;
    //loop adds length and longest word count
    while(i<word_count){

        while(info[i].word[count] != '\0'){
           count++;
        }

        //update longest word count (used for formating words)
        if(longest<count){
          longest =count;
        }

        info[i].length = count;
        count = 0;
        strncpy(words[i], info[i].word, 20);
        i++;
    }

    //initialize temp array
    i = 0;
    while(i<500){
      temp[i] = NULL;
      i++;
    }

    initialize_word(sentance, 80);
    character = fgetc(input_file);

  }


  i = 0;
  int j = 0;
  int flag = 1;
  int result = 0;
  char temp2[20];

      //orders temp array alphebetically (to be compared with key words to sort)
       for (i = 0; i < word_count - 1 ; i++){

          for (j = i + 1; j < word_count; j++){

              if (strcmp(words[i], words[j]) > 0){
                  strncpy(temp2, words[i], 20);
                  strncpy(words[i], words[j], 20);
                  strncpy(words[j], temp2, 20);

              }
          }
      }

      i = 0;
      j = 0;
      flag = 0;
      int order = 0;
      int checknew = 0;

      //compare sorted array with key words; prints key words alphebetically
      while(j< word_count){

          while(i<word_count && flag ==0){

              if(strncmp(words[j], info[i].word, 20) ==0 && info[i].seen == 0){
                int count = info[i].length;

                char* format = format_output(info[i].word,longest, info[i].length);

                if (info[i].flag == 0){
                    checknew++;
                    printf("%s%s (%d)\n", format, info[i].sentance,info[i].line);
                }else{
                    checknew++;
                    printf("%s%s (%d*)\n", format, info[i].sentance,info[i].line);

                }


                flag = 1;
                info[i].seen = 1;
            }
            i++;
        }
        flag = 0;
        j++;
        i = 0;
    }

    fclose(input_file);
    if (file_flag == 0){
      fclose(exempt_file);
    }

    return 0;
}
