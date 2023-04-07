#include "Triang.h"
#include <cassert>

// return < 0 if point p lies in the interior
// return = 0 if point p lies on the perimeter
// return > 0, otherwise
// assumes triangle points in clockwise order
//
// Hint: use orientation() exactly 3 times and distinguish cases given by the
//       number of results <,=,> 0
//
int Triangle::inside_test(const Point &p) const
{
  // ... implement ...
  Coordinate p0p1p, p0p2p, p1p2p;
  p0p1p = orientation_test(points[0], points[1], p);
  p0p2p = orientation_test(points[0], points[2], p);
  p1p2p = orientation_test(points[1], points[2], p);

  if((p0p2p > 0) || (p0p1p < 0) || (p1p2p < 0))
  {
      return -1;
  }

  if((p0p1p == 0) || (p0p2p == 0) || (p1p2p == 0))
  {
    return 0;
  }

  return 1;
}


// store dimensions and triangulate bounding rectangle
// (0,0)->(w,0)->(w,h)->(0,h)->(0,0)
// Outside facing edges need to contain index BORDER
// precond: w, h > 0
//
// Hint: at the end the triangulation must contain two triangles which
// together represent the rectangle.  Both triangles must be oriented
// clockwise - which can be checked with Triangle::check()
//
//          BORDER
// (0,h)    _|_ (w,h)
//         |  /|
// BORDER<-| / |->BORDER
//         |/__|
// (0,0)     |  (w,0)
//          BORDER
// 
Triangulation::Triangulation(Coordinate w, Coordinate h)
{
  // ... implement ...
  assert(w > 0);
  assert(h > 0);
  
  Point p1(0,0), p2(0,w), p3(0,h), p4(w,h);
  Triangle t1, t2;

  t1.points[0] = t2.points[0] = p1;
  t1.points[2] = t2.points[1] = p4;
  t1.points[1] = p3;
  t2.points[2] = p2;

  t1.neighbors[0] = t1.neighbors[1] = t2.neighbors[1] = t2.neighbors[2] = Triangle::BORDER;
  t1.neighbors[2] = 1;
  t2.neighbors[0] = 0;

  t1.check();
  t2.check();
  
  triangles.push_back(t1);
  triangles.push_back(t2);
}

// Check every triangle once by visiting all of its edges and flipping those
// that increase the minimum interior angle locally.
// If flag is set, stop after first flip.
// return number of flipped edges (0 => done)
//
// Hint: use flip_if_better()
//
size_t Triangulation::Delaunay_pass(bool stop_after_first)
{
  // ... implement ...
  size_t edges_flipped = triangles.size();
  auto it = triangles.begin();
  for (edges_flipped; edges_flipped >= 0; edges_flipped--)
  {
    for (int i = 0; i <= 2; i++)
    {
      flip_if_better(edges_flipped, i);
    }
  }


  return edges_flipped;
}


// return index of a triangle that contains p (on perimiter or interior) using
// an algorithm of your choice
//
// pre-cond: p lies inside bounding rectangle or on its perimeter
//
size_t Triangulation::locate(const Point &p) const
{
  // ... implement ...
  assert(p.x >= 0 && p.x <= width);
  assert(p.y >= 0 && p.y <= height);

  size_t index = 0;

  for(index; index <= triangles.size(); index++)
  {
    int contains = triangles[index].inside_test(p);
    if(contains == 1)
    {
      break;
    }
  }

  if (index > triangles.size())
  {
    index = -1;
  }

  return index;
}
