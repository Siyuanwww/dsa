#include<cstdio>
#include <ctime>
#include <iostream>
int matrix[2005][2005];
int main(){
    auto s = clock();
    int n,m,q;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            scanf("%d",&matrix[i][j]);
        }
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i){
        int x,y,a,b,sum = 0;
        scanf("%d %d %d %d",&x,&y,&a,&b);
        for(int j=0;j<a;++j){
            for(int k=0;k<b;++k){
                sum += matrix[x+j][y+k];
            }
        }
        printf("%d\n",sum);
    }
    std::cerr << clock() - s << std::endl;
    return 0;
}