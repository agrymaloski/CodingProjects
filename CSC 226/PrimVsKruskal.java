/* PrimVsKruskal.java
   CSC 226 - Summer 2020
   Assignment 2 - Prim MST versus Kruskal MST Template

   The file includes the "import edu.princeton.cs.algs4.*;" so that yo can use
   any of the code in the algs4.jar file. You should be able to compile your program
   with the command

	javac -cp .;algs4.jar PrimVsKruskal.java

   To conveniently test the algorithm with a large input, create a text file
   containing a test graphs (in the format described below) and run
   the program with

	java -cp .;algs4.jar PrimVsKruskal file.txt

   where file.txt is replaced by the name of the text file.

   The input consists of a graph (as an adjacency matrix) in the following format:

    <number of vertices>
	<adjacency matrix row 1>
	...
	<adjacency matrix row n>

   Entry G[i][j] >= 0.0 of the adjacency matrix gives the weight (as type double) of the edge from
   vertex i to vertex j (if G[i][j] is 0.0, then the edge does not exist).
   Note that since the graph is undirected, it is assumed that G[i][j]
   is always equal to G[j][i].
*/

 import edu.princeton.cs.algs4.*;
 import java.util.Scanner;
 import java.io.File;
 import java.util.*;

public class PrimVsKruskal{

  //checks to see if edge was visited, if not return false
  static boolean visited(int i, int j, int[][] array){

    if(array[i][j] == 1 || array[j][i] == 1){
      return true;
    }
    return false;
  }


//to solve  (1) The simplest way to solve this problem is to convert the adjacency matrix into an
//EdgeWeightedGraph object, running PrimMST and KruskalMST on the graph and then comparing the
//output trees to one another.


	/* PrimVsKruskal(G)
		Given an adjacency matrix for connected graph G, with no self-loops or parallel edges,
		determine if the minimum spanning tree of G found by Prim's algorithm is equal to
		the minimum spanning tree of G found by Kruskal's algorithm.

		If G[i][j] == 0.0, there is no edge between vertex i and vertex j
		If G[i][j] > 0.0, there is an edge between vertices i and j, and the
		value of G[i][j] gives the weight of the edge.
		No entries of G will be negative.
	*/
	static boolean PrimVsKruskal(double[][] G){

    MinPQ<Edge> primMST = new MinPQ<Edge>();
    MinPQ<Edge> kruskalMST = new MinPQ<Edge>();
    MinPQ<Edge> pq = new MinPQ<Edge>();
    int n = G.length;
    boolean[] explored = new boolean[G.length];
    int[][] visited = new int[n][n];
    UF uf = new UF(n);
    int i = 0;
    int j = 0;
    int v = 0;
    int u = 0;
	  boolean pvk = true;

    //PRIMS ALGORITHM START///////////////////////////////////////////
    double weight = 0;

    //explore first vertex; if edge add to pq
    for(j = 0; j < n; j++){
      if(G[i][j] > 0){
        Edge e = new Edge(i, j , G[i][j]);
        pq.insert(e);
      }
    }

    //search through pq to form mst
    while(!pq.isEmpty()){
      //get edge and 2 verticies
      Edge e = pq.delMin();
      v = e.either();
      u = e.other(v);

      //check for cycle; if none, add to mst
      if(!explored[u] || !explored[v]){
        explored[u] = true;
        explored[v] = true;
        weight = e.weight() + weight;
        primMST.insert(e);
        //System.out.println(e.toString());

        //explore new vertex
        i = u;
        for(j = 0; j < n; j++){
          if(G[i][j] > 0){
            Edge ee = new Edge(i, j , G[i][j]);
            pq.insert(ee);
          }
        }
      }
    }
    //System.out.println(weight);

    //START OF Kruskal ALGORITHM/////////////////////////////////////
    weight = 0;

    //trace through matrix; if edge found add to pq
    for( i = 0; i < n; i++){
      for (j = 0; j < n; j++){

        if(G[i][j] > 0  && visited(i, j, visited) == false){
            Edge e = new Edge(i, j , G[i][j]);
            pq.insert(e);
            visited[i][j]= 1;
        }
      }
    }
    //filter pq to form mst
    i = 0;
    while(!pq.isEmpty() && i < n){

      //get edge and its 2 vertices
      Edge e = pq.delMin();
      v = e.either();
      u = e.other(v);

      //if no cycle; add to mst
      if(uf.find(v) != uf.find(u)){
        uf.union(v,u);
        i++;
        kruskalMST.insert(e);
        weight = e.weight() + weight;
      //  System.out.println(e.toString());
      }
    }

    //System.out.println(weight);

    //next compare the two mst formed from both algorithm return true if same
    Iterator prim = primMST.iterator();


    int flag = 0;
    //loop through prims edges
    while(prim.hasNext()){

      //get edge and its 2 verticies
      Edge p = (Edge)prim.next();
      v = p.either();
      u = p.other(v);
      Iterator kruskal = kruskalMST.iterator();

      //loop through kruskal edges
      while(kruskal.hasNext()){

        //find edge and 2 vertices
        Edge temp = (Edge)kruskal.next();
        int t = temp.either();
        int g = temp.other(t);
        //if same edge, flag
        if(v == t && u == g || u == t && v == g ){
          flag = 1;
        }
      }
      //if flag = 0, no vertice matched; mst are not the same, return false
      if(flag == 0){
        pvk = false;
        return pvk;
      //else keep comparing mst's
      }else{
        flag = 0;
      }
    }

    //mst's are the same return true
    pvk = true;
		return pvk;
	}

	/* main()
	   Contains code to test the PrimVsKruskal function. You may modify the
	   testing code if needed, but nothing in this function will be considered
	   during marking, and the testing process used for marking will not
	   execute any of the code below.
	*/
   public static void main(String[] args) {
		Scanner s;
		if (args.length > 0){
			try{
				s = new Scanner(new File(args[0]));
			} catch(java.io.FileNotFoundException e){
				System.out.printf("Unable to open %s\n",args[0]);
				return;
			}
			System.out.printf("Reading input values from %s.\n",args[0]);
		}else{
			s = new Scanner(System.in);
			System.out.printf("Reading input values from stdin.\n");
		}

		int n = s.nextInt();
		double[][] G = new double[n][n];
		int valuesRead = 0;
		for (int i = 0; i < n && s.hasNextDouble(); i++){
			for (int j = 0; j < n && s.hasNextDouble(); j++){
				G[i][j] = s.nextDouble();
				if (i == j && G[i][j] != 0.0) {
					System.out.printf("Adjacency matrix contains self-loops.\n");
					return;
				}
				if (G[i][j] < 0.0) {
					System.out.printf("Adjacency matrix contains negative values.\n");
					return;
				}
				if (j < i && G[i][j] != G[j][i]) {
					System.out.printf("Adjacency matrix is not symmetric.\n");
					return;
				}
				valuesRead++;
			}
		}

		if (valuesRead < n*n){
			System.out.printf("Adjacency matrix for the graph contains too few values.\n");
			return;
		}

        boolean pvk = PrimVsKruskal(G);
        System.out.printf("Does Prim MST = Kruskal MST? %b\n", pvk);
    }
}
