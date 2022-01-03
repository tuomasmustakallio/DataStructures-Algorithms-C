#include <stdio.h>
#include <stdbool.h>
#define MAX 5

void haku(int k, int n, int luvut[MAX]){
    int i;
    bool mukana[MAX] = {false, false, false, false, false}; 
    if(k == n){
        for(i = 0;i<=n-1;i++){
            printf("%d", luvut[i]);
        }
        printf("\n");
    }
    else{
        for(i = 1;i<=n;i++){
            if(!mukana[i]){
                mukana[i] = true;
                luvut[k] = i;
                haku(k+1, n, luvut);
                mukana[i] = false;
            }
        }
    }
}

int main(){
    int luvut[MAX] = {1, 2, 3, 4, 5};
    int n = MAX;
    int k = 0;
    haku(k, n, luvut);
    return 0;
}