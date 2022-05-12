#include"math.h"

int simulateThreshold(unsigned int num1, unsigned int num2) {
    unsigned int res = num1 * num2; /* mult1 */

    res <<= 3; /* bs1 */
    res *= num1; /* mult2 */
    res >>= 3; /* bs2 */
    res *= num2; /* mult3 */
    res <<= 3; /* bs3 */
    res *= num1; /* mult4 */
    res >>= 3; /* bs4 */

    res *= num2; /* mult5 */
    res = floorSqrt(res);
    res *= num1; /* mult6 */
    res /= num2; /* div1 */
    res *= num1; /* mult7 */
    res /= num2; /* div2 */
    res *= num1; /* mult8 */

    return res;
}
