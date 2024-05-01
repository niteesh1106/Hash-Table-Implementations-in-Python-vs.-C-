"""Linear Probing Hash Table Implementation in Python"""
import time


class LinearProbing:
    def __init__(self, size=20):
        # Initialize the hash table with specified size
        self.table = [{'Key': None, 'Value': None} for _ in range(size)]
        self.collision = 0  # Tracks the number of collisions occurred during insertion
        self.total_probe = 0  # Tracks the total number of probes during insertion
        self.count_elements = 0  # Tracks the total number of elements inserted

    def __setitem__(self, key, value):
        # Insert an item into the hash table
        index = self.hash(key)  # Calculate hash value for the key
        self.count_elements += 1  # Increment the count of elements
        if self.table[index]['Key'] is None:
            # If the slot is empty, insert the item
            self.table[index] = {'Key': key, 'Value': value}
        else:
            # If collision occurs, use linear probing to find the next available slot
            self.collision += 1
            index = self.linear_probing(key)
            self.table[index] = {'Key': key, 'Value': value}

    def __getitem__(self, key):
        # Retrieve an item from the hash table
        index = self.hash(key)  # Calculate hash value for the key
        while index < len(self.table):
            if self.table[index]['Key'] == key:
                # If key matches, return the corresponding value
                return self.table[index]['Value']
            else:
                index += 1
        # If key not found, raise KeyError
        raise KeyError("Key does not exist!")

    def hash(self, key):
        # Hash function to map keys to indices in the hash table
        i = 10
        key_value = 0
        for char in key:
            key_value = key_value + (ord(char) * i)
            i *= 10
        return int((key_value / 10) % len(self.table))

    def linear_probing(self, key):
        # Linear probing to find the next available slot in case of collision
        index = self.hash(key)
        count = 0
        try:
            while self.table[index]['Key'] is not None:
                index = (index + 1) % len(self.table)
                count += 1
                self.total_probe += 1
                if count == len(self.table):
                    # If the entire table is probed, raise exception (table full)
                    raise Exception
        except Exception:
            print("HashTable is full and Key does not exist!")
            exit()  # Exit the program if table is full
        return index


if __name__ == '__main__':
    start_Time = time.time()
    ht = LinearProbing(1115)  # Initialize hash table with specified size
    dic = {}  # Dictionary to store items from the file
    with open("dictionary.txt", "r", encoding='utf-8') as f:
        for line in f:
            temp = line.rstrip().split(': ')
            key = temp[0]
            value = temp[1]
            dic[key] = value
            ht.__setitem__(key, value)  # Insert each item into the hash table
        T = (time.time() - start_Time) * 1000  # Calculate time taken
        print(f'Time taken to read the file and store {ht.count_elements} items in Hashtable: {T} ms')
        print("Total Collisions: ", ht.collision)  # Print total collisions
        average_probe_length = ht.total_probe / ht.count_elements
        print("Average Probe Length: ", average_probe_length, "\n")  # Print average probe length

        while True:
            word = input("Enter the word to find its meaning (enter 0 to exit): ")
            if word == "0":
                break
            try:
                print(f"{word} means: {ht.__getitem__(word)}\n")  # Retrieve and print meaning of the word
            except KeyError:
                print(f"The word '{word}' does not exist in the dictionary.\n")  # Handle key not found
