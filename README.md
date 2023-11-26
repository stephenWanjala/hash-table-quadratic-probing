# Hash Table with Quadratic Probing

This repository contains a C++ implementation of a hash table with quadratic probing. The hash table uses an array to store key-value pairs and resolves collisions using quadratic probing.

## Features

- **Hashing Function:** The original hash function uses the modulus operator to find the initial position.
- **Collision Resolution:** Quadratic probing is employed to find the next open spot in case of collisions.
- **Dynamic Resizing:** The hash table automatically resizes and rehashes the elements when the load factor exceeds the threshold.
- **User Interaction:** A simple user interface allows users to input key-value pairs and view the final hash table.

## Getting Started

1. **Clone the Repository:**
    ```bash
    git clone https://github.com/stephenWanjala/hash-table-quadratic-probing.git
    cd hash-table-quadratic-probing
    ```

2. **Compile and Run:**
    ```bash
    g++ -o hash_table tables.c++
    chmod +x hash_table
    ./hash_table
    ```

3. **Follow the Instructions:**
    - Enter the number of key-value pairs you want to insert.
    - For each pair, enter the key and value when prompted.

## Contributing

If you find any issues or have suggestions for improvements, feel free to open an issue or create a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

