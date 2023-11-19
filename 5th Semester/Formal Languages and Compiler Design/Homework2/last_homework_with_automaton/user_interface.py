from constants import SEPARATOR
from fip_table import FipTable
from table_of_symbols import TableOfSymbols
from tokenizer import Tokenizer


class UserInterface:
    def __init__(self, table_of_symbols_path: str):
        self._table = TableOfSymbols(table_of_symbols_path)
        self._tokenizer = Tokenizer(self._table, 'files/automatons')

    @staticmethod
    def _print_menu() -> int:
        print(SEPARATOR)
        print('1. Tokenize file')
        print('2. Print table of symbols')
        print('0. Exit')
        print(SEPARATOR)
        return int(input('> '))

    def _tokenize_file(self):
        print(SEPARATOR)
        file_path = input('Enter file path (e.g. files/codes/code1.cpp): ')
        with open(file_path, 'r') as file:
            lines = [line.strip() for line in file.readlines()]
            text = '\n'.join(lines)
            atoms = self._tokenizer.extract_atoms(lines, text)
            codes = [atom[0] for atom in atoms]
            print('Codes:', codes)
            while True:
                print(SEPARATOR)
                option = input('Do you want to reconstruct the code? [y/N]: ')
                if option == 'y':
                    print(SEPARATOR)
                    self._tokenizer.print_codes(codes)
                    break
                elif option == 'N':
                    break
            while True:
                print(SEPARATOR)
                option = input('Do you want to print the FIP table? [y/N]: ')
                if option == 'y':
                    fip_table = FipTable(atoms)
                    print(str(fip_table))
                    break
                elif option == 'N':
                    break

    def _table_to_markdown(self):
        print(SEPARATOR)
        print(self._table.to_markdown())

    def __call__(self, *args, **kwargs):
        while True:
            try:
                option = self._print_menu()
                if option == 1:
                    self._tokenize_file()
                elif option == 2:
                    self._table_to_markdown()
                elif option == 0:
                    print(SEPARATOR)
                    print('Bye!')
                    print(SEPARATOR)
                    break
            except Exception as exc:
                print(exc)
