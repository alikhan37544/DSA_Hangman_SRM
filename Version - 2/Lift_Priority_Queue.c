#include <stdio.h>
#include <stdlib.h>

// Basic struct for the queue
typedef struct Node {
    int floor;
    char direction;
    int priority;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    int priority;
} PriorityQueue;

void initializeQueue(PriorityQueue* queue, int priority) {
    queue->front = NULL;
    queue->priority = priority;
}

void enqueue(PriorityQueue* queue, int floor, char direction, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->floor = floor;
    newNode->direction = direction;
    newNode->priority = priority;
    newNode->next = NULL;

    // Insert based on priority
    if (queue->front == NULL || priority < queue->front->priority) {
        newNode->next = queue->front;
        queue->front = newNode;
    } else {
        Node* current = queue->front;
        while (current->next != NULL && priority >= current->next->priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void dequeue(PriorityQueue* queue) {
    if (queue->front != NULL) {
        Node* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    } else {
        printf("Queue is empty.\n");
    }
}

void displayQueue(PriorityQueue* queue) {
    printf("Queue Priority: %d\n", queue->priority);
    Node* current = queue->front;
    while (current != NULL) {
        printf("Priority: %d, Floor: %d, Direction: %c\n", current->priority, current->floor, current->direction);
        current = current->next;
    }
}

int main() {
    int queuePriority;
    printf("Enter priority for the lift queue: ");
    scanf("%d", &queuePriority);

    PriorityQueue liftQueue;
    initializeQueue(&liftQueue, queuePriority);

    while (1) {
        int choice;
        printf("\n1. Add person to lift queue\n");
        printf("2. Remove person from lift queue\n");
        printf("3. Display lift queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int floor, priority;
                char direction;
                printf("Enter floor: ");
                scanf("%d", &floor);
                printf("Enter direction (U/D): ");
                scanf(" %c", &direction);
                printf("Enter priority (1-6): ");
                scanf("%d", &priority);
                
                if (priority < 1 || priority > 6) {
                    printf("Invalid priority. Please enter a priority between 1 and 6.\n");
                } else {
                    enqueue(&liftQueue, floor, direction, priority);
                }
                break;
            }
            case 2: {
                dequeue(&liftQueue);
                printf("Person removed from lift queue.\n");
                break;
            }
            case 3: {
                displayQueue(&liftQueue);
                break;
            }
            case 4: {
                // Free allocated memory before exiting
                Node* current = liftQueue.front;
                while (current != NULL) {
                    Node* temp = current;
                    current = current->next;
                    free(temp);
                }
                return 0;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
