#include "hashtable.h"
typedef long long int64;

int naive_hashing::operator()(char* str, int N){
    if(str == NULL) return 0;
    else return (str[0]+N)%N;
}

int linear_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    return (last_choice + 1) % table_size;
}
void linear_probe::init(){
    return;// do nothing
}



int UnevenHashing::operator()(char *str, int N) {
    int h = 0;
    for (int i = 0; i < N; i++) {
        h ^= str[i];
    }
    return h;
}
int EvenHashing::operator()(char *str, int N) {
    const int kBase = 10007;
    int h = 0;
    for (int i = 0; i < N; i++) {
        h = ((int64)h * kBase + str[i]) % N;
    }
    return h;
}