from typing import List, Dict

from pydantic import BaseModel


class Production(BaseModel):
    idx: int
    non_terminal: str
    transition: List[str]

    def __eq__(self, other):
        return self.idx == other.idx

    def __hash__(self):
        return hash(self.idx)


class Grammar(BaseModel):
    starting_symbol: str
    non_terminals: List[str]
    terminals: List[str]
    raw_productions: List[Production]
    productions: Dict[str, List[Production]]

    @classmethod
    def from_file(cls, file_path: str) -> "Grammar":
        file = open(file_path, "r")

        starting_symbol = None
        non_terminals = []
        terminals = []
        raw_productions = []
        productions = {}

        # 1. Read the tokens
        while (line := file.readline()) != "":
            line = line.strip()
            if line == "%%":
                break
            if line == "":
                continue
            line_split = line.split(" ")
            if line_split[0] == "%token":
                for token in line_split[1:]:
                    terminals.append(token)
            else:
                raise ValueError(
                    "Invalid file! Before the production rules, all the non-empty lines "
                    "must start with one of the followings: [%token]"
                )
        else:
            raise ValueError(
                "Invalid file! The production rules must begin with the line: %%"
            )

        # 2. Read the productions
        while (line := file.readline()) != "":
            line = line.strip()
            if line == "":
                continue
            if line == "%%":
                break
            line_split = line.split(": ")
            if len(line_split) != 2:
                raise ValueError(
                    "Invalid file! Each production rule must be of the form: <non-terminal>: <production>"
                )
            non_terminal = line_split[0]
            if non_terminal in terminals:
                raise ValueError(
                    "Invalid file! The non-terminal symbol cannot be a terminal symbol."
                )
            if starting_symbol is None:
                # Augment the grammar with a new starting symbol
                starting_symbol = "S'"
                non_terminals.append(starting_symbol)
                production = Production(
                    idx=0, non_terminal=starting_symbol, transition=[non_terminal]
                )
                raw_productions.append(production)
                productions[starting_symbol] = [production]

            if non_terminal not in non_terminals:
                non_terminals.append(non_terminal)
                productions[non_terminal] = []

            production = Production(
                idx=len(raw_productions),
                non_terminal=non_terminal,
                transition=[
                    token
                    for token in line_split[1].split(" ")
                    if token != "" and token != "%empty"
                ],
            )
            if len(production.transition) == 0:
                raise ValueError("Invalid file! No ε-production allowed.")
            raw_productions.append(production)
            productions[non_terminal].append(production)

        else:
            raise ValueError(
                "Invalid file! The production rules must end with the line: %%"
            )

        file.close()
        return cls(
            starting_symbol=starting_symbol,
            non_terminals=non_terminals,
            terminals=terminals,
            raw_productions=raw_productions,
            productions=productions,
        )

    def first_table(self) -> Dict[str, List[str]]:
        first_table = {non_terminal: list() for non_terminal in self.non_terminals}
        for non_terminal in self.productions:
            for production in self.productions[non_terminal]:
                transition = production.transition
                if (
                    transition[0] in self.terminals
                    and transition[0] not in first_table[non_terminal]
                ):
                    first_table[non_terminal].append(transition[0])
        changes_made = True
        while changes_made:
            changes_made = False
            for non_terminal in self.non_terminals:
                non_terminal_row = first_table[non_terminal]
                for production in self.productions[non_terminal]:
                    transition = production.transition
                    if transition[0] not in self.non_terminals:
                        continue
                    for token in first_table[transition[0]]:
                        if token not in non_terminal_row:
                            non_terminal_row.append(token)
                            changes_made = True
        for non_terminal, first_row in first_table.items():
            first_table[non_terminal] = sorted(first_row)
        return first_table
