/* Biletul 7
   Fiind dat un multigraf, trebuie determinate ciclurile Euleriene, daca acesta este Eulerian.
   Date de intrare: numarul nodurilor, respectiv muchiilor apoi pe urmatoarele M linii se va afisa cate o muchie.
   Date de iesire:vom afisa secvente de M numere care vor fi muchii ale ciclului eulerian sau -1 in cazul in care G nu este eulerian.
  vom verifica daca se poate forma un ciclu eulerian , daca nu se poate afisam -1, iar daca da atunci
   vom folosi parcurgearea in adancime (DFS) nerecursiv.

 */
#include <stdio.h>
#include <stdlib.h>
#define nmax 100*1001
#define mmax 1000*1001

int s[mmax],p;//s[mmax]-stiva in care vom face parcurgerea pentru noduri (un nod poate sa apara de mai multe ori)
FILE *g;

typedef struct lista
{
    int n,p; //nodul si pozitia
    int pl; //pozitia din lista a arcului opus
    char v; //daca a fost vizitat sau nu
}  Lista;//lista
Lista l[mmax];
typedef struct nod
{
    int p,g; //pozitia ultimului fiu din lista, si gradul sau
    int ul; //pozitia ultimului fiu rezolvat
} Nod; //nodurile
int nr,mr; //numarul de noduri/muchii
Nod n[nmax];
void dfs(int x)
{
    s[p=1]=x;
    n[s[p]].ul=n[s[p]].p; //initializam stiva
    while(p) //cat timp avem elemente in stilva
    {
        for( ; n[s[p]].ul; n[s[p]].ul=l[n[s[p]].ul].p) //parcurgem copii ramasi neparcursi
            if(!l[n[s[p]].ul].v) //daca muchia nu a mai fost parcursa
            {
                l[l[n[s[p]].ul].pl].v=l[n[s[p]].ul].v=1; //marcam muchia ca vizitata (pe ambele sensuri)
                ++p;
                s[p]=l[n[s[p-1]].ul].n; //nodul urmator ce trebuie vizitat
                if(!n[s[p]].ul)
                    n[s[p]].ul=n[s[p]].p; //daca nodul se viziteaza pt prima data, ii pregatil ultimul fiu al sau nevizitat de el
                break; //oprim pentru moment nodul curent
            }
        if(!n[s[p]].ul)
        {
            if(p>1)
                fprintf(g,"%d ",s[p]);    //inseamna k trebuie sa revenim o pozitie din stiva, deci afisem nodul
            p--;
        }
    }
}

//adaugam muchie intre x si y, la pozitiile m, si m+1
void add(int m, int x, int y)
{
    l[m].n=y;
    l[m].p=n[x].p;
    n[x].p=m;
    l[m].pl=m+1; //adaugam arcul (x,y)
    l[m+1].n=x;
    l[m+1].p=n[y].p;
    n[y].p=m+1;
    l[m+1].pl=m; //adaugam arcul (y,x)
    n[x].g++;
    n[y].g++; //crestem gradele
}

void citire()
{
    FILE *f=fopen("intrare.txt","r");
    if(!f)
        exit(1);
    int i,x,y;
    fscanf(f,"%d %d",&nr,&mr);
    for(i=1; i<=mr; i++)
    {
        fscanf(f,"%d %d",&x,&y); //citim muchia
        add(2*i-1,x,y); //adaugam muchia dintre x si y
    }
}

void verificare()
{
    int i;
    for(i=1; i<=nr; i++)
        if(n[i].g%2) //are grad impar
            break; //oprim
    if(i<=nr)
        printf("-1"); //inseamna ca nu poate forma un ciclu eulerian
    else
        dfs(1); //inseamna ca se poate forma, deci facem parcurgerea dfs
}




int main()
{
    g=fopen("iesire.txt","w");
    citire();
    verificare();
    return 0;
}

