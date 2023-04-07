#ifndef HISTO_H
#define HISTO_H

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <utility>

class Histogram {
    public:
        // increment count for word w
        void count(const std::string &w){ has_string(w);}

        // print histogram in non-increasing count order to stream os
        void print(std::ostream &os) const{ make_sorted(os); }
    
    private:
    std::map<std::string, int> strings;
    void has_string(const std::string &w) //if the map has the string, increment count
    {
        auto it = strings.find(w);
        if (it != strings.end())
        {
            it->second += 1;
        } else
        {
            strings.insert({w,1}); //map doesn't have string so add it with a cout of one
        }
    }

    template <typename T1, typename T2>
    struct first_greater {
        bool operator()(std::pair<T1, T2> const& a, std::pair<T1, T2> const& b) const {
            return b.second < a.second; //return that the first value is greater than the second value
        }
    };
    
    void make_sorted(std::ostream &os) const
    {
        std::vector<std::pair<std::string, int>> count_sorted(strings.begin(), strings.end()); //copy map into a vector as pairs of key/value
        std::sort(count_sorted.begin(), count_sorted.end(), first_greater<std::string, int>()); //sord vector in descending order based on keys
        for (auto it = count_sorted.begin(); it != count_sorted.end(); ++it) //print out the key-value pair
        {
            os << (*it).first << " " << (*it).second << "\n";
        }
    }

};

#endif