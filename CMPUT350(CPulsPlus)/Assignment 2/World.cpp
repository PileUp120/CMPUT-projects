#include <cmath>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include "World.h"
#include "Unit.h"

using namespace std;

/* helper that you need to implement
   
 - move unit by (current_speed * heading)

 - units only collide with the map border
 
 - when a unit hits a wall it stops at the collision point (current_speed=0)
   and collision_hook needs to be called with the previous speed and an array
   of bools encoding all the walls that were hit (the array indexes need to be
   consistent with enum CollDir). This array is used to implement bouncing by
   only changing the unit's heading, i.e. even when bouncing the unit stays at
   the collision location for the remainder of the simulation frame and only
   starts moving again in the following frame

 - it is essential that units are located inside the map at all times. There
   can be no overlap. Ensure this property by clipping coordinates after
   moving

*/

void World::move_unit(Unit &u)
{
  // ... implement

    u.pos.x += (u.heading.x * u.max_speed);          //use the resultant heading to move the unit in the direction
    u.pos.y += (u.heading.y * u.max_speed);
}


// returns policy name
const char *apol2str(AttackPolicy pol)
{
  switch (pol) {
    case ATTACK_WEAKEST:
      return "attack-weakest";
    case ATTACK_CLOSEST:
      return "attack-closest";
    case ATTACK_MOST_DANGEROUS:
      return "attack-most-dangerous";
  }
  return "?";
}


World::~World()
{
  // clean up
  
  // ... implement

    auto iter = begin(units);
    for (; iter != units.end(); iter++) { 
        delete *iter;                                               //call the destructor for every unit so that the momory for them is freed
    }
    units.clear();
    units.shrink_to_fit();
}


// deducts hit points and calls attack_hook

void World::attack(Unit &attacker, Unit &attacked)
{
  // ... implement
    attacked.hp_old = attacked.hp;        //store the current hp of the attacked unit into it's hp_old
    attacked.hp -= attacker.damage;       //decrease the hp of the attacked unit based on the damage of the attacking unit
}


// return a random position at which a circle of that radius fits

Vec2 World::rnd_pos(double radius) const
{
  double slack = radius * 2;

  Vec2 p((width  - 2*slack) * rnd01() + slack,
         (height - 2*slack) * rnd01() + slack);
  
  // assert circle in rectangle
  assert(p.x > radius && p.x < width - radius);
  assert(p.y > radius && p.y < height - radius);
  return p;
}


// return uniform random heading
// length of vector = 1

Vec2 World::rnd_heading() const
{
  // implemented
    Vec2 head;
    srand(time(NULL));
    //generate a random coordinate in the range of width and height, then form a unit vector of that coordinate and return it
    double horizontal = ((double)rand() / RAND_MAX) * width;
    double vertical = ((double)rand() / RAND_MAX) * height;
    double uniter = sqrt(pow(horizontal, 2) + pow(vertical, 2));
    head.x = horizontal / uniter;
    head.y = vertical / uniter;
    assert((head.x >= 0) && (head.y >= 0));
    return head;
}

// mirror position with respect to map mid-point

Vec2 World::mirror(const Vec2 &pos) const
{
  // implemented
    Vec2 npos;
    double x_mid = width / 2;               //find the lines that divide the map in half, horizontally and vertically
    double y_mid = height / 2;
    double x_dist = abs(pos.x - x_mid);     //calculate the distance between the passed position and the dividing lines 
    double y_dist = abs(pos.y - y_mid);
    if (pos.x > x_mid) {                    //reflect x by the distance between it and the midpoint based on whether it is to the right or left of the midline
        npos.x = x_mid - x_dist;
    }
    else if (pos.x < x_mid) {
        npos.x = x_mid + x_dist;
    }
    else {
        npos.x = x_mid;                     //return the midline if x is on it
    }

    if (pos.y > y_mid) {                //reflect y by the distance between it and the midpoint based on whether it is above or below the midline
        npos.y = y_mid - y_dist;
    }
    else if (pos.y < y_mid) {
        npos.y = y_mid + y_dist;
    }
    else {
        npos.y = y_mid;                 //return the midline if y is on it
    }

    return npos;
}


// return squared distance between two unit centers

double World::distance2(const Unit &u, const Unit &v)
{
  // implement
    double dist = pow((u.pos.x-v.pos.x),2) + pow((u.pos.y-v.pos.y),2);      //square of distance between 2 points by the pythagoras formula
    return dist;
}

// return true iff u can attack v, i.e. distance of u's and v's centers is
// less than u's attack distance plus v's radius
bool World::can_attack(const Unit &u, const Unit &v)
{
  // implemented
    bool attackable = false;
    if (sqrt(distance2(u,v)) < (u.attack_radius + v.radius)) {      //check if the distance between u and v is small enough according to criteria
        attackable = true;
    }
    return attackable;
}

// populate a vector with enemy units that can be attacked by u;
// clears vector first
void World::enemies_within_attack_range(const Unit &u,
                                        vector<Unit*> &targets) const
{
  targets.clear();

  // ... implement
  auto iter = begin(units);
  for (; iter != units.end(); ++iter) {         //iterate through the vector of units and adds them if they can be attacked
      if (can_attack(u, *(*iter))) {
          targets.push_back((*iter));
      }
  }

  // use push_back to add elements to targets
}

// return a random unit that can be attacked by u with minimal hp_old value,
// or 0 if none exists

Unit *World::random_weakest_target(Unit &u) const
{
  vector<Unit*> targets;
  enemies_within_attack_range(u, targets);

  if (targets.empty()) {
      return 0;
  }
  else {
      Unit* lowest_hp_unit = targets.front();

      auto iter = begin(units);
      for (; iter != units.end(); iter++) {                 //iterate through vector of attackable targets and pick the one with the one with the lowest hp
          if ((*iter)->hp_old < lowest_hp_unit->hp_old) {
              lowest_hp_unit = (*iter);
          }
      }

      vector<Unit*> prime_targets;

      auto it = begin(targets);
      for (; it != targets.end(); it++) {                 //iterate through vector of attackable targets and remove those with invalid conditions
          if ((*it)->hp_old == lowest_hp_unit->hp_old) {
              prime_targets.push_back(*it);
          }
      }

      srand(time(NULL));

      lowest_hp_unit = prime_targets[rand() % prime_targets.size()];

      return lowest_hp_unit;
  }
  // ... implement
}


// return a random unit that can be attacked by u with minimal distance to
// u, or 0 if none exists

Unit *World::random_closest_target(Unit &u) const
{
  vector<Unit*> targets;
  enemies_within_attack_range(u, targets);

  if (targets.empty()) {
      return 0;
  }
  else {
      Unit* min_dist_unit = targets.front();

      auto iter = begin(units);
      for (; iter != units.end(); iter++) {
          if (distance2(u, *(*iter)) < distance2(u, *min_dist_unit)) {            //iterate through vector of attackable targets and pick the one with the one closest to the unit
              min_dist_unit = (*iter);
          }
      }

      vector<Unit*> prime_targets;

      auto it = begin(targets);
      for (; it != targets.end(); it++) {                 //iterate through vector of attackable targets and remove those with invalid conditions
          if (distance2(u, *(*it)) == distance2(u, *min_dist_unit)) {
              prime_targets.push_back(*it);
          }
      }

      srand(time(NULL));

      min_dist_unit = prime_targets[rand() % prime_targets.size()];

      return min_dist_unit;
  }
  // ... implement
}


// return a random unit that can be attacked by u with maximal damage/hp_old
// ratio, or 0 if none exists

Unit *World::random_most_dangerous_target(Unit &u) const
{
  vector<Unit*> targets;
  enemies_within_attack_range(u, targets);

  if (targets.empty()) {
      return 0;
  }
  else {
      Unit* big_danger_unit = targets.front();

      auto iter = begin(units);
      for (; iter != units.end(); iter++) {
          if (((*iter)->damage / (*iter)->hp_old) > (big_danger_unit->damage / big_danger_unit->hp_old)) {  //iterate through vector of attackable targets and pick the most dangerous one based on criteria
              big_danger_unit = (*iter);
          }
      }

      vector<Unit*> prime_targets;

      auto it = begin(targets);
      for (; it != targets.end(); it++) {                 //iterate through vector of attackable targets and remove those with invalid conditions
          if (((*it)->damage / (*it)->hp_old) == (big_danger_unit->damage / big_danger_unit->hp_old)) {
              prime_targets.push_back(*it);
          }
      }

      srand(time(NULL));

      big_danger_unit = prime_targets[rand() % prime_targets.size()];

      return big_danger_unit;
  }
  // ... implement
}


// return score for red: 2 for win, 0 for loss, 1 for draw, -1 for game not
// over yet

int World::red_score() const
{
  if (units.empty()) {
    return 1;
  }
  else {
      Team team_of_first = units[0]->team;      //check the team of the first unit
      auto iter = begin(units);
      for (; iter != units.end(); iter++) {
          if ((*iter)->team != team_of_first) {         //a member of the opposing team was found, the game is not over
              return -1;                
              break;
          }
          else {
              if (team_of_first == RED) {       //no team members of the opposing team found, return 2 is first is RED, return 0 otherwise
                  return 2;
              }
              else {
                  return 0;
              }
              
          }
      }
  }

  //interate through the vector of units, if any blue units found, break and return -1, if no blue units found return 2
  

  // ... implement
}

