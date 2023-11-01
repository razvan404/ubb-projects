import re

from table_of_symbols import TableOfSymbols


class Tokenizer:
    def __init__(self, table_of_symbols: TableOfSymbols):
        self._table_of_symbols = table_of_symbols
        self._code2symbol = table_of_symbols.get_symbols_list()
        self._symbols2code = table_of_symbols.get_symbol_to_code_dict()
        self._signification_dict = table_of_symbols.get_signification_to_symbol_dict()
        self._augment_signification_dict()

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
        accumulated_lines = 0
        current_word = ''
        for char in text:
            if char == '"' or char == '\'':
                inside_quotes = not inside_quotes
                current_word += char
            elif char in separators and not inside_quotes:
                if current_word != '':
                    yield line_idx, current_word
                current_word = ''
            else:
                current_word += char
            if char == '\n':
                if inside_quotes:
                    accumulated_lines += 1
                else:
                    line_idx += 1 + accumulated_lines
                    accumulated_lines = 0
        yield line_idx, current_word

    def extract_atoms(self, text: str) -> list[tuple[int, str or None]]:
        tokens = []
        for line, word in self._split_string_with_quotes(text):
            try:
                tokens += self._extract_atoms_from_word(word)
            except Exception as exc:
                raise ValueError(f'Lexical error at line {line}: {text[line - 1]}\nReason: {exc}')
        return tokens

    def _extract_atoms_from_word(self, word: str) -> list[tuple[int, str or None]]:
        if word == '':
            return []

        if word in self._symbols2code:
            return [(self._symbols2code[word], None)]

        if re.match(r'^(([+\-]?[0-9]+)|([+\-]?[0-9]+\.[0-9]+)|(\'\\?[0-9a-zA-Z]\')|("[^"]*"))$', word):
            return [(self._symbols2code['CONST'], word)]

        for i in range(self._max_joinable_len, 0, -1):
            for joinable_symbol in self._joinable_symbols_len_dict[i]:
                if (position := word.find(joinable_symbol)) != -1:
                    return [
                        *self._extract_atoms_from_word(word[:position]),
                        (self._symbols2code[joinable_symbol], None),
                        *self._extract_atoms_from_word(word[position + i:]),
                    ]

        if re.match(r'^[A-Za-z][A-Za-z0-9_]{0,249}$', word):
            return [(self._symbols2code['ID'], word)]

        raise ValueError(f'Cannot tokenize {word}')

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
