
using System;

public class Solution
{
    public int MaxWidthOfVerticalArea(int[][] points)
    {
        int[] x_points = new int[points.Length];
        for (int i = 0; i < points.Length; ++i)
        {
            x_points[i] = points[i][0];
        }

        RadixSort radixSort = new RadixSort(x_points);
        radixSort.sort();

        int maxWidthOfVerticalArea = 0;
        for (int i = 1; i < x_points.Length; ++i)
        {
            maxWidthOfVerticalArea = Math.Max(maxWidthOfVerticalArea, x_points[i] - x_points[i - 1]);
        }
        return maxWidthOfVerticalArea;
    }
}

class RadixSort
{

    private static readonly int NUMBER_OF_DIGITS = 10;
    private readonly int[] originalInput;

    public RadixSort(int[] originalInput)
    {
        this.originalInput = originalInput;
    }

    public void sort()
    {
        int maxValue = 0;
        foreach (int value in originalInput)
        {
            maxValue = Math.Max(maxValue, value);
        }
        for (int digitPlace = 1; maxValue / digitPlace > 0; digitPlace *= 10)
        {
            sortByDigit(digitPlace);
        }
    }

    private void sortByDigit(int digitPlace)
    {
        int[] frequency = new int[NUMBER_OF_DIGITS];
        foreach (int value in originalInput)
        {
            ++frequency[(value / digitPlace) % 10];
        }

        int[] positionInSortForCurrentDigit = new int[NUMBER_OF_DIGITS];
        positionInSortForCurrentDigit[0] = frequency[0];
        for (int i = 1; i < NUMBER_OF_DIGITS; ++i)
        {
            positionInSortForCurrentDigit[i] = frequency[i] + positionInSortForCurrentDigit[i - 1];
        }

        int[] sortedByCurrentDigit = new int[originalInput.Length];
        fill_sortedByCurrentDigit(sortedByCurrentDigit, positionInSortForCurrentDigit, digitPlace);
        updateOriginalInput(sortedByCurrentDigit);
    }

    private void fill_sortedByCurrentDigit(int[] sortedByCurrentDigit, int[] positionInCurrentSort, int digitPlace)
    {
        for (int i = originalInput.Length - 1; i >= 0; --i)
        {
            int index = positionInCurrentSort[(originalInput[i] / digitPlace) % 10] - 1;
            sortedByCurrentDigit[index] = originalInput[i];
            --positionInCurrentSort[(originalInput[i] / digitPlace) % 10];
        }
    }

    private void updateOriginalInput(int[] sortedByCurrentDigit)
    {
        for (int i = 0; i < originalInput.Length; ++i)
        {
            originalInput[i] = sortedByCurrentDigit[i];
        }
    }
}
