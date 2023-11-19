import string


def is_escaped(character):
    repr_character = repr(character)
    return repr_character.startswith("'\\") and repr_character.endswith("'")


if __name__ == "__main__":
    print("States: A,B,C,D,E")

    possible_characters = [char for char in list(string.printable) if not is_escaped(char)]
    escape = '\\'
    possible_characters.append(escape)
    print(f"Alphabet: {','.join(possible_characters)}")

    without_quote = [char for char in possible_characters if char != "'"]
    without_quote_and_escape = [char for char in without_quote if char != "\\"]
    print(f"Transitions: A,',B B,{','.join(without_quote_and_escape)},C B,\\,D D,{','.join(without_quote)},C C,',E")
    print("Start state: A")
    print("Accept states: E")
