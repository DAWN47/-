#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct Data {
	char a;
}data;

typedef struct TNode {
	struct TNode* parent;
	struct TNode* Lchild;
	struct TNode* Rchild;
	data a;
}TNode,*Tree;
typedef struct sNode {
	struct sNode* next;
	Tree t;
}sNode;

typedef struct Stack {
	sNode* base;
	sNode* top;
}*stack;

stack createStack1() {
	stack s = (stack)malloc(sizeof(struct Stack));
	sNode* base = (sNode*)malloc(sizeof(sNode));
	if (!s||!base)
	{
		printf("�ڴ��������");
		exit(0);
	}
	s->base = s->top = base;
	return s;
}
void pressOne(stack s, Tree t) {
	sNode* n = (sNode*)malloc(sizeof(sNode));
	n->t = t;
	n->next = s->top;
	s->top = n; 
}

sNode* bounceOne(stack s) {
	if (stackIsEmpty(s))
	{
		return NULL;
	}
	sNode* r = s->top;
	s->top = s->top->next;
	return r;
}
//�ж�ջ�Ƿ�Ϊ��
int stackIsEmpty(stack s) {
	if (s->base==s->top)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//������
Tree createTree() {
	Tree t = (Tree)malloc(sizeof(TNode));
	if (!t)
	{
		exit(0);
	}
	t->parent = NULL;
	t->Lchild = NULL;
	t->Rchild = NULL;
	return t;
}
//���ʽڵ�
void vist(Tree t) {
	printf("%c\n", t->a.a);
}
//�������
void traverseFirst(Tree t) {
	if (t)
	{
		vist(t);
		traverseFirst(t->Lchild);
		traverseFirst(t->Rchild);
	}
}
//�ǵݹ��������
void traverseFirstByStack(Tree t) {
	stack s = createStack1();
	while (t!=NULL)
	{
		vist(t);
		if (t->Rchild)
		{
			pressOne(s, t->Rchild);
		}
		if (t->Lchild)
		{
			pressOne(s, t->Lchild);
		}
		sNode* tmp = bounceOne(s);
		if (tmp == NULL)
		{
			t = NULL;
		}
		else
		{
			t = tmp->t;
		}
	}
}
//�������
void midOrderTraversal(Tree t) {
	if (t)
	{
		midOrderTraversal(t->Lchild);
		vist(t);
		midOrderTraversal(t->Rchild);
	}
}
//�������
void postOrderTraversal(Tree t) {
	if (t)
	{
		postOrderTraversal(t->Lchild);
		postOrderTraversal(t->Rchild);
		vist(t);
	}
}
//�����½ڵ�
Tree createTNode() {
	Tree t = (Tree)malloc(sizeof(TNode));
	if (!t)
	{
		exit(0);
	}
	t->parent = NULL;
	t->Lchild = NULL;
	t->Rchild = NULL;
	return t;
}
//��������
Tree constructTree(Tree t) {
	char input;
	scanf("%c", &input);
	getchar();
	if (input=='#')
	{
		t = NULL;
	}
	else
	{
		t->a.a = input;
		t->Lchild = createTNode();
		if (!constructTree(t->Lchild))
		{
			free(t->Lchild);
			t->Lchild = NULL;
		}
		t->Rchild = createTNode();
		if (!constructTree(t->Rchild))
		{
			free(t->Rchild);
			t->Rchild = NULL;
		}
	}
	return t;
}
//�������
int higth(Tree t) {
	int L = 0, R = 0;
	if (t==NULL)
	{
		return 0;
	}
	else
	{
		L = higth(t->Lchild);
		R = higth(t->Rchild);
	}
	return L > R ? L + 1 : R + 1;
}
//��ȡ�ڵ�����
int getNodeNumber(Tree t) {
	int L = 0, R = 0;
	if (t==NULL)
	{
		return 0;
	}
	else
	{
		L = getNodeNumber(t->Lchild);
		R = getNodeNumber(t->Rchild);
	}
	return L + R + 1;
}
//��ȡҶ�ӽڵ�����
int getLeafNodes(Tree t) {
	static int i = 0;
	if (t==NULL)
	{
		return 0;
	}
	else {
		if (t->Lchild==NULL&&t->Rchild==NULL)
		{
			i++;
		}
		else
		{
			getLeafNodes(t->Lchild);
			getLeafNodes(t->Rchild);
		}
	}
	return i;
}
//��ȡ�ڵ�����
int getNodeNumber1(Tree t) {
	static int i = 0;
	if (t)
	{
		i++;
		getNodeNumber1(t->Lchild);
		getNodeNumber1(t->Rchild);
	}
	return i;
}

int main() {
	/*Tree t = createTree();
	t->a.a = 1;
	t->Lchild = createTree();
	t->Rchild = createTree();
	t->Lchild->a.a = 2;
	t->Rchild->a.a = 3;
	t->Lchild->Lchild = createTree();
	t->Lchild->Lchild->a.a = 4;
	postOrderTraversal(t);*/

	Tree t = createTree();
	constructTree(t);
	traverseFirstByStack(t);
	return 0;
 }