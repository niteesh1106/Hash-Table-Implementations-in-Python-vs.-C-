/*Linear Probing Hash Table Implementation in C*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TABLE_SIZE 1115 // Define the size of the hash table

typedef struct {
    char* key;
    char* value;
} KeyValuePair; // Define a key-value pair structure

typedef struct {
    KeyValuePair* table[TABLE_SIZE]; // Array of pointers to KeyValuePair
    int collision; // Counter for collisions during insertion
    int total_probe; // Total number of probes during insertion and search
    int count_elements; // Number of elements stored in the hash table
} LinearProbing; // Define the linear probing hash table structure

// Hash function to generate an index for a given key
unsigned int hash(char* key) {
    unsigned int i = 10;
    unsigned int key_value = 0;
    while (*key != '\0') {
        key_value = key_value + (*key * i);
        i *= 10;
        key++;
    }
    return (key_value / 10) % TABLE_SIZE;
}

// Linear probing collision resolution strategy
int linear_probing(LinearProbing* ht, char* key) {
    int index = hash(key);
    int count = 0;
    while (ht->table[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
        count++;
        ht->total_probe++;
        if (count == TABLE_SIZE) {
            // Full table, can't find empty slot
            printf("HashTable is full and Key does not exist!\n");
            exit(EXIT_FAILURE);
        }
    }
    return index;
}

// Insert a key-value pair into the hash table
void insert(LinearProbing* ht, char* key, char* value) {
    int index = hash(key);
    ht->count_elements++;
    if (ht->table[index] == NULL) {
        ht->table[index] = (KeyValuePair*)malloc(sizeof(KeyValuePair));
        ht->table[index]->key = strdup(key); // Allocate memory for key and copy the key
        ht->table[index]->value = strdup(value); // Allocate memory for value and copy the value
    } else {
        ht->collision++; // Collision occurred
        index = linear_probing(ht, key); // Resolve collision using linear probing
        ht->table[index] = (KeyValuePair*)malloc(sizeof(KeyValuePair));
        ht->table[index]->key = strdup(key);
        ht->table[index]->value = strdup(value);
    }
}

// Search for the value associated with a given key
char* search(LinearProbing* ht, char* key) {
    int index = hash(key);
    int original_index = index;
    while (ht->table[index] != NULL) {
        if (strcmp(ht->table[index]->key, key) == 0) {
            return ht->table[index]->value; // Found the key, return the associated value
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == original_index) {
            // We have traversed the entire table without finding the key
            return NULL;
        }
    }
    return NULL;
}

// Free memory allocated for the hash table
void destroy(LinearProbing* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->table[i] != NULL) {
            free(ht->table[i]->key);
            free(ht->table[i]->value);
            free(ht->table[i]);
        }
    }
}

int main() {
    LinearProbing ht;
    ht.collision = 0;
    ht.total_probe = 0;
    ht.count_elements = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.table[i] = NULL; // Initialize hash table with NULL pointers
    }

    clock_t start_time = clock();
    FILE* file = fopen("dictionary.txt", "r"); // Open dictionary file
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[256];
    char* key;
    char* value;
    while (fgets(line, sizeof(line), file)) { // Read lines from file
        key = strtok(line, ":"); // Extract key from line
        if (key != NULL) {
            // Remove leading and trailing whitespaces from the key
            while (isspace((unsigned char)*key)) key++;
            char* end_key = key + strlen(key) - 1;
            while (end_key > key && isspace((unsigned char)*end_key)) end_key--;
            *(end_key + 1) = '\0'; // Null terminate the key

            value = strtok(NULL, ""); // Extract value from line
            if (value != NULL) {
                // Remove leading and trailing whitespaces from the value
                while (isspace((unsigned char)*value)) value++;
                char* end_value = value + strlen(value) - 1;
                while (end_value > value && isspace((unsigned char)*end_value)) end_value--;
                *(end_value + 1) = '\0'; // Null terminate the value

                insert(&ht, key, value); // Insert key-value pair into hash table
            }
        }
    }
    fclose(file); // Close the dictionary file

    double T = ((double)(clock() - start_time) / CLOCKS_PER_SEC) * 1000;
    printf("Time taken to read the file and store %d items in Hashtable: %.2f ms\n", ht.count_elements, T);
    printf("Total Collisions: %d\n", ht.collision);
    double average_probe_length = (double)ht.total_probe / ht.count_elements;
    printf("Average Probe Length: %.2f\n\n", average_probe_length);

    while (1) {
        char word[100];
        printf("Enter the word to find its meaning (enter 0 to exit): ");
        scanf("%s", word);
        if (strcmp(word, "0") == 0)
            break;
        char* meaning = search(&ht, word);
        if (meaning != NULL) {
            printf("%s means: %s\n\n", word, meaning);
        } else {
            printf("The word '%s' does not exist in the dictionary.\n\n", word);
        }
    }

    destroy(&ht); // Free memory allocated for the hash table
    return 0;
}
