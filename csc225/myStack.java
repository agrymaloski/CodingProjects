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



public boolean isEmpty(){

  if (stack.size() == 0){
    return true;
  }
  return false;

}


public int size(){

  return stack.size();

}

public void push(Object element){
  int temp = stack.size() - 1;
    stack.add(0, element);
}


public Object pop(){

  if (stack.size() == 0){
  throw new NoSuchElementException();
  }

  Object obj = stack.get(0);
  stack.remove(0);
  return obj;
}


public Object peek(){

  if (stack.size() == 0){
  throw new NoSuchElementException();
  }

  return stack.get(0);
}

}
