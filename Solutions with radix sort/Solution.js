
/**
 * @param {number[][]} points
 * @return {number}
 */
var maxWidthOfVerticalArea = function (points) {

    const x_points = new Array(points.length);
    for (let i = 0; i < points.length; ++i) {
        x_points[i] = points[i][0];
    }

    const radixSort = new RadixSort(x_points);
    radixSort.sort();

    let maxWidthOfVerticalArea = 0;
    for (let i = 1; i < x_points.length; ++i) {
        maxWidthOfVerticalArea = Math.max(maxWidthOfVerticalArea, x_points[i] - x_points[i - 1]);
    }
    return maxWidthOfVerticalArea;
};

class RadixSort {

    static NUMBER_OF_DIGITS = 10;

    /**
     * @param {number[][]} originalInput
     */
    constructor(originalInput) {
        this.originalInput = originalInput;
    }

    /**
     * @return {void} 
     */
    sort() {
        let maxValue = 0;
        for (let value of this.originalInput) {
            maxValue = Math.max(maxValue, value);
        }
        for (let digitPlace = 1; Math.floor(maxValue / digitPlace) > 0; digitPlace *= 10) {
            this.sortByDigit(digitPlace);
        }
    }

    /**
     * @param {number} digitPlace
     * @return {void}
     */
    sortByDigit(digitPlace) {
        const frequency = new Array(RadixSort.NUMBER_OF_DIGITS).fill(0);
        for (let value of this.originalInput) {
            ++frequency[Math.floor(value / digitPlace) % 10];
        }

        const positionInSortForCurrentDigit = new Array(RadixSort.NUMBER_OF_DIGITS);
        positionInSortForCurrentDigit[0] = frequency[0];
        for (let i = 1; i < RadixSort.NUMBER_OF_DIGITS; ++i) {
            positionInSortForCurrentDigit[i] = frequency[i] + positionInSortForCurrentDigit[i - 1];
        }

        const sortedByCurrentDigit = new Array(this.originalInput.length);
        this.fill_sortedByCurrentDigit(sortedByCurrentDigit, positionInSortForCurrentDigit, digitPlace);
        this.updateOriginalInput(sortedByCurrentDigit);
    }

    /**
     * @param {number[]} sortedByCurrentDigit
     * @param {number[]} positionInCurrentSort
     * @param {number} digitPlace
     * @return {void}
     */
    fill_sortedByCurrentDigit(sortedByCurrentDigit, positionInCurrentSort, digitPlace) {
        for (let i = this.originalInput.length - 1; i >= 0; --i) {
            let index = positionInCurrentSort[Math.floor(this.originalInput[i] / digitPlace) % 10] - 1;
            sortedByCurrentDigit[index] = this.originalInput[i];
            --positionInCurrentSort[Math.floor(this.originalInput[i] / digitPlace) % 10];
        }
    }

    /**
     * @param {number[]} sortedByCurrentDigit
     * @return {void}
     */
    updateOriginalInput(sortedByCurrentDigit) {
        for (let i = 0; i < this.originalInput.length; ++i) {
            this.originalInput[i] = sortedByCurrentDigit[i];
        }
    }
}
