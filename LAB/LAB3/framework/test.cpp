#include <bits/stdc++.h>
#include <windows.h>

int main() {
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 3; j++) {
            for (int k = 1; k <= 3; k++) {
                char command[100];
                sprintf(command, "main %d %d < sample%d.in > out", i, j, k);
                printf("%d %d %d: ", i, j, k);
                system(command);
                // if (system(("diff -q out sample" + std::to_string(k) + ".ans").c_str())) {
                //     printf("Error!\n");
                //     return 0;
                // }
                // printf("ok\n");
            }
        }
    }
    return 0;
}