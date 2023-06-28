from typing import List, Union


def line_with_most_1s(matrix: List[List[int]]) -> Union[List[int], int]:
    ans = []
    smallest_1_index = len(matrix[0]) - 1
    index = 0

    for line in matrix:
        if line[smallest_1_index] == 0:
            continue

        left = 0
        right = smallest_1_index

        while left <= right:
            mid = (left + right) // 2
            if line[mid] is 0:
                left = mid + 1
            else:
                right = mid - 1

        if left < smallest_1_index:
            smallest_1_index = left
            ans = [index]
        elif left == smallest_1_index:
            ans.append(index)
        index += 1

    return ans[0] if len(ans) is 1 else ans
