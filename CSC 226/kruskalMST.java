import edu.princeton.cs.algs4.*;
import java.io.File;
import java.util.*;


public class kruskalMST{

  //Accepts a 2d adjacency matrix and returns the minimum spanning tree using kruskals algorithm
  static MinPQ KruskalMST(double[][] G){

    //keeps track of visited nodes
    int[][] visited = new int[G.length][G.length];
    //finds cycles
    UF uf = new UF(G.length);
    double weight = 0;
    int i = 0;
    int j = 0;
    int v = 0;
    int w = 0;

    MinPQ<Edge> pq = new MinPQ<Edge>();
    MinPQ<Edge> mst = new MinPQ<Edge>();

    //loop through entire matrix
    for( i = 0; i < G.length; i++){
      for (j = 0; j < G.length; j++){

        //if edge found put in pq; mark as visited
        if(G[i][j] > 0  && visited(i, j, visited) == false){

            Edge e = new Edge(i, j , G[i][j]);
            pq.insert(e);
            visited[i][j]= 1;
        }
      }
    }

    i = 0;
    //search through pq to form mst
    while(!pq.isEmpty() && i < G.length){
      //get edge and its 2 verticies
      Edge e = pq.delMin();
      v = e.either();
      w = e.other(v);

      //check for cycle; if none, put in mst
      if(uf.find(v) != uf.find(w)){
        uf.union(v,w);
        i++;
        mst.insert(e);
        weight = e.weight() + weight;
        System.out.println(e.toString());
      }

    }
    System.out.println(weight);
    return mst;
  }

}
