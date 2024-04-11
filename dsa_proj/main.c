#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cust_management.h"
#include"queue.c"

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

void occupy_tables(restaurant* r, int num_people) {
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
            }
        }
    }
    //else { printf("Sorry, there are not enough seats available in any section.\n");}
    if(flag == 0){printf("Sorry, there are not enough seats available in any section.\n");}
    
}

int main() {
    restaurant r;
    init_restaurant(&r, 3);
    occupy_tables(&r, 6);
    occupy_tables(&r, 6);
    occupy_tables(&r, 6);
    return 0;
}
