#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 999999

typedef struct ListNode{
	char* Data;
	int index;
	struct ListNode* next;
}Node;		//��� ����ü ����

typedef struct LinkedList{
	int size;
	Node* head;
}List;		//����Ʈ ����ü ����


List* InitList(){		//����Ʈ ����
	List* L=(List*)malloc(sizeof(List));
	L->head=NULL;
	L->size=0;
	return L;
}

void AddNode(List* l, Node* N){		//��ũ�帮��Ʈ�� ��带 �߰�
	if(l->head==NULL){
		l->head=N;
		l->size++;
		N->index=l->size;
	}
	else{
	Node* temp=l->head;
	while(temp!=NULL){		//temp�� �̿��� �տ������� ��� NULL�� ã�� �� ��ġ�� �߰�
		if(temp->next==NULL){
			temp->next=N;
			l->size++;			//��尡 �߰��� ������ size����
			N->index=l->size;	//��尡 �߰��� �� ����� index�� ����
			break;
			}
		temp=temp->next;
		}
	}
}

Node* PutData(char* D, int size){		//���ο� ��忡 ������ ����
	Node* N=(Node*)malloc(sizeof(Node));
	N->Data=(char*)malloc(sizeof(char)*(size+1));	//strtok�Լ��� �������� \0�� �߰��Ѵ�.
	strcpy(N->Data,D);
	N->next=NULL;
	return N;
}

int main(){
	List* list=InitList();
	
	char* data;
	char str[BUFF_SIZE];
	int i;
	Node* n;
	FILE *fp;
	FILE *fpB;

	fp=fopen("input.txt","r");
	if(fp==NULL){
		printf("�������\n");
		return 0;
	}
	fpB=fopen("B.txt","w");
	if(fpB==NULL){
		printf("���ºҰ�\n");
		return 0;
	}	
	int y=0;
	while(!feof(fp)){
		str[y]=fgetc(fp);
		if(str[y]==NULL){
		break;
		}	//�ڷ� �� ���� �����Ƿ� �ݺ��� �����ϴ�.�Ʒ��� �����ȣ ���ִ� ����
		else if(str[y]=='.'){
			str[y]=' ';
			continue;
		}	
		else if(str[y]==','){
			str[y]=' ';
			continue;
		}
		else if(str[y]=='\''){
			str[y]=' ';
			continue;
		}
		else if(str[y]=='?'){
			str[y]='\n';
			continue;
		}
		else if(str[y]=='!'){
			str[y]='\n';
			continue;
		}
		else if(str[y]=='\"'){
			str[y]=' ';
		}
		else
			fputc(str[y],fpB);//�����ȣ�� ���� ���� ����
		y++;
	}
	fclose(fp);
	fclose(fpB);

	fp=fopen("B.txt","r");
	if(fp==NULL){
		printf("���ºҰ�\n");
		return 0;
	}	

	while(!feof(fp)){
		fgets(str,BUFF_SIZE,fp);
		data=strtok(str," ");	//strtok�Լ��� �̿� ���� �͵��� ��ū���� ����Ͽ� ��ū������ ���´�. 
		while(data!=NULL){
		i=strlen(data);
		n=PutData(data,i);
		AddNode(list,n);
		data=strtok(NULL," ");	//���� ��ġ���� �ٽ� �˻��ϱ� ���Ѱ�
		}
	}
	fclose(fp);
	printf("�� %d�� ���\n",list->size);
	while(1){		//��� �˻����ֱ����� ���ѷ���
	printf("�˻��� �ܾ �Է��ϼ���. : ");
	scanf("%s",str);
	int x=0;
	Node* temp=list->head;
	while (temp->next!=NULL){
		if(!strcmp(temp->Data, str)) {		//������ 0�� ��ȯ�ϴ� strcmp��� if������ 0�� �����̹Ƿ� !�ٿ��־���.
			printf("%d index���� ",temp->index);
			x++;
		}
		temp=temp->next;
	}
	printf("�� %d��\n", x);
	}
	return 0;
}

