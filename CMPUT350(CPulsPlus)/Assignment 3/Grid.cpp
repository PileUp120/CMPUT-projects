#include "Grid.h"

#include "GridInclude.h"

typedef std::array<int, 5> data; //an array of ints intended to store {fcost, hcost, gcost, parent x, parent y} for a given x1/y1
typedef std::array<int, 2> node; //an array to store a node in the format {x1, y1}
typedef std::map<node, data> node_info; //a map storing information for a node

typedef std::pair<node, data> created_node; //create a pair of node/data to be inserted into the closed or open lists
typedef std::array<int, 7> open_node; // store the combined info of node and data so that the open list can sort based on f-cost, in format {fcost, hcost, gcost, parent x, parent y, x1, y1}
typedef std::priority_queue<open_node, std::vector<open_node>, std::greater<open_node>> lowest_first_queue; //a priority queue that has the lowest element first

created_node make_cnode(open_node& node) //return a created_node type given an open_node type
{
	created_node c_node({ node[5], node[6] }, { node[0], node[1], node[2], node[3], node[4] });
	return c_node;
}

open_node calculate_costs(int orig_x, int orig_y, int x, int y, int goal_x,int goal_y, int parent_x, int parent_y) //cost set = {fcost, hcost, gcost, x1, y1}
{
	int x_diff = abs(goal_x - x); // x/y distance from this node to the goal
	int y_diff = abs(goal_y - y); 
	int from_org_x = abs(x - orig_x); // x/y distance from the starting node to this node
	int from_org_y = abs(y - orig_y);
	int h_cost, g_cost, f_cost;

	if (x_diff == 0 && y_diff == 0)  //this is the goal node, so find only the gcost
	{
		h_cost = 0;
		g_cost = CARDINAL_COST * (from_org_x + from_org_y) + (DIAGONAL_COST - 2 * CARDINAL_COST) * min(from_org_x, from_org_y);
	}
	else if (from_org_x == 0 && from_org_y == 0) //this is the starting node so find only the hcost
	{
		h_cost = CARDINAL_COST * (x_diff + y_diff) + (DIAGONAL_COST - 2 * CARDINAL_COST) * min(x_diff, y_diff);
		g_cost = 0;
	}
	else //find the gcost and the hcost
	{
		h_cost = CARDINAL_COST * (x_diff + y_diff) + (DIAGONAL_COST - 2 * CARDINAL_COST) * min(x_diff, y_diff);
		g_cost = CARDINAL_COST * (from_org_x + from_org_y) + (DIAGONAL_COST - 2 * CARDINAL_COST) * min(from_org_x, from_org_y);
	}

	f_cost = h_cost + g_cost;

	open_node this_node = { f_cost, h_cost, g_cost, parent_x, parent_y , x, y };
	return this_node;
}

void find_nodes(int size, open_node &curr_node, int orig_x, int orig_y, int goal_x, int goal_y, Grid::Tile sc_tile, node_info const *closed, lowest_first_queue *open, Grid *g)
{
	bool mv_right = true, mv_left = true, mv_up = true, mv_down = true;

	if ((curr_node[5] + size + 1) <= width && (curr_node[6] + size) <= height) //verify the unit can move cardinally right
	{
		int i = curr_node[5] + size + 1;
		for (int j = curr_node[6]; j <= (curr_node[6] + size); j++)
		{
			if (!(g->getTile(i, j) == sc_tile))
			{
				mv_right = false; //unit cannot move cardinally right because of clipping
			}
		}
	}
	if (mv_right && (closed->find({ curr_node[5] + 1, curr_node[6] }) == closed->end())) //since unit can move right, add the node to it's right into the open queue
	{
		open_node new_node = calculate_costs(orig_x, orig_y, curr_node[5] + 1, curr_node[6], goal_x, goal_y, curr_node[5], curr_node[6]);
		open_nodes.push(new_node);
	}

	if ((curr_node[5] - 1) >= 0 && (curr_node[6] + size) <= height) //verify the unit can move cardinally left
	{
		int i = curr_node[5] - 1;
		for (int j = curr_node[6]; j <= (curr_node[6] + size); j++)
		{
			if (!(getTile(i, j) == sc_tile))
			{
				mv_left = false; //unit cannot move cardinally leftt because of clipping
			}
		}
	}
	if (mv_left && (closed->find({ curr_node[5] - 1, curr_node[6] }) == closed->end()))
	{
		open_node new_node = calculate_costs(orig_x, orig_y, curr_node[5] - 1, curr_node[6], goal_x, goal_y, curr_node[5], curr_node[6]);
		open_nodes.push(new_node);
	}

	if ((curr_node[5] + size) <= width && (curr_node[6] - 1) >= 0) //verify the unit can move cardinally up
	{
		int j = curr_node[6] - 1;
		for (int i = curr_node[5]; i <= (curr_node[5] + size); i++)
		{
			if (!(getTile(i, j) == sc_tile))
			{
				mv_up = false; //unit cannot move cardinally up because of clipping
			}
		}
	}
	if (mv_up && (closed->find({ curr_node[5] , curr_node[6] - 1}) == closed->end()))
	{
		open_node new_node = calculate_costs(orig_x, orig_y, curr_node[5], curr_node[6] - 1, goal_x, goal_y, curr_node[5], curr_node[6]);
		open_nodes.push(new_node);
	}

	if ((curr_node[5] + size) <= width && (curr_node[6] + size + 1) <= height) //verify the unit can move cardinally down
	{
		int j = curr_node[6] + size + 1;
		for (int i = curr_node[5]; i <= (curr_node[5] + size); i++)
		{
			if (!(getTile(i, j) == sc_tile))
			{
				mv_down = false; //unit cannot move cardinally up because of clipping
			}
		}
	}
	if (mv_down && (closed->find({ curr_node[5], curr_node[6] + 1 }) == closed->end()))
	{
		open_node new_node = calculate_costs(orig_x, orig_y, curr_node[5], curr_node[6] + 1, goal_x, goal_y, curr_node[5], curr_node[6]);
		open_nodes.push(new_node);
	}

	if (mv_down && mv_right && (g->getTile(curr_node[5] + size + 1, curr_node[6] + size + 1) == sc_tile)) //unit cannot move south east
	{
		open_node new_node = calculate_costs(orig_x, orig_y, curr_node[5] + 1, curr_node[6] + 1, goal_x, goal_y, curr_node[5], curr_node[6]);
		open_nodes.push(new_node);
	}
	if (mv_down && mv_left && (g->getTile(curr_node[5] - 1, curr_node[6] + size + 1) == sc_tile)) //unit cannot move south west
	{
		open_node new_node = calculate_costs(orig_x, orig_y, curr_node[5] - 1, curr_node[6] + 1, goal_x, goal_y, curr_node[5], curr_node[6]);
		open_nodes.push(new_node);
	}
	if (mv_up && mv_right && (g->getTile(curr_node[5] + size + 1, curr_node[6] - 1) == sc_tile)) //unit cannot move north east
	{
		open_node new_node = calculate_costs(orig_x, orig_y, curr_node[5] + 1, curr_node[6] - 1, goal_x, goal_y, curr_node[5], curr_node[6]);
		open_nodes.push(new_node);
	}
	if (mv_up && mv_left && (g->getTile(curr_node[5] - 1, curr_node[6] - 1) == sc_tile)) //unit cannot move north west
	{
		open_node new_node = calculate_costs(orig_x, orig_y, curr_node[5] - 1, curr_node[6] - 1, goal_x, goal_y, curr_node[5], curr_node[6]);
		open_nodes.push(new_node);
	}
}
//...need to implement
void trace_back(node_info const &closed, std::vector<Grid::Direction>& path)
{
	typedef std::array<int, 7> no_fcost; //since a path has been found, fcost is no longer needed, this array stores {hcost, gcost, x, y, parent_x, parent_y}
	std::set<no_fcost> reduced_closed;
	std::vector<Grid::Direction> path_back;
	for (auto it = closed.begin(); it != closed.end(); it++)
	{
		no_fcost _node = {};
		reduced_closed.insert(_node);
	}


}

Grid::Grid(int width, int height)
{
	//set grid width and height
	this->width = width;
	this->height = height;

	this->isCon_calledBefore = false;
}
Grid::~Grid()
{
	//destroy grid
	for (auto it = gridTiles.begin(); it != gridTiles.end(); ++it) //iterate through grid tiles and delete individual nodes
	{
		delete (*it);
	}
	delete gridTiles; //delete the container to free space

	used_coords.clear(); //empty the map structure
}

// Map properties
int Grid::getWidth() const
{
	return this->width;
}

int Grid::getHeight() const
{
	return this->height;
}

// tile setter/getter
Grid::Tile Grid::getTile(int x, int y) const
{
	assert(x >= 0 && x <= width);
	assert(y >= 0 && y <= height);
	//return the tile in which this set of x/y coordinates lie;
	return gridTiles[x][y];
}
void Grid::setTile(int x, int y, Tile tile)
{
	//set the tile at a particular coordinate to type "tile"
	assert(x >= 0 && x <= width);
	assert(y >= 0 && y <= height);

	gridTiles[x][y] = tile;
}
// Pathfinding operations

// Return true iff object with a given size can reside on (x1, y1)
// and move from there to (x2, y2) while staying at the same tile
// type without colliding 
//
// This should execute faster than calling findShortestPath()
// 
// Also, if the map hasn't changed, subsequent calls with the same
// x1,y1,x2,y2 coordinates SHOULD BE MUCH FASTER. Hint: flood fill + caching
bool Grid::isConnected(int size, int x1, int y1, int x2, int y2) const
{
	assert(x1 >= 0 && x1 <= width);
	assert(y1 >= 0 && y1 <= height);
	assert(x2 >= 0 && x2 <= width);
	assert(y2 >= 0 && y2 <= height);
	bool connected;

	if (getTile(x1, y1) != getTile(x2, y2))
	{
		//first check that tile at x1/y1 and x2/y2 is of the same type, if not return false immediately
		connected = false;
	}
	else if (x1 == x2 && y1 == y2) //the given node is the goal node, or the goal noad has been reached
	{
		connected = true;
	}
	else
	{
		if (!used_coords.empty() && (used_coords.find({size, x1, y1, x2, y2 }) != used_coords.end()))
		{
			//the function has been called before with this exact same x1/y1 x2/y2 pair, so retrieve the connected value
			connected = used_coords[{x1, y1, x2, y2}];
		}
		else //the particular coordinate pair wasn't sent to the function before
		{
			std::set<node> visited_nodes; //a set to store nodes that have been visited during bfs
			std::set<node> open_nodes; // a set to store nodes that have not been visited during bfs

			Tile sc_tile = getTile(x1, y1);
			connected = false; //assume by default that the nodes are not connected so that if all open nodes are exhaused, there is an end condition
			
			visited_nodes.insert({ x1,y1 }); //add the starting node to visited
			
			for (int i = x1 - 1; i <= x1 + 1; i++) //iterate every node in a (size+1)x(size+1) scope to look for potential open nodes
			{
				for (int j = y1 - 1; j <= y1 + 1; j++)
				{
					//the set container does not allow duplicates, so if a tile is of the same type, add it to the open set if it hasn't been visited
					if (i >= 0 && i <= width && j >= 0 && j <= width && (getTile(i, j) == sc_tile) && (visited_nodes.find({ i,j }) == visited_nodes.end())) //do not go out of bounds when adding open nodes
					{
						open_nodes.insert({ i, j });
					}
				}
			}
											/*this block is mainly to make sure that a unit of size 1 or 2 can traverse cardinally,
									it likely won't affect size 0 cardinal movements, but is needed to check diagonal movements for all three sizes*/
			bool mv_right = true, mv_left = true, mv_up = true, mv_down = true;
			if ((x1 + size + 1) <= width && (y1 + size) <= height) //verify the unit can move cardinally right
			{
				int i = x1 + size + 1;
				for (int j = y1; j <= (y1 + size); j++)
				{
					if (!(getTile(i, j) == sc_tile))
					{
						mv_right = false; //unit cannot move cardinally right because of clipping
					}
				}
			}
			if (!mv_right)
			{
				visited_nodes.insert({ x1 + 1,  y1 }); // remove the associated node from open nodes
				open_nodes.erase({ x1 + 1,  y1 });
			}

			if ((x1 - 1) >= 0 && (y1 + size) <= height) //verify the unit can move cardinally left
			{
				int i = x1 - 1;
				for (int j = y1; j <= (y1 + size); j++)
				{
					if (!(getTile(i, j) == sc_tile))
					{
						mv_left = false; //unit cannot move cardinally leftt because of clipping
					}
				}
			}
			if (!mv_left)
			{
				visited_nodes.insert({ x1 - 1 ,  y1 }); //remove the associated node from open nodes
				open_nodes.erase({ x1 - 1,  y1 });
			}

			if ((x1 + size) <= width && (y1 - 1) >= 0) //verify the unit can move cardinally up
			{
				int j = y1 - 1;
				for (int i = x1; i <= (x1 + size); i++)
				{
					if (!(getTile(i, j) == sc_tile))
					{
						mv_up = false; //unit cannot move cardinally up because of clipping
					}
				}
			}
			if (!mv_up)
			{
				visited_nodes.insert({ x1 ,  y1 - 1 }); // remove the associated node from open nodes
				open_nodes.erase({ x1 ,  y1 - 1 });
			}

			if ((x1 + size) <= width && (y1 + size + 1) <= height) //verify the unit can move cardinally down
			{
				int j = y1 + size + 1;
				for (int i = x1; i <= (x1 + size); i++)
				{
					if (!(getTile(i, j) == sc_tile))
					{
						mv_down = false; //unit cannot move cardinally up because of clipping
					}
				}
			}
			if (!mv_down)
			{
				visited_nodes.insert({ x1 ,  y1 + size + 1 }); // remove the associated node from open nodes
				open_nodes.erase({ x1 ,  y1 + size + 1 });
			}
														
													/*this block makes sure that a unit can move diagonally without clipping*/
			if (!(mv_down && mv_right)) //unit cannot move south east
			{
				visited_nodes.insert({ x1 + 1,  y1 + 1 }); // remove the associated node from open nodes
				open_nodes.erase({ x1 + 1,  y1 + 1 });
			}
			if (!(mv_down && mv_left)) //unit cannot move south west
			{
				visited_nodes.insert({ x1 - 1,  y1 + 1 }); // remove the associated node from open nodes
				open_nodes.erase({ x1 - 1,  y1 + 1 });
			}
			if (!(mv_up && mv_right)) //unit cannot move north east
			{
				visited_nodes.insert({ x1 + 1,  y1 - 1 }); // remove the associated node from open nodes
				open_nodes.erase({ x1 + 1,  y1 - 1 });
			}
			if (!(mv_up && mv_left)) //unit cannot move north west
			{
				visited_nodes.insert({ x1 - 1,  y1 - 1 }); // remove the associated node from open nodes
				open_nodes.erase({ x1 - 1,  y1 - 1 });
			}

			//recursively call isConnected on all the open nodes with x2/y2 as target destination until open nodes are empty or the destination has been found

			for (auto it = open_nodes.begin(); it != open_nodes.end(); ++it)
			{
				connected = isConnected(size, *(*it)[0], *(*it)[1], x2, y2);
				if (connected) //found that the tiles are connected, so break out of iteration
				{
					break;
				}
			}
		}
	}
	
	isCon_calledBefore += 1; //remember that isConnected has been called before
	used_coords[{size, x1, y1, x2, y2}] = connected; //cache the result of calling isConnected with this particular data set for future reference
	visited_nodes.clear();
	open_nodes.clear();
	return connected;
}

// Compute a shortest path from (x1, y1) to (x2, y2) for an object with a
// given size using A*. Store the shortest path into path, and return the
// cost of that path (using CARDINAL_COST for the moves N, E, S, and W, and
// DIAGONAL_COST for the moves NE, SE, SW, and NW) or -1 if there is no
// path
int Grid::findShortestPath(int size, int x1, int y1, int x2, int y2,
	std::vector<Direction>& path) const
{
	assert(x1 >= 0 && x1 <= width);
	assert(y1 >= 0 && y1 <= height);
	assert(x2 >= 0 && x2 <= width);
	assert(y2 >= 0 && y2 <= height);

	int totalPathCost = 0; //initialise total path cost with 0, in case x1/y1 is the goal node

	if (isConnected(size, x1, y1, x2, y2))		//attempt to find a path if the cells are connected, otherwise return -1
	{
		if (x1 == x2 && y1 == y2) //no need to calcualte shortest path bacuse the starting node is the goal node
		{
			break;
		}

		node_info closed_nodes; //stores all closed nodes as pairs of {x1, y1}:{fcost, hcost, gcost, parent x, parent y}
		lowest_first_queue open_nodes; //priority queue with lowest fcost element on top, has all data that closed node would need

		Tile sc_tile = getTile(x1, y1);
		open_node curr_node = calculate_costs(x1, y1, x1, y1, x2, y2, -1, -1); //set the "parent" of the starting node to -1,-1 so that when path is found, the function knows that this is the starting node
		find_nodes(size, curr_node, x1, y1, x2, y2, sc_tile, &closed_nodes, &open_nodes, this);
		closed_nodes.insert(make_cnode(curr_node));
		
		while (!open_nodes.empty())
		{
			//pop a node and find potential open nodes around it
			curr_node = open_nodes.top();
			closed_nodes.insert(make_cnode(curr_node));
			open_nodes.pop();
			if (curr_node[1] == 0) //hcost is zero, so the goal node has been reached
			{
				break;
			}
			find_nodes(size, curr_node, x1, y1, x2, y2, sc_tile, &closed_nodes, &open_nodes, this);
		}

		trace_back(closed_nodes, path);

		for (auto it = path.begin(); it != path.end(); ++it)
		{
			if ((*it) == N || (*it) == E || (*it) == S || (*it) == W) {
				totalPathCost += DIAGONAL_COST;
			}
			else if ((*it) == NE || (*it) == SE || (*it) == SW || (*it) == NW)
			{
				totalPathCost += DIAGONAL_COST;
			}
		}
	}
	else 
	{
		totalPathCost = -1;
	}

	return totalPathCost;
}