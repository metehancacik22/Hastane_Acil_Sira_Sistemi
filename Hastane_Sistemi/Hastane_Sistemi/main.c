#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Hasta yapısı
typedef struct {
    char name[MAX_NAME_LENGTH];
    int priority; // 1: Acil, 2: Orta, 3: Düşük
    int id;
} Patient;

// Kuyruk düğümü
typedef struct Node {
    Patient patient;
    struct Node* next;
} Node;

// Kuyruk yapısı
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Kuyruğu başlatma
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Yeni hasta ekleme (önceliğe göre sıralı ekleme)
void enqueue(Queue* q, char* name, int priority, int id) {
    Node* temp = (Node*)malloc(sizeof(Node));
    strcpy(temp->patient.name, name);
    temp->patient.priority = priority;
    temp->patient.id = id;
    temp->next = NULL;
    
    if (q->front == NULL || priority < q->front->patient.priority) {
        temp->next = q->front;
        q->front = temp;
        if (q->rear == NULL) q->rear = temp;
        return;
    }
    
    Node* current = q->front;
    while (current->next != NULL && current->next->patient.priority <= priority) {
        current = current->next;
    }
    temp->next = current->next;
    current->next = temp;
    if (temp->next == NULL) q->rear = temp;
}

// Hastayı sıradan çıkarma
Patient dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("Kuyruk boş!\n");
        exit(1);
    }
    Node* temp = q->front;
    Patient patient = temp->patient;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return patient;
}

// Kuyruktaki hastaları listeleme
void displayQueue(Queue* q) {
    Node* temp = q->front;
    while (temp != NULL) {
        printf("Hasta: %s, Öncelik: %d, ID: %d\n", temp->patient.name, temp->patient.priority, temp->patient.id);
        temp = temp->next;
    }
}

int main() {
    Queue* emergencyQueue = createQueue();
    enqueue(emergencyQueue, "Ahmet", 2, 101);
    enqueue(emergencyQueue, "Mehmet", 1, 102);
    enqueue(emergencyQueue, "Ayşe", 3, 103);
    enqueue(emergencyQueue, "Fatma", 1, 104);
    
    printf("\nAcil Servis Hastaları:\n");
    displayQueue(emergencyQueue);
    
    printf("\nİşlem Görecek Hasta: %s\n", dequeue(emergencyQueue).name);
    
    printf("\nGüncellenmiş Kuyruk:\n");
    displayQueue(emergencyQueue);
    
    return 0;
}
