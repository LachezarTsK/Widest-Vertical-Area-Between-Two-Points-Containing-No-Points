
using System;

public class Solution
{
    public int MaxWidthOfVerticalArea(int[][] points)
    {
        Array.Sort(points, (x, y) => x[0] - y[0]);
        int maxWidthOfVerticalArea = 0;

        for (int i = 1; i < points.Length; ++i)
        {
            maxWidthOfVerticalArea = Math.Max(maxWidthOfVerticalArea, points[i][0] - points[i - 1][0]);
        }
        return maxWidthOfVerticalArea;
    }
}
