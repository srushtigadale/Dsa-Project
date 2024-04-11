
typedef struct table {
    int occupied; //indicates if table is occupied
} table;

// Customer management
typedef struct section {
    table* t; //tables in each section
    int no_of_tables;
    int chairs; // no. of chair each table has
} section;

typedef struct restaurant {
    int no_of_sections;
    section* array_of_all_sections;
} restaurant;