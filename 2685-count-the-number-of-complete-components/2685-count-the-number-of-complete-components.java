import java.util.*;

class Solution {
    public int countCompleteComponents(int n, int[][] edges) {
        // Build adjacency list
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }

        boolean[] visited = new boolean[n];
        int completeComponentsCount = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                // Track nodes and edge count for the current component
                int[] stats = bfs(i, adj, visited);
                int nodeCount = stats[0];
                int edgeCount = stats[1] / 2; // undirected edges are counted twice

                // A component is complete if E = V * (V - 1) / 2
                if (edgeCount == nodeCount * (nodeCount - 1) / 2) {
                    completeComponentsCount++;
                }
            }
        }

        return completeComponentsCount;
    }

    private int[] bfs(int start, List<List<Integer>> adj, boolean[] visited) {
        Queue<Integer> queue = new LinkedList<>();
        queue.add(start);
        visited[start] = true;

        int nodeCount = 0;
        int edgeCount = 0;

        while (!queue.isEmpty()) {
            int curr = queue.poll();
            nodeCount++;
            edgeCount += adj.get(curr).size();

            for (int neighbor : adj.get(curr)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.add(neighbor);
                }
            }
        }

        return new int[] { nodeCount, edgeCount };
    }
}