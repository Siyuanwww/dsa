int solve1(int* matrix,int n,int m,int x,int y,int a,int b){
    int ans = 0;
    for (int i = x; i < x + a; i++) {
        for (int j = y; j < y + b; j++) {
            ans += *(matrix + (i * 2005) + j);
        }
    }
    return ans;
}