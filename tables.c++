#include <iostream>
#include <cmath>
#include <cassert>

// A constant variable to store the load factor
const double LOAD_FACTOR = 0.5;

// A class to represent a key-value pair
class Pair {
public:
    int key;
    int value;
    Pair(int k, int v) : key(k), value(v) {}
};

// A class to represent a hash table
class HashTable {
private:
    // An array to store the key-value pairs
    Pair** table;
    // The size of the array
    int size;
    // The number of elements in the hash table
    int count;

    // Quadratic probing parameters
    int c1;
    int c2;

    // A function to hash a key and return an index
    int hash(int key) {
        // The original hash function using modulus
        return key % size;
    }

    // A function to resize the array and rehash the elements
    void resize() {
        // Store the old table and size
        Pair** oldTable = table;
        int oldSize = size;

        // Find the new size as the smallest prime number greater than double the old size
        size = nextPrime(2 * oldSize);

        // Allocate a new array with the new size
        table = new Pair*[size];

        // Initialize the new array with NULL values
        for (int i = 0; i < size; i++) {
            table[i] = NULL;
        }

        // Reset the count
        count = 0;

        // Rehash the elements from the old table to the new table
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != NULL) {
                // Get the key and value from the old table
                int key = oldTable[i]->key;
                int value = oldTable[i]->value;

                // Delete the pair from the old table
                delete oldTable[i];

                // Insert the pair into the new table
                insert(key, value);
            }
        }

        // Delete the old table
        delete[] oldTable;
    }

    // A function to find the next prime number greater than a given number
    int nextPrime(int n) {
        if (n <= 1) return 2;
        int prime = n;
        bool found = false;
        while (!found) {
            prime++;
            if (isPrime(prime)) found = true;
        }
        return prime;
    }

    // A function to check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

public:
    // A constructor to initialize the hash table
    HashTable(int s) : size(s), count(0), c1(0), c2(1) {
        // Allocate an array of pointers to pairs
        table = new Pair*[size];

        // Initialize the array with NULL values
        for (int i = 0; i < size; i++) {
            table[i] = NULL;
        }
    }

    // A destructor to delete the hash table
    ~HashTable() {
        // Loop through the array and delete the pairs
        for (int i = 0; i < size; i++) {
            if (table[i] != NULL) {
                delete table[i];
            }
        }
        // Delete the array
        delete[] table;
    }

    // A function to insert a key-value pair into the hash table
    void insert(int key, int value) {
        // Check if the key is within the range
        if (key < 100 || key > 999) {
            // Print an error message and return
            std::cout << "Invalid key: " << key << std::endl;
            return;
        }

        // Check if the load factor meets or exceeds the threshold
        if (count >= size * LOAD_FACTOR) {
            // Resize the array and rehash the elements
            resize();
        }

        // Hash the key and get the index
        int index = hash(key);

        // Quadratic probing to find the next open spot
        int i = 0;
        while (table[(index + c1 * i + c2 * i * i) % size] != NULL) {
            // Increment the probe number
            i++;
        }

        // Insert the pair into the hash table
        table[(index + c1 * i + c2 * i * i) % size] = new Pair(key, value);

        // Increment the count
        count++;
    }

    // A function to search for a key and return the value
    int search(int key) {
        // Hash the key and get the index
        int index = hash(key);

        // Quadratic probing to find the next open spot
        int i = 0;
        while (table[(index + c1 * i + c2 * i * i) % size] != NULL && table[(index + c1 * i + c2 * i * i) % size]->key != key) {
            // Increment the probe number
            i++;
        }

        // Check if the slot is not empty and the key matches
        if (table[(index + c1 * i + c2 * i * i) % size] != NULL && table[(index + c1 * i + c2 * i * i) % size]->key == key) {
            // Return the value
            return table[(index + c1 * i + c2 * i * i) % size]->value;
        }
        else {
            // Return -1 to indicate not found
            return -1;
        }
    }

    // A function to print the hash table
    void print() {
        // Loop through the array
        for (int i = 0; i < size; i++) {
            // Check if the slot is not empty
            if (table[i] != NULL) {
                // Print the key and value
                std::cout << table[i]->key << " " << table[i]->value << " ";
            }
            else {
                // Print an underscore
                std::cout << "_ ";
            }
        }
        // Print a new line
        std::cout << std::endl;
    }
};
void runTests() {
    // Test 1: Insert and Search
    HashTable ht1(11);
    ht1.insert(123, 42);
    assert(ht1.search(123) == 42);

    // Test 2: Insert with Duplicate Key
    HashTable ht2(11);
    ht2.insert(123, 42);
    ht2.insert(123, 99); // This should print a message that the key already exists
    assert(ht2.search(123) == 42); // The value should remain the same

    // Test 3: Insert and Resize
    HashTable ht3(5); // Small initial size for testing resizing
    ht3.insert(123, 42);
    ht3.insert(456, 78);
    ht3.insert(789, 99);
    ht3.insert(101, 23);
    ht3.insert(102, 34); // Trigger resize
    printf("ht3.search(123) = %d\n", ht3.search(123));
    assert(ht3.search(123) == 42);
    printf("ht3.search(456) = %d\n", ht3.search(456));
    assert(ht3.search(456) == 78);
    printf("ht3.search(789) = %d\n", ht3.search(789));
    assert(ht3.search(789) == 99);
    printf("ht3.search(101) = %d\n", ht3.search(101));
    assert(ht3.search(101) == 23);
    printf("ht3.search(102) = %d\n", ht3.search(102));
    assert(ht3.search(102) == 34);
    printf("ht3.search(103) = %d\n", ht3.search(34));
}


void  withSampleInput(){
    // Create a hash table with the initial size of 11
    HashTable ht(11);

    // Ask the user for the number of values to be entered
    std::cout << "Enter the number of values: ";
    int n;
    std::cin >> n;

    // Loop n times
    for (int i = 0; i < n; i++) {
        // Ask the user for the key and value
        std::cout << "Enter the key and value: ";
        int key, value;
        std::cin >> key >> value;

        // Insert the key-value pair into the hash table
        ht.insert(key, value);
    }

    // Print the final hash table
    std::cout << "The final hash table is: " << std::endl;
    ht.print();
}
// A main function to test the hash table
int main() {
    withSampleInput();
    // runTests();  // Uncomment this line to run the tests
    // Return 0 to indicate success
    
    return 0;
}



