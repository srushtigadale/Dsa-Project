#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50
double totalincome = 0;
typedef struct queue_node {
    int num_people;
    struct queue_node* next;
} queue_node;
typedef struct queue_nodec {
    char *itemname;
    struct queue_nodec* next;
} queue_nodec;
typedef struct {
    queue_node* front;
    queue_node* rear;
} queue;
struct MenuItem {
    char name[MAX_NAME_LENGTH];
    double price;
};
typedef struct {
    queue_nodec* front;
    queue_nodec* rear;
} queuec;
typedef struct node{
    char *ordername;
    struct node* next;
    double price;
}node;
typedef node* list;//taking customer's order in LL
typedef struct table {
    int occupied;
    list order;
    //indicates if table is occupied
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
void init_list(list *head){
    *head = NULL;
}
void init_queuec(queuec* q) {
    q->front = q->rear = NULL;
}
void init_queue1(queue* q) {
    q->front = q->rear = NULL;
}
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
void create_node(list *head ,char ordern[] , double p ){
    // printf("I'm here");
    node *nn = (node*)malloc(sizeof(node));
    nn->ordername = (char*)malloc(strlen(ordern));
    nn->ordername = ordern;
    nn->price = p;
    nn->next = NULL;
    if(*head == NULL){
        *head = nn;
        return;
    }
    node *temp = *head;
    while(temp->next != NULL){
        // printf("srush");
        temp = temp->next;
    }
    temp->next = nn;
}
int is_empty(queuec* q) {
    return q->front == NULL;
}
int is_empty1(queue* q) {
    return q->front == NULL;
}
int dequeue(queue* q) {
    if (is_empty1(q)) {
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
void enqueuec(queuec* q, char order_name[]) {
    queue_nodec* new_node = (queue_nodec*)malloc(sizeof(queue_nodec));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->itemname =(char*)malloc(strlen(order_name));
    new_node->itemname = order_name;
    new_node->next = NULL;
    if (is_empty(q)) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

void take_the_order(section *sec , int t1 , queuec* chefq){
    init_list(&sec->t[t1].order);
    int c;
    FILE* fp = fopen("menu.csv", "r");
    if (!fp) {
        printf("Error opening the file.\n");
        return ;
    }
    struct MenuItem menu[MAX_ITEMS];
    int itemCount = 0;
// Read menu items from the CSV file
while (itemCount < MAX_ITEMS && fscanf(fp, "%49[^,],%lf\n", menu[itemCount].name, &menu[itemCount].price) == 2) {
    //printf("Read item: %s, %.2lf\n", menu[itemCount].name, menu[itemCount].price); // Debug statement
    itemCount++;
}
// ...
fclose(fp);
// Print the menu
printf("Today's Menu:\n");
printf("\n");
for (int i = 0; i < itemCount; i++) {
        printf("%-30s %.2lf\n", menu[i].name, menu[i].price);
        printf("\n");
    }
while(1){
        printf("Enter the number of the item you want to order. Press -1 to stop");
        scanf("%d" , &c);
        if(c == -1)
            break;
        create_node(&sec->t[t1].order,menu[c-1].name,menu[c-1].price);
        // printf("hey");
        enqueuec(chefq ,menu[c-1].name);
        // printf("yo");
        // printf("order is - %s , %d\n" , menu[c-1].name ,(int) menu[c-1].price);
    }
}

void deoccupy_tables(restaurant *r , section *sec , int t1 ,queuec *chefq, queue *waitlist){
    // sec->
    sec->t[t1].occupied = 0;
    double bill = 0;
    node *temp = sec->t[t1].order;
    printf("Bill\n");
    while (temp){
        printf("%s\t%f\n" , temp->ordername , temp->price);
        bill += temp->price;
        temp = temp->next;
    }
    printf("Total money to be paid is %f\nThankyou for visiting, Comeagain!" , bill);
    totalincome += bill;
    // return ;
    
}
void occupy_tables(restaurant* r, int num_people,queuec *chefq , queue *waitlist) {
    int n;
    int temp1, temp2;
    int flag = 0;
    temp2 = 10000;
    int chosen_section_index = -1;
    int table;
    // Find section with minimum number of chairs greater than or equal to num_people
    for (int i = 0; i < (*r).no_of_sections; i++){
        temp1 = (*r).array_of_all_sections[i].chairs;
        if (temp1 >= num_people && temp2 > temp1){
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

    // If a suitable section is found, occupy the tables
    if (chosen_section_index != -1) {
        section* chosen_section = &((*r).array_of_all_sections[chosen_section_index]);
        //no. of chairs are either required for 1 table or 2 tables
        if (table == 1) {
            for (int j = 0; j < chosen_section->no_of_tables; j++) {
                if (chosen_section->t[j].occupied == 0) {
                    chosen_section->t[j].occupied = 1;
                    flag =1;
                    printf("Table %d allocated\n", j + 1);
                    take_the_order(chosen_section , j+1,chefq);
                    while(1){
                    printf("Your order has been served.\nIf you wish to order more press 1 or press 2 to proceed towards billing");
                    scanf("%d" , &n);
                    if(n == 1){
                        take_the_order(chosen_section , j+1,chefq);
                    }
                    else if (n == 2){
                         deoccupy_tables(r , chosen_section , j+1 ,chefq, waitlist);
                         if(!is_empty1(waitlist)){
                            int num_of_ppl =  dequeue(waitlist);
                            occupy_tables(r ,num_of_ppl,chefq,waitlist );   
    }
                        // fillerfunc(r , chosen_section , j+1 ,chefq, waitlist);
                        break;
                    }
                }
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
                            take_the_order(chosen_section , j+1,chefq);
                            take_the_order(chosen_section , j+1,chefq);
                    while(1){
                    printf("Your order has been served.\nIf you wish to order more press 1 or press 2 to proceed towards billing");
                    scanf("%d" , &n);
                    if(n == 1){
                        take_the_order(chosen_section , j+1,chefq);
                    }
                    else if (n == 2){
                         deoccupy_tables(r , chosen_section , j+1 ,chefq, waitlist);
                         if(!is_empty1(waitlist)){
                            int num_of_ppl =  dequeue(waitlist);
                            occupy_tables(r ,num_of_ppl,chefq,waitlist );  } 
                            flag =1;
                            break;
                            // return; // No need to continue after assigning tables
                        }
                    }
                }
            }
        }
                }
            }
    }

    //else { printf("Sorry, there are not enough seats available in any section.\n");}
    if(flag == 0){printf("Sorry, there are not enough seats available in any section.\n");}

    }

int main() {
    restaurant r;
    init_restaurant(&r, 2);
    // occupy_tables(&r, 4);
    queuec chefq;
    queue waitlist;
    init_queue1(&waitlist);
    init_queuec(&chefq);
    occupy_tables(&r, 6 , &chefq , &waitlist);
    
    // occupy_tables(&r, 6);
    printf("end");
    return 0;
}
