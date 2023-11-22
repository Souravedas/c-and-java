#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, W;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    int val[n], wt[n];
    int i, j;
   

    for (int i = 0; i < n; i++) {
    	printf("For Item %d :\n",i+1);
        printf("Enter Weight and Value : ");
        scanf("%d %d",&wt[i],&val[i]);
    }

    printf("Enter the maximum weight capacity of the knapsack: ");
    scanf("%d", &W);
     int dp[n + 1][W + 1];
    

    for (i = 0; i <= n; i++) {
        for (j = 0; j <= W; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (wt[i - 1] <= j)
                dp[i][j] = max(val[i - 1] + dp[i - 1][j - wt[i - 1]], dp[i - 1][j]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    printf("Maximum value: %d\n", dp[n][W]);

    return 0;
}
