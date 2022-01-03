#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Kaari
{
    int alku, loppu, paino;
};

struct Graafi
{
    int solmut, kaaret;
    struct Kaari* kaari;
};

// Luo graafin
struct Graafi* luoGraafi(int solmut, int kaaret)
{
    struct Graafi* graafi = (struct Graafi*)(malloc(sizeof(struct Graafi)));

    graafi->solmut = solmut;
    graafi->kaaret = kaaret;
    graafi->kaari = (struct Kaari*)malloc(sizeof(struct Kaari)*kaaret);

    return graafi;
}

struct lapsi
{
    int vanhempi;
    int jarjestys;
};

int loyda(struct lapsi lapset[], int i)
{
    if(lapset[i].vanhempi != i)
    {
        lapset[i].vanhempi = loyda(lapset, lapset[i].vanhempi);
    }
    return lapset[i].vanhempi;
}

// Luo yhteys
void yhteys(struct lapsi lapset[], int x, int y)
{
    int xjuuri = loyda(lapset, x);
    int yjuuri = loyda(lapset, y);

    if (lapset[xjuuri].jarjestys < lapset[yjuuri].jarjestys)
    {
        lapset[xjuuri].vanhempi = yjuuri;
    }
    else if (lapset[xjuuri].jarjestys > lapset[yjuuri].jarjestys)
    {
        lapset[yjuuri].vanhempi = xjuuri;
    }
    else
    {
        lapset[yjuuri].vanhempi = xjuuri;
        lapset[xjuuri].jarjestys++;
    }
}

//Vertaa kaarein painoa
int vertaa(const void* a, const void* b)
{
    struct Kaari* a1 = (struct Kaari*)a;
    struct Kaari* b1 = (struct Kaari*)b;

    return a1->paino > b1->paino;
}

//Luo Virittivän puun
void Kruskal(struct Graafi* graafi)
{
    int solmut = graafi->solmut;
    struct Kaari tulos[solmut];
    int e = 0;
    int i = 0;

    qsort(graafi->kaari, graafi->kaaret, sizeof(graafi->kaari[0]),vertaa);

    struct lapsi* lapset = (struct lapsi*)malloc(solmut * sizeof(struct lapsi));

    for (int s = 0; s < solmut; ++s)
    {
        lapset[s].vanhempi = s;
        lapset[s].jarjestys = 0;
    }

    while(e < solmut - 1 && i < graafi->kaaret) 
    {
        struct Kaari seuraavaKaari = graafi->kaari[i++];

        int x = loyda(lapset, seuraavaKaari.alku);
        int y = loyda(lapset, seuraavaKaari.loppu);

        if(x != y)
        {
            tulos[e++] = seuraavaKaari;
            yhteys(lapset, x, y);
        }
    }

    printf("Viritetyssä puussa olevat kaaret:\n");

    int minimi = 0;

    for(i = 0; i < e; ++i)
    {
        printf("d(%d,%d)=%d\n", tulos[i].alku, tulos[i].loppu, tulos[i].paino);
        minimi += tulos[i].paino;
    }

    printf("Minimi: %d", minimi);

    return;
}

int main()
{
    /*Luodaan analysoitava graafi:
            4
        0------1
        |   /  |
       5| 6/   |9
        | /  6 |
        2------3
        |   /
      12| 5/
        | /
        4
    */
    
    int solmut = 5;
    int kaaret = 7;
    struct Graafi* graafi = luoGraafi(solmut, kaaret);

    // 0-1
    graafi->kaari[0].alku = 0;
    graafi->kaari[0].loppu = 1;
    graafi->kaari[0].paino = 4;

    // 0-2
    graafi->kaari[1].alku = 0;
    graafi->kaari[1].loppu = 2;
    graafi->kaari[1].paino = 5;

    // 1-2
    graafi->kaari[2].alku = 1;
    graafi->kaari[2].loppu = 2;
    graafi->kaari[2].paino = 6;

    // 1-3
    graafi->kaari[3].alku = 1;
    graafi->kaari[3].loppu = 3;
    graafi->kaari[3].paino = 9;

    // 2-3
    graafi->kaari[4].alku = 2;
    graafi->kaari[4].loppu = 3;
    graafi->kaari[4].paino = 6;

    // 2-4
    graafi->kaari[5].alku = 2;
    graafi->kaari[5].loppu = 4;
    graafi->kaari[5].paino = 12;

    // 3-4
    graafi->kaari[6].alku = 3;
    graafi->kaari[6].loppu = 4;
    graafi->kaari[6].paino = 5;

    Kruskal(graafi);

    return 0;
}