#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char nume[100],data_prim[100],data_exp[100];
    float pret;
    int cantitate;
} Medicament;
typedef struct med
{
    Medicament info;
    struct med *st,*dr;
} NOD;
Medicament initMed(char* buf)
{
    int i=0;
    char sep[]=",";
    char *result = strtok(buf,sep);
    Medicament m;
    while(result != NULL) // se tratează fiecare componentă
    {
        // pentru o instanță, prima componentă e
        switch(i)
        {
        case 0:
        {
            strcpy(m.nume,result);
            break;
        }
        case 1:
        {
            m.pret=atof(result); // conversie sir caractere in număr
            break;
        }
        case 2:
        {
            m.cantitate=atoi(result);
            break;
        }
        case 3:
        {
            strcpy(m.data_prim,result);
            break;
        }
        case 4:
        {
            strcpy(m.data_exp,result);
            break;
        }
        }
        i++;
        result=strtok(NULL,sep);
    }
    return m;
}

NOD *inserareMed(NOD* rad,Medicament m)
{
    if(rad)
    {
        int fan=strcmp(rad->info.nume,m.nume);
        if(fan>0)
        {
            rad->st=inserareMed(rad->st,m);
        }
        else
        {
            rad->dr=inserareMed(rad->dr,m);
        }
        return rad;
    }
    else
    {
        NOD* nou = (NOD*)malloc(sizeof(NOD));
        nou->info=m;
        nou->dr=nou->st=NULL;
        return nou;
    }
}
void afisare(Medicament m)
{
    printf("Nume = %s Pret = %.2lf Cantitate = %d Data intarii %s Data expirarii %s", m.nume, m.pret, m.cantitate,m.data_prim,m.data_exp);
}
void inordine(NOD *rad)
{
    if(rad)
    {
        inordine(rad->st);
        afisare(rad->info);
        inordine(rad->dr);
    }
}
void inordinesalvat(NOD *rad,FILE* f)
{
    if(rad)
    {
        inordinesalvat(rad->st,f);
        fprintf(f,"%s,%.2lf,%d,%s,%s", rad->info.nume, rad->info.pret, rad->info.cantitate,rad->info.data_prim,rad->info.data_exp);
        inordinesalvat(rad->dr,f);
    }
}
void schimbaPret(NOD* rad,float prec,char m[100])
{
    if(rad)
    {
        int fan=strcmp(rad->info.nume,m);
        if(fan==0)
        {
            rad->info.pret=prec;
            return rad;
        }
        else if(fan>0)
        {
            schimbaPret(rad->st,prec,m);
        }
        else
        {
            schimbaPret(rad->dr,prec,m);
        }
    }
}
NOD *stergere_nod(NOD *rad,char key[100])
{
    NOD *p,*tata_p;/* p este nodul de sters, iar tata_p este tatal lui */
    NOD *nod_inlocuire,*tata_nod_inlocuire;/*nodul care il va inlocui pe p si tatal sau */
    int directie; /*stg=1;dr=2*/
    if(rad==0)
        return 0; /*arborele este vid */
    p=rad;
    tata_p=0;
    /* cautare nod cu cheia key */
    while(p!=0 && strcmp(p->info.nume,key))
    {
        if (strcmp(p->info.nume,key)>0)      /*cautare in stanga */
        {
            tata_p=p;
            p=p->st;
            directie=1;
        }
        else      /*cautare in dreapta */
        {
            tata_p=p;
            p=p->dr;
            directie=2;
        }
    }
    if(p==0)
    {
        printf("NU EXISTA MEDICAMENTUL: %s\n",key);
        return rad;
    }
    /* s-a gasit nodul p de cheie key */
    if(p->st==0)
        nod_inlocuire=p->dr; /* nodul de sters p nu are fiu sting */
    else if(p->dr==0)
        nod_inlocuire=p->st;	/*nodul de sters p  nu are fiu drept*/
    else    /* nodul de sters p are fiu stang si fiu drept */
    {
        tata_nod_inlocuire=p;
        nod_inlocuire=p->dr;        /* se cauta in subarborele drept*/
        while(nod_inlocuire->st!=0)
        {
            tata_nod_inlocuire=nod_inlocuire;
            nod_inlocuire=nod_inlocuire->st;
        }
        if(tata_nod_inlocuire!=p)
        {
            tata_nod_inlocuire->st=nod_inlocuire->dr;
            nod_inlocuire->dr=p->dr;
        }
        nod_inlocuire->st=p->st;
    }
    free(p);
    printf("Medicamentul %s a fost sters!\n",key);
    if(tata_p==0)
        return nod_inlocuire; /*s-a sters chiar radacina initiala */
    else
    {
        if (directie==1)
            tata_p->st=nod_inlocuire;
        else
            tata_p->dr=nod_inlocuire;
        return rad;
    }
}
NOD *r=NULL;
void initArboreExp(NOD *rad,char data_expirare[10])
{
    if(rad)
    {
        initArboreExp(rad->st,data_expirare);
        if(strcmp(rad->info.data_exp,data_expirare)<0)
        {
            r = inserareMed(r,rad->info);
        }
        initArboreExp(rad->dr,data_expirare);
    }
}

int main()
{
    int o;
    char buf[100];
    FILE* f = fopen("medicament.txt","r");
    NOD* rad = NULL;
    while(!feof(f))
    {
        buf[0]='\0';
        fgets(buf, 100, f);
        if(strlen(buf)>0) // validare date de intrare
            rad = inserareMed(rad,initMed(buf));
    }
    fclose(f);

    while(1)
    {
        printf("1 Afisare 2 Schimba Pret 3 Sterge Nod 4 SubArbore 5 Terminare proces: ");
        scanf("%d",&o);
        switch(o)
        {
        case 1:
        {
            inordine(rad);
            break;
        }
        case 2:
        {
            float pret_nou;
            char m[100];
            printf("Medicament: ");
            scanf("%s",&m);
            printf("Pret: ");
            scanf("%f",&pret_nou);
            schimbaPret(rad,pret_nou,m);
            break;
        }
        case 3:
        {
            char med[100];
            printf("Medicament: ");
            scanf("%s",&med);
            rad = stergere_nod(rad,med);
            fflush(stdin);
            break;
        }
        case 4:
        {
            char d[100];
            printf("Data expirarii(yyyy,mm,dd): ");
            scanf("%s",&d);
            initArboreExp(rad,d);
            inordine(r);
            break;
        }
        case 5:
        {
            FILE* fo = fopen("medicament.txt","w");
            inordinesalvat(rad,fo);
            printf("La revedere!");
            return 0;
        }
        default:
        {
            printf("Optiune gresita!\n");
            break;
        }
        }
    }
    return 0;
}
