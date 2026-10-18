import java.util.*;

class Solution {
    class Edge{
        int to;
        int dist;
        Edge(int to, int dist){
            this.to = to;
            this.dist = dist;
        }
    }
    public int minScore(int n, int[][] roads) {
        List<List<Edge>> graph = new ArrayList<>();
        for(int i = 0; i <= n; i++){
            graph.add(new ArrayList<>());
        }

        for(int[] road : roads){
            int u = road[0];
            int v = road[1];
            int dist = road[2];
            graph.get(u).add(new Edge(v, dist));
            graph.get(v).add(new Edge(u, dist));
        }
        boolean[] visited = new boolean[n + 1];
        Queue<Integer> queue = new LinkedList<>();

        queue.offer(1);
        visited[1] = true;

        int minScore = Integer.MAX_VALUE;

        while (!queue.isEmpty()){
            int curr = queue.poll();

            for(Edge edge : graph.get(curr)){

                minScore = Math.min(minScore, edge.dist);

                if(!visited[edge.to]){
                    visited[edge.to] = true;
                    queue.offer(edge.to);
                }
            }
        }
        return minScore;
    }
}