#include <cstring>
#include "hashtable.h"
typedef long long int64;

int naive_hashing::operator()(char* str, int N){
    if(str == NULL) return 0;
    else return (str[0]+N)%N;
}
int UnevenHashing::operator()(char *str, int N) {
    int h = 0, n = 0;
    for (int i = 0; str[i] > 0; i++) {
        h += str[i];
        n++;
    }
    return (int64)h * n % N;
}
int EvenHashing::operator()(char *str, int N) {
    static const int kBase = 10007;
    int h = 0;
    for (int i = 0; str[i] > 0; i++) {
        h = ((int64)h * kBase + str[i]) % N;
    }
    return h;
}
void linear_probe::init(){
    return;// do nothing
}
int linear_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    return (last_choice + 1) % table_size;
}
void QuadraticProbing::init() {
    sgn = -1;
    step = 0;
}
int QuadraticProbing::operator()(hash_entry* Table, int table_size, int last_choice) {
    int lst = sgn * step * step;
    sgn = -sgn;
    step += (sgn > 0);
    return ((last_choice - lst + sgn * step * step) % table_size + table_size) % table_size;
}