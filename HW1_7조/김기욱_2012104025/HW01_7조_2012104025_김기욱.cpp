<<<<<<< HEAD
asdf
=======
/*
2012104025 김기욱
window에서 visual studio2015로 작성
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

struct node {
	struct node *next;
	int index;
	char *word;
}typedef mnode;
struct {
	int size;
	mnode *start;
	mnode *end;
}typedef mlist;

//함수 선언부
mlist* make_list();
mnode* make_node(char* input);
void add_node(mlist* list, mnode* node);

void main() {
	mlist *list = make_list();
	mnode *node;
	int j;
	FILE *f;
	char buffer[1024 * 10];
	char *word;
	//파일 경로는 기본 사용.
	printf("input.txt 열기 시도\n");
	f = fopen("input.txt", "r");
	if (f == NULL) {
		printf("파일 없음.\n프로그램 종료\n");
		return;
	}
	printf("열기 성공\n");
	//파일 입력
	while (!feof(f)) {
		//1줄단위로 입력받는다. 10k가 통째로 한줄일 리는 없으니 10k단위로 받음.
		//문단구성으로 인해 10k동안 줄바꿈이 없다면 오류를 일으키지만 처리하지 않음.
		fgets(buffer, 1024 * 10, f);
		//아래와 같은 것들이 나오면 잘라서 word에 넣는다. 아스키가 아닌 문자열을 치환하면 한글이 깨지는 문제가 있으므로 아스키만 처리.
		word = strtok(buffer, " <>[]():;&*,.?!`'\"");
		//word가 null을 반환하기 전까지 계속 잘라서 노드로 만든다.
		while (word != NULL) {
			node = make_node(word);
			add_node(list, node);
			word = strtok(NULL, " ,.?!`'\"");
		}
	}
	fclose(f);
	printf("리스트 제작 종료\n총 %d개의 노드\n", list->size);
	//list 제작이 끝났다. node를 list의 첫 노드로 만들어서
	printf("검색어 : ");
	scanf("%s", buffer);
	//입력과정에서 헛짓 방지
	word = strtok(buffer, " <>[]():;&*,.?!`'\"");
	//loop는 list에 들어있는 노드의 횟수만큼 돌아간다.
	for (j = 0, node = list->start; node != NULL; node = node->next) {
		//substring 검색을 할 필요가 없으므로 strcmp를 사용한다.
		//stricmp를 사용했기에 Apple와 apple는 같은 단어로 판정된다.
		if (!stricmp(node->word, word)) {
			printf("%d 위치에서 %s 발견\n", node->index, buffer);
			j++;
			if (j == 21) {
				printf("18503 : %s'\n18504 : %s'\n18505 : %s'\n18506 : %s'\n", node->next->word, node->next->next->word, node->next->next->next->word, node->next->next->next->next->word);
			}
		}
	}
	printf("총 %d회 %s 발견\n", j, buffer);

	return;
}
//list를 만드는 함수
mlist* make_list() {
	mlist *list = (mlist*)malloc(sizeof(mlist));
	list->start = NULL;
	list->end = NULL;
	list->size = 0;
	return list;
}
//list에 node를 연결하는 함수
void add_node(mlist* list, mnode* node) {
	if (list->start == NULL) {
		list->start = list->end = node;
		list->size = 1;
	}
	else {
		list->end->next = node;
		list->end = node;
		list->size++;
	}
	list->end->index = list->size;
	return;
}
//문자를 입력받아 node에 넣는 함수
mnode* make_node(char* input) {
	mnode *node;
	int word_size;
	node = (mnode*)malloc(sizeof(mnode));
	word_size = strlen(input);
	node->index = -1;
	//word사이즈가 가변적이기에 size를 입력받고, '\0'를 넣기 위해 size+1을 malloc한다.
	node->word = (char*)malloc(sizeof(char)*(word_size + 1));
	strcpy(node->word, input);
	node->next = NULL;
	return node;
}
>>>>>>> a0f3377fb7017aa2c9102fa1c15db5cfe9dd6a10
