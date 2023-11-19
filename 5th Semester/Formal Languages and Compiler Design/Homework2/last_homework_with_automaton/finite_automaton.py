from enum import Enum
import re


class FiniteAutomaton:
    def __init__(self, states: list[chr], alphabet: list[chr], transitions: dict[chr, dict[chr, chr]],
                 start_state: chr, accept_states: list[chr], raw_transitions: list[str] = None,
                 is_determinist: bool = True):
        self.__states = states
        self.__alphabet = alphabet
        self.__transitions = transitions
        self.__start_state = start_state
        self.__accept_states = accept_states
        self.__raw_transitions = raw_transitions
        self._is_determinist = is_determinist

    class AcceptResponse(Enum):
        ACCEPT_BY_FINAL_STATE = 0
        REJECT_BY_FINAL_STATE = 1
        REJECT_BY_NO_TRANSITION = 2
        REJECT_BY_ALPHABET = 3

    def accepts(self, string: str) -> (bool, AcceptResponse):
        if not self._is_determinist:
            raise ValueError("Automaton is not determinist.")
        current_state = self.__start_state

        for char in string:
            if char not in self.__alphabet:
                return False, self.AcceptResponse.REJECT_BY_ALPHABET
            if current_state not in self.__transitions or char not in self.__transitions[current_state]:
                return False, self.AcceptResponse.REJECT_BY_NO_TRANSITION
            current_state = self.__transitions[current_state][char]

        return (True, self.AcceptResponse.ACCEPT_BY_FINAL_STATE) if current_state in self.__accept_states else \
            (False, self.AcceptResponse.REJECT_BY_FINAL_STATE)

    def longest_prefix(self, string: str) -> str | None:
        if not self._is_determinist:
            raise ValueError("Automaton is not determinist.")
        current_state = self.__start_state
        longest_prefix = ""
        passed_accept_state = self.__start_state in self.__accept_states
        for idx, char in enumerate(string):
            if char not in self.__alphabet:
                break
            if char not in self.__transitions[current_state]:
                break
            current_state = self.__transitions[current_state][char]
            if current_state in self.__accept_states:
                passed_accept_state = True
                longest_prefix = string[:idx + 1]
        if not passed_accept_state:
            return None
        return longest_prefix if longest_prefix != "" else "eps"

    def __transitions_str(self) -> str:
        # if self.__raw_transitions:
        #     return ' '.join(self.__raw_transitions)
        result = ""
        for state in self.__transitions:
            for char in self.__transitions[state]:
                result += f"{state},{char},{self.__transitions[state][char]} "
        return result[:-1]

    def __str__(self) -> str:
        return f"States: {','.join(self.__states)}\n" \
               f"Alphabet: {','.join(self.__alphabet)}\n" \
               f"Transitions: {self.__transitions_str()}\n" \
               f"Start state: {self.__start_state}\n" \
               f"Accept states: {','.join(self.__accept_states)}"


class AutomatonReader:
    @classmethod
    def __custom_comma_split(cls, input_string: str):
        inputs = input_string.split(',')
        for i in range(len(inputs) - 1):
            if inputs[i] == '' and inputs[i + 1] == '':
                inputs.pop(i + 1)
                inputs[i] = ','
                break
            elif inputs[i] == '':
                raise ValueError('Corrupted files')
        return inputs

    @classmethod
    def __custom_space_split(cls, input_string: str):
        pattern = re.compile(r'(?<!,)\s+(?!,)')
        return re.split(pattern, input_string)

    @classmethod
    def __raw_transitions_to_dict(cls, transitions_raw: list[str]) -> (dict[chr, dict[chr, chr]], bool):
        transitions = {}
        is_determinist = True
        for transition in transitions_raw:
            transition = cls.__custom_comma_split(transition)
            if transition[0] not in transitions:
                transitions[transition[0]] = {}
            for char in transition[1:-1]:
                if char in transitions[transition[0]]:
                    is_determinist = False
                transitions[transition[0]][char] = transition[-1]
        return transitions, is_determinist

    @classmethod
    def read_from_file(cls, file_name: str) -> FiniteAutomaton:
        with open(file_name, "r") as file:
            state_str, states = file.readline().split(": ")
            if state_str != "States":
                raise IOError("Invalid file format, failed reading states!")
            states = states.strip().split(",")
            alphabet_str, alphabet = file.readline().split(": ")
            if alphabet_str != "Alphabet":
                raise IOError("Invalid file format, failed reading alphabet!")
            alphabet = cls.__custom_comma_split(alphabet.strip())
            transitions_str, raw_transitions = file.readline().split(": ")
            if transitions_str != "Transitions":
                raise IOError("Invalid file format, failed reading transitions!")
            transitions, is_determinist = cls.__raw_transitions_to_dict(cls.__custom_space_split(raw_transitions.strip()))
            start_state_str, start_state = file.readline().split(": ")
            if start_state_str != "Start state":
                raise IOError("Invalid file format, failed reading start state!")
            start_state = start_state.strip()
            accept_states_str, accept_states = file.readline().split(": ")
            if accept_states_str != "Accept states":
                raise IOError("Invalid file format, failed reading accept states!")
            accept_states = accept_states.strip().split(",")
            return FiniteAutomaton(states, alphabet, transitions, start_state, accept_states,
                                   raw_transitions, is_determinist)

    @classmethod
    def read_from_console(cls) -> FiniteAutomaton:
        states = input("States: ").strip().split(",")
        alphabet = input("Alphabet: ").strip().split(",")
        raw_transitions = cls.__custom_space_split(input("Transitions: ").strip())
        transitions, is_determinist = cls.__raw_transitions_to_dict(raw_transitions)
        start_state = input("Start state: ").strip()
        accept_states = input("Accept states: ").strip().split(",")
        return FiniteAutomaton(states, alphabet, transitions, start_state, accept_states,
                               raw_transitions, is_determinist)
