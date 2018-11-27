
#include "AVL.h"

#include <stdio.h>
#include <stdlib.h>


void R_Rotate(BBSTree &p);

void L_Rotate(BBSTree &p);


void LeftBalance(BBSTree &T);

void RightBalance(BBSTree &T);

void DestroyAVL(BBSTree &T)
{
    if (T!=NULL)
    {
        DestroyAVL(T->lchild);
        DestroyAVL(T->rchild);
        free(T);
        T=NULL;
    }
}

int Depth(BBSTree T)
{
    int ldepth,rdepth;
    if (T==NULL) return 0;
    else
    {
        ldepth=Depth(T->lchild);
        rdepth=Depth(T->rchild);
        return 1+(ldepth>rdepth?ldepth:rdepth);
    }
}

void Leaf(BBSTree T,int &k)
{
    if (T!=NULL)
    {
        if (T->lchild==NULL&&T->rchild==NULL) k++;
        Leaf(T->lchild,k);
        Leaf(T->rchild,k);
    }
}

void PrintAVL(BBSTree T)
{
    if (T)
    {
        PrintAVL(T->lchild);
        printf("%d ",T->data.key);
        PrintAVL(T->rchild);
    }
}

void Print(BBSTree T)
{
    if (T)
    {
        printf("%d[",T->data.key);
        if (T->lchild) printf("%d,",T->lchild->data.key);
        else printf(" ,");
        if (T->rchild) printf("%d]\n",T->rchild->data.key);
        else printf(" ]\n");
        Print(T->lchild);
        Print(T->rchild);
    }
}

BBSTree SearchAVL(BBSTree T,KeyType k)
{
    if (T==NULL) return NULL;
    if (T->data.key==k) return T;
    if (T->data.key>k) return SearchAVL(T->lchild,k);
    return SearchAVL(T->rchild,k);
}

void R_Rotate(BBSTree &p)
{
    BBSTree lc=p->lchild;
    p->lchild=lc->rchild;
    lc->rchild=p;
    p=lc;
}

void L_Rotate(BBSTree &p)
{
    BBSTree rc=p->rchild;
    p->rchild=rc->lchild;
    rc->lchild=p;
    p=rc;
}

void LeftBalance(BBSTree &T)
{
    BBSTree lc,rd;
    lc=T->lchild;
    switch (lc->bf)
    {
        case LH:
            T->bf=lc->bf=EH;
            R_Rotate(T);
            break;
        case EH:
            T->bf=LH;
            lc->bf=RH;
            R_Rotate(T);
            break;
        case RH:
            rd=lc->rchild;
            switch (rd->bf)
        {
            case LH:
                T->bf=RH;
                lc->bf=EH;
                break;
            case EH:
                T->bf=lc->bf=EH;
                break;
            case RH:
                T->bf=EH;
                lc->bf=LH;
                break;
        }
            rd->bf=EH;
            L_Rotate(T->lchild);
            R_Rotate(T);
            break;
    }
}

void RightBalance(BBSTree &T)
{
    BBSTree rc,ld;
    rc=T->rchild;
    switch (rc->bf)
    {
        case LH:
            ld=rc->lchild;
            switch (ld->bf)
        {
            case LH:
                T->bf=EH;
                rc->bf=RH;
                break;
            case EH:
                T->bf=EH;
                rc->bf=EH;
                break;
            case RH:
                T->bf=LH;
                rc->bf=EH;
                break;
        }
            ld->bf=EH;
            R_Rotate(T->rchild);
            L_Rotate(T);
            break;
        case EH:
            T->bf=RH;
            rc->bf=LH;
            L_Rotate(T);
            break;
        case RH:
            T->bf=rc->bf=EH;
            L_Rotate(T);
            break;
    }
}

Status InsertAVL(BBSTree &T,RcdType e,Status &taller)
{
    if (T==NULL)
    {
        T=(BBSTree)malloc(sizeof(BBSTNode));
        T->data=e;
        T->bf=EH;
        T->lchild=T->rchild=NULL;
        taller=TRUE;
    }
    else
    {
        if (e.key==T->data.key)
        {
            taller=FALSE;
            printf("Can't insert.It has existed.\n");
            return FALSE;
        }
        if (e.key<T->data.key)
        {
            if (InsertAVL(T->lchild,e,taller)==FALSE) return FALSE;
            if (taller==TRUE)
            {
                switch (T->bf)
                {
                    case LH:
                        LeftBalance(T);
                        taller=FALSE;
                        break;
                    case EH:
                        T->bf=LH;
                        taller=TRUE;
                        break;
                    case RH:
                        T->bf=EH;
                        taller=FALSE;
                        break;
                }
            }
        }
        if (e.key>T->data.key)
        {
            if (InsertAVL(T->rchild,e,taller)==FALSE) return FALSE;
            if (taller==TRUE)
            {
                switch (T->bf)
                {
                    case LH:
                        T->bf=EH;
                        taller=FALSE;
                        break;
                    case EH:
                        T->bf=RH;
                        taller=TRUE;
                        break;
                    case RH:
                        RightBalance(T);
                        taller=FALSE;
                        break;
                }
            }
        }
    }
    return TRUE;
}

Status DeleteAVL(BBSTree &T,RcdType e,Status &shorter)
{
    BBSTree P;
    if (T==NULL) return FALSE;
    else
    {
        if (e.key==T->data.key)
        {
            if (T->lchild==NULL&&T->rchild==NULL)
            {
                free(T);
                T=NULL;
                shorter=TRUE;
            }
            else
                if (T->lchild==NULL)
                {
                    T=T->rchild;
                    shorter=TRUE;
                }
                else
                    if (T->rchild==NULL)
                    {
                        T=T->lchild;
                        shorter=TRUE;
                    }
                    else
                    {
                        P=T->lchild;
                        while (P->rchild) P=P->rchild;
                        T->data=P->data;
                        DeleteAVL(T->lchild,T->data,shorter);
                    }
        }
        else
            if (e.key<T->data.key)
            {
                if (DeleteAVL(T->lchild,e,shorter)==FALSE)
                    return FALSE;
                else
                {
                    switch (T->bf)
                    {
                        case LH:
                            T->bf=EH;
                            shorter=TRUE;
                            break;
                        case EH:
                            T->bf=RH;
                            shorter=FALSE;
                            break;
                        case RH:
                            if (T->lchild->bf==EH) shorter=FALSE;
                            else shorter=TRUE;
                            RightBalance (T);
                            break;
                    }
                }
            }
            else
                if (e.key>T->data.key)
                {
                    if (DeleteAVL(T->rchild,e,shorter)==FALSE) return FALSE;
                    else
                    {
                        switch (T->bf)
                        {
                            case LH:
                                if (T->lchild->bf==EH) shorter=FALSE;
                                else shorter=TRUE;
                                LeftBalance(T);
                                break;
                            case EH:
                                T->bf=LH;
                                shorter=FALSE;
                                break;
                            case RH:
                                T->bf=EH;
                                shorter=TRUE;
                                break;
                        }
                    }
                }
        return TRUE;
    }
}


