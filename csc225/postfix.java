import java.util.ArrayList;

//program is a postfix calculator. It will accept an input string from the command 
//line containing a combination of numbers and operators. It computes the postfix expression using myStack.java and prints the results
//Example input: “ 3 10 5 + * ” Resulting calculation:
//10 + 5 = 15
//3 * 15 = 45
//Example output: 45



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

        //checks to see if it was a number of opperator
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
