
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "AVL.h"

int main()
{
    BBSTree t=NULL;
    RcdType y;
    int x=0,ycount=0,zcount=0;
    int flag;
    do
    {

        printf("-----------------\n");
        printf("    1:search\n");
        printf("    2:destroy\n");
        printf("    3:insert\n");
        printf("    4:delete\n");
        printf("    5:exit\n");
        printf("-----------------\n");
        scanf("%d",&x);
        ycount=0;
        switch (x)
        {
            case 1:
                scanf("%d",&y.key);
                printf("\n");
                if (SearchAVL(t,y.key)!=NULL) printf("Search successfully.\n");
                else printf("Can't search.It doesn't exist.\n");
                break;

            case 2:
                DestroyAVL(t);
                ycount=zcount=0;
                printf("\n");
                break;
            case 3:
                scanf("%d",&(y.key));
                printf("\n");
                if (InsertAVL(t,y,flag)==TRUE)
                {
                    zcount++;
                    printf("Insert successfully.\n");
                }
                break;
            case 4:
                scanf("%d",&(y.key));
                printf("\n");
                if (SearchAVL(t,y.key)==NULL) printf("Can't delete.It doesn't exist.\n");
                else
                {
                    DeleteAVL(t,y,flag);
                    zcount--;
                    printf("Delete successfully.\n");
                }
                break;
            case 5:
                exit(0);
                break;
            default:printf("\nNumber ERROR.Please input a corrent number.\n");
        }
        if (t!=NULL)
        {
            printf("InOrderTraverse:");
            PrintAVL(t);
            printf("\n");
            Print(t);
        }
        else printf("This is an empty tree.\n");
        Leaf(t,ycount);
        printf("Depth:%d  Node number:%d  Leaf number:%d\n\n",Depth(t),zcount,ycount);
    } while (1>0);
    return 0;
}

