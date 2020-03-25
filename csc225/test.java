import java.util.ArrayList;

//this class tests myQueue.java and myStack.java. It accepts data from the command line
public class test{

  
  public static void main(String args[]){

    ArrayList<Object> stack = new ArrayList<Object>();
    ArrayList<Object> queue = new ArrayList<Object>();


    myStack s1 = new myStack(stack);
    myQueue q1 = new myQueue(queue);

    
    //read arguments from command line and put in queue and stack
    for(int i= 0; i< args.length; i++){
           s1.push(args[i]);
           q1.enqueue(args[i]);
        }

    //print the stack
    while(!s1.isEmpty()){
      System.out.print(s1.pop().toString() + " " );
    }
    System.out.println("\nThe Stack is empty");


    //print the queue
    while(!q1.isEmpty()){
      System.out.print(q1.dequeue().toString() + " ");
    }
    System.out.println("\nThe Queue is empty");



  }

}
