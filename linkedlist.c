#include <stdio.h>
#include <stdlib.h>
 
struct solmu {
    int arvo;
    struct solmu *seuraava;
};
typedef struct solmu SOLMU;

SOLMU *lisaaSolmu(SOLMU *alku){
    SOLMU *uusisolmu;
    int num;
    printf("Anna alkiolle arvo: ");
    scanf("%d", &num);
    getchar();
    uusisolmu = (SOLMU*)malloc(sizeof(SOLMU));
    uusisolmu->arvo = num;
    uusisolmu->seuraava = NULL;
    if(alku == NULL){
        alku = uusisolmu;
        return alku;
    }else{
        SOLMU *valimuisti = alku;
        while (valimuisti->seuraava != NULL){
            valimuisti = valimuisti->seuraava;
        }
        valimuisti->seuraava = uusisolmu;
    }
    SOLMU *n = alku;
    while(n != NULL){
        printf("%d ", n->arvo);
        n = n->seuraava;
    }
    printf("\n");
    return alku;
}

SOLMU *poistaSolmu(SOLMU *alku){
    int num;
    SOLMU *valimuisti = alku;
    SOLMU *viimeinen;
    printf("Valitse alkio jonka haluat poistaa: ");
    scanf("%d", &num);
    getchar();
    while (valimuisti->arvo != num) {
        viimeinen = valimuisti;
        valimuisti = valimuisti->seuraava;
    }
    viimeinen->seuraava = viimeinen->seuraava->seuraava;
    free(valimuisti);
    SOLMU *n = alku;
    while(n != NULL){
        printf("%d ", n->arvo);
        n = n->seuraava;
    }
    printf("\n");
    return alku;
}

int main(){
    int c = -1;
    SOLMU *alku = NULL;
    printf("Tämä ohjelma leikkii linkitetyn listan kanssa:)\n");
    while(c!=0){
        printf("1: Lisää alkio, 2: Poista alkio, 0: Lopeta ja tyhjennä lista, Valinta: ");
        scanf("%d", &c);
        getchar();
        switch (c){
        case 1:
            alku = lisaaSolmu(alku);
            break;
        case 2:
            alku = poistaSolmu(alku);
            break;
        case 0:
            printf("Kiitos käytöstä.\n");
            SOLMU *ptr = alku;
            while (alku != NULL) {
                ptr = alku->seuraava;
                free(alku);
                alku = ptr;
	        }
            break;
        default:
            printf("Valintaa ei tunnistettu");
            break;
        }
    }
    return 0;
}