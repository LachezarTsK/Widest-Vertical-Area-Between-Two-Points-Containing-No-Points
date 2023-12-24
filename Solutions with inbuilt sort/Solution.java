
import java.util.Arrays;

public class Solution {

    public int maxWidthOfVerticalArea(int[][] points) {
        Arrays.sort(points, (x, y) -> x[0] - y[0]);
        int maxWidthOfVerticalArea = 0;

        for (int i = 1; i < points.length; ++i) {
            maxWidthOfVerticalArea = Math.max(maxWidthOfVerticalArea, points[i][0] - points[i - 1][0]);
        }
        return maxWidthOfVerticalArea;
    }
}
