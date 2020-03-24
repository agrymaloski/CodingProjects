import java.io.*;
import java.lang.*;
import java.util.ArrayList;
import java.util.NoSuchElementException;


//this class was written to create a stack from a linked list. It implements typical methods of a stack and is tested
//and used in test.java.

public class myStack{

    public ArrayList<Object> stack = new ArrayList<Object>();

    myStack(ArrayList<Object> stack){
      this.stack = stack;

    }


    //checks if stack is empty, returns boolean
    public boolean isEmpty(){

        if (stack.size() == 0){
            return true;
        }
        return false;
    }

    
    //returns number of elements in the stack
    public int size(){

        return stack.size();

    }

    
    //accepts an element and adds element to the stack
    public void push(Object element){
        int temp = stack.size() - 1;
        stack.add(0, element);
    }


    //removes an element from the stack and returns removed object. throws exception if empty
    public Object pop(){

        if (stack.size() == 0){
            throw new NoSuchElementException();
        }

        Object obj = stack.get(0);
        stack.remove(0);
        return obj;
    }

    //returns top element from the stack, if empty throws exception
    public Object peek(){

        if (stack.size() == 0){
            throw new NoSuchElementException();
        }

        return stack.get(0);
    }

}
