typedef struct queue_node {
    int num_people;
    struct queue_node* next;
} queue_node;

typedef struct {
    queue_node* front;
    queue_node* rear;
} queue;

// Initialize an empty queue
void init_queue(queue* q) {
    q->front = q->rear = NULL;
}

// Check if the queue is empty
int is_empty(queue* q) {
    return q->front == NULL;
}

// Enqueue a customer into the queue
void enqueue(queue* q, int num_people) {
    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->num_people = num_people;
    new_node->next = NULL;
    if (is_empty(q)) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

// Dequeue a customer from the queue
int dequeue(queue* q) {
    if (is_empty(q)) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    queue_node* temp = q->front;
    int data = temp->num_people;
    q->front = q->front->next;
    free(temp);
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return data;
}

// Display the customers in the queue
void display_queue(queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Waitlist:\n");
    queue_node* current = q->front;
    while (current != NULL) {
        printf("Group of %d\n", current->num_people);
        current = current->next;
    }
}

