#include <iostream>
#include <cstdlib>
#include "String.h"
using namespace std;

String::String(const char *p) {
    shared = new SharedData;
    int len=0;
    for(const char *i = p; *i; ++i){ //go from the pointer to the string literal and count number of characters, add to length
        len++;
    }
    char* sArr = new char[len]; //allocate an array of size len and return the pointer to it 
    for(int f = 0; f <=len ; f++){ //loop through the string and add each character to array
        sArr[f] = p[f];
    }
    shared->data = sArr; //assign the pointer to the data value
    shared->count = 1; //set it's inital count to 1
    shared->n = len; //save it's length
}
// destructor (when can shared data be released?)
String::~String(){ //if the count is one, then delete the object after decreasing the ref count, otherwise decrease the count
    if(shared->count == 1){
        delete [] shared->data;
    }
    shared->count -= 1;
}

// if it isn't self assigning, act like the initialiser does then call the helper function to change count
String::String(const String &x){
    if ((this->shared == NULL) || ((this->shared != NULL) && (x.shared != this->shared))){
        if (this->shared != NULL){
            delete [] this->shared;
        }
        shared = new SharedData;
        shared->n = x.size();
        char* nArr = new char[x.size()];
        for(int f = 0; f <=(int)x.size() ; f++){
            nArr[f] = x.cstr()[f];
        }
        shared->data = (char*)nArr;
        x.shared->inc_count();
        shared->count = x.ref_count();
    }
}

// if it isn't self assigning, act like the initialiser does then call the helper function to change count
String &String::operator=(const String &x){
    if ((this->shared == NULL) || ((this->shared != NULL) && (x.shared != this->shared))){
        if (this->shared != NULL){
            delete [] this->shared;
        }
        shared = new SharedData;
        shared->n = x.size();
        char* nArr = new char[x.size()];
        for(int f = 0; f <=(int)x.size() ; f++){
            nArr[f] = x.cstr()[f];
        }
        shared->data = (char*)nArr;
        x.shared->inc_count();
        shared->count = x.ref_count();
    }
    return *this;
} 
  
  // return number of non-0 characters in string
size_t String::size() const{
    return shared->n;
}

  // return reference count
size_t String::ref_count() const{
    return shared->count;
}
  
  // returns pointer to C-string
const char* String::cstr() const{
    return shared->data;
}

int main()
{
  String s("aaa"), t("bbbb");  // construct
  String u = t;                // copy construct
  String v("cccc");            // construct
  v = s;                       // assign

  cout << "s: " << s.cstr() << " " << s.size() << " " << s.ref_count() << endl
       << "t: " << t.cstr() << " " << t.size() << " " << t.ref_count() << endl
       << "u: " << u.cstr() << " " << u.size() << " " << u.ref_count() << endl
       << "v: " << v.cstr() << " " << v.size() << " " << v.ref_count() << endl;

  return 0;
}

/*
  output:

s: aaa 3 2
t: bbbb 4 2
u: bbbb 4 2
v: aaa 3 2

*/