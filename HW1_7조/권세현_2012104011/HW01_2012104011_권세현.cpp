#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 999999

typedef struct ListNode{
	char* Data;
	int index;
	struct ListNode* next;
}Node;		//노드 구조체 정의

typedef struct LinkedList{
	int size;
	Node* head;
}List;		//리스트 구조체 정의


List* InitList(){		//리스트 생성
	List* L=(List*)malloc(sizeof(List));
	L->head=NULL;
	L->size=0;
	return L;
}

void AddNode(List* l, Node* N){		//링크드리스트에 노드를 추가
	if(l->head==NULL){
		l->head=N;
		l->size++;
		N->index=l->size;
	}
	else{
	Node* temp=l->head;
	while(temp!=NULL){		//temp를 이용해 앞에서부터 계속 NULL을 찾아 그 위치에 추가
		if(temp->next==NULL){
			temp->next=N;
			l->size++;			//노드가 추가될 때마다 size증가
			N->index=l->size;	//노드가 추가될 때 싸이즈를 index로 정의
			break;
			}
		temp=temp->next;
		}
	}
}

Node* PutData(char* D, int size){		//새로운 노드에 데이터 저장
	Node* N=(Node*)malloc(sizeof(Node));
	N->Data=(char*)malloc(sizeof(char)*(size+1));	//strtok함수는 마지막에 \0를 추가한다.
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
		printf("열기실패\n");
		return 0;
	}
	fpB=fopen("B.txt","w");
	if(fpB==NULL){
		printf("오픈불가\n");
		return 0;
	}	
	int y=0;
	while(!feof(fp)){
		str[y]=fgetc(fp);
		if(str[y]==NULL){
		break;
		}	//뒤로 더 값이 없으므로 반복을 끝냅니다.아래는 문장부호 없애는 과정
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
			fputc(str[y],fpB);//문장부호를 없앤 것을 저장
		y++;
	}
	fclose(fp);
	fclose(fpB);

	fp=fopen("B.txt","r");
	if(fp==NULL){
		printf("오픈불가\n");
		return 0;
	}	

	while(!feof(fp)){
		fgets(str,BUFF_SIZE,fp);
		data=strtok(str," ");	//strtok함수를 이용 앞의 것들을 토큰으로 취급하여 토큰단위로 끊는다. 
		while(data!=NULL){
		i=strlen(data);
		n=PutData(data,i);
		AddNode(list,n);
		data=strtok(NULL," ");	//끊은 위치부터 다시 검색하기 위한것
		}
	}
	fclose(fp);
	printf("총 %d개 노드\n",list->size);
	while(1){		//계속 검색해주기위한 무한루프
	printf("검색할 단어를 입력하세요. : ");
	scanf("%s",str);
	int x=0;
	Node* temp=list->head;
	while (temp->next!=NULL){
		if(!strcmp(temp->Data, str)) {		//같으면 0을 반환하는 strcmp사용 if문에서 0은 거짓이므로 !붙여주었다.
			printf("%d index에서 ",temp->index);
			x++;
		}
		temp=temp->next;
	}
	printf("총 %d개\n", x);
	}
	return 0;
}

