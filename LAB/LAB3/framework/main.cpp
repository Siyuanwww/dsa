#include <cstdio>
#include <ctime>
#include <iostream>
#include "hashtable.h"

int main(int argc, char *argv[]) {
    double st = clock();
    hashtable table(TABLE_SIZE, nullptr, nullptr);
    if (argv[1][0] == '1' && argv[2][0] == '1') {
        table.my_hashing = new UnevenHashing();
        table.my_collision = new linear_probe();
    } else if (argv[1][0] == '1' && argv[2][0] == '2') {
        table.my_hashing = new UnevenHashing();
        table.my_collision = new QuadraticProbing();
    } else if (argv[1][0] == '1' && argv[2][0] == '3') {
        table.my_hashing = new UnevenHashing();
        table.my_collision = new PublicOverflow();
    } else if (argv[1][0] == '2' && argv[2][0] == '1') {
        table.my_hashing = new EvenHashing();
        table.my_collision = new linear_probe();
    } else if (argv[1][0] == '2' && argv[2][0] == '2') {
        table.my_hashing = new EvenHashing();
        table.my_collision = new QuadraticProbing();
    } else if (argv[1][0] == '2' && argv[2][0] == '3') {
        table.my_hashing = new EvenHashing();
        table.my_collision = new PublicOverflow();
    }
    int type;
    char buffer[1000];int data;
    while(true){
        scanf("%d", &type);
        if(type == 0){
            scanf("%s", buffer);scanf("%d",&data);
            table.insert(hash_entry(buffer, data));
        }else if(type == 1){
            scanf("%s",buffer);
            printf("%d\n", table.query(buffer));
        }else break;
    }
    std::cerr << (clock() - st) / CLOCKS_PER_SEC << std::endl;
    return 0;
}