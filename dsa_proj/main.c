#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cust_management.h"
#include"queue.c"
double totalincome = 0;
void init_section(section* s, int total_tables_in_section, int chair) {
    s->no_of_tables = total_tables_in_section;
    s->chairs = chair;
    s->t = (table*)malloc(sizeof(table) * total_tables_in_section);
    for (int i = 0; i < total_tables_in_section; i++) {
        s->t[i].occupied = 0;
    }
}
void init_list(list *head){
    *head = NULL;
}
void create_node(list *head ,char ordern[] , double p ){
    node *nn = (node*)malloc(sizeof(node));
    nn->*ordername = (char*)malloc(len(ordern));
    nn->price = p;
    nn->next = NULL;
    if(*head == NULL)
        *head = nn;
    node *temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = nn;
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
void init_list(list *head){
    *head = NULL;
}
void take_the_order(section *sec , int t1 , queue* chefq){
    init(&sec->t[t1].order);
    int c;
    FILE* fp = fopen("menu.csv", "r");
    if (!fp) {
        printf("Error opening the file.\n");
        return 1;
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
        enqueuec(&chefq ,menu[c-1].name);
        // fprintf(f ,"%s , %d\n" , menu[c-1].name ,(int) menu[c-1].price);
    }
}
int chef_gives_order(){
    double bill_chef = 0;
    FILE* fp = fopen("shoppinglist.csv", "r");
    if (!fp) {
        printf("Error opening the file.\n");
        return 1;
    }

    struct Shoppinglist shoppinglist[MAX_ITEMS];
    int itemCount = 0;

    // Read menu items from the CSV file
    // ...

// Read menu items from the CSV file
while (itemCount < MAX_ITEMS && fscanf(fp, "%49[^,],%lf\n", shoppinglist[itemCount].name, &shoppinglist[itemCount].price) == 2) {
    // printf("Read item: %s, %.2lf\n", shoppinglist[itemCount].name, shoppinglist[itemCount].price); // Debug statement
    itemCount++;
}

// ...


    fclose(fp);

    // Print the menu
    printf("Items available for buying\n");
    printf("\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%-30s %.2lf\n", shoppinglist[i].name, shoppinglist[i].price);
        printf("\n");
    }
    int c;
    while(1){
        printf("Enter the number of the item you want to purchase. Press -1 to stop");
        scanf("%d" , &c);
        if(c == -1)
            break;
        create_node(&chefpov,shoppinglist[c-1].name,shoppinglist[c-1].price);
        bill_chef += shoppinglist[c-1].price;
        // fprintf(f ,"%s , %d\n" , menu[c-1].name ,(int) menu[c-1].price);
    }
    return bill_chef;
}
void totalincome_r(double totalincome1 , double bill_chef1){
    double profit = totalincome - bill_chef;
    if(profit >= 0){
        printf("purchase made");
    }
    else printf("Sorry no money left for expenditure");
}
void occupy_tables(restaurant* r, int num_people) {
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
                    take_the_order()
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
                            take_the_order()
                            flag =1;
                            break;
                            // return; // No need to continue after assigning tables
                        }
                    }
                }
            }
        }
    }
    //else { printf("Sorry, there are not enough seats available in any section.\n");}
    if(flag == 0){printf("Sorry, there are not enough seats available in any section.\n");}

}
void deoccupy_tables(restaurant *r , section *sec , int t1 , queue *waitlist){
    // sec->
    sec->t[t1].occupied = 0;
    double bill = 0;
    node *temp = sec->t[t1].order;
    printf("\t\t\tBill\t\t\t\n");
    while (temp){
        printf("%s\t%f\n" , temp->ordername , temp->price);
        bill += temp->price;
        temp = temp->next;
    }
    printf("Total money to be paid is %f\nThankyou for visiting, Comeagain!" , bill);
    totalincome += bill;
    if(!is_empty(&waitlist)){
        int num_of_ppl =  dequeue(&waitlist);
        occupy_tables(&r ,num_of_ppl );   
    }
}
int main() {
    restaurant r;
    init_restaurant(&r, 3);
    occupy_tables(&r, 6);
    occupy_tables(&r, 6);
    occupy_tables(&r, 6);
    queue waitlist;
    queue chefq;
    init_queue(&chefq);
    init_queue(&waitlist);
    list chefpov;
    init_list(&chefpov);
    return 0;
}
