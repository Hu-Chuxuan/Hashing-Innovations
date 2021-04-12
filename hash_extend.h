#include "hashset.h"

//
//  hash_extend.h
//  
//
//  Created by Hu Chuxuan on 21.03.21.
//

//This class defines the Last-Come-First-Served Hashing
template<class T> class HashSet_LCFS{
    /* Refer to the given code to design the new hashset */
public:
    HashSet_LCFS(int size = 20);
    void insert(T item);       
    void add(T item); //this is a helper function for chaining search based on the initial hashset implementation
    void display();   //this function is a helper function for checking
    bool member(T item);
private:
    int numitems;           
    T **reprarray;
    T *pt_nil;          
    int maxsize;           
};

//This class defines the Robin-Hood Hashing
template<class T> class HashSet_RH{

public:
    HashSet_RH(int size = 20);
    void insert(T item);
    void display(void);
    bool member(T item);
private:
    int numitems;           
    T **reprarray;
    T *pt_nil;          
    int maxsize; 

};
//Constructer for Robin-Hood Hashing
template<class T> HashSet_RH<T>::HashSet_RH(int size){
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new T*[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;
    }
    T *pt0 = new T;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
};
//Insertion function for Robin-Hood Hashing
template<class T> void HashSet_RH<T>::insert(T item){
    hash<T> hashfunction; 
    int index;
    index = hashfunction(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.

    // cout << "The item " << item << " has index " << index <<"\n";     //test for correctness

    while (reprarray[index] != 0) 
    {
        if (*reprarray[index] == item) // We first check, if the item is already in the hashtable
            return;                    // item found; no insertion


        //Here we check if the stored value should be farther away from the position
        T prev=*(reprarray[index]);   
        int prev_ind=hashfunction(prev) % maxsize;
        int tmp_ind=hashfunction(item) % maxsize;
        //if it is not, we take up this position
        if((prev_ind-index)*(prev_ind-index) < (tmp_ind-index)*(tmp_ind-index)){
            T *pt = new T;
            *pt = item;
            reprarray[index] = pt;   // store item in the hashtable
            insert(prev);            //recursively call the function to let the occupied item moves further
            return;                  //stopping condition for this element
        }
        index = (index + 1) % maxsize;
    }

    //stopping condition for all the elements
    //as only if one of the elements finds a null(empty space) to store, we stop the process
    T *pt = new T;
    *pt = item;
    reprarray[index] = pt;

    //increment on numitems at the end
    ++ numitems;
};
//Constructure for LCFS
template<class T> HashSet_LCFS<T>::HashSet_LCFS(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new T*[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;
    }
    T *pt0 = new T;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}
//Insertion function for LCFS Hashing
template<class T> void HashSet_LCFS<T>::insert(T item){
    hash<T> hashfunction; 
    int index;
    index = hashfunction(item) % maxsize; 

    // cout << "The item " << item << " has index " << index <<"\n";     //test for correctness

    //Case1:if the index is occupied, we put the element in the place and find a position for the original data
    //applying add() from initial hashsets for the element to be replaced by
    //as this should be a chain search
    if(reprarray[index]!=0){
        T prev=*(reprarray[index]);
        T* pt=new T;
        *pt=item;
        reprarray[index]=pt;
        add(prev);
        return;
    }
    //Case2:if the index is not occupied, we simply put the element at the index position
    T* pt=new T;
    *pt=item;
    reprarray[index]=pt;
    ++numitems;
    return;
}

template<class T> void HashSet_LCFS<T>::display(void) // only for test purposes
{
    cout << "The size of the hashtable is: " << maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "The entry " << i + 1 << " is undefined.\n";
        else if (reprarray[i] == pt_nil)
            cout << "The entry " << i + 1 << " is free.\n";
        else
            cout << "The entry " << i + 1 << " is " << *reprarray[i] << " .\n";
    }
    return;
}

template<class T> void HashSet_RH<T>::display(void) // only for test purposes
{
    cout << "The size of the hashtable is: " << maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "The entry " << i + 1 << " is undefined.\n";
        else if (reprarray[i] == pt_nil)
            cout << "The entry " << i + 1 << " is free.\n";
        else
            cout << "The entry " << i + 1 << " is " << *reprarray[i] << " .\n";
    }
    return;
}

/*For test on performances between various hash algorithms*/
template<class T> bool HashSet_LCFS<T>::member(T item)
{
    hash<T> hashfunction;  // use the "key" function for the type T (if defined)
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return true;  // item was found
        index = (index + 1) % maxsize;
    }
    return false;  // a null pointer was found, so item is not in the hashtable
}

template<class T> bool HashSet_RH<T>::member(T item)
{
    hash<T> hashfunction;  // use the "key" function for the type T (if defined)
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return true;  // item was found
        index = (index + 1) % maxsize;
    }
    return false;  // a null pointer was found, so item is not in the hashtable
}
//Helper function for LCFS
template<class T> void HashSet_LCFS<T>::add(T item)
{
    hash<T> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hashfunction(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    while (reprarray[index] != 0) // We first check, if the item is already in the hashtable
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return;   // item found; no insertion
        if (location < 0 && reprarray[index] == pt_nil) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        index = (index + 1) % maxsize;
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    if (location < 0)
        location = index;
    T *pt = new T;
    *pt = item;
    reprarray[location] = pt;   // store item in the hashtable
    ++ numitems;
    return;
}