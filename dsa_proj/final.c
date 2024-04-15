#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50


double totalincome = 0;
/*all queue dunctions for waitlists */
typedef struct queue_node {
    int node_number;  // New field to store the node number
    int num_people;
    struct queue_node* next;
} queue_node;

typedef struct {
    queue_node* front;
    queue_node* rear;
    int node_count; // To keep track of the number of nodes
} queue;

// Initialize an empty queue
void init_queue(queue* q) {
    q->front = q->rear = NULL;
    q->node_count = 0; // Initialize node count
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
    new_node->node_number = q->node_count + 1; // Assign node number
    q->node_count++; // Increment node count
    new_node->num_people = num_people;
    new_node->next = NULL;
    if (is_empty(q)) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

int dequeue_waitlist(queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return -1; 
    }

    int num_people = q->front->num_people;
    queue_node* temp = q->front;
    q->front = q->front->next;
    free(temp);

    if (q->front == NULL) {
        q->rear = NULL;
    }
    return num_people;
}


// Display the customers in the queue along with node numbers
void display_queue(queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Waitlist:\n");
    queue_node* current = q->front;
    while (current != NULL) {
        printf("Waitlist number: %d: Group of : %d\n", current->node_number, current->num_people);
        current = current->next;
    }
}

/*end of queue functions for waitlists*/


typedef struct queue_nodec {
    char *itemname;
    struct queue_nodec* next;
} queue_nodec;

typedef struct {
    queue_nodec* front;
    queue_nodec* rear;
} queuec;

void init_queuec(queuec* q) {
    q->front = q->rear = NULL;
}

int is_emptyc(queuec* q) {
    return q->front == NULL;
}

void enqueuec(queuec* q, char order_name[]) {
    queue_nodec* new_node = (queue_nodec*)malloc(sizeof(queue_nodec));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->itemname = (char*)malloc(strlen(order_name) + 1); // Allocate memory for the string
    strcpy(new_node->itemname, order_name); // Copy the string content
    new_node->next = NULL;
    if (is_emptyc(q)) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}


void dequeuec(queuec* q) {
    if (is_emptyc(q)) {
        printf("Queue is empty\n");
        return;
    }

    char* item_name = q->front->itemname;
    queue_nodec* temp = q->front;
    q->front = q->front->next;
    free(temp);
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    printf("Delivered: %s\n", item_name);
}


struct MenuItem {
    char name[MAX_NAME_LENGTH];
    double price;
};


typedef struct node{
    char *ordername;
    struct node* next;
    double price;
}node;

typedef node* list;//taking customer's order in LL

void init_list(list *head){
    *head = NULL;
}

void create_node(list *head, char ordern[], double p) {
    node *nn = (node*)malloc(sizeof(node));
    nn->ordername = (char*)malloc(strlen(ordern) + 1); // Allocate memory for the string
    strcpy(nn->ordername, ordern); // Copy the string content
    nn->price = p;
    nn->next = NULL;
    if(*head == NULL){
        *head = nn;
        return;
    }
    node *temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = nn;
}

typedef struct table {
    int occupied;//indicates if table is occupied
    list order;
    
}table;


typedef struct section {
    table* t; //tables in each section
    int no_of_tables;
    int chairs;// no. of chair each table has
} section;

typedef struct restaurant {
    int no_of_sections;
    section* array_of_all_sections;
} restaurant;

void init_section(section* s, int total_tables_in_section, int chair) {
    s->no_of_tables = total_tables_in_section;
    s->chairs = chair;
    s->t = (table*)malloc(sizeof(table) * total_tables_in_section);
    for (int i = 0; i < total_tables_in_section; i++) {
        s->t[i].occupied = 0;
    }
}
void init_restaurant(restaurant* r, int sections) {
    r->no_of_sections = sections;
    r->array_of_all_sections = (section*)malloc(sizeof(section) * sections);
    int i = 1;
    int t = sections;
    int tb, c;
    while (t) {
        printf("\nEnter no.of tables and enter no. of chairs for section %d:  ", i);
        scanf("%d%d", &tb, &c);
        init_section(&(r->array_of_all_sections[i - 1]), tb, c);
        i++;
        t--;
    }
}



void take_the_order(restaurant *res,int sec , int t1 , queuec* chefq){
    if(sec > res->no_of_sections){
        printf("section not in restaurant\n");
        return;
    }
    if (t1 < 1 || t1 > res->array_of_all_sections[sec - 1].no_of_tables || res->array_of_all_sections[sec - 1].t[t1 - 1].occupied == 0) {
        printf("Table not in section or unoccupied\n");
        return;
    }

    int i = 0;
    if(res->array_of_all_sections[sec - 1].t[t1].order == NULL)
        init_list(&(res->array_of_all_sections[sec - 1].t[t1].order));
    
    int c;

    FILE* fp = fopen("menu.csv", "r");//is causing error

    
    if (!fp) {
        printf("Error opening the file.\n");
        return ;
    }
    
    struct MenuItem menu[MAX_ITEMS];
    int itemCount = 0;
    int serialNumber; // Added to store the serial number of the item
    // Read menu items from the CSV file
    while (itemCount < MAX_ITEMS && fscanf(fp, "%d,%49[^,],%lf\n", &serialNumber, menu[itemCount].name, &menu[itemCount].price) == 3) {
        printf("%-5d %-30s %.2lf\n", itemCount + 1, menu[itemCount].name, menu[itemCount].price); // Printing serial number and menu item
        itemCount++;
    }

    fclose(fp);

    printf("Press -1 to stop\n");
    while(1){
            printf("Enter item no. to order: ");
            scanf("%d" , &c);
            if(c == -1)
                break;
            create_node(&(res->array_of_all_sections[sec - 1].t[t1].order), menu[c - 1].name, menu[c - 1].price);
            enqueuec(chefq ,menu[c-1].name);
            
        }
    printf("%d\n",i);
    i++;

    printf("Chef is delivering the order...\n");
}



void occupy_tables(restaurant* r, int num_people, queue *q) {
    // int canBseated =0;
    
    int temp1, temp2;
    int flag = 0;
    temp2 = 10000;
    int chosen_section_index = -1;
    int table;
    // Find section with minimum number of chairs greater than or equal to num_people
    for (int i = 0; i < (*r).no_of_sections; i++) {
        temp1 = (*r).array_of_all_sections[i].chairs;
        if (temp1 >= num_people && temp2 > temp1) {
            temp2 = temp1;
            table = 1;
            chosen_section_index = i;
        }
    }

    // If no suitable section with single tables is found, check for sections with tables that can accommodate twice the number of people
    if (chosen_section_index == -1) {
        for (int i = 0; i < (*r).no_of_sections; i++) {
            temp1 = (*r).array_of_all_sections[i].chairs * 2;
            if (temp1 >= num_people && temp2 > temp1) {
                temp2 = temp1;
                chosen_section_index = i;
                table = 2;
            }
        }
    }

    if(chosen_section_index == -1){
        printf("Sorry, Cannot be seated\n");
    }

    // If a suitable section is found, occupy the tables
    if (chosen_section_index != -1) {
        section* chosen_section = &((*r).array_of_all_sections[chosen_section_index]);
        //no. of chairs are either required for 1 table or 2 tables
        if (table == 1) {
            for (int j = 0; j < chosen_section->no_of_tables; j++) {
                if (chosen_section->t[j].occupied == 0) {
                    chosen_section->t[j].occupied = 1;
                    flag =1;
                    printf("Table %d allocated in section %d \n", j + 1,chosen_section_index+1);
                    break;
                }
            }
        }
        else { //tables req = 2
            for (int j = 0; j < chosen_section->no_of_tables; j++) {
                if (chosen_section->t[j].occupied == 0) {
                    for (int k = j+1; k < chosen_section->no_of_tables; k++) {
                        if (chosen_section->t[k].occupied == 0) {
                            chosen_section->t[j].occupied = 1;
                            chosen_section->t[k].occupied = 1;
                            printf("Table %d allocated\n", j + 1);
                            printf("Table %d allocated\n", k + 1);
                            printf("Tables occupied successfully in section %d!\n", chosen_section_index + 1);
                            flag =1;
                            break;
                            // return; // No need to continue after assigning tables
                        }
                    }
                }
                break;
            }
        }
    }
    //else { printf("Sorry, there are not enough seats available in any section.\n");}
    if(flag == 0){

        printf("Sorry, there are not enough seats available in any section.\n");
        enqueue(q,num_people);
        display_queue(q);

    }
    
}

void deoccupy_tables(restaurant *r , int sec , int t1 ,queuec *chefq, queue *waitlist){
    if(sec > r->no_of_sections){
        printf("section not in restaurant\n");
        return;
    }
    if(t1 > r->array_of_all_sections[sec-1].no_of_tables){
        printf("Table not in section\n");
        return;
    }
    r->array_of_all_sections[sec-1].t[t1].occupied=0;
    double bill = 0;
    node *temp = r->array_of_all_sections[sec-1].t[t1].order;
    printf("Bill\n");
    while (temp){
        printf("%s\t%.2f\n" , temp->ordername , temp->price);
        bill += temp->price;
        node* to_free = temp;
        temp = temp->next;
        free(to_free->ordername); // Free the allocated memory for order name
        free(to_free);
    }
    printf("Total money to be paid is %f\nThankyou for visiting, Comeagain!" , bill);
    totalincome += bill;

    int waiting_group_size = dequeue_waitlist(waitlist);
    if (waiting_group_size != -1) {
        occupy_tables(r, waiting_group_size, waitlist);
    }
    // return ;
    
}


struct Item {
    int id;
    char name[50];
    float price;
};


void readItems(struct Item items[]) {
    FILE *file = fopen("shoppinglist.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[100];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%f", &items[count].id, items[count].name, &items[count].price);
        count++;
    }

    fclose(file);
}

// Function to print items and get user input
float chefshops() {
    struct Item items[31];
    readItems(items);
    int itemId,itemCount = 31;
    float totalCost = 0.0;

    printf("Available items:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d. %s - %.2f\n", items[i].id, items[i].name, items[i].price);
    }

    printf("\nEnter the item IDs you want to buy (separated by spaces), 0 to finish: ");
    while (1) {
        scanf("%d", &itemId);
        if (itemId == 0) {
            break;
        }
        if (itemId < 1 || itemId > 31) {
            printf("Invalid item ID. Please enter a valid ID.\n");
            continue;
        }
        totalCost += items[itemId - 1].price;
    }

    return totalCost;
}

int main() {
    restaurant r;
    queue waitlist;
    queuec chefq;
    int section, p, tableno, spending = 0;
    int choice;

    printf("Initializing the restaurant...\n");
    printf("Enter the number of sections: ");
    scanf("%d", &section);
    init_restaurant(&r, section);
    init_queue(&waitlist);
    init_queuec(&chefq);
    
    do {
        printf("\n--- Menu ---\n");
        printf("1. Occupy Tables\n");
        printf("2. Take Order\n");
        printf("3. Deoccupy Tables\n");
        printf("4. View Total Sales\n");
        printf("5. Chef delivers food\n");
        printf("6. Chef buys groceries\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of people in a group: ");
                scanf("%d", &p);
                occupy_tables(&r, p, &waitlist);
                break;
            case 2:
                printf("Enter section to order from: ");
                scanf("%d", &section);
                printf("Enter table no to order from: ");
                scanf("%d", &tableno);
                take_the_order(&r, section, tableno, &chefq);
                
                break;
            case 3:
                printf("Enter section to deoccupy: ");
                scanf("%d", &section);
                printf("Enter table no to deoccupy: ");
                scanf("%d", &tableno);
                deoccupy_tables(&r, section, tableno, &chefq, &waitlist);
                // int watingppl = 0;
                // watingppl = dequeue_waitlist(&waitlist);
                // if (watingppl != -1){
                //     occupy_tables(&r, watingppl, &waitlist);
                // }
                break;
            case 4:
                printf("Viewing total sales: %f\n", totalincome - spending);
                break;
            case 5:
                printf("Delivering food\n");
                dequeuec(&chefq);
                break;
            case 6:
                spending += chefshops();
                break;
            case 7:
                printf("Restaurant Closed.Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
    } while (choice != 7);

    return 0;
}
