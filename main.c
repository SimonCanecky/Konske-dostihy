#include <stdio.h>

#ifndef K
#define K 4
#endif

#define MIN_TRACK 10 // minimalna dlzka trate
#define MAX_TRACK 100 // max. dlzka trate

// generovanie pseudo-nahodnych cisiel.
//
// Funkcia srnd(seed):
// * 1-krat na zaciatku programu na
// inicializaciu generovanej postupnosti cisiel.
//
// Funkcia rnd(from, to):
// * Sluzi na vygenerovanie dalsieho nahodneho
// cisla z intervalu <from,to>.

#define R_MAX 2147483647

static long long unsigned int SEED = 0x1; // seed generatora

void srnd(int seed) {
    SEED = seed;
}

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}

int control(int n, int p) {
    if (n < MIN_TRACK || n > MAX_TRACK) {
        printf("E1");
        return 0;
    }
    else if (p > n/2) {
        printf("E2");
        return 0;
    }
    return 1;
}

int main() {
    int n,p,seed,r,pos_after,value;
    int track[MAX_TRACK];
    int horse[K];
    int pos_before[K];
    int winner[K];
    int obstacle = 0;
    int round = 1;
    int end = 0;
    int win = 0;

    scanf("%d%d%d",&n,&p,&seed);
    srnd(seed);
    value = control(n,p);
    if (value == 0)
        return 0;

    for (int i=0; i < n; i++)
        track[i] = 0;

    for (int i=0; i < p; i++) {
        int pos = rnd(1,n-2);
        if (track[pos] == 0)
            track[pos] = 1;
        else
            i -= 1;
    }

    for (int i=0; i < n; i++) {
        if (track[i] == 1)
            obstacle += 1;
        else
            obstacle = 0;
        if (obstacle > 3) {
            printf("E3");
            return 0;
        }
    }
    printf("%d %d %d %d\n",K,n,p,seed);
    for (int i=0; i < n;i++)
        printf("%d",track[i]);

    while(end != K){
        for (int j=0;j < K;j++) {
            if (round == 1) {
                r = rnd(1,6);
                horse[j] = j + 1;
                pos_before[j] = -1;
                pos_after = 0 + r;
            }
            else if(horse[j] == -1 || horse[j] == -3)
                continue;
            else if(horse[j] == -2) {
                horse[j] = j + 1;
                printf("\n%*d %*d   -   -   -",3,round,3,horse[j]);
                continue;
            }
            else {
                r = rnd(1,6);
                pos_after = pos_before[j] + r;
            }

            if (pos_after > n) {
                printf("\n%*d %*d %*d %*d %*d *",3,round,3,horse[j],3,pos_before[j],3,r,3,pos_after);
                winner[win] = horse[j];
                win++;
                horse[j] = -1;
                end++;
            }
            else if (track[pos_after-1] == 1 && track[pos_after] == 0) {
                pos_after++;
                printf("\n%*d %*d %*d %*d %*d N",3,round,3,horse[j],3,pos_before[j],3,r,3,pos_after);
                horse[j] = -2;
            }
            else if (track[pos_after-1] == 1 && track[pos_after] != 0) {
                printf("\n%*d %*d %*d %*d %*d F",3,round,3,horse[j],3,pos_before[j],3,r,3,pos_after);
                horse[j] = -3;
                end++;
            }
            else
                printf("\n%*d %*d %*d %*d %*d",3,round,3,horse[j],3,pos_before[j],3,r,3,pos_after);

            pos_before[j] = pos_after;
        }
        round++;
    }

    printf("\nORDER:");
    for (int i=0;i < win;i++)
        printf(" %d",winner[i]);

    return 0;
}