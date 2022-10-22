for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (dist[j][k] > (dist[j][i] + dist[i][k]) && (dist[j][i] != INF && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
        }
    }
}
