#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree; /*二叉树类型*/

struct TNode{ //树结点定义
    ElementType Data;/*结点数据*/
    BinTree Left;/*指向左子树*/
    BinTree Right;/*指向右子树*/
};
BinTree BuildTree(int *post, int *in, int n);
void PreOrder(BinTree T);
BinTree NewNode(int V);

int main(){
	int i,N;
	BinTree T;
	scanf("%d", &N);
	int post[N],in[N];
	for(i = 0; i<N; i++){
		scanf("%d", &post[i]);
	}
	for(i = 0; i<N; i++){
		scanf("%d", &in[i]);
	}
	T = BuildTree(post, in, N);
	printf("Preorder:");
	PreOrder(T);
	return 0;
} 

BinTree BuildTree(int *post, int *in, int n){
	int i = 0;
	BinTree Root;
	Root = NewNode(n);
	Root->Data = post[n-1];
	if(!n){
		return NULL;
	}
	while(in[i] != post[n-1]){
		i++;
	}
	Root->Left = BuildTree(post,in,i);
	Root->Right = BuildTree(post+i, in+i+1 ,n-i-1);
	return Root;
}

BinTree NewNode(int V){
	BinTree T = (BinTree)malloc(sizeof(struct TNode));
	T->Left = T->Right = NULL;
	return T;
}

void PreOrder(BinTree T){
	if(T){
		printf(" %d",T->Data);
		PreOrder(T->Left);
		PreOrder(T->Right);
	}
}
