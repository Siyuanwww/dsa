int solve2(int* matrix,int n,int m,int x,int y,int a,int b){
    static int sum[2005][2005];
    static bool initiated = false;
    if (!initiated) {
        initiated = true;
        for (int i = 1; i <= n; i++) {
            sum[i][0] = 0;
            for (int j = 1; j <= m; j++) {
                sum[i][j] = sum[i][j - 1] + *(matrix + i * 2005 + j);
            }
        }
    }
    int ans = 0;
    for (int i = x; i < x + a; i++) {
        ans += sum[i][y + b - 1] - sum[i][y - 1];
    }
    return ans;
}