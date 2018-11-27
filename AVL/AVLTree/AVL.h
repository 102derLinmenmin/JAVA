#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#define LH +1
#define EH 0
#define RH -1
#define TRUE 1
#define FALSE 0

typedef int KeyType;
typedef int Status;

typedef struct
{
    KeyType key;
}RcdType;

typedef struct BSTNode
{
    RcdType data;
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;

typedef struct BBSTNode
{
    RcdType data;
    int bf;
    struct BBSTNode *lchild, *rchild;
}*BBSTree;

void DestroyAVL(BBSTree &T);

int Depth(BBSTree T);

void Leaf(BBSTree T,int &k);

void PrintAVL(BBSTree T);

void Print(BBSTree T);

BBSTree SearchAVL(BBSTree T,KeyType k);



Status InsertAVL(BBSTree &T,RcdType e,Status &taller);

Status DeleteAVL(BBSTree &T,RcdType e,Status &shorter);





#endif // AVL_H_INCLUDED
