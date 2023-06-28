# 6. Pentru un șir cu n numere întregi care conține și duplicate, să se determine elementul majoritar (care apare de
# mai mult de n / 2 ori). De ex. 2 este elementul majoritar în șirul [2,8,7,2,2,5,2,3,1,2,2].
from typing import List


def majority_element(nums: List[int]) -> int:
    flag = 0
    current_majority = nums[0]

    for num in nums[1:]:
        if num != current_majority:
            if flag == 0:
                current_majority = num
            else:
                flag -= 1
        else:
            flag += 1

    return current_majority
