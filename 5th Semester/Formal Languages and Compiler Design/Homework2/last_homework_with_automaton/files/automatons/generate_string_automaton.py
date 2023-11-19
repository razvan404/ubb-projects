import string


def is_escaped(character):
    repr_character = repr(character)
    return repr_character.startswith("'\\") and repr_character.endswith("'")


if __name__ == "__main__":
    print("States: A,B,C")
    possible_characters = [char for char in list(string.printable) if not is_escaped(char)]
    possible_characters.append("\\")
    print(f"Alphabet: {','.join(possible_characters)}")
    possible_characters_without_double_quote = [char for char in possible_characters if char != '"']
    print(f"Transitions: A,\",B B,{','.join(possible_characters_without_double_quote)},B B,\",C")
    print("Start state: A")
    print("Accept states: C")
