
/**
 * @param {number[][]} points
 * @return {number}
 */
var maxWidthOfVerticalArea = function (points) {
    points.sort((x, y) => x[0] - y[0]);
    let maxWidthOfVerticalArea = 0;

    for (let i = 1; i < points.length; ++i) {
        maxWidthOfVerticalArea = Math.max(maxWidthOfVerticalArea, points[i][0] - points[i - 1][0]);
    }
    return maxWidthOfVerticalArea;
};
