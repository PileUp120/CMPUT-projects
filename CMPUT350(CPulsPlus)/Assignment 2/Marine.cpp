#include "Marine.h"
#include "World.h"
#include <vector>
using namespace std;

// ... implement

Marine::Marine(Team team, const Vec2& pos, AttackPolicy pol, bool bounce) : Unit(team, pos, 10, 40, 10, 1, 45){
	this->policy = pol;
	this->bounce = bounce;
}

// execute one attack depending on policy
// when attacking you need to call w.attack
void Marine::act(World& w) {
	//move in the direction of the unit vector at it's speed
	w.move_unit(*this);
	
	//attack if there is an enemy unit nearby
	vector<Unit*> targets;
	w.enemies_within_attack_range(*this, targets);
	
	if (!targets.empty()) {
		//based on poilcy choose on of the 3 functions to 
		switch (policy) {
		case ATTACK_WEAKEST: 
			w.attack(*this, *(w.random_weakest_target(*this))); //attack a random weak target in range
			break;
		case ATTACK_MOST_DANGEROUS: 
			w.attack(*this, *(w.random_most_dangerous_target(*this))); //attack random most dangerous target in range
			break;
		case ATTACK_CLOSEST: w.attack(*this, *(w.random_most_dangerous_target(*this))); //attack a random closest target in range
			break;
		default:
			break;
		}
	}
	
	//when colliding with a wall, identify the collided side and call collision hook by passing a bool array with the collided direction and the max speed
	if ((pos.x >= (w.width - this->radius)) || (pos.x <= this->radius) || (pos.y >= (w.height - this->radius)) || (pos.y <= this->radius)) {
		bool collided[4] = { 0 };
		if (pos.x >= (w.width - this->radius)) {					//if-else block is used to ensure that the correct action is taken when colliding with corners, as in both x and y is an extreme value
			collided[RIGHT] = RIGHT + 1;
		}
		else if (pos.x <= this->radius) {
			collided[LEFT] = LEFT + 1;
		}
		if (pos.y >= (w.height - this->radius)) {
			collided[TOP] = TOP + 1;
		}
		else if (pos.y <= this->radius) {
			collided[BOTTOM] = BOTTOM + 1;
		}
		collision_hook(max_speed, collided);
	}
}

// deal with wall collisions depending on bounce
void Marine::collision_hook(double prev_speed, bool collisions[4]) {
	if (this->bounce) {
		if (collisions[0] || collisions[1]) {
			this->heading.x *= -1;
			this->current_speed = prev_speed;
		}
		if (collisions[2] || collisions[3]) {
			this->heading.y *= -1;
			this->current_speed = prev_speed;
		}
	}
	else {
		this->heading.x = 0;
		this->heading.y = 0;
	}
}
