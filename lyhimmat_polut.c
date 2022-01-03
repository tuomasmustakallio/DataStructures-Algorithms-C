#include <stdio.h>

#define n 6
#define loputon 999999

int lyhimmat_polut(int d[n][n]){
    int m[n][n], i, j, k;

    for (i = 1; i < n; i++){
        for(j = 1; j < n; j++){
            m[i][j] = d[i][j];
        }
    }
    for(k = 1; k < n; k++){
        for(i = 1; i < n; i++){
            for(j = 1; j < n; j++){
                if(m[i][k] + m[k][j] < m[i][j])
                    m[i][j] = m[i][k] + m[k][j];
            }
        }
    }
    return m;
}

void printtaa(int d[n][n]){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (d[i][j] == loputon)
                printf("%7s", "INF");
            else
                printf ("%7d", d[i][j]);
        }
        printf("\n");
    }
}

int main(void){
    int taulukko[n][n] ={{      0,       4, loputon, loputon,       5, loputon},
                         {loputon,       0,       6, loputon, loputon,       1},
                         {loputon, loputon,       0,       1, loputon,       2},
                         {loputon, loputon, loputon,       0,       2,       4},
                         {loputon, loputon, loputon, loputon,       0, loputon},
                         {loputon, loputon, loputon, loputon, loputon,       0}
                        };
    printtaa(taulukko);
    int lyhyintaulukko[n][n] = lyhimmat_polut(taulukko);
    printtaa(lyhyintaulukko);
    return 0;
}