import pandas as pd

from binary_tree import BinaryTree
from constants import SEPARATOR


class TsTable:
    def __init__(self):
        self._table = BinaryTree[str]()
        self._word2index = {}

    def __add__(self, word: str):
        self._table.add(word)
        return self

    def __contains__(self, word: str) -> bool:
        return word in self._table

    def __call__(self, *args, **kwargs):
        self._word2index = {word: i for i, word in enumerate(self._table.inorder())}

    def __getitem__(self, word: str) -> int:
        return self._word2index[word]

    def __str__(self):
        return (
            pd.DataFrame.from_dict(data=self._word2index, orient='index', columns=['TS Code'])
            .to_markdown()
        )


class FipTable:
    def __init__(self, atom_pairs: list[tuple[int, str or None]]):
        self._ts_table = TsTable()
        self._table = []
        for atom_pair in atom_pairs:
            if atom_pair[1] is not None and atom_pair[1] not in self._ts_table:
                self._ts_table += atom_pair[1]
        self._ts_table()
        for atom_pair in atom_pairs:
            if atom_pair[1] is not None:
                self._table.append((atom_pair[0], self._ts_table[atom_pair[1]]))
            else:
                self._table.append((atom_pair[0], None))

    def __str__(self):
        table_string = (
            pd.DataFrame.from_records(data=self._table, columns=['Atom code', 'TS code'])
            .to_markdown(index=False)
        )
        return f'{SEPARATOR}\nFIP TABLE\n{SEPARATOR}\n{table_string}\n' + \
            f'{SEPARATOR}\nTS TABLE\n{SEPARATOR}\n{str(self._ts_table)}'
