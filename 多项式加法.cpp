#include <stdio.h>
#include <stdlib.h>
struct PolyNode{
	int coef;
	int exp;
	struct PolyNode *Next;
};
typedef struct PolyNode *Poly;

void Attach(int c, int e, Poly *pRear);

Poly Add(Poly P1, Poly P2){
	Poly front,rear,temp;
	int sum;
	rear = (Poly)malloc(sizeof(struct PolyNode));
	while(P1 && P2){
		if(P1->exp == P2->exp){
			sum = P1->coef + P2->coef;
			if(sum){
				Attach(sum, P1->exp, &rear);
			}
			P1 = P1->Next; P2 = P2->Next;
		}else if(P1->exp > P2->exp){
			Attach(P1->coef, P1->exp, &rear);
			P1 = P1->Next;
		}else{
			Attach(P2->coef, P2->exp, &rear);
			P2 = P2->Next;
		}
	}
	for(;P1;P1 = P1->Next){
		Attach(P1->coef, P1->exp, &rear);
	}
	for(;P2;P2 = P2->Next){
		Attach(P2->coef, P2->exp, &rear);
	}
	rear->Next = NULL;
	temp = front; front = front->Next; free(temp);
	return front;
} 

Poly Mult(Poly P1, Poly P2){
	Poly P, Rear, t1, t2, t;
	int c, e;
	if( !P1 || !P2){
		return NULL;
	}
	t1 = P1; t2 = P2;
	P = (Poly)malloc(sizeof(struct PolyNode));P->Next = NULL;
	Rear = P;
	while(t2){
		Attach(t1->coef * t2->coef, t1->exp + t2->exp, &Rear);
		t2 = t2->Next;
	}
	t1 = t1->Next;
	while(t1){
		t2 = P2; Rear = P;
		while(t2){
			e = t1->exp + t2->exp;
			c = t1->coef * t2->coef;
			while(Rear->Next && Rear->Next->exp > e){
				Rear = Rear->Next;
			}
			if(Rear->Next && Rear->Next->exp == e){
				if(Rear->Next->coef + c){
					Rear->Next->coef += c;
				}else{
					t = Rear->Next;
					Rear->Next = t->Next;
					free(t);
				}
			}else{
				t = (Poly)malloc(sizeof(struct PolyNode));
				t->coef = c; t->exp = e;
				t->Next = Rear->Next;
				Rear->Next = t; Rear = Rear->Next;
			}
			t2 = t2->Next;
		}
		t1 = t1->Next;
	}
	t2 = P; P = P->Next; free(t2); 
	return P;
}

void Attach(int c, int e, Poly *pRear){
	Poly P;
	P = (Poly)malloc(sizeof(struct PolyNode));
	P->coef = c; P->exp = e;
	P->Next = NULL;
	(*pRear)->Next = P;
	*pRear = P;
}

Poly Read(){
	int n,c,e;
	Poly P,Rear,t;
	scanf("%d", &n);
	P = (Poly)malloc(sizeof(struct PolyNode));
	P->Next = NULL;
	Rear = P;
	while(n--){
		scanf("%d %d", &c, &e);
		Attach(c,e, &Rear);
	}
	t = P;
	P = P->Next;
	free(t);
	return P;
}

void Print(Poly P){
	int flag = 0;
	if(!P){
		printf("0 0\n");
		return;
	}
	while(P){
		if(!flag){
			flag = 1;
		}else{
			printf(" ");
		}
		printf("%d %d",P->coef, P->exp);
		P = P->Next;
	}
	printf("\n");
}
int main(){
	Poly P1, P2, P3, P4; 
	P1 = Read();
	P2 = Read();
	P4 = Add(P1,P2);
	P3 = Mult(P1,P2);
	Print(P3);
	Print(P4);
	return 0;
} 
