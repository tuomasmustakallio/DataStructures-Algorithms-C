#include <stdio.h>

void rekursiivinenLajittelu(int lista[], int n){
    if (n <= 1){
        return;
    }
    rekursiivinenLajittelu( lista, n-1 );
    int v = lista[n-1];
    int j = n-2;
    while (j >= 0 && lista[j] > v){
        lista[j+1] = lista[j];
        j--;
    }
    lista[j+1] = v;
}
int main(){
    int lista[] = {8, 16, 24, 20, 16, 28, 6, 3};
    int n = sizeof(lista)/sizeof(lista[0]);
    rekursiivinenLajittelu(lista, n);
    for (int i=0; i < n; i++)
        printf("%d ",lista[i]);
    return 0;
}