#include <stdio.h>
#include <stdlib.h>

double satunnainen(){return (double)rand() / (double)RAND_MAX ;}

int main(){

    int M = 0;//Kokonaismäärä arvauksia
    int k=0;//Arvaukset (0,1) ympyrän sisällä
    double x, y, z;

    printf("Monta iteraatiota haluat piin arviomiseen: ");
    scanf("%d",&M);
    getchar();

    for(int i=0; i<M; i++)
    {
        x = satunnainen();//Arvotaan x
        y = satunnainen();//ja y koordinaatit

        z = x*x +y*y;

        if(z < 1)// Jos piste on (0,1) ympyrän sisällä
        {
            k+=1;
        }
    }

    double pii = (double)k/M*4;
    printf("Arvioitu piin arvo on: %g", pii);
    return 0;
}
