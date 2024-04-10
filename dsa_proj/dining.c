#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50

// Structure to store menu items
struct MenuItem {
    char name[MAX_NAME_LENGTH];
    double price;
};

int main() {
    FILE* fp = fopen("menu.csv", "r");
    if (!fp) {
        printf("Error opening the file.\n");
        return 1;
    }

    struct MenuItem menu[MAX_ITEMS];
    int itemCount = 0;

    // Read menu items from the CSV file
    // ...

// Read menu items from the CSV file
while (itemCount < MAX_ITEMS && fscanf(fp, "%49[^,],%lf\n", menu[itemCount].name, &menu[itemCount].price) == 2) {
    // printf("Read item: %s, %.2lf\n", menu[itemCount].name, menu[itemCount].price); // Debug statement
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

    return 0;
}
