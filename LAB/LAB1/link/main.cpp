#include<cstdio>
#include<cstdlib>
#include"solve1.h"
#include"solve2.h"
int matrix[2005][2005];
int main(int argc, char** argv){
    
    int n,m,q;
    int cmdline_arg = 0;
    if(argc >= 1){
        cmdline_arg = atoi(argv[1]); 
    }
    if(cmdline_arg!=1 && cmdline_arg!=2){
        return -1;
    }

    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            scanf("%d",&matrix[i][j]);
        }
    }
    scanf("%d",&q);
    int sum = 0;
    for(int i=1;i<=q;++i){
        int x,y,a,b;
        scanf("%d %d %d %d",&x,&y,&a,&b);
        int sum;
        if (cmdline_arg == 1)
        {
            sum = solve1(matrix[0],2000,2000,x,y,a,b);
        }else if(cmdline_arg == 2){
            sum = solve2(matrix[0],2000,2000,x,y,a,b);
        }else{
            return -1;
        }
        
        printf("%d\n",sum);
    }
    return 0;
}