
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define true
#define false 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#define OVERFLOW -2
#define STACK_INIT_SIZE 100 // �洢�ռ��ʼ������
#define STACKINCREMENT 10 // �洢�ռ��������
#define MAXQsize 100 //���пռ��ʼ��������
#define LH +1 //��߸�
#define RH -1 //�ұ߸�
#define EH 0 //�ȸ�

typedef int ElemType;
typedef int Status;
typedef int SElemType;
typedef int STACK_TYPE;

bool taller;
int flag=0;//���ҵı��
int l=0; //�����������
int r=0; //�����������
int jiedian=0; //���Ľ����

typedef struct BBSTNode
{
  ElemType data;
  int bf; //ƽ������
  int out;  //��������ķǵݹ��㷨�ı�ǣ��Ƿ���ʹ���
  struct BBSTNode *lchild,*rchild;//���Һ���ָ��
} BBSTNode,*BBSTree;  //���Ľṹ


struct SqStack //˳��ջ
{
  BBSTree *base; // ��ջ����֮ǰ������֮��base��ֵΪNULL
  BBSTree *top; // ջ��ָ��
  int stacksize; // ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
};


struct Queue // ˳�����
{
  BBSTree base[MAXQsize];
  int Front; // ��ͷָ��
  int rear; // ��βָ��ָ��
};

Status InitStack(SqStack &S)  //��ʼ��ջ
{
	// ����һ����ջS����ջԤ�����СΪSTACK_INIT_SIZE
	S.base = (BBSTree*)malloc(STACK_INIT_SIZE * sizeof(BBSTree));
	if (!S.base) return ERROR;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status StackEmpty(SqStack S) //ջ�п�
{
	//�ж�ջ�Ƿ�Ϊ���Ƿ���1�����򷵻�0��
	if (S.top == S.base)return OK;
	else return ERROR;
}

Status Push(SqStack &S, BBSTree e)//��ջ
{
	// ��ջS�в���Ԫ��eΪ�µ�ջ��Ԫ��
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S, BBSTree &e)//��ջ
{
	// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	if (S.top == S.base) return ERROR;
	e = *(--S.top);
	return OK;
}

BBSTree Getop(SqStack &S)//����ջ��Ԫ��
{
	// ��ջ���գ��򷵻�S��ջ��Ԫ�أ����򷵻�NULL��
	if (S.top == S.base) return NULL;
	return *(S.top - 1);
}

Status InitQueue(Queue &Q)  //��ʼ������
{
	Q.Front = 0;
	Q.rear = 0;
	return OK;
}

Status QueueEmpty(Queue Q) //	�п�Ŀ����У��������ǻ��
{
	//�ж϶����Ƿ�Ϊ���Ƿ���1�����򷵻�0��
	if (Q.Front == Q.rear)return OK;
	else return ERROR;
}

Status Enqueue(Queue &Q, BBSTree T) //Ԫ�����
{
	//��������û��������T���

	if (Q.rear == MAXQsize)return ERROR;


	if (T)Q.base[Q.rear++] = T;


	return OK;
}

Status Delqueue(Queue &Q)
{
	//�������Q��Ϊ�գ��������ͷ���ݣ�����������ӣ���ͷ���ӡ�
	if (Q.Front == Q.rear)return ERROR;
	else
	{
		printf("%d ", Q.base[Q.Front]->data);
		Enqueue(Q, Q.base[Q.Front]->lchild);//���������
		Enqueue(Q, Q.base[Q.Front]->rchild);//���������
		Q.Front++;
	}
	return OK;
}


 int IsBalance(BBSTree T) {    //�ж�T���Ƿ���ƽ�����������Ϊ1,��Ϊ0
	int BBSTDepth(BBSTree T);
	if(T == NULL) return 1;
	else {
		int bf;
		bf = BBSTDepth(T->lchild)- BBSTDepth(T->rchild);
		if(bf < -1|| bf > 1) return 0;
		else {
			if(IsBalance(T->lchild) && IsBalance(T->rchild)) return 1;
			else return 0;
		}
	 }
 }

void DestoryBBST(BBSTree T) {             //����һ����
  if(T != NULL) {
    DestoryBBST(T->lchild);
    DestoryBBST(T->rchild);
	free(T);
  }
}

int BBSTDepth(BBSTree T) {               //����һ�����ĸ߶�
	if(T == NULL) return 0;
	else {
		int depthLeft, depthRight;
		depthLeft = BBSTDepth(T->lchild);
		depthRight = BBSTDepth(T->rchild);
		return 1+(depthLeft > depthRight ? depthLeft : depthRight);
	 }
}

int node=0;

Status NodeNum(BBSTree T)
{
	//������Ҷ�ӽ���������ﶨ����һ��ȫ�ֱ�����ֱ�Ӽ�¼Ҷ�ӽ����
	if (T)
	{
		if ((T->lchild == NULL) && (T->rchild == NULL))	node++;
		else
		{
			NodeNum(T->lchild);
			NodeNum(T->rchild);
		}
	}
	return OK;
}

BBSTree SearchBBST(BBSTree T, int key) {    //��������key��λ�ã����ڷ�����ָ�룬�����ڷ���NULL
	while(T != NULL) {
		if(T->data == key) return T;
		else if(T->data < key) T = T->rchild;
		else if(T->data > key) T = T->lchild;
	}
	return NULL;
}

void R_Rotate(BBSTree &p) {       //����LL��
	BBSTree lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}

void L_Rotate(BBSTree &p) {		//����RR��
	BBSTree rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

void LR_Rotate(BBSTree &p) {     //LR��
	L_Rotate(p->lchild);
	R_Rotate(p);
}

void RL_Rotate(BBSTree &p) {      //RL��
	R_Rotate(p->rchild);
	L_Rotate(p);
}

void LeftBalance(BBSTree &T) {		//ʵ�ֶ���TΪ����������ƽ�⴦��
	BBSTree lc, rd;
	lc = T->lchild;
	switch(lc->bf) {                //�����T��������ƽ������
		case LH:                   //LL�ͣ���������
			T->bf = lc->bf = EH;
			R_Rotate(T);
			break;
		case RH:                   //�²�������T�����ӵ��������ϣ�LR�ͣ�˫������
			rd = lc->rchild;
			switch(rd->bf) {
				case LH:
					T->bf = RH;
					lc->bf = EH;
					break;
				case EH:
					T->bf = lc->bf = EH;
					break;
				case RH:
					T->bf = EH;
					lc->bf = LH;
					break;
			}
			rd->bf = EH;
			LR_Rotate(T);
			break;
	}
}

void RightBalance(BBSTree &T) {  //ʵ�ֶ���TΪ��������ƽ�����
	BBSTree rc, ld;
	rc = T->rchild;
	switch(rc->bf) {
		case RH:
			T->bf = rc->bf = EH;
			L_Rotate(T);
			break;
		case LH:
			ld = rc->lchild;
			switch(ld->bf) {
				case RH:
					T->bf = LH;
					rc->bf = EH;
					break;
				case EH:
					T->bf = rc->bf = EH;
					break;
				case LH:
					T->bf = EH;
					rc->bf = RH;
					break;
			}
			ld->bf = EH;
			RL_Rotate(T);
			break;
	}
}

static BBSTree FindMin(BBSTree T)  //������С�Ľ��
{
	if (NULL == T)		//����
		return NULL;
	while (NULL != T->lchild)		//����ƽ���� T �йؼ�����С�Ľ��Ϊ�����֧�ϵ�Ҷ��
		T = T->lchild;
	return T;
}

static BBSTree FindMax(BBSTree T)   //�������Ľ��
{
	if (NULL == T)		//����
		return NULL;
	while (NULL != T->rchild)	//����ƽ���� T �йؼ������Ľ��Ϊ���ҷ�֧�ϵ�Ҷ��
		T = T->rchild;
	return T;
}

void onDelete_LeftBalance(BBSTree &T, int &shorter) {
	//ɾ�����ʱ����ƽ�����
	BBSTree right, left;
	if(T->bf == 1) {         //���1��p����������ߣ�ɾ������p->bf = 0�����䰫
		T->bf = 0;
		shorter = 1;
	} else if(T->bf == 0) {   //���2��p��㺬������������ɾ������p->bf = -1�����߲���
		T->bf = -1;
		shorter = 0;
	} else {
		//���3��p����������ߣ���������R0,R-1,R1�������
		right = T->rchild;
		if(right->bf == 0) {          //R0���
			L_Rotate(T);
			right->bf = 1;
			T->bf = -1;
			shorter = 0;
		}else if(right->bf == -1) {   //R-1���
			L_Rotate(T);
			T->bf = 0;
			right->bf = 0;
			shorter = 1;
		} else {                      //R1��� ,�ַ�T�����������������L0,L-1,L1�������
			left = right->lchild;
			right->lchild = left->rchild;
			left->rchild = right;
			T->rchild = left->lchild;
			left->lchild = T;
			if(left->bf == 0) {           //L0���
				T->bf = 0;
				right->bf = 0;
			} else if(left->bf == -1) {   //L-1���
				T->bf = 1;
				right->bf = 0;
			} else {                      //L1���
				T->bf = 0;
				right->bf = -1;
			}
			left->bf = 0;
			T = left;
			shorter = 1;
		}

	}
}

void onDelete_RightBalance(BBSTree &T, int &shorter) {
	//ɾ�����ʱ����ƽ�����
	BBSTree right, left;
	if(T->bf == -1) {         //���1��p����������ߣ�ɾ������p->bf = 0�����䰫
		T->bf = 0;
		shorter = 1;
	} else if(T->bf == 0) {   //���2��p��㺬������������ɾ������p->bf = 1�����߲���
		T->bf = 1;
		shorter = 0;
	} else {
		//���3��p����������ߣ���������L0,L-1,L1�������
		left = T->lchild;
		if(left->bf == 0) {           //L0���
			R_Rotate(T);
			left->bf = -1;
			T->bf = 1;
			shorter = 0;
		}else if(left->bf == 1) {     //L1���
			R_Rotate(T);
			T->bf = 0;
			left->bf = 0;
			shorter = 1;
		} else {                      //L-1��� ,�ַ�T�����������������R0,R-1,R1�������
			right = left->rchild;
			left->rchild = right->lchild;
			right->lchild = left;
			T->lchild = right->rchild;
			right->rchild = T;
			if(right->bf == 0) {           //R0���
				T->bf = 0;
				left->bf = 0;
			} else if(right->bf == 1) {   //R1���
				T->bf = 1;
				left->bf = 0;
			} else {                      //R-1���
				T->bf = 0;
				left->bf = 1;
			}
			left->bf = 0;
			T = right;
			shorter = 1;
		}

	}
}

void DeleteOperation(BBSTree keytree, BBSTree &T, int &shorter) {
  //��T���е�q������ɾ������
	if(T->rchild == NULL) {
		keytree->data = T->data;
		keytree = T;
		T = T->lchild;
		free(keytree);
		shorter = 1;
	} else {
		DeleteOperation(keytree, T->rchild, shorter);
		if(shorter == 1)
		  onDelete_RightBalance(T, shorter);
	}
}

int DeleteBBST(BBSTree &T, int key, int &shorter) {     //ɾ�����е�key�ؼ���
	int k;
	BBSTree keytree;
	if(!T) {                               //�ؼ��ֲ�����
		printf("�����ڸý�㣡\n");
		return 0;
	} else if(key < T->data) {             //�ؼ�������������
		k = DeleteBBST(T->lchild, key, shorter);
		if(shorter == 1)
			onDelete_LeftBalance(T, shorter);
		return k;
	} else if(key > T->data) {             //�ؼ�������������
		k =  DeleteBBST(T->rchild, key, shorter);
		if(shorter == 1)
			onDelete_RightBalance(T, shorter);
		return k;
	} else {
		keytree = T;
		if(T->rchild == NULL) {           //������Ϊ�գ�ֻ���ؽ�������
			T = T->lchild;
			free(keytree);
			shorter = 1;
		} else if(T->lchild == NULL) {    //������Ϊ�գ�ֻ���ؽ�������
			T = T->rchild;
			free(keytree);
			shorter = 1;
		} else {                          //������������
			DeleteOperation(keytree, keytree->lchild, shorter);
			if(shorter == 1)
				onDelete_LeftBalance(T, shorter);
			T = keytree;
		}
		return 1;
	}
}

int InsertAVL(BBSTree &T, int key, bool &taller) {
	//ʵ�ֶ�key���뵽�������Ĳ��� ,taller�����ĸ߶��Ƿ�����1
	if(NULL == T) {                       //�ҵ�����ص�
		T = (BBSTree)malloc(sizeof(BBSTNode));
		T->data = key;
		T->bf= EH;  T->lchild = NULL; T->rchild = NULL; taller = TRUE;
		return TRUE;
	} else if(key == T->data) {           //�Ѵ��ڲ��ò���
		taller = FALSE;
		printf("�Ѵ�����ͬ�Ľ��.\n");
		return FALSE;
	} else if(key < T->data) {            //��������Ѱ�Ҳ���ص����
		if(FALSE == InsertAVL(T->lchild, key, taller)) return FALSE;
		if(TRUE == taller) {
			switch (T->bf) {
				case LH: LeftBalance(T); taller = FALSE; break;
				case EH: T->bf = LH; taller = TRUE; break;
				case RH: T->bf = EH; taller = FALSE; break;
			}
		}
	} else {                              //��������Ѱ�Ҳ���ص����
		if(FALSE == InsertAVL(T->rchild, key, taller)) return FALSE;
		 if(TRUE == taller) {
			switch(T->bf) {
				case LH:
					 T->bf = EH; taller = FALSE; break;
				case EH:
					 T->bf = RH; taller = TRUE; break;
				case RH:
					 RightBalance(T); taller = FALSE; break;
			 }
		}
	}
	return TRUE;
}

void InOrderPrintBBST(BBSTree T) {         //������� ��ӡ��T
	if(T) {                                //���ǿ�
		InOrderPrintBBST(T->lchild);       //�ȷ���������
		printf("%d ", T->data);            //���ʸ����
		InOrderPrintBBST (T->rchild);      //����������
	}
}

void PreOrderPrintBBST(BBSTree T){         //�������
	if(T) {
		printf("%d ", T->data);            //�ȷ��ʸ����
		PreOrderPrintBBST(T->lchild);      //����������
		PreOrderPrintBBST(T->rchild);      //����������
	}
}

void LastOrderPrintBBST(BBSTree T) {           //�������
	if(T) {
		LastOrderPrintBBST(T->lchild);        //�ȷ���������
		LastOrderPrintBBST(T->rchild);        // ����������
		printf("%d ", T->data);               //���ʸ����
	}
}


static Status Visit(int e)    // ���Ԫ��e��ֵ
{
	printf("%d ", e);
	return OK;
}// PrintElement

Status PreOrderTraverse(BBSTree T)//�������ƽ�������(�ǵݹ飩������ջ�����������ص�
{
	//����ÿ��Ԫ�أ��ȷ����������ݣ�Ȼ���ٽ�ջ���������ӣ���ջ��ֱ������Ϊ�գ���ջ��
	//����ջ��Ԫ�ص����к��ӡ�
	SqStack S;
	BBSTree p;
	p = (BBSTree)malloc(sizeof(BBSTNode));
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Visit(p->data);
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			p = Getop(S);
			Pop(S, p);
			p = p->rchild;
		}
	}
	return OK;
}

Status InOrderTraverse(BBSTree T)//�������ƽ�������(�ǵݹ飩
{

	//����ÿ��Ԫ�أ��Ƚ�ջ��ֱ������Ϊ�գ���ջ������ջ��Ԫ�ص����ݡ�
	SqStack S;
	BBSTree p;
	p = (BBSTree)malloc(sizeof(BBSTNode));
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			if (!Visit(p->data))return ERROR;
			p = p->rchild;
		}
	}
	return OK;
}

Status PostOrderTraverse(BBSTree T) //�ǵݹ�������ƽ�������
{

	//������out����һ�����
	//�ж��Ƿ���ʹ�
	SqStack S;
	BBSTree p;
	p = (BBSTree)malloc(sizeof(BBSTNode));
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S))
	{
		if (p && !p->out)
		{
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			p = Getop(S);
			if (p->out)
			{
				Visit(p->data);
				Pop(S, p);
				p = NULL;
			}
			else
			{
				p->out = 1;
				p = p->rchild;
			}
		}
	}
	//printf("\n");
	return OK;
}

Status LevelOrderTraverse(BBSTree &T)
{
	Queue Q;
	InitQueue(Q);
	if (T)Enqueue(Q, T);
	while (!QueueEmpty(Q))
	{
		Delqueue(Q);
	}
	return OK;
}

void PrintBBST(BBSTree T) {                  //������ӡ��
    printf("-----------------------------------------\n");
    printf("\n�ݹ���������Ľ��  :( ");
	PreOrderPrintBBST(T);
	printf(")\n�ǵݹ���������Ľ��:( ");
	PreOrderTraverse(T);
	printf(")\n�ݹ���������Ľ��  :( ");
	InOrderPrintBBST(T);
	printf(")\n�ǵݹ���������Ľ��:( ");
	InOrderTraverse(T);
	printf(")\n�ݹ��������Ľ��  :( ");
	LastOrderPrintBBST(T);
	printf(")\n�ǵݹ��������Ľ��:( ");
	PostOrderTraverse(T);
	printf(")\n��α����Ľ��      :( ");
	LevelOrderTraverse(T);
	printf(")\n");
	printf("-----------------------------------------\n");
}

void PrintAsTree(BBSTree &T, int t) {       //�����������Ӵ�ӡ
	int Count;
	if(T){
	for(Count = 1;Count < t-1;Count++)
	       printf(" ");
	printf("%d\n",T->data);
	if(T->lchild)
	{
	    for(Count = 1;Count < t-1;Count++)
	       printf(" ");
	    PrintAsTree(T->lchild,t+5);
	}
	if(T->rchild)
	{
	    for(Count = 1;Count < t-1;Count++)
	       printf(" ");
	    PrintAsTree(T->rchild,t+5);
	}
	}
}

int CreateBBST(BBSTree &T) {               //����һ����
	int record ;                           //key������������ؼ���
	bool tall = FALSE;
	T = NULL;
	printf("------------------------------\n");
	printf("���������֣�����'00'ʱ��������\n");
	while (1) {                            //����1��������

			scanf("%d", &record);
			getchar();                     //��getchar����scanf�еĻ��������ݣ���ֹ����bug
			if(record == 00) break;
			InsertAVL(T, record, tall);   //���ܵ���keyһ��������
			tall = FALSE;
	}

	printf("------------------------------\n");
	return 0;
}

void DepartTree(BBSTree &T, int depart, BBSTree &T2, BBSTree &T3) {
	//T����ֺ�,T3���С�ڵ���depart�Ĺؼ��֣�T2��Ŵ���depart�Ĺؼ���
	bool taller = false;
	if(!T)  return;
	SqStack S;
	BBSTree p;//,q;
	p = (BBSTree)malloc(sizeof(BBSTNode));
	//q = (BBSTree)malloc(sizeof(BBSTNode));
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
		//	q = p;
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			if (p->data > depart) {
		InsertAVL(T2, p->data, taller);
			}
			else if(p->data <= depart) {
		InsertAVL(T3, p->data, taller);
	    }
			p = p->rchild;
		}
	}
}

void Merge(BBSTree &T, BBSTree &T1) {     //����T1�ϲ�����T��
	bool iftall = false;
	if(T1) {
		Merge(T, T1->lchild);
		InsertAVL(T, T1->data, iftall);
		Merge(T, T1->rchild);
	}
}

int main(void)
{
	int selection ;
	int info, Search, deletor, depart;
	BBSTree T,T1,T2,T3;
	T2 = T3 = NULL;
	T1 = T = (BBSTree)malloc(sizeof(BBSTNode));
	if(T == NULL&&T1 == NULL) return 0;
	bool taller = FALSE;
	int shorter = 0;
	while(1) {
		printf("                  --------------------------------               \n");
		printf("                  | 16��5��������ƽ���������ʾ��|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  0��      ����0ʱ�˳���      |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  1��   ����һ��ƽ���������  |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  2��  �������ĸ߶Ⱥ�Ҷ������ |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  3��  ��ƽ������������㣻 |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  4�� ����ƽ��������еĽ�㣻|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  5�� ɾ���������е�ĳ����㣻|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  6�����ֱ��������δ�ӡ������;|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  7��  ������һ�������ϲ�;    |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  8������ؼ��ֽ������������;|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  9�� ��������������С�ڵ�; |               \n");
		printf("                  --------------------------------               \n");
		printf("                                                                 \n");
		printf("���������ѡ��");
		scanf("%d", &selection);
		getchar();           //��ֹscanf���������ݲ�������
		switch(selection) {
			case 1: {
				if(CreateBBST(T) != 0) return 0;
				if(T) {
					printf("������ɣ�\n");
		    printf("�����İ������ʽΪ��\n");
					PrintAsTree(T, 5);
				}
				break;
			}
			case 2: {
			    int cnt1=node;
				printf("����������ǣ�%d\n", BBSTDepth(T));
				NodeNum(T);
				printf("������Ҷ�ӽ�����ǣ�%d\n",node);
				printf("�����İ������ʽΪ��\n");
				PrintAsTree(T,5);
				break;
			}
			case 3: {
				printf("��ƽ������������㣺");
				scanf("%d", &info);
				getchar();
				InsertAVL(T, info, taller);
				printf("�����İ������ʽΪ��\n");
				PrintAsTree(T, 5);
				break;
			}
			case 4: {
				printf("����ƽ��������еĽ�㣺");
				scanf("%d",&Search);
				getchar();
				if(SearchBBST(T, Search) != NULL) {
					printf("���%d�������������!\n", Search);
		    printf("�����İ������ʽΪ��\n");
					PrintAsTree(T, 5);
				} else {
					printf("����ʧ��,��㲻������.\n");
				}
				break;
			}
			case 5: {
				printf("ɾ���������е�ĳ����㣺");
				scanf("%d", &deletor);
				getchar();
				DeleteBBST(T, deletor, shorter);
				printf("�����İ������ʽΪ��\n");
				PrintAsTree(T, 5);
				break;
			}
			case 6: {            //��ӡ��
				PrintBBST(T);
				printf("�����İ������ʽΪ��\n");
				PrintAsTree(T, 5);
				break;
			}
			case 7: {             //�ϲ�������
				if(CreateBBST(T1) != 0) return 0;
				printf("�������Ϊ:\n");
				PrintAsTree(T1, 5);
				Merge(T, T1);
				printf("�ϲ������Ϊ:\n");
				PrintAsTree(T, 5);
				break;
			}
			case 8: {            //���ݹؼ��ֲ����
				printf("����ؼ���:");
				scanf("%d", &depart);
		DepartTree(T, depart, T2, T3);
		printf("\n��ֺ����Ϊ:\n");
		printf("\n");
		PrintAsTree(T2, 5);
		printf("\n");
		PrintAsTree(T3, 5);
				break;
			}
			case 9: {
			    BBSTree P,Q;
		P=FindMax(T);
		Q=FindMin(T);
		printf("ƽ����������������ǣ�%d",P->data);
		printf("\n");
		printf("ƽ�����������С�����ǣ�%d",Q->data);
		printf("\n");
				printf("�����İ������ʽΪ��\n");
				PrintAsTree(T2, 5);
			}
			case 0: {
				free(T);
				free(T1);
				free(T2);
				free(T3);
				return 0;
			}         //����ѡ��
			default:
				printf("�����������������...");
				break;
		}
	}
	return 0;
}
