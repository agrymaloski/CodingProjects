import edu.princeton.cs.algs4.*;
import java.io.File;
import java.util.*;



  public class primMST{

    //Accepts a 2d adjacency matrix and returns the minimum spanning tree using prims algorithm
    static MinPQ MST{
      int i = 0;
      int j = 0;
      //keeps track of visited vertex
      boolean[] explored = new boolean[G.length];
      int count = 0;
      double weight = 0;
      MinPQ<Edge> pq = new MinPQ<Edge>();
      MinPQ<Edge> mst = new MinPQ<Edge>();

      //explore first vertex
      for(j = 0; j < G.length; j++){
        if(G[i][j] > 0){
          Edge e = new Edge(i, j , G[i][j]);
          pq.insert(e);
        }
      }

      //sort through priority queue to find minimul spanning tree
      while(!pq.isEmpty()){

        //get edge, find attached vertices
        Edge e = pq.delMin();
        int v = e.either();
        int u = e.other(v);

        //checks for a cycle; if none, add to mst
        if(!explored[u] || !explored[v]){

          explored[u] = true;
          explored[v] = true;

          //add weight t mst
          weight = e.weight() + weight;

          //add edge to mst
          mst.insert(e);

          //print edges in mst
          System.out.println(e.toString());

          //explore new vertex
          i = u;
          for(j = 0; j < G.length; j++){
            if(G[i][j] > 0){
              Edge ee = new Edge(i, j , G[i][j]);
              pq.insert(ee);
            }
          }
        }
      }
      System.out.println(weight);
      return mst;
    }
  }
}
