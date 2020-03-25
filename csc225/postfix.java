import java.util.ArrayList;

public class postfix{

  public static void main(String args[]){

ArrayList<Object> stack = new ArrayList<Object>();
ArrayList<Object> stack2 = new ArrayList<Object>();
int result = 0;
int temp1 = 0;
int temp2 = 0;


    myStack numbers = new myStack(stack);
    String[]  string  = args[0].split(" ");

    for(String s : string){

        String var = s;

           if (s.equals("+") ||s.equals("-")|| s.equals("/")|| s.equals("*")){



              temp1 = Integer.parseInt(numbers.pop().toString());
              temp2 = Integer.parseInt(numbers.pop().toString());


             if (s.equals("+")){
               result = temp1 + temp2;

             }else if(s.equals("-")){
               result = temp1 - temp2;


             }else if(s.equals("/")){
               result = temp1 / temp2;


             }else if (s.equals("*")){
               result = temp1 * temp2;

             }
             numbers.push(result);


           }else {
             numbers.push(var);
           }
        }


    System.out.println(result);


  }

}
