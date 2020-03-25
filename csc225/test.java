import java.util.ArrayList;

public class test{

  public static void main(String args[]){

    ArrayList<Object> stack = new ArrayList<Object>();
    ArrayList<Object> queue = new ArrayList<Object>();


    myStack s1 = new myStack(stack);
    myQueue q1 = new myQueue(queue);

    //read arguments from user
    for(int i= 0; i< args.length; i++){
           s1.push(args[i]);
           q1.enqueue(args[i]);
        }

    //print stack
    while(!s1.isEmpty()){
      System.out.print(s1.pop().toString() + " " );
    }
    System.out.println("\nThe Stack is empty");


    //print stack
    while(!q1.isEmpty()){
      System.out.print(q1.dequeue().toString() + " ");
    }
    System.out.println("\nThe Queue is empty");




/*
    s1.push("a");
    s1.push("b");
    s1.push("c");
    System.out.println(stack);
    s1.pop();
    s1.pop();
    System.out.println(stack);
*/


  }

}
