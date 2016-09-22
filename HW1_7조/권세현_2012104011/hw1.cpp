#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 999999
#pragma warning(disable:4996)

typedef struct ListNode{
	char* Data;
	struct ListNode* next;
}Node;		//링크드리스트를 위한 노드생성 

Node *head;

Node* InitList(){
	head=(Node*)malloc(sizeof(Node));
	head->next=NULL;
	head->Data=NULL;
	return head;
}

void AddNode(Node* head, char* data){
	Node* newNode = new Node;
	newNode->Data=data;
	newNode->next = NULL;

	if(head==NULL){
	head=newNode;
	}
	else{
	Node* temp=head;
	while(temp!=NULL){
		if(temp->next==NULL){
			temp->next=newNode;
			break;
			}
		temp=temp->next;
		}
	}
}		//노드를 추가하는 함수

int main(){
	FILE *fpin;
	FILE *fpout;
	char* data;
	char str[BUFF_SIZE];
	int x=0;

	fpin=fopen("A.txt","r");
	if(fpin==NULL){
		printf("오픈불가\n");
		return 0;
	}
	fpout=fopen("B.txt","a+");
	if(fpout==NULL){
		printf("오픈불가\n");
		return 0;
	}	

	InitList();
	while(!feof(fpin)){
		fgets(str,BUFF_SIZE,fpin);
		data=strtok(str," ,.'\"");
		while(data!=NULL){
			fprintf(fpout,"%s ,",data);
		AddNode(head,data);
		data=strtok(NULL, " ,.'\"");
		}
	fclose(fpin);
	fclose(fpout);

	Node* p=head;
	while(p!=NULL){
	printf("%s, ",p->Data);
	p=p->next;
	}

	scanf("%s",str);

	return 0;
	}
}