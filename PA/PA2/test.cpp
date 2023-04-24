# include<cstdio>
#include <cassert>
long long totr=0,tot1=0,tot2=0,tot4=0;
struct s{
    long long x,y;
};
int cop(s a,s b){
    long long m;
    m=a.y*b.x-a.x*b.y;
    if(m>0){
        return 1;
    }
    if(m==0){
        return 2;
    }
    else{
        return 3;
    }
}
// void merge2(s* a,long long lo,long long mid,long long hi){
//     s *a1 = new s[mid-lo];
//     s *a2 = new s[hi-mid];
//     s *m = new s[hi-lo];
//     long long cnt1 = 0, cnt2 = 0;
//     for (long long i = lo; i < mid; i++)
//     {
//         s[cnt1++] = a[i];
//     }
//     for (long long i = mid; i < hi; i++)
//     {
//         a2[cnt2++] = a[i];
//     }
//     long long p = 0, p1 = 0, p2 = 0;
//     while (p1 < cnt1 || p2 < cnt2)
//     {
//         if ((a1[p1] <= a2[p2] || p2==cnt2) && a1[p1]!=0)
//         {
//             m[p++] = a1[p1++];
//         }
//         else if((a2[p2]<a1[p1] || p1==cnt1) && a2[p2]!=0)
//         {
//             if(a2[p2]<a1[p1]){
//             tot1+=cnt1-p1; 
//             }
//             m[p++] = a2[p2++];
//         }
//     }
//     for (long long i = lo; i < hi; i++)
//     {
//         a[i] = m[i - lo];
//     }
//     delete[] a1;
//     delete[] a2;
//     delete[] m;
// }
void merge1(long long *a, long long lo, long long mid, long long hi)
{
    long long *a1 = new long long[mid-lo];
    long long *a2 = new long long[hi-mid];
    long long *m = new long long[hi-lo];
    long long cnt1 = 0, cnt2 = 0;
    for (long long i = lo; i < mid; i++)
    {
        a1[cnt1++] = a[i];
    }
    for (long long i = mid; i < hi; i++)
    {
        a2[cnt2++] = a[i];
    }
    assert(cnt1 == mid - lo);
    assert(cnt2 == hi - mid);
    long long p = 0, p1 = 0, p2 = 0;
    while (p1 < cnt1 || p2 < cnt2)
    {
        if ((p2 == cnt2 || a1[p1] <= a2[p2]))
        {
            if (p >= hi - lo) {
                printf("fail [p] 1\n");
            }
            if (p1 >= mid - lo) {
                printf("fail [p1] 1\n");
            }
            m[p++] = a1[p1++];
        }
        else if((p1 == cnt1 || a2[p2]<a1[p1]))
        {
            if(p1 < cnt1 && a2[p2]<a1[p1]){
            tot1+=cnt1-p1; 
            }
            m[p++] = a2[p2++];
        }
    }
    for (long long i = lo; i < hi; i++)
    {
        a[i] = m[i - lo];
    }
    delete[] a1;
    delete[] a2;
    delete[] m;
}
void merges1(long long *a, long long lo, long long hi)
{
    // printf("%lld %lld\n", lo, hi);
    if (hi - lo < 2)
    {
        return;
    }
    long long mid = (lo + hi) / 2;
    merges1(a, lo, mid);
    merges1(a, mid, hi);
    merge1(a, lo, mid, hi);
}
long long A[400005];
s B[400005];
int main(){
    int n;
    scanf("%d",&n);
    // printf("0");
    for(long long i=0;i<n;i++){
        scanf("%lld",&A[i]);
        B[i].x=A[i];
        B[i].y=i;
    }
    merges1(A,0,n);
    for (long long i = 0; i < n; i++)
    {
        printf("%lld ", A[i]);
    }
    printf("\n");
    printf("%lld",tot1);

}