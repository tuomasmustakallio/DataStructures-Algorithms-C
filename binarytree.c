#include <stdio.h>
#include <stdlib.h>
 
struct solmu{
    int avain;
    struct solmu *vasen, *oikea;
};
 
struct solmu* uusiSolmu(int num){
    struct solmu* temp = (struct solmu*)malloc(sizeof(struct solmu));
    temp->avain = num;
    temp->vasen = temp->oikea = NULL;
    return temp;
}
 
void inorder(struct solmu* juuri){
    if (juuri != NULL) {
        inorder(juuri->vasen);
        printf("%d \n", juuri->avain);
        inorder(juuri->oikea);
    }
}

struct solmu* syota(struct solmu* solmu, int avain){
    
    if (solmu == NULL){
        return uusiSolmu(avain);
    }if (avain < solmu->avain){
        solmu->vasen = syota(solmu->vasen, avain);
    }else if (avain > solmu->avain){
        solmu->oikea = syota(solmu->oikea, avain);
    }
    return solmu;
}
 
int main(){
    struct solmu* juuri = NULL;
    int c;
    printf("Haluatko puun rakenteeksi,\n1: 25, 23, 28, 16, 44, 24, 27\n2: 44, 28, 27, 23, 16, 24, 25\nValinta: ");
    scanf("%d", &c);
    getchar();
    switch (c)
    {
    case 1:
        juuri = syota(juuri, 50);
        syota(juuri, 25);
        syota(juuri, 23);
        syota(juuri, 28);
        syota(juuri, 16);
        syota(juuri, 44);
        syota(juuri, 24);
        syota(juuri, 27);
        inorder(juuri);
        break;
    case 2:
        juuri = syota(juuri, 50);
        syota(juuri, 44);
        syota(juuri, 28);
        syota(juuri, 27);
        syota(juuri, 23);
        syota(juuri, 16);
        syota(juuri, 24);
        syota(juuri, 25);
        inorder(juuri);
        break;
    default:
        printf("Ei vaihtoehto.");
        break;
    }
    return 0;
}