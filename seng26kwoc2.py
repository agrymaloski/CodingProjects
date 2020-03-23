#Aleah Grymaloski V00909691 Feb. 28th 2020

#This program uses a list of dictionaries to store key word info.
#key words are words that do not appear in the exempt file (files given through command line)
#words will print in alphebetical order with associated sentance line number
#words that appear more that once in a sentance will print with an astricks symbol
#repeat words will only print once.

import sys
from collections import OrderedDict


#dictionary for key word info
word_dict = {
    'word': "hello",
    'sentance': "world",
    'line_count': 1,
    'seen': "FALSE",
    'repeat': "FALSE"
}



#Function will check if a word is a key word
def eliminate_words(file, test):
    file.seek(0)

    for line in file:
        temp = line.lower()
        if (test == temp.rstrip('\n')):
            return 1
    return 0



#tests words: if ends with a - then not true word, if contains -- not true word
def checkHyphen(word):

    if(word.endswith('-') == True):
        return 1

    if (("--" in word)== True):
        return 2

    return 0




#function will print out all the key words in alphebetical order
def printString(word_dict, longest_word, word_count, sorted_words):


    i = 0
    k = 0

    for word in sorted_words:

        for elements in word_dict:

            if (word_dict[i]['word'] == word.upper() and word_dict[i]['seen'] == 'FALSE'):
                word_dict[i]['seen'] = 'TRUE'
                k = 2

                while (len(word_dict[i]["word"]) + k < longest_word + 2):
                    k = k + 1;

                if(word_dict[i]['repeat'] == "TRUE"):
                    print (word_dict[i]['word'] + " "*k + word_dict[i]['sentance'] + " (*" + str(word_dict[i]['line_count']) + ")")
                else:
                    print (word_dict[i]['word']+ " "*k + word_dict[i]['sentance'] + " (" + str(word_dict[i]['line_count']) + ")")
            i = i + 1


        i = 0




#reads files from command line
#accounts for 3 possibilities
# input_file -e exempt_file
# input_file
# -e exempt_file input_file

def readFile(argv):

    if len(argv) <= 2:

        input_file = open(argv[1], "r")
        exempt_file = None
        return 1, input_file, exempt_file

    elif argv[2] == '-e':

        input_file = open(argv[1], "r")
        exempt_file = open(argv[3], "r")
        return 0, input_file, exempt_file


    elif argv[1] == '-e':

        input_file = open(argv[3], "r")
        exempt_file = open(argv[2], "r")

    return 0, input_file, exempt_file






#####MAIN LOOP#####
def main():
    #read files from command line
    fileFlag, input_file, exempt_file = readFile(sys.argv)

    i = 0

    line_count = 0;
    word_count = 0
    longest_word = 0
    word_dict = []
    flag = 0
    repeat = 0
    sorted_words = []


    sentance = input_file.readlines()

    #prints line by line
    for line in sentance:
        #keeps track of line number
        line_count = line_count+1
        #holds value of original line
        temp = line.strip()
        temp2 = temp
        #splits line into individual words
        words = temp.split()


        for word in words:

            #if key word then print
            #check if word is repeated
            if (words.count(word) > 1):
                flag = 1

            if (fileFlag == 0):
                result = eliminate_words(exempt_file, word.lower())
            else:
                result = 0

            if (result == 0 and checkHyphen(word) == 0):

                #set longest word length
                if (len(word) > longest_word):
                    longest_word = len(word)



                if (flag == 0):
                    word_dict.append({'word': word.upper(), 'sentance': temp2, 'line_count': line_count,'seen': "FALSE", 'repeat': "FALSE"})
                    sorted_words.append(word)
                else:
                    word_dict.append({'word': word.upper(), 'sentance': temp2, 'line_count': line_count, 'seen': "FALSE", 'repeat': "TRUE" })
                    words.remove(word)

                    flag = 0
                    word_count = word_count + 1
                    sorted_words.append(word)


    sorted_words.sort()
    #print the string

    printString(word_dict, longest_word, word_count, sorted_words)


    input_file.close()

    if (fileFlag == 0):
        exempt_file.close()




main()
