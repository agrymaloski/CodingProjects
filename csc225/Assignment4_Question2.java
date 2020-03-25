import java.io.File;
import java.io.FileReader;
import java.io.*;
import java.util.Scanner;



class Find{

  public static void main (String[] args) throws Exception{


    FileReader input_file = null;
    BufferedReader input = null;

    //declare file and file reader
    if (args.length > 0){
      input_file = new FileReader(args[0]);
      input = new BufferedReader(input_file);

    }
    int arraySum = 0;
    int correctSum = 0;
    int i = 1;
    int result = 0;



    String character = input.readLine();
    String[] values = character.split(",");

    //read characters separated by a comma
    //calculate the actual sum
    for(String str : values){
        arraySum = Integer.parseInt(str) + arraySum;
        i++;
        }

      // add up what the sum should be
      while(i > 0){
        correctSum = correctSum + i;
        i--;
      }

        //print out the difference to get the missing number
        System.out.println(correctSum-arraySum);

        input_file.close();

    }

  }
