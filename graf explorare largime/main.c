/*2. Se da un graf orientat cu n noduri, si m muchii, fara costuri citit prin
vectorul muchiilor din fisierul "GRAF.TXT".Fisierul contine pe prima linie numarul
de noduri urmat de numarul de muchii,iar pe fiecare din liniile urmatoare va
contine o pereche de numere ce reprezinta un arc prin varful de unde pleaca arcul
si varful unde ajunge arcul. Trebuie sa folosim algoritmul de explorare
in largime pt a afisa pe nivele arborele de acoperire avand radacina nodul s
(la iesirea standard). Nodul s se citeste de la intrarea standard.Datele de iesire vor fi
afisate pe ecran . In Programul principal vom citi datele de intrare si apoi va apela modulul
traversarii in largime.La parcurgerea in largime vom observa de fiecare data nivelul pornind de
la radacina s , si vom afisa in acest caz un mesaj corespunzator pentru a retine nivelul. */
#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

int adiacenta[NMAX][NMAX];
typedef struct vector
{
    int a,b;
}Vector;

void explorare_largime(int n, int s)
{
    int i,w,coada[NMAX],g,j,c,d;
    int vizitat[NMAX],prim,ultim;
    for(i=1; i<=n; i++)
        vizitat[i]=0;
    vizitat[s]=1;
    prim=1;
    ultim=1;// primul si ultimul sunt 1
    coada[ultim]=s;
    while (prim<=ultim)
    {
        w=coada[prim];
        for (i=1;i<=n;i++)
        {
            if(adiacenta[w][i]==1 && vizitat[i]==0)
            {
                ultim++;
                coada[ultim]=i;
                vizitat[i]=1;
            }
        }
        prim++;
    }
    i=1;
    printf("Nivelul %d : ",i-1);
    printf("%d ",coada[i]);
    d=1;
    vizitat[coada[i]]=0;
    while(d<=n)
    {
        c=coada[i];
        printf("\n");
        printf("Nivelul %d : ",i);
        for (j=1;j<=n;j++)
           if(adiacenta[c][j]==1)
             {
               if(vizitat[j]==1)
               {
                 printf("%d ",j);
                 vizitat[j]=0;
               }
               d++;
             }
        i++;
    }
}

int main()
{
    Vector v[NMAX];
    int n,m,i,s,y,j,vi,vf;
    FILE *f;
    f=fopen("graf.txt","r");
        if(f == NULL)
    {
        printf("NU s-a deschis fisierul graf.txt...");
        exit(1);
    }
    fscanf(f,"%d",&n);
    fscanf(f,"%d",&m);
    for (i=1;i<=n;i++)
      for(j=1;j<=n;j++)
        adiacenta[i][j]=0;
    for (i=1;i<=m;i++)
    {
        fscanf(f,"%d %d",&vi,&vf);
        v[i].a=vi;
        v[i].b=vf;
        adiacenta[vi][vf]=1;
    }
    fclose(f);
    do
    {

        printf("Nodul radacina s:");
    scanf("%d",&s);
    }
    while(s<=0 || s>n);
    explorare_largime(n,s);
    return 0;
}
