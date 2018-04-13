/* This program demonstrates the use of a hash table with the following
operations: insert, delete, and find.
Accepts and hashes a string key.
Christopher K. Dierolf
4/13/2018 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;
/****** BEGIN CLASS HASHITEM *******/
class HashItem {
public: 
	string key;
	int data;
	HashItem(string k, int d) : key(k), data(d)
	{ }
};
/****** END CLASS HASHITEM *******/

/****** BEGIN CLASS HASHTABLE *******/
class HashTable
{
private:
	HashItem * pNonItem;
	vector<HashItem*> vectHash;
	int vectSize;
public:
	//ctor
	HashTable(int size) : vectHash(size)
	{
		vectSize = size;
		vectHash.resize(vectSize);
		for (int i = 0; i < vectSize; i++)
		{
			vectHash[i] = NULL;
		}
		pNonItem = new HashItem("**", 0);
	}

	// Hash Function
	int hashFunction(string key)
	{
		unsigned int hashVal = 0;
		for (int i = 0; i < key.length(); ++i)
		{
			hashVal ^= (hashVal << 5) + (hashVal >> 2) + key[i];
		}
		return hashVal % vectSize;
	}

	// Method to insert a new hash item
	void insert(HashItem *pItem)
	{
		string key = pItem->key;				// Get the key from the passed in item
		int hashedKey = hashFunction(key);		// Hash the key

		while (vectHash[hashedKey] != NULL && vectHash[hashedKey]->key != "**") // Keep going until a cell is encountered
																			   // that isn't null, or contains "o"
		{
			if (hashedKey ==  hashFunction(pItem->key)) // Collision Immenint! Take evasive action! 
			{
				cout << "COLLISION ALARM!\n"; // Evasive pattern Echo 3! All ahead flank speed!
				break;
			}
			else
			{
				++hashedKey;						// Advance to the next cell
				hashedKey %= vectSize;				// Handle the wrap-around
			}
		}
		vectHash[hashedKey] = pItem;			// Insert the item
	}

	// Method to locate an item based on its key
	HashItem *find(string key)
	{
		int hashedKey = hashFunction(key);			// Hash the key passed into the method.

		while (vectHash[hashedKey] != NULL)
		{
			if (vectHash[hashedKey]->key == key)	// Compare the hashed key in the table with the hashed key passed into the method.
			{
				cout << "Item found...\n";
				return vectHash[hashedKey];			// If found.
			}
			++hashedKey;
			hashedKey %= vectSize;
		}
		return NULL;								// Item not found
	}

	// Method to display the table
	void displayTable()
	{
		cout << "Table:\n";
		for (int i = 0; i < vectSize; i++)
		{
			if (vectHash[i] != NULL)
			{
				cout << i << ": Key: " << vectHash[i]->key;
				cout << " Data: " << vectHash[i]->data << endl;
			}
			else
			{
				cout << i + 1 << ": ** ";
			}
		}
		cout << endl;
	}
	// Method to remove an item from the hash table.
	HashItem *removeItem(string key)
	{
		int hashedKey = hashFunction(key);		// Hash the key parameter.

		while (vectHash[hashedKey] != NULL)		// Loop through...
		{
			if (vectHash[hashedKey]->key == key)	// If the hashed key in the table equals the hashed key passed into this method...
			{
				HashItem *pTemp = vectHash[hashedKey];	// Assign a temporary item to hold the slot
				vectHash[hashedKey] = pNonItem;			// delete the item in the slot
				cout << "Item deleted...\n";
				return pTemp;
			}
			++hashedKey;
			hashedKey %= vectSize;
		}
		cout << "Key not found...\n";
		return NULL;
	}
};
/****** END CLASS HASHTABLE *******/

/****** BEGIN MAIN *******/
int main()
{

	HashItem *pHI;

	int selection, size, data;
	string key, keyFind, keyDel;

	cout << "This program demonstrates the use of a hash table that accepts a string as the key.\n\n";
	// Get the hash table size.
	cout << "Enter the size of the hash table that you would like to create: ";
	cin >> size;
	HashTable ht(size);
	// Display the menu
	do {
		cout << "Select an option from the following menu: \n";
		cout << "\t1. Insert a new item.\n";
		cout << "\t2. Find an item.\n";
		cout << "\t3. Delete an item.\n";
		cout << "\t4. Display the table.\n";
		cout << "\t0. Exit.\n";
		cout << "\nEnter a selection (0-4): ";
		cin >> selection;
		while (selection < 0 || selection > 4) // Validate the selection
		{
			cout << "\nInvalid selection\n";
			cout << "Enter a valid menu option (0-4): ";
			cin >> selection;
		}
		// Handle the selection.
		if (selection == 1)
		{
			cout << "Enter the key as a string: ";
			cin >> key;
			cout << "Enter the data you wish held with key: " << key << ": ";
			cin >> data;
			pHI = new HashItem(key, data);
			ht.insert(pHI);

		}
		else if (selection == 2)
		{
			cout << "Enter the key of the item you wish to find as a string: ";
			cin >> keyFind;
			ht.find(keyFind);
		}
		else if (selection == 3)
		{
			cout << "Enter the key of the item you wish to delete as a string: ";
			cin >> keyDel;
			ht.removeItem(keyDel);
		}
		else if (selection == 4)
		{
			ht.displayTable();
		}
		else
		{
			exit(0);
		}

	} while (selection != 0);
	return 0;
}
/****** END MAIN *******/
