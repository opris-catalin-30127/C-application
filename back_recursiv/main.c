#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 5
int linie[]={2,1,-1,-2,-2,-1,1,2,2};
int col[]={1,2,2,1,-1,-2,-2,-1,1};

int FI(int x,int y)
{
    if(x<0||y<0||x>=NMAX||y>=NMAX)
        return 0;
    return 1;

}


void back_recursiv(int vizitat[NMAX][NMAX],int x,int y,int pos)
{
    vizitat[x][y]=pos;
    int i,j;
    if(pos>=NMAX*NMAX)
    {
        for(i=0;i<NMAX;i++)
        {
            for(j=0;j<NMAX;j++)
                if(vizitat[i][j]==1)
            {
                printf("%d ",1);


            }else if(vizitat[i][j]==2)
            {
                 printf("%c ",'*');
            }else if(vizitat[i][j]>2)
               {

                printf("%d ",0);
               }
           printf("\n");
        }

        vizitat[x][y]=0;
          printf("\n");
        return ;
    }

    int k;
    for(k=0;k<8;k++)
    {
        int new_x=x+linie[k];
        int new_y=y+col[k];
        if(FI(new_x,new_y)&& !vizitat[new_x][new_y])
           back_recursiv(vizitat,new_x,new_y,pos+1);
    }
    vizitat[x][y]=0;
}
int main()
{


    int vizitat[NMAX][NMAX];
    memset(vizitat,0,sizeof(vizitat));
     back_recursiv(vizitat,0,0,1);
    return 0;
}
