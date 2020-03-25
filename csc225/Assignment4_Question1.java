//Aleah Grymaloski V00909691

//script will take input from the command line specifying the name of a .txt file
//which will contain arrays to be sorted
//arrays will be given in this form 1,3,5,6;8,9,20
//two seperate arrays given separated by a semi-colon, each number separated by a comma
//output will be a sorted array (sorted by a merge sort algorithm o(n).
import java.io.File;
import java.io.FileReader;
import java.io.*;
import java.util.Scanner;


  class Sort{

    public static void main (String[] args) throws Exception{

      FileReader input_file = null;
      BufferedReader input = null;
      Scanner scanner = null;

      
      //creates files and file readers
      if (args.length > 0){
        input_file = new FileReader(args[0]);
        input = new BufferedReader(input_file);
        scanner = new Scanner(input_file);

      }
      

      int flag = 0;
      int k = 0;
      int array1_count = 0;
      int array2_count = 0;
      int i = 0;
      int count = 0;
      String temporary = "";
      String character = input.readLine();
      String[] values = character.split(",");

      
      //declares 2 arrays and one finished array
      int [] array1 = new int[character.length()];
      int [] array2 = new int[character.length()];
      int [] array = new int[character.length()];


      //read characters separated by a comma
      for(String str : values){

        //if reading from first array
        if (flag == 0){

            //if a string contains a semi-colon split string
            if (str.indexOf(';') >= 0){
              array1[i] = Integer.parseInt(str.split(";")[0]);
              flag = 1;
              array1_count ++;
              i++;
              //store integer after semicolon for array2
              temporary = str.split(";")[1];

            //if not add number to array 1
            }else{
              array1[i] = Integer.parseInt(str);
              array1_count ++;
              i++;
            }

          
        //if starting second array, copy number over
        }else if (flag == 1){
          array2[k] = Integer.parseInt(temporary);
          flag = 2;
          array2_count++;
          k++;

          
        //add integer to second array
        }else{
          array2[k] = Integer.parseInt(str);

          k++;
          array2_count++;
        }

      }


   //merge sort algorithm o(n) begins. 
      i = 0;
      k = 0;
      int c = 0;
      int temp = 0;


      //while arrays have numbers in them
      while(i < array1_count && k < array2_count){

          //compare numbers and sort arrays accordingly
          if (array1[i] < array2[k]){

             temp = array1[i];
             i++;
          
          } else {
             temp = array2[k];
             k++;
          }
        
          array[c] = temp;
          c++;

      }

      //copy temp array into new array
      while(k<array2_count){
          array[c] = array2[k];
          k++;
          c++;

      }

      //cooy temp array into new array
      while(i<array2_count){
          array[c] = array1[i];
          i++;
          c++;
      }

      //print array!
      i =0;
      while(i<(array1_count + array2_count)){
           System.out.print(array[i] + " ");
           i++;
      }
      System.out.println("");

      input_file.close();

   }
}
