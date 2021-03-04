#include <stdio.h>
#include <stdlib.h>

typedef struct locomotiva
{
    int id;
    char tip[21];
    float gr;
    struct locomotiva *urm;
}LOCOMOTIVA;
void intrare(LOCOMOTIVA **prim, LOCOMOTIVA **ultim);
void iesire(LOCOMOTIVA **prim, LOCOMOTIVA **ultim);
void afisare(LOCOMOTIVA *prim);
int main()
{
    int o;
    LOCOMOTIVA *prim=0,*ultim=0;
    while(1)
    {
        printf("1 intrare, 2 iesire, 3 afisare, 4 terminare ");
        scanf("%d",&o);
        switch(o)
        {
            case 1:{intrare(&prim,&ultim);break;}
            case 2:{iesire(&prim,&ultim);break;}
            case 3:{
                if(prim==0)printf("Depoul este gol!\n");
                    else afisare(prim);break;}
            case 4:{printf("La revedere !");return 0;}
                default:{printf("Optiune gresita!\n");break;}
        }
    }
    return 0;
}
void intrare(LOCOMOTIVA **prim, LOCOMOTIVA **ultim)
{
    LOCOMOTIVA *p = (LOCOMOTIVA *)malloc(sizeof(LOCOMOTIVA));
    printf("ID = ");scanf("%d",&p->id);
    printf("Tip = ");scanf("%s",p->tip);
    printf("Greutate = ");scanf("%f",&p->gr);
    p->urm=0;
    if(*prim==0){
        *prim=p;
        *ultim=p;
   } else
    {
        (*ultim)->urm = p;
        (*ultim)=p;
    }
}
void iesire(LOCOMOTIVA **prim, LOCOMOTIVA **ultim)
{
    LOCOMOTIVA *p;
    if(*prim!=NULL)
    {
        p=*prim;
        printf("Locomotiva care iese are detaliile: Id = %d Tip = %s Greutate = %f\n",p->id,p->tip,p->gr);
       *prim = (*prim)->urm;
    free(p);
    if(*prim == NULL)*ultim=NULL;
    }
    else printf("Depoul este gol!\n");
}
void afisare(LOCOMOTIVA *prim)
{
    LOCOMOTIVA *p=prim;
    int i=0;
    while(p)
    {
        i++;
        printf("Locomotiva %d are urm detalii: Id = %d Tip = %s Greutate = %f\n",i,p->id,p->tip,p->gr);
        p=p->urm;
    }
}
