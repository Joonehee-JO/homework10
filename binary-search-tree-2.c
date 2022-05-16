/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
   int key;
   struct node *left;
   struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE      20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE      20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();   //큐에 데이터를 팝하는 함수
void enQueue(Node* aNode);   //큐에 데이터를 푸쉬하는 함수

int initializeBST(Node** h);   //이진트리를 초기화하는 함수

/* functions that you have to implement */
void recursiveInorder(Node* ptr);     /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);             /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();   //스택에 들어있는 노드의 값을 출력하는 함수



int main()
{
   char command;
   int key;
   Node* head = NULL;

   printf("[----- [Cho Joon Hee]  [2017038076] -----]\n");

   do{
      printf("\n\n");
      printf("----------------------------------------------------------------\n");
      printf("                   Binary Search Tree #2                        \n");
      printf("----------------------------------------------------------------\n");
      printf(" Initialize BST       = z                                       \n");
      printf(" Insert Node          = i      Delete Node                  = d \n");
      printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
      printf(" Level Order (Queue)  = l      Quit                         = q \n");
      printf("----------------------------------------------------------------\n");

      printf("Command = ");   //커맨드 입력
      scanf(" %c", &command);

      switch(command) {
      case 'z': case 'Z':
         initializeBST(&head);   //트리 초기화
         break;
      case 'q': case 'Q':
         freeBST(head);      //종료 전 메모리 반납
         break;
      case 'i': case 'I':
         printf("Your Key = ");
         scanf("%d", &key);
         insert(head, key);   //트리에 입력한 값을 갖는 노드 삽입 
         break;
      case 'd': case 'D':
         printf("Your Key = ");
         scanf("%d", &key);
         deleteNode(head, key);   //트리에 입력한 값을 갖는 노드 삭제
         break;

      case 'r': case 'R':
         recursiveInorder(head->left);   //재귀적 중위 순회를 통하여 트리의 노드들 출력
         break;
      case 't': case 'T':
         iterativeInorder(head->left);   //반복 중위 순회를 통하여 트리의 노드 출력
         break;

      case 'l': case 'L':
         levelOrder(head->left);      //레벨순서 순회를 통해 트리의 노드 출력
         break;

      case 'p': case 'P':
         printStack();      //현재 스택에 들어있는 노드의 값 출력
         break;

      default:
         printf("\n       >>>>>   Concentration!!   <<<<<     \n");
         break;
      }

   }while(command != 'q' && command != 'Q');

   return 1;
}

int initializeBST(Node** h) {   //트리를 초기화 하는 함수

   /* if the tree is not empty, then remove all allocated nodes from the tree*/
   if(*h != NULL)      //메모리를 할당받았다면 freeBST함수 호출
      freeBST(*h);

   /* create a head node */
   *h = (Node*)malloc(sizeof(Node));   //헤드노드 생성
   (*h)->left = NULL;   /* root */
   (*h)->right = *h;
   (*h)->key = -9999;

   top = -1;         //스택의 초기상태 / 반복적중위순회를 위해 사용하는 자료구조

   front = rear = -1;   //원형큐의 초기상태 / 레벨오더순회를 위해 사용하는 자료구조

   return 1;
}



void recursiveInorder(Node* ptr)   //재귀적 중위 순회를 통하여 트리의 노드를 출력하는 함수
{
   if(ptr) {   //ptr이 존재한다면
      recursiveInorder(ptr->left);   //먼저 ptr이 가리키는 노드의 왼쪽을 인자로 넘겨줌(왼쪽 끝까지 내려감)
      printf(" [%d] ", ptr->key);      //해당 노드의 key값 출력
      recursiveInorder(ptr->right);   //그 뒤 오른쪽 노드로 이동
   }
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)   //반복적 중위 순회를 통해 트리의 노드들을 출력하는 함수
{
   for(;;)   {   //무한루프돌면서
      for(; node; node = node->left)   //node가 null이 아닐 시 스택에 푸쉬 / 왼쪽 자식노드가 존재한다면 끝까지 이동
         push(node);      //스택에 삽입
      node = pop();      //스택의 탑을 팝함

      if(!node) break;   //스택에서 팝한것이 NULL이라면 스택에 아무것도 존재하지 않는 것이므로 루프탈출
      
      printf(" [%d] ", node->key);   //팝한것이 NULL이 아니라면 팝한 값을 출력
      node = node->right;      //오른쪽 자식 노드로 이동, 중위순회를 위함
   }
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)   //레벨순서 순회를 통해 트리의 노드들을 출력하는 함수
{
   if(!ptr) return;   //트리가 비어있을 경우 함수종료
   enQueue(ptr);      //ptr이 가리키고 있는 값을 큐에 푸쉬 / 루트노드의 값

   for(;;){   //무한루프를 돌면서 같은 레벨의 노드를 출력
      ptr = deQueue();   //큐의 첫번째 원소를 팝함
      if(ptr){      //ptr이 가리키는 노드가 존재한다면
         printf(" [%d] ", ptr->key);   //ptr이 가리키고 있는 노드의 값 출력
         if(ptr->left)         //해당노드의 왼쪽자식노드가 존재한다면
            enQueue(ptr->left);   //왼쪽자식노드를 큐에 푸쉬
         if(ptr->right)         //해당노드의 오른쪽자식노드가 존재한다면
            enQueue(ptr->right); //오른쪽자식노드를 큐에 푸쉬
      }
      else break;   //ptr이 null이라면 루프탈출
   }
}


int insert(Node* head, int key)   //입력받은 값을 갖는 노드를 삽입하는 함수
{
   Node* newNode = (Node*)malloc(sizeof(Node));   //삽입할 노드와 필드값 초기화
   newNode->key = key;
   newNode->left = NULL;
   newNode->right = NULL;

   if (head->left == NULL) {   //트리가 비어있을 경우
      head->left = newNode;   //삽입노드를 루트노드로 만듦
      return 1;
   }

   /* head->left is the root */
   Node* ptr = head->left;      //트리가 비어있지 않다면 ptr이 트리의 루트노드를 가리키도록함

   Node* parentNode = NULL;   //부모노드를 가리킬 포인터
   while(ptr != NULL) {      //ptr이 가리키는 노드가 존재한다면

      /* if there is a node for the key, then just return */
      if(ptr->key == key) return 1;   //입력한 값이 이미 존재한다면 함수종료

      /* we have to move onto children nodes,
       * keep tracking the parent using parentNode */
      parentNode = ptr;   //현재 탐색할 노드의 위치를 변경시키기 전 현재노드를 부모노드로 만듦

      /* key comparison, if current node's key is greater than input key
       * then the new node has to be inserted into the right subtree;
       * otherwise the left subtree.
       */
      if(ptr->key < key)   //값을 비교하여 입력한 값이 클 경우
         ptr = ptr->right;   //오른쪽 자식노드로 이동
      else            //작을 경우
         ptr = ptr->left;   //왼쪽 자식노드로 이동
   }

   /* linking the new node to the parent */
   //반복문을 빠져나와 노드를 삽입하는 과정, node는 NULL값을 가짐
   if(parentNode->key > key)      //입력된 값이 부모노드의 key보다 클 경우
      parentNode->left = newNode;   //부모노드의 오른쪽 자식노드에 삽입
   else                     //작을 경우
      parentNode->right = newNode;//부모노드의 왼쪽 자식노드에 삽입
   return 1;
}


int deleteNode(Node* head, int key)   //입력한 값을 갖는 노드를 삭제하는 함수
{
	if (head == NULL) {   //헤더노드가 메모리를 할당받지 못했을 경우
		printf("the momory is not allocated\n");
		return 1;
	}

	if (head->left == NULL) {   //트리에 노드가 존재하지 않을 경우
		printf("the tree is empty\n");
		return 1;
	}

	Node* node = head->left;   //진행할 노드를 가리킬 포인터
	Node* parent = NULL;      //부모노드를 가리킬 포인터

	while(node != NULL){   //node가 가리키는 노드가 존재한다면
		if(node->key == key) break;   //입력한 값을 갖는 노드를 찾은 경우 루프탈출

		parent = node;      //parent가 현재 노드를 가리키도록 하고

		if(node->key > key)   //node의 값이 입력한 값보다 클 경우
			node = node->left;   //왼쪽으로 이동
		else            //node의 값이 입력한 값보다 작을 경우
			node = node->right;   //오른쪽으로 이동
	}

	if(node == NULL){   //입력한 값을 갖는 노드를 찾지 못했을 경우
		printf("the node with that key does not exist in the tree\n");   
		return 1;
	}

	//입력한 값을 갖는 노드를 찾았을 경우
	if(node->left == NULL && node->right == NULL){   //해당 노드가 리프노드라면
		if(parent != NULL) {     //parent가 가리키는 노드가 존재할 경우(찾은노드가 루트노드가 아닐경우)
			if(parent->left == node)   //찾은노드가 부모노드의 왼쪽에 있다면
				parent->left = NULL;   //해당 링크필드 NULL로 초기화
			else                  //찾은노드가 부모노드의 오른쪽에 있다면
				parent->right = NULL;   //해당 링크필드 NULL로 초기화
		} else {                  //찾은노드가 루트노드라면
			head->left = NULL;         //헤더노드의 왼쪽자식을 가리키는 값 NULL로 초기화
		}

		free(node);         //변경해야하는 것들을 바꿔주고 해당 노드 삭제
		return 1;
	}

	if ((node->left == NULL || node->right == NULL)){   //해당노드의 차수가 1이라면 앞에서 리프노드의 경우를 찾았기에
		Node* child;      //삭제할 노드의 자식노드를 가리킬 포인터

		if (node->left != NULL)   //하나의 자식노드가 왼쪽에 위치할 경우
			child = node->left;   //child가 왼쪽 자식 노드를 가리키도록함
		else               //하나의 자식노드가 오른쪽에 위치할 경우
			child = node->right;   //child가 오른쪽 자식 노드를 가리키도록함

		if(parent != NULL){      //찾은 노드가 루트노드가 아닐경우
			if(parent->left == node)   //찾은 노드가 부모노드의 왼쪽에 존재할 경우
				parent->left = child;   //부모노드의 왼쪽자식을 삭제할 노드의 자식노드로 변경(부모노드->삭제노드의 자식노드)
			else                  //찾은 노드가 부모노드의 오른쪽에 존재할 경우
				parent->right = child;   //부모노드의 오른쪽자식을 삭제할 노드의 자식노드로 변경
		} else {   //찾은 노드가 루트노드일 경우
			head->left = child;   //루트노드 삭제노드의 자식노드로 변경
		}

		free(node);   //찾은 노드 삭제
		return 1;
	}

	if(node->left && node->right){   //해당노드의 차수가 2라면(자식노드 2개를 갖는 노드일시)
		Node* minNode;   //삭제하고자 하는 노드의 오른쪽 서브트리 중 가장 작은 노드를 가리킬 포인터
		parent = node;      //해당 노드의 부모노드를 가리킬 포인터

		minNode = node->right;   

		while(minNode->left != NULL){   //가장 작은 노드를 찾기 위한 루프(가장 작은 노드는 오른쪽 서브트리 중 가장 왼쪽에 있는 노드)
			parent = minNode;         
			minNode = minNode->left;
		}

		if (parent->right == minNode)   //가장 작은 노드가 부모노드의 오른쪾에 위치할 경우
			parent->right = minNode->right;   //가장 작은 노드를 삭제할 것이기에 부모의 오른쪽 노드를 가장작은 노드의 오른쪽 자식노드로 변경(왼쪽 자식노드가 존재할 경우 해당 노드가 가장 작은 값이므로 성립하지 않음)
		else                     //부모노드의 왼쪽노드가 가장 작은 노드라면
			parent->left = minNode->right;   //부모의 왼쪽 노드를 가장 작은 노드의 오른쪽으로 변경
		
		node->key = minNode->key;   //기존 삭제하고자 하는 노드의 값을 가장 작은 노드의 값으로 변경, 기존 삭제해야하는 노드 대신 가장 작은 노드를 삭제
		
		free(minNode);      //가장 작은 노드의 값은 삭제하고자 찾은 노드의 값으로 변경했기에 대체자 노드 삭제
		return 1;
	}
}


void freeNode(Node* ptr)   //트리의 노드들을 재귀적으로 접근하여 해제하는 함수
{
	if(ptr) {            //ptr이 가리키는 노드가 존재한다면
		freeNode(ptr->left);   //ptr이 가리키는 노드의 왼쪽 자식 노드로 이동
		freeNode(ptr->right);   //ptr이 가리키는 노드의 오른쪽 자식노드로 이동
		free(ptr);            //마지막으로 ptr이 가리키는 노드 메모리 반납
	}
}

int freeBST(Node* head)      //트리를 구성하기위해 사용한 메모리를 반납하는 함수
{

	if(head->left == head)   //자식노드들이 없다면
	{
		free(head);         //헤드노드 메모리 반납 후 함수종료
		return 1;
	}

	Node* p = head->left;   //루트노드부터 시작

	freeNode(p);      //freeNode함수 호출하여 트리의 노드들 메모리 해제

	free(head);         //마지막으로 헤드노드 메모리 해제
	return 1;
}


Node* pop()   //스택의 탑을 팝하는 함수
{
	if(top == -1) return NULL;   //스택의 top이 -1일 경우(스택이 비어있을 경우) NULL값 리턴

	return stack[top--];   //그렇지 않다면 스택의 탑을 팝함, 팝하므로 top을 줄임
}

void push(Node* aNode)   //스택에 값을 푸쉬하는 함수
{   
	if(top == 19) return;   //스택이 꽉 찼을 경우 함수종료

	stack[++top] = aNode;   //스택에 값(노드)을 푸쉬함
}

void printStack()   //스택에 들어있는 노드의 값을 출력하는 함수
{
	if(top == -1)   //스택이 비어있을 경우
		printf("current stack is empty\n");
	
	for(int i = top; i>=0; i--){   //반복문을 통해 스택에 들어있는 노드의 값 출력
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

Node* deQueue()   //큐에 데이터를 팝하는 함수
{
	if (front == rear) {   //현재 큐가 비어있다면
		//printf("current Queue is empty\n" );
		return NULL;
	}
	else{         //큐가 비어있지 않다면 
		front = (front + 1) % MAX_QUEUE_SIZE;   //모듈러 연산을 통해 front값 변경(원형큐형태)
		return queue[front];         //팝하여 원소를 빼냄
	}
}

void enQueue(Node* aNode)   //큐에 값을 푸쉬하는 함수
{
	if((rear+1) % MAX_QUEUE_SIZE == front){   //모듈러연산을 통해 큐가 꽉차있는지 체크
		printf("current Queue is Full\n");   //꽉차있다면 함수종료
		return;
	}
	else {         //큐가 비어있다면
		rear = (rear+1) % MAX_QUEUE_SIZE;   //모듈러연산을 통하여 rear값 변경, 큐가 원형큐형태를 띔
		queue[rear] = aNode;            //큐에 푸쉬
	}
}




