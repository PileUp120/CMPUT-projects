#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

struct World; // forward declaration - World& needed in Animal

// Animal base-class

struct Animal
{
    // implement ...
    Animal(){}
    ~Animal(){
        free(type);
    }
    virtual void act(World& w) = 0;
    void print(std::ostream& os) {
        fprintf(" %s %d %d %d\n", type, x, y, age);
    }
    void inc_age() const {
        age += 1;
    }

    int x, y, age;
    bool alive;
    char* type;

    Animal(const Expr&) = delete;
    Animal& operator=(const Expr&) = delete;
};


// simulation environment

struct World
{
    // ONLY CHANGE CODE IN BLOCKS DESIGNATED WITH "implement ..." !

    // init_cap: make room for that many animals initially
    World(int init_cap = 1)
        : capacity(init_cap)
    {
        assert(capacity > 0);
        n = 0;
        op = A = new Animal * [capacity];
    }

    ~World()
    {
        for (int i = 0; i < n; ++i) {
            delete A[i];
        }
        delete[] A;
    }

    // CC and AO not implemented
    World(const World&) = delete;
    World& operator=(const World&) = delete;

    // return number of animals
    int animal_number() const { return n; }

    // return pointer to random animal
    Animal* get_random_animal()
    {
        assert(n > 0);
        // note: only approximates uniform distribution (better use C++11 rng facility)
        return A[random() % n];
    }

    // add new animal to array (world now owns it)
    void add_animal(Animal* p)
    {
        assert(op < A + capacity);
        *op++ = p;
    }

    // print world state (list of animals)
    void print() const
    {
        // implement ...
        fprintf(" %d animal(s)", n);
        for (int j = 0; j < this.n; j++) {
            A[j].print();
        }

    }

    // execute 'steps' action rounds
    void simulate(int steps)
    {
        remove_dead_animals(); // also sets n

        printf("iter 0\n");
        print();

        for (int i = 0; i < steps && n > 0; ++i) {

            // allocate sufficient space for new offspring
            make_room_for_offspring();

            // all animals act and have their age incremented

            // implement ...
            for (int j = 0; j < this.n; j++) {
                A[j].act(w);
                A[j].inc_age();
            }

            // finally, remove dead animals
            remove_dead_animals();

            printf("iter %d\n", i + 1);
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
        if (capacity < 2 * n) {

            // we need more space: allocate larger array and copy animal pointers
            // over
            capacity = 2 * n;
            Animal** B = new Animal * [capacity];

            for (int i = 0; i < n; ++i) {
                B[i] = A[i];
            }

            delete[] A;
            A = B;
        }

        op = A + n; // where offspring is stored, initially points right behind animals
    }

    // remove all dead animals
    void remove_dead_animals()
    {
        for (Animal** p = A; p < op; ++p) {
            if (!(*p)->alive) {
                delete* p;
                --op;
                *p = *op; // copy last element
                --p;      // recheck same position
            }
        }

        // update number of animals
        n = op - A;
    }

    // data

    Animal** A;   // array of animal pointers (owner)
    int n;        // number of animals stored in A (can be < capacity)
    int capacity; // number of elements in A
    Animal** op;  // where to store offspring pointers, gets incemented after
                  // adding a new animal  
};

// implement ... Mouse, Goose, Rabbit, Bear here

struct Mouse : public Animal {
    Mouse(World& w) {
        this->age = 0;
        this->x = rand() % 100;
        this->y = rand() % 100;
        this->age = 0;
        char s[] = "Mouse";
        this->type = s;
    }
    void act(World& w) {
        x += 1;
    }

};

struct Goose : public Animal {
    Goose(World& w) {
        this->age = 0;
        this->x = rand() % 100;
        this->y = rand() % 100;
        this->age = 0;
        char s[] = "Goose";
        this->type = s;
    }
    void act(World& w) {
        y -= 1;
    }
};

struct Rabbit : public Animal {
    Rabbit(World& w) {
        this->age = 0;
        this->x = rand() % 100;
        this->y = rand() % 100;
        this->age = 0;
        char s[] = "Rabbit";
        this->type = s;
    }
    void act(World& w) {
        w.add_animal(this);
    }
};

struct Bear : public Animal {
    Bear(World& w) {
        this->age = 0;
        this->x = rand() % 100;
        this->y = rand() % 100;
        this->age = 0;
        char s[] = "Bear";
        this->type = s;
    }
    void act(World& w) {
        Animal a = w.get_random_animal();
        a->alive = 0;
    }
};

int main()
{
    /*
      initialize random number generator with current time (different seed
      each second)
      for testing you may want to fix the seed for reproducability

      note: this is old-school random number generation (man random); C++11
      provides a better random number generation facility
    */

    srandom(time(0));

    /* test code:

       populate world with some animals and simulate a few steps
    */

    // implement ...

    World w(7);
    w.add_animal(new Goose(w));
    w.add_animal(new Rabbit(w));
    w.add_animal(new Mouse(w));
    w.add_animal(new Goose(w));
    w.add_animal(new Bear(w));
    w.simulate(3);

        return 0;
}