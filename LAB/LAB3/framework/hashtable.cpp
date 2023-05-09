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
    for (char *p = str; *p != '\0'; p++) {
        h ^= *p;
    }
    return h % N;
}
int EvenHashing::operator()(char *str, int N) {
    const int kBase = 10007;
    int h = 0;
    for (char *p = str; *p != '\0'; p++) {
        h = ((int64)h * kBase + *p) % N;
    }
    return h;
}


void QuadraticProbing::init() {
    offset = 1;
    step = 1;
}
int QuadraticProbing::operator()(hash_entry* Table, int table_size, int last_choice) {
    int nextChoise = (last_choice + offset) % table_size;
    if (offset > 0) {
        offset = -offset;
        step++;
    } else {
        offset = step * step % table_size;
    }
    return nextChoise;
}