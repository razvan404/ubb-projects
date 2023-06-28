# 5. Pentru un șir cu n elemente care conține valori din mulțimea {1, 2, ..., n - 1} astfel încât o singură valoare se
# repetă de două ori, să se identifice acea valoare care se repetă. De ex. în șirul [1,2,3,4,2] valoarea 2 apare de
# două ori.
from typing import List


def double_occurrence(nums: List[int]) -> int:
    nums_sum = sum(nums)
    return nums_sum - len(nums) * (len(nums) - 1) // 2
