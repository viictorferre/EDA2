#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h" // Include the header file containing the structs

#define MAX_SKILLS 50
#define MAX_WEAPONS 10
#define MAX_EQUIPPED_SKILLS 4
#define MAX_EQUIPPED_WEAPONS 1
#define ENEMIES 4
#define OPTIONS 5

// Queue Node
typedef struct QueueNode {
    int turnNumber;
    struct QueueNode* next;
} QueueNode;

// Queue
typedef struct {
    QueueNode *front, *rear;
    int turnCount;
} Queue;

// Function prototypes
Queue* createQueue();
void enqueue(Queue* queue);
int dequeue(Queue* queue);
int isEmpty(Queue* queue);

// Function definitions

// Create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    queue->turnCount = 0;
    return queue;
}

// Add a turn to the queue
void enqueue(Queue* queue) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->turnNumber = queue->turnCount + 1;
    newNode->next = NULL;
    
    // If queue is empty, set both front and rear to new node
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        // Add the new node at the end of queue and change rear
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    
    // Increment turn count
    queue->turnCount++;
}

// Remove a turn from the queue
int dequeue(Queue* queue) {
    // If queue is empty, return -1
    if (isEmpty(queue))
        return -1;
    
    // Store previous front and move front one node ahead
    QueueNode* temp = queue->front;
    int turnNumber = temp->turnNumber;
    queue->front = queue->front->next;
    
    // If front becomes NULL, then change rear also as NULL
    if (queue->front == NULL)
        queue->rear = NULL;
    
    free(temp);
    return turnNumber;
}

// Check if queue is empty
int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}
