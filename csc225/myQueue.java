import java.io.*;
import java.lang.*;
import java.util.ArrayList;
import java.util.NoSuchElementException;



public class myQueue{

    public ArrayList<Object> queue = new ArrayList<Object>();

    myQueue(ArrayList<Object> queue){
      this.queue = queue;

    }



public boolean isEmpty(){

  if (queue.size() == 0){
    return true;
  }
  return false;

}

public int size(){
  return queue.size();
}

public void enqueue(Object element){
    queue.add(0,element);
}


public Object dequeue(){

  if (queue.size() == 0){
  throw new NoSuchElementException();
  }

  Object obj = queue.get(queue.size() - 1);
  queue.remove(queue.size() - 1);
  return obj;
}


public Object front(){

  if (queue.size() == 0){
  throw new NoSuchElementException();
  }

  return queue.get(queue.size() - 1);
}

}
