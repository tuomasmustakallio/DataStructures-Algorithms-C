//Tekijä: Tuomas Mustakallio

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define D 9
#define V 3

typedef struct puusolmu_t {
    int luku;
    short tila; /* tasapainoilmaisin */
    struct puusolmu_t *vasen, *oikea;
} puusolmu, *puuosoitin;

void lisaa_solmu(puuosoitin *, int, int *);
void oikea_kierto(puuosoitin *, int *);
void tulosta_puu(puuosoitin, int);
void vasen_kierto(puuosoitin *, int *);
int * lue_tiedosto(int avaimet[]);
void etsi_solmu(puuosoitin *, int);

int main(){
    int etp = 0, i;
    int avaimet[D];
    puuosoitin puu = NULL;
    int valinta;
    srand(time(NULL));
    int r = rand();

    printf("Alustetaan puu...\nHaluatko alkiot\n1) Tiedostosta avaimet.txt\n2) 100 satunnaista alkiota\n3) 1 000 satunnaista alkiota\n4) 10 000 alkiota\n5) 100 000 alkiota\nValinta: ");
    scanf("%d", &valinta);
    getchar();
    switch (valinta)
    {
    case 1:
        printf("Lisätään alustavat avaimet puuhun tiedostosta avaimet.txt\n");
        lue_tiedosto(avaimet);

        for(i = 0; avaimet[i] != 0; i++){
            lisaa_solmu(&puu, avaimet[i], &etp);
        }
        break;
    case 2:
        for(int i = 0; i < 100; i++){
            r = rand();
            lisaa_solmu(&puu, r, &etp);
        }
        break;
    case 3:
        for(int i = 0; i < 1000; i++){
            r = rand();
            lisaa_solmu(&puu, r, &etp);
        }
        break;
    case 4:
        for(int i = 0; i < 10000; i++){
            lisaa_solmu(&puu, i, &etp);
        }
        break;
    case 5:
        for(int i = 0; i < 100000; i++){
            lisaa_solmu(&puu, i, &etp);
        }
        break;
    default:
        printf("Ei vaihtoehto");
        exit(0);
        break;
    }

    tulosta_puu(puu, 0);
    printf("\n");

    int c = -1;
    int alkio;

    while(c!=0){
        printf("\n1) Etsi alkio\n2) Lisää alkio\n3) Tulosta puu\n0) Lopettaa\nValinta: ");
        scanf("%d", &c);
        getchar();
        switch (c)
        {
        case 1:
            printf("\nMinkä alkion haluat etsiä puusta?\n");
            scanf("%d", &alkio);
            getchar();
            clock_t aloita = clock();
            etsi_solmu(&puu, alkio);
            clock_t lopeta = clock();
            double haku_aika = (double)(lopeta - aloita) / CLOCKS_PER_SEC;
            printf("Haussa kesti %f sekunttia\n", haku_aika);
            break;
        case 2:
            printf("\nMinkä alkion haluat lisätä puuhun?\n");
            scanf("%d", &alkio);
            getchar();
            lisaa_solmu(&puu, alkio, &etp);
            printf("Solmu lisätty.\n");
            break;
        case 3:
            tulosta_puu(puu, 0);
            break;
        default:
            printf("Kiitos ohjelman.\n");
            break;
        }
    }

    return 0;
}

;void etsi_solmu(puuosoitin *emo, int solmu){
    puuosoitin *esim = emo;
    int kerros = 0;
    while((*esim)->luku != solmu){
        if((*esim)->luku > solmu){
            if(!(*esim)->vasen==NULL){
                esim = &(*esim)->vasen;
                kerros++;
            }else{
                printf("Solmua ei löytynyt\n");
                break;
            }
        }else if((*esim)->luku < solmu){
            if(!(*esim)->oikea==NULL){
                esim = &(*esim)->oikea;
                kerros++;
            }else{
                printf("Solmua ei löytynyt\n");
                break;
            }
        }
    }
    if((*esim)->luku == solmu){
        printf("Solmu %d löytyi muistipaikasta %p, kerroksesta %d\n",(*esim)->luku, esim, kerros);
    }
}

int * lue_tiedosto(int avaimet[]){
    FILE *filu;
    char buffer[10];

    if((filu = fopen("avaimet.txt", "r")) == NULL){
		perror("Tiedoston avaaminen epäonnistui");
		exit(0);
	}

    for(int i =0; i<D; i++){
        fgets(buffer,10, filu);
        avaimet[i] = atoi(buffer);
    }
    fclose(filu);

    return avaimet;
}

void lisaa_solmu(puuosoitin *emo, int luku, int *etp){
    if(!(*emo)){
        *etp = 1;
        if(!(*emo = (puuosoitin)malloc(sizeof(puusolmu)))){
            perror("malloc");
            exit(1);
        }
        (*emo)->vasen = (*emo)->oikea = NULL;
        (*emo)->tila = 0;
        (*emo)->luku = luku;
    } else if(luku < (*emo)->luku){
        lisaa_solmu(&(*emo)->vasen, luku, etp);
        if(*etp){
            switch((*emo)->tila){
            case -1:
                (*emo)->tila = 0;
                *etp = 0;
                break;
            case 0:
                (*emo)->tila = 1;
                break;
            case 1:
                vasen_kierto(emo, etp);
            }
        }
    } else if(luku > (*emo)->luku){
        lisaa_solmu(&(*emo)->oikea, luku, etp);
        if(*etp){
            switch((*emo)->tila){
            case 1:
                (*emo)->tila = 0;
                *etp = 0;
                break;
            case 0:
                (*emo)->tila = -1;
                break;
            case -1:
                oikea_kierto(emo, etp);
            }
        }
    } else{
        *etp = 0;
        printf("Luku %d on jo puussa\n", luku);
    }
}

void tulosta_puu(puuosoitin solmu, int vali){
    if(!solmu) return;
    vali += V;
    tulosta_puu(solmu->oikea, vali);

    printf("\n");
    for(int i = V; i < vali; i++){
        printf(" ");
    }
    printf("%d\n", solmu->luku);
    
    tulosta_puu(solmu->vasen, vali);
}

void vasen_kierto(puuosoitin *emo, int *etp){
    puuosoitin lapsi, lapsenlapsi;

    lapsi = (*emo)->vasen;
    if(lapsi->tila == 1)/* LL-kierto */{
        (*emo)->vasen = lapsi->oikea;
        lapsi->oikea = *emo;
        (*emo)->tila = 0;
        (*emo) = lapsi;
    } else /* LR-kierto */{
        lapsenlapsi = lapsi->oikea;
        lapsi->oikea = lapsenlapsi->vasen;
        lapsenlapsi->vasen = lapsi;
        (*emo)->vasen = lapsenlapsi->oikea;
        lapsenlapsi->oikea = *emo;
        switch(lapsenlapsi->tila){
        case 1:
            (*emo)->tila = -1;
            lapsi->tila = 0;
            break;
        case 0:
            (*emo)->tila = lapsi->tila = 0;
            break;
        case -1:
            (*emo)->tila = 0;
            lapsi->tila = 1;
        }
        *emo = lapsenlapsi;
    }
    (*emo)->tila = 0;
    *etp = 0;
}

void oikea_kierto(puuosoitin *emo, int *etp){
    puuosoitin lapsi, lapsenlapsi;

    lapsi = (*emo)->oikea;
    if(lapsi->tila == -1)/* RR-kierto */{
        (*emo)->oikea = lapsi->vasen;
        lapsi->vasen = *emo;
        (*emo)->tila = 0;
        (*emo) = lapsi;
    } else /* RL-kierto */{
        lapsenlapsi = lapsi->vasen;
        lapsi->vasen = lapsenlapsi->oikea;
        lapsenlapsi->oikea = lapsi;
        (*emo)->oikea = lapsenlapsi->vasen;
        lapsenlapsi->vasen = *emo;
        switch(lapsenlapsi->tila){
        case 1:
            (*emo)->tila = -1;
            lapsi->tila = 0;
            break;
        case 0:
            (*emo)->tila = lapsi->tila = 0;
            break;
        case -1:
            (*emo)->tila = 0;
            lapsi->tila = 1;
        }
        *emo = lapsenlapsi;
    }
    (*emo)->tila = 0;
    *etp = 0;
}