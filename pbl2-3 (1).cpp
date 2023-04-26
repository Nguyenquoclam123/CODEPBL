#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} Node;

Node *readList(FILE *fp, int M) {
    Node *head = NULL;
    Node *tail = NULL;
    int ptu;
    for (int i = 0; i < M; i++) {
        if (fscanf(fp, "%d", &ptu) != 1) {
            break;
        }
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = ptu;
        newNode->next = NULL;
        newNode->prev = tail;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

void chenptu(Node **head, int position, int ptu) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = ptu;

    if (*head == NULL || position == 0) {
        newNode->next = *head;
        newNode->prev = NULL;
        if (*head != NULL) {
            (*head)->prev = newNode;
        }
        *head = newNode;
        return;
    }

    Node *current = *head;
    for (int i = 0; i < position - 1 && current->next != NULL; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

void writeList(FILE *fp, Node *head) {
    while (head != NULL) {
        fprintf(fp, "%d ", head->data);
        head = head->next;
    }
}

int main() {
FILE *inputFile = fopen("DAYSO.IN.txt", "r");
if (inputFile == NULL) {
printf("Khong the mo tep DAYSO.IN\n");
return -1;
}

int N;
fscanf(inputFile, "%d", &N);

Node **lists = (Node **)malloc(N * sizeof(Node *));
for (int i = 0; i < N; i++) {
lists[i] = readList(inputFile, N - 1);
}

fclose(inputFile);

int ptu;
printf("Nhap gia tri phan tu can chen: ");
scanf("%d", &ptu);

for (int i = 0; i < N; i++) {
chenptu(&lists[i], (N - 1) / 2, ptu);
printList(lists[i]);
printf("\n");
}

FILE *outputFile1 = fopen("RESULT1.OUT.txt", "w");
if (outputFile1 == NULL) {
printf("Khong the mo tep RESULT1.OUT\n");
return -1;
}

for (int i = 0; i < N; i++) {
writeList(outputFile1, lists[i]);
fprintf(outputFile1, "\n");
}

fclose(outputFile1);
return 0;
}
