#include <iostream>
#include <cmath>
#include <set>
#include <array>
#include <algorithm>
#include <vector>

class Sorter
{
    public:

    void add_point(float x, float y){ points.insert({x,y});}

    void print_sorted_closest_to(float x, float y){print_sorted(x,y);}

    private:

    std::set<std::array<float, 2>> points;

    void print_sorted(float x, float y) {
        std::vector<std::array<float, 3>> coords_distances;
        //calculate distances from the coordinate to each of the points and store in the array in the format {distance, x, y}
        for(auto it = points.begin(); it != points.end(); ++ it)
        {
            coords_distances.insert({sqrt(((*it)), *it[0], *it[1]});
        }
        std::sort(coords_distances.begin(), coords_distances.end());
    }
};