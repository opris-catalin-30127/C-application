#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  nod
{
    char ch;
    int i;
    struct nod *stang, *drept;
} Nod;

typedef struct tip_nod
{
    int cod;
    int nr_fii;
    struct tip_nod *adr_fii [30];
} TIP_NOD;

typedef struct nod_lista
{
    TIP_NOD *ptr;
    struct nod_lista *urm;
} NOD_LISTA;

TIP_NOD *radacina;
NOD_LISTA *prim, *ultim;

void preordine(Nod *p,int nivel)
{
    int i;
    if(p!=0)
    {
        for(i=0; i<=nivel; i++)
            printf(" ");
        printf("%c\n",p->ch);
        preordine(p->stang,nivel+1);
        preordine(p->drept,nivel+1);

    }


}


void inordine(Nod *p,int nivel)
{
    int i;
    if(p!=0)
    {
        inordine(p->stang,nivel+1);
        for(i=0; i<=nivel; i++)
            printf(" ");
        printf("%c\n",p->ch);
        inordine(p->drept,nivel+1);
    }
}

void postordine(Nod *p,int nivel)
{
    int i;
    if(p!=0)
    {
        postordine(p->stang,nivel+1);
        postordine(p->drept,nivel+1);
        for(i=0; i<=nivel; i++)
            printf(" ");
        printf("%c\n",p->ch);


    }


}

Nod *con()
{

    Nod * p=NULL;
    char c;
    fflush(stdin);
    printf("c=");
    scanf("%c",&c);
    if(c!='*')
    {
        p=(Nod*)malloc(sizeof(Nod));
        p->ch=c;
        p->stang=con();
        p->drept=con();
    }
    return p;
}

Nod* construire_echilibrat(int nr_noduri)
{
    Nod *p=NULL;
    int n_stg,n_dr;
    if(nr_noduri!=0)
    {
        n_stg=nr_noduri/2;
        n_dr=nr_noduri-n_stg-1;
        p=(Nod*)malloc(sizeof(Nod));
        fflush(stdin);
        printf("\nIntroduceti informatia din nod in preordine ");
        scanf("%c",&(p->ch));
        p->stang=construire_echilibrat(n_stg);
        p->drept=construire_echilibrat(n_dr);
    }
    return p;

}

TIP_NOD *construire_oarecare();
int traversare(TIP_NOD *rad);
int push(TIP_NOD *p);
TIP_NOD *pop();
TIP_NOD *elimin();
int adaug(TIP_NOD *p);

int main()
{
    Nod *capB=NULL;
    Nod *capBO=NULL;
    radacina=NULL;
    int optiune;

    while(1)
    {
        printf("Optiuni: 1 arbore binar 2 orbore binar total echilibrat 3 arbore oarecare 4 Iesire\n");
        scanf("%d",&optiune);

        switch(optiune)
        {
        case 1:
        {
            capB=con();
            preordine(capB,0);
            break;
        }
        case 2:
        {
            printf("Introduce nr de noduri: ");
            int nr_noduri;
            scanf("%d",&nr_noduri);
            capBO=construire_echilibrat(nr_noduri);
            preordine(capBO,0);
            break;
        }
        case 3:
        {   //adaug(radacina);
            radacina=construire_oarecare();
            traversare(radacina);
            break;
        }
        case 4:
        {
            printf("La revedere!!!\n");
            return 0;
            break;
        }
        default:
        {
            printf("Optiunea este incorecta!!\n");
            break;
        }
        }
    }





    return 0;
}


TIP_NOD *construire_oarecare()
{

    TIP_NOD *p;
    int n;
    int i;
    printf("\nIntroduceti nr. total de noduri");
    scanf("%d", &n);
    prim = NULL;
    while(n > 0)
    {
        p = (TIP_NOD *)malloc(sizeof(TIP_NOD));
        if(p == NULL)
        {
            printf("\nNU s-a alocat memorie");
            return p;
        }
        fflush(stdin);
        printf("\nCodul nodului= ");
        scanf("%d", &p->cod);
        fflush(stdin);
        printf("\nNumarul de fii= ");
        scanf("%d", &p->nr_fii);
        i = p->nr_fii;
        while(i > 0)
        {

            if((p->adr_fii[i] = pop()) == 0)
            {
                printf("\nEroare de introducere");
                return NULL;
            }
            i--;
        }
        if(push(p) == 0)
        {
            printf("\nEroare la adaugare pe stiva");
            return NULL;
        }
        n--;
    }
    return pop();
}

int traversare(TIP_NOD *rad)
{

    TIP_NOD *p;
    int i;
    prim = ultim = NULL;
    if(adaug(rad) == 0)
        return 0;
    do
    {
        p = elimin();
        if(p != NULL)
        {
            fflush(stdin);
            printf("Codul nodului= %d\n", p->cod);
            for(i = 1; i <= p->nr_fii; i++)
            {
                if(adaug(p->adr_fii[i]) == 0)
                    return 0;
            }
        }
    }
    while( p!= NULL);
    return 1;
}

int push(TIP_NOD *p) // returnează 1 succes, 0 insucces
{
    // pune adresa unui nod al arborelui pe stivă
    NOD_LISTA *q = (NOD_LISTA *)malloc(sizeof(NOD_LISTA));
    if(q == NULL)
    {
        printf("\nEroare la alocare spatiu pentru un nod al stivei! \n");
        return 0;
    }
    else
    {
        q->ptr = p;
        q->urm = prim;
        prim = q;
        return 1;
    }
}

TIP_NOD *pop()
{

    TIP_NOD *p;
    NOD_LISTA *q;
    if(prim == NULL)
    {

        return 0;
    }
    else
    {
        q = prim;
        prim = prim->urm;
        if(prim == 0)
            ultim = 0;
        p = q->ptr;
        free(q);
        return p;
    }


}

int adaug(TIP_NOD *p)
{

    NOD_LISTA *q = (NOD_LISTA *)malloc(sizeof(NOD_LISTA));
    if(q == NULL)
    {
        printf("\nEroare la alocare spatiu pentru un nod al cozii! \n");
        return 0;
    }
    q->ptr = p;
    q->urm = 0;
    if(prim == 0)
    {
        prim = q;
        ultim = q;
    }
    else
    {
        ultim->urm = q;
        ultim = q;
    }
    return 1;
}

TIP_NOD *elimin()
{

    TIP_NOD *p;
    NOD_LISTA *q;
    if(prim == 0)
        return 0;
    else
    {
        q = prim;
        prim = prim->urm;
        p = q->ptr;
        free(q);
        return p;
    }
}

