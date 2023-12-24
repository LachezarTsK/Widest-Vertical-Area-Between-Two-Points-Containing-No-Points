
#include <ranges>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) const {
        
        //Alternatively, applying prior to C++20 versions: sort(points.begin(), points.end(), lambda expression) 
        ranges::sort(points, [](const vector<int>& a, const vector<int>& b){ return a[0] < b[0]; });
        int maxWidthOfVerticalArea = 0;

        for (size_t i = 1; i < points.size(); ++i) {
            maxWidthOfVerticalArea = max(maxWidthOfVerticalArea, points[i][0] - points[i - 1][0]);
        }
        return maxWidthOfVerticalArea;
    }
};
