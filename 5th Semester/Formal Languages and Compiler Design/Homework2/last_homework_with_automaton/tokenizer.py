import os

from finite_automaton import AutomatonReader
from table_of_symbols import TableOfSymbols


class Tokenizer:
    def __init__(self, table_of_symbols: TableOfSymbols, automatons_dir: str):
        self._table_of_symbols = table_of_symbols
        self._code2symbol = table_of_symbols.get_symbols_list()
        self._symbols2code = table_of_symbols.get_symbol_to_code_dict()
        self._signification_dict = table_of_symbols.get_signification_to_symbol_dict()
        self._augment_signification_dict()
        self._id_automaton = AutomatonReader.read_from_file(os.path.join(automatons_dir, "ids.txt"))
        self._integer_automaton = AutomatonReader.read_from_file(os.path.join(automatons_dir, "integers.txt"))
        self._real_automaton = AutomatonReader.read_from_file(os.path.join(automatons_dir, "reals.txt"))
        self._char_automaton = AutomatonReader.read_from_file(os.path.join(automatons_dir, "chars.txt"))
        self._string_automaton = AutomatonReader.read_from_file(os.path.join(automatons_dir, "strings.txt"))

    def _augment_signification_dict(self):
        joinable_significations = ['separator', 'operator', 'parenthesis']
        joinable_symbols_len_dict = {}
        max_joinable_len = 0

        for key in joinable_significations:
            if key in self._signification_dict:
                self._signification_dict[key] = self._signification_dict[key]
                for symbol in self._signification_dict[key]:
                    if len(symbol) not in joinable_symbols_len_dict:
                        joinable_symbols_len_dict[len(symbol)] = []
                    joinable_symbols_len_dict[len(symbol)].append(symbol)
                    if len(symbol) > max_joinable_len:
                        max_joinable_len = len(symbol)
            else:
                self._signification_dict[key] = []

        self._joinable_symbols_len_dict = joinable_symbols_len_dict
        self._max_joinable_len = max_joinable_len

    @staticmethod
    def _split_string_with_quotes(text: str, separators: str = None):
        if separators is None:
            separators = [' ', '\n', '\t']
        inside_quotes = False
        line_idx = 1
        current_word = ''
        for char in text:
            if char == '"' or char == '\'':
                if not inside_quotes and current_word != '':
                    yield line_idx, current_word
                    current_word = ''
                inside_quotes = not inside_quotes
                current_word += char
                if not inside_quotes:
                    yield line_idx, current_word
                    current_word = ''
            elif char in separators and not inside_quotes:
                if current_word != '':
                    yield line_idx, current_word
                current_word = ''
            elif char == '\n' and inside_quotes:
                yield line_idx, current_word
                current_word = ''
                inside_quotes = False
            else:
                current_word += char
            if char == '\n':
                line_idx += 1
        yield line_idx, current_word

    def extract_atoms(self, lines: list[str], text: str) -> list[tuple[int, str or None]]:
        tokens = []
        for line, word in self._split_string_with_quotes(text):
            try:
                tokens += self._extract_atoms_from_word(word)
            except Exception as exc:
                raise ValueError(f'Lexical error at line {line}: {lines[line - 1]}\nReason: {exc}')
        return tokens

    def _extract_atoms_from_word(self, word: str) -> list[tuple[int, str or None]]:
        if word is None or word == '':
            return []

        if self._real_automaton.accepts(word)[0] or \
                self._integer_automaton.accepts(word)[0] or \
                self._char_automaton.accepts(word)[0] or \
                self._string_automaton.accepts(word)[0]:
            return [(self._symbols2code['CONST'], word)]

        const_prefix = self._real_automaton.longest_prefix(word) or \
            self._integer_automaton.longest_prefix(word) or \
            self._char_automaton.longest_prefix(word) or \
            self._string_automaton.longest_prefix(word)

        if const_prefix is not None:
            return [
                (self._symbols2code['CONST'], const_prefix),
                *self._extract_atoms_from_word(word[len(const_prefix):])
            ]

        for i in range(self._max_joinable_len, 0, -1):
            for joinable_symbol in self._joinable_symbols_len_dict[i]:
                if joinable_symbol == word[:len(joinable_symbol)]:
                    return [
                        (self._symbols2code[joinable_symbol], None),
                        *self._extract_atoms_from_word(word[len(joinable_symbol):]),
                    ]

        id_prefix = self._id_automaton.longest_prefix(word)
        if id_prefix is None:
            raise ValueError(f'Cannot tokenize {word}')

        if id_prefix in self._symbols2code:
            return [(self._symbols2code[id_prefix], None), *self._extract_atoms_from_word(word[len(id_prefix):])]

        return [(self._symbols2code['ID'], id_prefix), *self._extract_atoms_from_word(word[len(id_prefix):])]


    def print_codes(self, codes: list[int]):
        tabs = 0
        endline_before = False
        for i, atom in enumerate(codes):
            token = self._code2symbol[atom]
            if endline_before:
                if token != '}':
                    print(tabs * '\t' + token, end=' ')
                else:
                    print((tabs - 1) * '\t' + token, end=' ')
            else:
                print(token, end=' ')

            if token == ';' or token == '{' or (token == '}' and (
                    i + 1 == len(codes) or self._code2symbol[codes[i + 1]] != ';'
            )):
                endline_before = True
                print()
            else:
                endline_before = False

            if token == '{':
                tabs += 1
            elif token == '}':
                tabs -= 1
