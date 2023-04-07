#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

struct World; // forward declaration - World& needed in Animal

// animal base-class

struct Animal
{
  // implemented ...
  
  Animal(int x, int y)
    : x(x), y(y), alive(true), age(0)
  { }
  
  // act in the world
  virtual void act(World &w) = 0;

  // prints animal data
  virtual void print() const = 0;

  virtual ~Animal() { }

  // sends type and common data to stdout
  void print_common(const char *type) const
  {
    printf("%s %d %d %d\n", type, x, y, age);
  }
  
  // data

  int x, y;   // animal's location
  bool alive; // true iff animal is alive
  int age;    // animal's age
};


// simulation environment

struct World
{
  // ONLY CHANGE CODE IN BLOCKS DESIGNATED WITH "implement ..." !
  
  // init_cap: make room for that many animals initially
  World(int init_cap = 1)
    : capacity(init_cap)
  {
    assert(init_cap > 0);
    n = 0;
    op = A = new Animal*[capacity];
  }

  ~World()
  {
    for (int i=0; i < n; ++i) {
      delete A[i];
    }
    delete [] A;
  }

  // CC and AO not implemented
  World(const World &) = delete;
  World &operator=(const World &) = delete;

  // return number of animals
  int animal_number() const { return n; }
  
  // return pointer to random animal
  Animal *get_random_animal()
  {
    assert(n > 0);
    // note: only approximates uniform distribution (better use C++11 rng
    // facility)
    return A[random() % n];
  }
  
  // add animal to array (world now owns it)
  // assumes there is enough space left
  void add_animal(Animal *p)
  {
    assert(op < A + capacity);
    *op++ = p;
  }
  
  // print world state (list of animals)
  void print() const
  {
    // implemented ...

    printf(" %d animal(s)\n", n);

    for (int i=0; i < n; ++i) {
      printf(" ");
      A[i]->print();
    }

    puts("");
  }

  // execute 'steps' action rounds
  void simulate(int steps)
  {
    remove_dead_animals(); // also sets n
    
    printf("iter 0\n");
    print();

    for (int i=0; i < steps && n > 0; ++i) {

      // allocate sufficient space for new offspring
      make_room_for_offspring();

      // all animals act and have their age incremented

      // implemented ...

      for (int j=0; j < n; ++j) {
        A[j]->act(*this);
        ++(A[j]->age);
      }

      // finally, remove dead animals
      remove_dead_animals();

      printf("iter %d\n", i+1);
      print();
    }
  }

private:

  // helper functions and data members

  // these are implementation details you don't have to understand

  // reserve enough space for the maximum possible number of offspring animals
  // created in one iteration
  void make_room_for_offspring()
  {
    if (capacity < 2*n) {
      
      // we need more space: allocate larger array and copy animal pointers
      // over

      capacity = 2*n;
    
      Animal **B = new Animal*[capacity];
      
      for (int i=0; i < n; ++i) {
        B[i] = A[i];
      }
      
      delete [] A;
      A = B;
    }

    op = A+n; // where offspring is stored, initially points right behind animals
  }

  // remove all dead animals
  void remove_dead_animals()
  {
    for (Animal **p=A; p < op; ++p) {
      if (!(*p)->alive) {
        delete *p;
        --op;
        *p = *op; // copy last element
        --p;      // recheck same position
      }
    }

    // update number of animals
    n = op - A;
  }
  
  // data members

  Animal **A;   // array of animal pointers (owner)
  int n;        // number of animals stored in A (can be < capacity)
  int capacity; // number of elements in A
  Animal **op;  // where to store offspring pointers, gets incemented after
                // adding a new animal  
};

// implemented ... Mouse, Goose, Rabbit, Bear here

struct Mouse : public Animal
{
  Mouse(int x, int y) : Animal(x, y) { }
  
  void act(World &) override
  // "override indicates that we want to override a virtual function
  // if print() is not a virtual function in the base-class the compiler
  // will complain => safety feature
  {
    ++x;   // move East
  }

  void print() const override
  {
    print_common("Mouse");
  }
};

struct Goose : public Animal
{
  Goose(int x, int y) : Animal(x, y) { }
  
  void act(World &) override
  {
    --y;    // fly south ...
  }

  void print() const override
  {
    print_common("Goose");
  }
};

struct Rabbit : public Animal
{
  Rabbit(int x, int y) : Animal(x, y) { }
  
  void act(World &w) override
  {
    // create offspring
    w.add_animal(new Rabbit(x, y));
  }

  void print() const override
  {
    print_common("Rabbit");
  }
};

struct Bear : public Animal
{
  Bear(int x, int y) : Animal(x, y) { }
  
  void act(World &w) override
  {
    // kill random animal
    // note: in a more realistic simulation, we would check proximity
    
    if (w.animal_number() > 1) {

      // try until another animal is killed
      for (;;) {
        Animal *v = w.get_random_animal();
        if (v != this) { // no suicide
          v->alive = false;
          break;
        }
      }
    }
  }

  void print() const override
  {
    print_common("Bear");
  }
};


int main()
{
  /*
    initialize random number generator with current time (a different seed
    each second)
    for testing you may want to fix the seed for reproducability
  
    note: this is old-school random number generation (man random); C++11
    provides a better random number generation facility
  */
  
  srandom(time(0)); 

  /* test code:
  
     populate world with some animals
     and simulate a few steps
  */
  
#if 1

  // populate world with random animals
  
  // a few random animals at (i, i) locations

  int N = 30;
  World w(N);
  
  for (int i=0; i < N; ++i) {

    // note: only approximates uniform distribution (better use C++11 rng
    // facility)

    switch (random() % 4) {
      case 0: w.add_animal(new Mouse(i, i));  break;
      case 1: w.add_animal(new Goose(i, i));  break;
      case 2: w.add_animal(new Rabbit(i, i)); break;
      case 3: w.add_animal(new Bear(i, i));   break;      
    }
  }

  // run a few steps
  
  w.simulate(5);

#else

  // problems.txt test case

  // a few animals

  World w(6);
  
  w.add_animal(new Mouse(100, 100));
  w.add_animal(new Mouse(50, 60));
  w.add_animal(new Goose(90, 80));
  w.add_animal(new Goose(10, 20));
  w.add_animal(new Rabbit(80, 80));
  w.add_animal(new Bear(70, 90));

  // run a few steps
  
  w.simulate(20);
  
#endif
  
  return 0;
}
