
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
#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACKINCREMENT 10 // 存储空间分配增量
#define MAXQsize 100 //队列空间初始化分配量
#define LH +1 //左边高
#define RH -1 //右边高
#define EH 0 //等高

typedef int ElemType;
typedef int Status;
typedef int SElemType;
typedef int STACK_TYPE;

bool taller;
int flag=0;//查找的标记
int l=0; //左子树的深度
int r=0; //有子树的深度
int jiedian=0; //树的结点数

typedef struct BBSTNode
{
  ElemType data;
  int bf; //平衡因子
  int out;  //后序遍历的非递归算法的标记（是否访问过）
  struct BBSTNode *lchild,*rchild;//左右孩子指针
} BBSTNode,*BBSTree;  //树的结构


struct SqStack //顺序栈
{
  BBSTree *base; // 在栈构造之前和销毁之后，base的值为NULL
  BBSTree *top; // 栈顶指针
  int stacksize; // 当前已分配的存储空间，以元素为单位
};


struct Queue // 顺序队列
{
  BBSTree base[MAXQsize];
  int Front; // 对头指针
  int rear; // 队尾指针指针
};

Status InitStack(SqStack &S)  //初始化栈
{
	// 构造一个空栈S，该栈预定义大小为STACK_INIT_SIZE
	S.base = (BBSTree*)malloc(STACK_INIT_SIZE * sizeof(BBSTree));
	if (!S.base) return ERROR;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status StackEmpty(SqStack S) //栈判空
{
	//判断栈是否为空是返回1，否则返回0；
	if (S.top == S.base)return OK;
	else return ERROR;
}

Status Push(SqStack &S, BBSTree e)//入栈
{
	// 在栈S中插入元素e为新的栈顶元素
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S, BBSTree &e)//出栈
{
	// 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
	if (S.top == S.base) return ERROR;
	e = *(--S.top);
	return OK;
}

BBSTree Getop(SqStack &S)//返回栈顶元素
{
	// 若栈不空，则返回S的栈顶元素；否则返回NULL；
	if (S.top == S.base) return NULL;
	return *(S.top - 1);
}

Status InitQueue(Queue &Q)  //初始化队列
{
	Q.Front = 0;
	Q.rear = 0;
	return OK;
}

Status QueueEmpty(Queue Q) //	判空目标队列，并返回是或否
{
	//判断队列是否为空是返回1，否则返回0；
	if (Q.Front == Q.rear)return OK;
	else return ERROR;
}

Status Enqueue(Queue &Q, BBSTree T) //元素入队
{
	//如果入队列没有满，则T入队

	if (Q.rear == MAXQsize)return ERROR;


	if (T)Q.base[Q.rear++] = T;


	return OK;
}

Status Delqueue(Queue &Q)
{
	//如果队列Q不为空，则输出队头数据，左右子树入队，对头出队。
	if (Q.Front == Q.rear)return ERROR;
	else
	{
		printf("%d ", Q.base[Q.Front]->data);
		Enqueue(Q, Q.base[Q.Front]->lchild);//入队左子树
		Enqueue(Q, Q.base[Q.Front]->rchild);//入队右子树
		Q.Front++;
	}
	return OK;
}


 int IsBalance(BBSTree T) {    //判断T树是否是平衡二叉树，是为1,否为0
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

void DestoryBBST(BBSTree T) {             //销毁一颗树
  if(T != NULL) {
    DestoryBBST(T->lchild);
    DestoryBBST(T->rchild);
	free(T);
  }
}

int BBSTDepth(BBSTree T) {               //计算一棵树的高度
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
	//求树的叶子结点数，这里定义了一个全局变量，直接记录叶子结点数
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

BBSTree SearchBBST(BBSTree T, int key) {    //查找树中key的位置，存在返回其指针，不存在返回NULL
	while(T != NULL) {
		if(T->data == key) return T;
		else if(T->data < key) T = T->rchild;
		else if(T->data > key) T = T->lchild;
	}
	return NULL;
}

void R_Rotate(BBSTree &p) {       //右旋LL型
	BBSTree lc = p->lchild;
	p->lchild = lc->rchild;
	lc->rchild = p;
	p = lc;
}

void L_Rotate(BBSTree &p) {		//左旋RR型
	BBSTree rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

void LR_Rotate(BBSTree &p) {     //LR型
	L_Rotate(p->lchild);
	R_Rotate(p);
}

void RL_Rotate(BBSTree &p) {      //RL型
	R_Rotate(p->rchild);
	L_Rotate(p);
}

void LeftBalance(BBSTree &T) {		//实现对以T为根的树的左平衡处理
	BBSTree lc, rd;
	lc = T->lchild;
	switch(lc->bf) {                //检查树T的左子树平衡因子
		case LH:                   //LL型，右旋处理
			T->bf = lc->bf = EH;
			R_Rotate(T);
			break;
		case RH:                   //新插入结点在T的左孩子的右子树上，LR型，双旋处理
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

void RightBalance(BBSTree &T) {  //实现对以T为根结点的右平衡操作
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

static BBSTree FindMin(BBSTree T)  //查找最小的结点
{
	if (NULL == T)		//空树
		return NULL;
	while (NULL != T->lchild)		//二叉平衡树 T 中关键字最小的结点为其左分支上的叶子
		T = T->lchild;
	return T;
}

static BBSTree FindMax(BBSTree T)   //查找最大的结点
{
	if (NULL == T)		//空树
		return NULL;
	while (NULL != T->rchild)	//二叉平衡树 T 中关键字最大的结点为其右分支上的叶子
		T = T->rchild;
	return T;
}

void onDelete_LeftBalance(BBSTree &T, int &shorter) {
	//删除结点时的左平衡操作
	BBSTree right, left;
	if(T->bf == 1) {         //情况1，p结点左子树高，删除结点后p->bf = 0，树变矮
		T->bf = 0;
		shorter = 1;
	} else if(T->bf == 0) {   //情况2，p结点含有左右子树，删除结点后p->bf = -1，树高不变
		T->bf = -1;
		shorter = 0;
	} else {
		//情况3，p结点右子树高：分右子树R0,R-1,R1三种情况
		right = T->rchild;
		if(right->bf == 0) {          //R0情况
			L_Rotate(T);
			right->bf = 1;
			T->bf = -1;
			shorter = 0;
		}else if(right->bf == -1) {   //R-1情况
			L_Rotate(T);
			T->bf = 0;
			right->bf = 0;
			shorter = 1;
		} else {                      //R1情况 ,又分T结点右子树的左子树L0,L-1,L1三种情况
			left = right->lchild;
			right->lchild = left->rchild;
			left->rchild = right;
			T->rchild = left->lchild;
			left->lchild = T;
			if(left->bf == 0) {           //L0情况
				T->bf = 0;
				right->bf = 0;
			} else if(left->bf == -1) {   //L-1情况
				T->bf = 1;
				right->bf = 0;
			} else {                      //L1情况
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
	//删除结点时的右平衡操作
	BBSTree right, left;
	if(T->bf == -1) {         //情况1，p结点右子树高，删除结点后p->bf = 0，树变矮
		T->bf = 0;
		shorter = 1;
	} else if(T->bf == 0) {   //情况2，p结点含有左右子树，删除结点后p->bf = 1，树高不变
		T->bf = 1;
		shorter = 0;
	} else {
		//情况3，p结点左子树高：分右子树L0,L-1,L1三种情况
		left = T->lchild;
		if(left->bf == 0) {           //L0情况
			R_Rotate(T);
			left->bf = -1;
			T->bf = 1;
			shorter = 0;
		}else if(left->bf == 1) {     //L1情况
			R_Rotate(T);
			T->bf = 0;
			left->bf = 0;
			shorter = 1;
		} else {                      //L-1情况 ,又分T结点左子树的右子树R0,R-1,R1三种情况
			right = left->rchild;
			left->rchild = right->lchild;
			right->lchild = left;
			T->lchild = right->rchild;
			right->rchild = T;
			if(right->bf == 0) {           //R0情况
				T->bf = 0;
				left->bf = 0;
			} else if(right->bf == 1) {   //R1情况
				T->bf = 1;
				left->bf = 0;
			} else {                      //R-1情况
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
  //对T树中的q树进行删除操作
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

int DeleteBBST(BBSTree &T, int key, int &shorter) {     //删除树中的key关键字
	int k;
	BBSTree keytree;
	if(!T) {                               //关键字不存在
		printf("不存在该结点！\n");
		return 0;
	} else if(key < T->data) {             //关键字在左子树中
		k = DeleteBBST(T->lchild, key, shorter);
		if(shorter == 1)
			onDelete_LeftBalance(T, shorter);
		return k;
	} else if(key > T->data) {             //关键字在右子树中
		k =  DeleteBBST(T->rchild, key, shorter);
		if(shorter == 1)
			onDelete_RightBalance(T, shorter);
		return k;
	} else {
		keytree = T;
		if(T->rchild == NULL) {           //右子树为空，只需重接左子树
			T = T->lchild;
			free(keytree);
			shorter = 1;
		} else if(T->lchild == NULL) {    //左子树为空，只需重接右子树
			T = T->rchild;
			free(keytree);
			shorter = 1;
		} else {                          //含有左右子树
			DeleteOperation(keytree, keytree->lchild, shorter);
			if(shorter == 1)
				onDelete_LeftBalance(T, shorter);
			T = keytree;
		}
		return 1;
	}
}

int InsertAVL(BBSTree &T, int key, bool &taller) {
	//实现对key插入到二叉树的操作 ,taller是树的高度是否增加1
	if(NULL == T) {                       //找到插入地点
		T = (BBSTree)malloc(sizeof(BBSTNode));
		T->data = key;
		T->bf= EH;  T->lchild = NULL; T->rchild = NULL; taller = TRUE;
		return TRUE;
	} else if(key == T->data) {           //已存在不用插入
		taller = FALSE;
		printf("已存在相同的结点.\n");
		return FALSE;
	} else if(key < T->data) {            //往左子树寻找插入地点插入
		if(FALSE == InsertAVL(T->lchild, key, taller)) return FALSE;
		if(TRUE == taller) {
			switch (T->bf) {
				case LH: LeftBalance(T); taller = FALSE; break;
				case EH: T->bf = LH; taller = TRUE; break;
				case RH: T->bf = EH; taller = FALSE; break;
			}
		}
	} else {                              //往右子树寻找插入地点插入
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

void InOrderPrintBBST(BBSTree T) {         //中序遍历 打印树T
	if(T) {                                //树非空
		InOrderPrintBBST(T->lchild);       //先访问左子树
		printf("%d ", T->data);            //访问根结点
		InOrderPrintBBST (T->rchild);      //访问右子树
	}
}

void PreOrderPrintBBST(BBSTree T){         //先序遍历
	if(T) {
		printf("%d ", T->data);            //先访问根结点
		PreOrderPrintBBST(T->lchild);      //访问左子树
		PreOrderPrintBBST(T->rchild);      //访问右子树
	}
}

void LastOrderPrintBBST(BBSTree T) {           //后序遍历
	if(T) {
		LastOrderPrintBBST(T->lchild);        //先访问左子树
		LastOrderPrintBBST(T->rchild);        // 访问右子树
		printf("%d ", T->data);               //访问根结点
	}
}


static Status Visit(int e)    // 输出元素e的值
{
	printf("%d ", e);
	return OK;
}// PrintElement

Status PreOrderTraverse(BBSTree T)//先序遍历平衡二叉树(非递归），利用栈的先入后出的特点
{
	//对于每个元素，先访问他的数据，然后再进栈，访问左孩子，进栈，直到左孩子为空，出栈，
	//访问栈顶元素的所有孩子。
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

Status InOrderTraverse(BBSTree T)//中序遍历平衡二叉树(非递归）
{

	//对于每个元素，先进栈，直到左孩子为空，出栈，访问栈顶元素的数据。
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

Status PostOrderTraverse(BBSTree T) //非递归后序遍历平衡二叉树
{

	//这里用out做了一个标记
	//判断是否访问过
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

void PrintBBST(BBSTree T) {                  //遍历打印树
    printf("-----------------------------------------\n");
    printf("\n递归先序遍历的结果  :( ");
	PreOrderPrintBBST(T);
	printf(")\n非递归先序遍历的结果:( ");
	PreOrderTraverse(T);
	printf(")\n递归中序遍历的结果  :( ");
	InOrderPrintBBST(T);
	printf(")\n非递归中序遍历的结果:( ");
	InOrderTraverse(T);
	printf(")\n递归后序遍历的结果  :( ");
	LastOrderPrintBBST(T);
	printf(")\n非递归后序遍历的结果:( ");
	PostOrderTraverse(T);
	printf(")\n层次遍历的结果      :( ");
	LevelOrderTraverse(T);
	printf(")\n");
	printf("-----------------------------------------\n");
}

void PrintAsTree(BBSTree &T, int t) {       //按照树的样子打印
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

int CreateBBST(BBSTree &T) {               //创建一棵树
	int record ;                           //key用来接受输入关键字
	bool tall = FALSE;
	T = NULL;
	printf("------------------------------\n");
	printf("请输入数字，输入'00'时结束创建\n");
	while (1) {                            //输入1结束输入

			scanf("%d", &record);
			getchar();                     //用getchar接受scanf中的缓存区数据，防止出现bug
			if(record == 00) break;
			InsertAVL(T, record, tall);   //接受到的key一个个插入
			tall = FALSE;
	}

	printf("------------------------------\n");
	return 0;
}

void DepartTree(BBSTree &T, int depart, BBSTree &T2, BBSTree &T3) {
	//T树拆分后,T3存放小于等于depart的关键字，T2存放大于depart的关键字
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

void Merge(BBSTree &T, BBSTree &T1) {     //将树T1合并到树T中
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
		printf("                  | 16计5林文敏《平衡二叉树演示》|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  0、      输入0时退出；      |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  1、   创建一棵平衡二叉树；  |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  2、  计算树的高度和叶子数； |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  3、  向平衡二叉树插入结点； |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  4、 查找平衡二叉树中的结点；|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  5、 删除二叉树中的某个结点；|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  6、七种遍历和树形打印出该树;|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  7、  输入另一棵树并合并;    |               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  8、输入关键字将树拆成两棵树;|               \n");
		printf("                  --------------------------------               \n");
		printf("                  |  9、 查找树中最大和最小节点; |               \n");
		printf("                  --------------------------------               \n");
		printf("                                                                 \n");
		printf("请输入你的选择：");
		scanf("%d", &selection);
		getchar();           //防止scanf缓冲区数据残留问题
		switch(selection) {
			case 1: {
				if(CreateBBST(T) != 0) return 0;
				if(T) {
					printf("创建完成！\n");
		    printf("该树的凹入表形式为：\n");
					PrintAsTree(T, 5);
				}
				break;
			}
			case 2: {
			    int cnt1=node;
				printf("该树的深度是：%d\n", BBSTDepth(T));
				NodeNum(T);
				printf("该树的叶子结点数是：%d\n",node);
				printf("该树的凹入表形式为：\n");
				PrintAsTree(T,5);
				break;
			}
			case 3: {
				printf("向平衡二叉树插入结点：");
				scanf("%d", &info);
				getchar();
				InsertAVL(T, info, taller);
				printf("该树的凹入表形式为：\n");
				PrintAsTree(T, 5);
				break;
			}
			case 4: {
				printf("查找平衡二叉树中的结点：");
				scanf("%d",&Search);
				getchar();
				if(SearchBBST(T, Search) != NULL) {
					printf("结点%d存在于这棵树上!\n", Search);
		    printf("该树的凹入表形式为：\n");
					PrintAsTree(T, 5);
				} else {
					printf("查找失败,结点不在树上.\n");
				}
				break;
			}
			case 5: {
				printf("删除二叉树中的某个结点：");
				scanf("%d", &deletor);
				getchar();
				DeleteBBST(T, deletor, shorter);
				printf("该树的凹入表形式为：\n");
				PrintAsTree(T, 5);
				break;
			}
			case 6: {            //打印树
				PrintBBST(T);
				printf("该树的凹入表形式为：\n");
				PrintAsTree(T, 5);
				break;
			}
			case 7: {             //合并两棵树
				if(CreateBBST(T1) != 0) return 0;
				printf("输入的树为:\n");
				PrintAsTree(T1, 5);
				Merge(T, T1);
				printf("合并后的树为:\n");
				PrintAsTree(T, 5);
				break;
			}
			case 8: {            //根据关键字拆分树
				printf("输入关键字:");
				scanf("%d", &depart);
		DepartTree(T, depart, T2, T3);
		printf("\n拆分后的树为:\n");
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
		printf("平衡二叉树中最大的数是：%d",P->data);
		printf("\n");
		printf("平衡二叉树中最小的数是：%d",Q->data);
		printf("\n");
				printf("该树的凹入表形式为：\n");
				PrintAsTree(T2, 5);
			}
			case 0: {
				free(T);
				free(T1);
				free(T2);
				free(T3);
				return 0;
			}         //结束选择
			default:
				printf("输入错误，请重新输入...");
				break;
		}
	}
	return 0;
}
