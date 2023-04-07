#pragma once

#include <vector> // used for storing paths

#include "GridInclude.h" // add needed #include lines to this file

class Grid
{
public: 

  // no changes in the public interface!

  // data

  enum Tile { GROUND, WATER, BLOCKED };
    
  enum Direction { N, NE, E, SE, S, SW, W, NW };
    
  static const int CARDINAL_COST = 100; // Cost to move in cardinal direction
  static const int DIAGONAL_COST = 142; // Cost to move diagonally
  // (>100*sqrt(2) => air distance is admissible)

  // methods

  Grid(int width, int height);
  ~Grid();
    
  // Map properties
  int getWidth() const;
  int getHeight() const;

  // tile setter/getter
  Tile getTile(int x, int y) const;
  void setTile(int x, int y, Tile tile);
    
  // Pathfinding operations

  // Return true iff object with a given size can reside on (x1, y1)
  // and move from there to (x2, y2) while staying at the same tile
  // type without colliding 
  //
  // This should execute faster than calling findShortestPath()
  // 
  // Also, if the map hasn't changed, subsequent calls with the same
  // x1,y1,x2,y2 coordinates SHOULD BE MUCH FASTER. Hint: flood fill + caching
  bool isConnected(int size, int x1, int y1, int x2, int y2) const;

  // Compute a shortest path from (x1, y1) to (x2, y2) for an object with a
  // given size using A*. Store the shortest path into path, and return the
  // cost of that path (using CARDINAL_COST for the moves N, E, S, and W, and
  // DIAGONAL_COST for the moves NE, SE, SW, and NW) or -1 if there is no
  // path
  int findShortestPath(int size, int x1, int y1, int x2, int y2, 
                       std::vector<Direction> &path) const;
private:

  // add private members in file below

#include "GridPriv.h"
};
