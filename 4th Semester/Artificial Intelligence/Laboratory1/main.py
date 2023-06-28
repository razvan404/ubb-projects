from task1.last_lexicographically import find_last_lexicographically
from task2.euclidean_distance import euclidean_distance
from task3.vectors_dot_product import vectors_dot_product
from task4.single_occurrence import single_occurrence
from task5.double_occurrence import double_occurrence
from task6.majority_element import majority_element
from task7.os_select import os_select
from task8.binary_list import binary_list
from task9.submatrices_sums import submatrices_sums
from task10.line_with_most_1s import line_with_most_1s

if __name__ == '__main__':
    task = 10

    if task == 1:
        print('Last lexicographically word:', find_last_lexicographically('Elon Musk nu are bani'))
    elif task == 2:
        print('Euclidean distance:', euclidean_distance([1, 5], [4, 1]))
    elif task == 3:
        print('Rare vectors dot product:', vectors_dot_product([1, 0, 2, 0, 3], [1, 2, 0, 3, 1]))
    elif task == 4:
        print('Single occurrence elements:', single_occurrence('ana are ana are mere rosii ana'))
    elif task == 5:
        print('Double occurrence element:', double_occurrence([1, 2, 3, 4, 2]))
    elif task == 6:
        print('Majority element:', majority_element([2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]))
    elif task == 7:
        print('Nth biggest number:', os_select([7, 4, 6, 3, 9, 1], 2))
    elif task == 8:
        print('Binary list:', binary_list(4))
    elif task == 9:
        print('Submatrices sums:', submatrices_sums([[0, 2, 5, 4, 1],
                                                     [4, 8, 2, 3, 7],
                                                     [6, 3, 4, 6, 2],
                                                     [7, 3, 1, 8, 3],
                                                     [1, 5, 7, 9, 4]], [[[1, 1], [3, 3]], [[2, 2], [4, 4]]]))
    elif task == 10:
        print('The line with the most 1s:', line_with_most_1s([[0, 0, 0, 1, 1],
                                                               [0, 1, 1, 1, 1],
                                                               [0, 0, 1, 1, 1]]))
