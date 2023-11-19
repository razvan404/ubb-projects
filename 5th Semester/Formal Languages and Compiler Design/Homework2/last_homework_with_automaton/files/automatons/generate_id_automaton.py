import string

if __name__ == '__main__':
    states = [f'q{i}' for i in range(256)]
    print(f"States: {','.join(states)}")

    letters = list(string.ascii_letters)
    numbers = [chr(num) for num in range(ord('0'), ord('9') + 1)]
    valid_characters = [*letters, *numbers, '_']
    print(f"Alphabet: {','.join(valid_characters)}")

    print(f"Transitions: {','.join([states[0], *letters, states[1]])}", end='')

    for i in range(1, 255):
        print(' ' + ','.join([states[i], *valid_characters, states[i + 1]]), end='')
    else:
        print()

    print(f"Start state: {states[0]}")
    print(f"Accept states: {','.join(states[1:])}")
