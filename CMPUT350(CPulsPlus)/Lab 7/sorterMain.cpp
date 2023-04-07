#include "Sorter.h"

int main()
{
    Sorter new_point_set;       //add multiple points
    new_point_set.add_point(3.6, 7);
    new_point_set.add_point(1, 5);
    new_point_set.add_point(0, 9.14);
    new_point_set.add_point(13, 6.5);
    new_point_set.add_point(1.19, 4);

    new_point_set.print_sorted_closest_to(2, 8);

    return 0;
}