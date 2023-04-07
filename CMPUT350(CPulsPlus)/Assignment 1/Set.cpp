#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Set.h"
static const int INT_BITS = sizeof(int)*8;

using namespace std;

unsigned int *toBin(unsigned int n) 
{ 
    unsigned int *binarySeq = new unsigned int[INT_BITS]; // 0 initialized array to store binary representation
    for (int i = 0; i < INT_BITS; i++){
        binarySeq[i] = 0;
    }
    int i = (INT_BITS-1); 
    while (n > 0) { // store the remainer of dividing the int by 2 at specified index, this fills array from last to first
        binarySeq[i] = n % 2; 
        n = n / 2; 
        i--; 
    }
    return binarySeq;
}

unsigned int getInt(size_t n, unsigned int d){
    int p = n-(d * INT_BITS);   //determine at which point in the binary sequence to change a 0 to 1 based on criteria from description
    int a[INT_BITS] = {0}; //create an empty array of int_size and initialize with zeros
    a[(INT_BITS-p-1)] = 1; //change a specified index to 1 to represent n as a binary sequence
    string str;
    for(int i = 0; i<INT_BITS; i++){ //convert the binary sequence to a string
        str += to_string(a[i]);
    }
    unsigned int c = stoul(str, 0, 2); //convert the binary string that represents an int base 2 to an int base 10
    return c;
}

Set::Set(size_t n){ // create empty subset of {0..n-1}
    this->n = n; //set the largest value the set can store
    int s = n/INT_BITS;
    if (n%INT_BITS != 0){ s+=1;} //based on the size of an int, allocate sufficient ints to store set representation
    this->a = s;
    unsigned int* int_set = new unsigned int[s]; //allocate an array of size s to hold the number of ints specified
    for (int i = 0; i < s; i++){
        int_set[i] = 0;
    }
    this->bits = int_set;
    
}                
 
Set::~Set(){    // destructor
    delete [] this->bits;
}                       

Set::Set(const Set &s){ // copy constructor
    if (this != &s){    //verify that self assignment is not happening
        this->n = s.n;
        this->a = s.a;
        unsigned int* int_set = new unsigned int[s.a];
        for (int c=0; c<(int)(s.a); c++){   //copy the elements of the passed set one by one into a newly created int array of specified size
            int_set[c] = s.bits[c];
        }
        this->bits = int_set; 
    }
}            

Set &Set::operator=(const Set &s){  // assignment operator
    if (this != &s){    //verify that self assignment is not happening
        this->n = s.n;
        this->a = s.a;
        unsigned int* int_set = new unsigned int[s.a];
        for (int c=0; c<(int)(s.a); c++){   //copy the elements of the passed set one by one into a newly created int array of specified size
            int_set[c] = s.bits[c];
        }
        this->bits = int_set; 
    }
    return *this;
} 

void Set::clear(){  // empty set
    for (int i = 0; i<(int)(this->a);i++){ //set each element in the bits set to 0
        this->bits[i] = 0;
    }
}              
void Set::complement(){ // negate set (x was in set before <=> x is not in set after)
    //impement funtionality
    for (int i = 0; i<(int)(this->a);i++){ //use bitwise not on each element of the int set to find the complement
        this->bits[i] = ~this->bits[i];
    }
}         

bool Set::has(size_t x) const{  // return true iff x is element of set (0 <= x < n)
    assert(x < (this->n));
    //cerr << "This set cannot store negative values and the largest value this set can store is " << (this->n-1)<< endl;
    bool contains = 0;
    unsigned int indx = x/INT_BITS; //based on the value of x, determine the appropriate int in the set to alter
    unsigned int c = getInt(x, indx); //get back an int representaion of x, after binary transformation according to assignment criteria
    if ((this->bits[indx] & c) !=0){ //use bitwise & to determine that the union of the set exists, if it does then x is in set
        contains = 1;
    }
    return contains;
}  

void Set::add(size_t x){    // add element x to set (0 <= x < n)
    assert(x < (this->n));
    //cerr << "This set cannot store negative values and the largest value this set can store is" << (this->n-1)<< endl;
    unsigned int indx = x/INT_BITS; //based on the value of x, determine the appropriate int in the set to alter
    unsigned int c = getInt(x, indx); //get back an int representaion of x, after binary transformation according to assignment criteria
    this->bits[indx] = (this->bits[indx] | c); //use bitwise or to form a union of the 2 ints
}        

void Set::remove(size_t x){ // remove element x from set (0 <= x < n)
    assert(x < (this->n));
    //cerr << "The given value is out of bounds" << endl;
    unsigned int indx = x/INT_BITS; //based on the value of x, determine the appropriate int in the set to alter
    unsigned int c = getInt(x, indx); //get back an int representaion of x, after binary transformation according to assignment criteria
    if (this->has(x)) {
        this->bits[indx] = (this->bits[indx] ^ c); //use bitwise exclusive or to remove bits that exist in both numbers
    }
}     

void Set::add(const Set &s){    // add all elements of s to set; pre-cond: s.n == n
    assert(s.n == this->n);
    //cerr << "The 2 arrays to be added must be of the same size" << endl;
    for (int i = 0; i<(int)(this->a);i++){
        this->bits[i] = (this->bits[i]) | (s.bits[i]); //use bitwise or to form a union of the two ints from the 2 sets
    }
}    

void Set::remove(const Set &s){ // remove all elements of s from set; pre-cond: s.n == n
    assert(s.n == this->n);
    //cerr << "The 2 arrays to be added must be of the same size" << endl;
    for (int i = 0; i<(int)(this->a);i++){
        this->bits[i] = (this->bits[i]) ^ (s.bits[i]); //use bitwise exclusive or to remove elements that exist in both sets from the first
    }
} 

/* print elements to output stream os (default std::cout) like so: 
[ 1 2 4 5 ]
for set {1,2,4,5} (no extra spaces, no newline characters) */
void Set::print(std::ostream &os) const{
    os << "[ ";
    //loop through the int array, then loop trhough the binary rep array to print the correct numbers
    for(int i = 0; i<(int)(this->a);i++){
        unsigned int *c = toBin(this->bits[i]);
        for (int j = INT_BITS-1; j >=0 ; j--){
            if (c[j] != 0){
                os << INT_BITS-j-1+(i*INT_BITS)<< " ";
            }
        }
        delete []c;
    }
    os << "]";
}