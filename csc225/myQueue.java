import java.io.*;
import java.lang.*;
import java.util.ArrayList;
import java.util.NoSuchElementException;

//this program implements methods to implement a queue from an array list

public class myQueue{

    public ArrayList<Object> queue = new ArrayList<Object>();

        myQueue(ArrayList<Object> queue){
        this.queue = queue;
    }


    //checks if queue is empty and returns a boolean
    public boolean isEmpty(){

     if (queue.size() == 0){
      return true;
     }
     return false;

    }

    //returns the size of the queue
    public int size(){
      return queue.size();
    }

    //accepts an object and adds it to the queue
    public void enqueue(Object element){
      queue.add(0,element);
    }

    //removes an element from the queue and returns the removed element (throws exception if queue is empty)
    public Object dequeue(){

        if (queue.size() == 0){
            throw new NoSuchElementException();
        }

        Object obj = queue.get(queue.size() - 1);
        queue.remove(queue.size() - 1);
        return obj;
    }

    
    //returns the object at the head of the queue, throws exception if queue is empty
    public Object front(){

        if (queue.size() == 0){
            throw new NoSuchElementException();
        }

        return queue.get(queue.size() - 1);
    }

}
