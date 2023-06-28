# 7. Să se determine al k-lea cel mai mare element al unui șir de numere cu n elemente (k < n). De ex. al 2-lea cel mai
# mare element din șirul [7,4,6,3,9,1] este 7.
from typing import List
from random import randint


def partition(nums: List[int], left: int, right: int) -> int:
    pivot_index = randint(left, right)
    pivot = nums[pivot_index]
    nums[pivot_index], nums[right] = nums[right], nums[pivot_index]
    store_index = left

    for index in range(left, right):
        if nums[index] < pivot:
            nums[store_index], nums[index] = nums[index], nums[store_index]
            store_index += 1

    nums[right], nums[store_index] = nums[store_index], nums[right]
    return store_index


def os_select(nums: List[int], rank: int) -> int:
    left = 0
    right = len(nums) - 1
    rank_index = len(nums) - rank + 1

    while True:
        pivot_index = partition(nums, left, right)
        selected_index = pivot_index - left + 1

        if rank_index == selected_index:
            return nums[pivot_index]
        elif rank_index < selected_index:
            right = pivot_index - 1
        else:
            rank_index -= selected_index
            left = pivot_index + 1
