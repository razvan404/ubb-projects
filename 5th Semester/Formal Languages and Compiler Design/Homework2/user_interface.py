from finite_automaton import FiniteAutomaton, AutomatonReader


class UserInterface:
    def __init__(self):
        self._finite_automaton: FiniteAutomaton | None = None

    @classmethod
    def __print_menu(cls) -> int:
        print("1. Load finite automaton")
        print("2. Print loaded automaton")
        print("3. Check if a string is accepted by the automaton")
        print("4. Find the longest accepted prefix of a string")
        print("0. Exit")
        return int(input("> "))

    def __load_automaton(self) -> None:
        while True:
            print("1. From file")
            print("2. From keyboard")
            option = int(input("> "))
            if option == 1:
                self.__load_automaton_from_file()
                break
            elif option == 2:
                self.__load_automaton_from_keyboard()
                break
            else:
                print("Invalid option!")
        print("Automaton loaded successfully!")

    def __load_automaton_from_file(self) -> None:
        file_name = "files/" + input("File name: ")
        self._finite_automaton = AutomatonReader.read_from_file(file_name)

    def __load_automaton_from_keyboard(self) -> None:
        self._finite_automaton = AutomatonReader.read_from_console()

    def __print_automaton(self) -> None:
        if self._finite_automaton is None:
            raise ValueError("No automaton loaded!")
        print(self._finite_automaton)

    def __check_string(self) -> None:
        if self._finite_automaton is None:
            raise ValueError("No automaton loaded!")
        string = input("String: ")
        if (resp := self._finite_automaton.accepts(string)) == FiniteAutomaton.AcceptResponse.ACCEPT_BY_FINAL_STATE:
            print("String is accepted!")
        else:
            print(f"String is not accepted! - {resp.name}")

    def __longest_prefix(self) -> None:
        if self._finite_automaton is None:
            raise ValueError("No automaton loaded!")
        string = input("String: ")
        if (longest_prefix := self._finite_automaton.longest_prefix(string)) is None:
            print("No prefix found!")
        else:
            print(f"Longest prefix: {longest_prefix}")

    def run(self) -> None:
        while True:
            try:
                option = self.__print_menu()
                if option == 0:
                    print("Bye!")
                    break
                elif option == 1:
                    self.__load_automaton()
                elif option == 2:
                    self.__print_automaton()
                elif option == 3:
                    self.__check_string()
                elif option == 4:
                    self.__longest_prefix()
                else:
                    print("Invalid option!")
            except Exception as ex:
                print(ex)
