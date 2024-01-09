import os

from grammar import Grammar
from lr1_parser import LR1Parser


class UserInterface:
    @classmethod
    def _print_parse_result(cls, result: bool):
        if result:
            print("The string is accepted by the grammar.")
        else:
            print("The string is not accepted by the grammar.")

    @classmethod
    def _parse_strings(cls, parser: LR1Parser):
        while True:
            string = input("String to be parsed: ")
            if string == "":
                break
            cls._print_parse_result(parser.parse_string(string))

    @classmethod
    def _parse_files(cls, parser: LR1Parser):
        while True:
            file_name = input("File to be parsed: ")
            if file_name == "":
                break
            try:
                cls._print_parse_result(
                    parser.parse_file(os.path.join("files", "fip", file_name))
                )
            except FileNotFoundError:
                print("Invalid file path, try again!")

    @classmethod
    def run(cls):
        print("Tip: Enter nothing if you want to cancel the current action :D\n")
        while True:
            file_name = input("Enter the name of the file with the grammar: ")

            if file_name == "":
                print("Bye!")
                break

            try:
                file_path = os.path.join("files", file_name)
                grammar = Grammar.from_file(file_path)
            except FileNotFoundError:
                print("Invalid file path, try again!")
                continue

            parser = LR1Parser(grammar)
            print(parser, end="\n\n")

            while True:
                print("1. Parse some input strings")
                print("2. Parse some input files")
                option = input("> ")

                if option == "":
                    break
                elif option == "1":
                    cls._parse_strings(parser)
                elif option == "2":
                    cls._parse_files(parser)
                else:
                    print("Invalid option, try again!")
