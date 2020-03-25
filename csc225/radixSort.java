import java.io.File;
import java.io.FileReader;
import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;

public class radixSort{



static ArrayList<String> radixSort(ArrayList <String> list, int diget_num){

  int k = 0;
  String lowest;
  char lowestc;
  String temp;
  char tempc = '0';
  int lowest_el = 0;
  ArrayList<String> newList = new ArrayList<String>();
  int count =0;

  //while array list is not empty
  while(list.size() != 0){

    //set first element to lowest
    lowest = list.get(0).toString();

    if(0 > (lowest.length() - diget_num - 1)){
      lowestc = '0';
    }else{
      lowestc = lowest.charAt(lowest.length() - diget_num - 1);
    }

    k = 0;
    while(k < list.size()){

        //get next element
        temp = list.get(k).toString();

        if(0 > (temp.length() - diget_num - 1)){
          tempc = '0';
        }else{
          tempc = temp.charAt(temp.length() - diget_num - 1);
        }

        if (tempc < lowestc){
          lowestc = tempc;
          lowest = temp;
          lowest_el = k;
        }
        k++;
      }

      newList.add(lowest);
      list.remove(lowest_el);
      lowest_el = 0;

   }



   return newList;
}



  public static void main(String args[]){

ArrayList<String> list = new ArrayList<String>();
ArrayList<String> sorted = new ArrayList<String>();



    String[] string  = args[0].split(" ");


int most_digets = 0;


    for(String s : string){
       list.add(s);
       if (s.length() > most_digets){
         most_digets = s.length();
       }
    }


    int i = 0;
    int p = 0;
    while(i < most_digets){


     sorted = radixSort(list, i);

     while(p < sorted.size()){
       System.out.print(sorted.get(p) + " ");
       p++;
     }
     System.out.println("");

     p=0;

     list = sorted;

      i++;
    }

    System.out.println("");
  }

}
