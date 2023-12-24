
#include <span>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

class RadixSort {
    
    static constexpr int NUMBER_OF_DIGITS = 10;
    vector<int>& originalInput;

public:
    RadixSort(vector<int>& originalInput) : originalInput{originalInput}{}

    void sort() {
        int maxValue = 0;
        for (int value : originalInput) {
            maxValue = max(maxValue, value);
        }
        for (int digitPlace = 1; maxValue / digitPlace > 0; digitPlace *= 10) {
            sortByDigit(digitPlace);
        }
    }

private:
    void sortByDigit(int digitPlace) {
        array<int, NUMBER_OF_DIGITS>frequency{};
        for (const auto& value : originalInput) {
            ++frequency[(value / digitPlace) % 10];
        }

        array<int, NUMBER_OF_DIGITS> positionInSortForCurrentDigit{};
        positionInSortForCurrentDigit[0] = frequency[0];
        for (int i = 1; i < NUMBER_OF_DIGITS; ++i) {
            positionInSortForCurrentDigit[i] = frequency[i] + positionInSortForCurrentDigit[i - 1];
        }

        vector<int> sortedByCurrentDigit(originalInput.size());
        fill_sortedByCurrentDigit(sortedByCurrentDigit, positionInSortForCurrentDigit, digitPlace);
        updateOriginalInput(sortedByCurrentDigit);
    }

    //Alternatively, prior to C++20 versions:
    // ...(vector<int>& sortedByCurrentDigit, array<int, NUMBER_OF_DIGITS>& positionInCurrentSort, int digitPlace) ...
    void fill_sortedByCurrentDigit(span<int> sortedByCurrentDigit, span<int> positionInCurrentSort, int digitPlace) const {
        for (size_t i = originalInput.size() - 1; i != variant_npos; --i) {
            int index = positionInCurrentSort[(originalInput[i] / digitPlace) % 10] - 1;
            sortedByCurrentDigit[index] = originalInput[i];
            --positionInCurrentSort[(originalInput[i] / digitPlace) % 10];
        }
    }

    //Alternatively, prior to C++20 versions:
    // ...(const vector<int>& sortedByCurrentDigit)...
    void updateOriginalInput(span<const int> sortedByCurrentDigit) {
        for (size_t i = 0; i < originalInput.size(); ++i) {
            originalInput[i] = sortedByCurrentDigit[i];
        }
    }
};

class Solution {
    
public:
    int maxWidthOfVerticalArea(const vector<vector<int>>& points) const {

        vector<int> x_points(points.size());
        for (int i = 0; i < points.size(); ++i) {
            x_points[i] = points[i][0];
        }

        RadixSort radixSort(x_points);
        radixSort.sort();

        int maxWidthOfVerticalArea = 0;
        for (int i = 1; i < x_points.size(); ++i) {
            maxWidthOfVerticalArea = max(maxWidthOfVerticalArea, x_points[i] - x_points[i - 1]);
        }

        return maxWidthOfVerticalArea;
    }
};
