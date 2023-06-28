# 9. Considerându-se o matrice cu n x m elemente întregi și o listă cu perechi formate din coordonatele a 2 căsuțe din
# matrice ((p,q) și (r,s)), să se calculeze suma elementelor din sub-matricile identificate de fieare pereche.
from typing import List


def submatrices_sums(matrix: List[List[int]], coord_pairs: List[List[List[int]]]) -> List[int]:
    partial_submatrices_sums = [[]]
    rows_count = len(matrix)
    columns_count = len(matrix[0])
    for column in range(0, columns_count):
        partial_submatrices_sums[0].append(matrix[0][column])

    for row in range(1, rows_count):
        partial_submatrices_sums.append([])
        for column in range(0, columns_count):
            partial_submatrices_sums[row].append(matrix[row][column] + partial_submatrices_sums[row - 1][column])

    for row in range(0, rows_count):
        for column in range(1, columns_count):
            partial_submatrices_sums[row][column] += partial_submatrices_sums[row][column - 1]

    print(partial_submatrices_sums)

    sums_list = []
    for [[coord1_row, coord1_column], [coord2_row, coord2_column]] in coord_pairs:
        if coord1_row > coord2_row:
            coord1_row, coord2_row = coord2_row, coord1_row
        if coord1_column > coord2_column:
            coord1_column, coord2_column = coord2_column, coord1_column

        current_sum = partial_submatrices_sums[coord2_row][coord2_column]
        if coord1_row > 0:
            current_sum -= partial_submatrices_sums[coord1_row - 1][coord2_column]
        if coord1_column > 0:
            current_sum -= partial_submatrices_sums[coord2_row][coord1_column - 1]
        if coord1_row > 0 and coord1_column > 0:
            current_sum += partial_submatrices_sums[coord1_row - 1][coord1_column - 1]
        sums_list.append(current_sum)

    return sums_list
