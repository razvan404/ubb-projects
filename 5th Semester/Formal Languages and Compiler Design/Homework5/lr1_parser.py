from typing import Dict, List, Optional, Tuple

from pydantic import BaseModel
from prettytable import PrettyTable

from grammar import Grammar


class ExtendedProduction(BaseModel):
    idx: int
    lookahead: List[str]
    point_idx: int = 0

    def __eq__(self, other: "ExtendedProduction") -> bool:
        return (
            self.idx == other.idx
            and self.lookahead == other.lookahead
            and self.point_idx == other.point_idx
        )

    def __hash__(self) -> int:
        return hash(
            (
                self.idx,
                tuple(self.lookahead),
                self.point_idx,
            )
        )


State = List[ExtendedProduction]


class LR1Parser:
    def __init__(self, grammar: Grammar):
        self._grammar = grammar
        self._first_table = self._grammar.first_table()
        self._all_symbols = list(
            filter(
                lambda x: x != self._grammar.starting_symbol,
                self._grammar.non_terminals + self._grammar.terminals,
            )
        )
        (
            self._canon_collection,
            self._analysis_table,
        ) = self._build_canon_collection_and_analysis_table()

    @classmethod
    def _merge_arrays_unique(cls, array1: List, array2: List) -> List:
        new_array, i, j = [], 0, 0
        while i < len(array1) and j < len(array2):
            if array1[i] < array2[j]:
                new_array.append(array1[i])
                i += 1
            elif array1[i] > array2[j]:
                new_array.append(array2[j])
                j += 1
            else:
                new_array.append(array1[i])
                i += 1
                j += 1
        new_array += array1[i:]
        new_array += array2[j:]
        return new_array

    def _build_closure(self, productions: State) -> State:
        closure = []
        new_items = productions
        while len(new_items) > 0:
            closure += new_items
            unverified_items = len(new_items)
            new_items = []
            for production in closure[-unverified_items:]:
                transition = self._grammar.raw_productions[production.idx].transition
                point_idx = production.point_idx

                if point_idx == len(transition):
                    continue
                current_symbol = transition[point_idx]
                if current_symbol in self._grammar.terminals:
                    continue

                if point_idx + 1 == len(transition):
                    next_lookahead = production.lookahead
                elif (
                    next_symbol := transition[point_idx + 1]
                ) in self._grammar.terminals:
                    next_lookahead = [next_symbol]
                else:
                    next_lookahead = self._first_table[next_symbol]

                for next_production in self._grammar.productions[current_symbol]:
                    next_production = ExtendedProduction(
                        idx=next_production.idx,
                        lookahead=next_lookahead,
                    )
                    if (
                        next_production not in closure
                        and next_production not in new_items
                    ):
                        new_items.append(next_production)
        for i in range(len(closure)):
            j = i + 1
            while j < len(closure):
                if (
                    closure[i].idx == closure[j].idx
                    and closure[i].point_idx == closure[j].point_idx
                ):
                    closure[i].lookahead = self._merge_arrays_unique(
                        closure[i].lookahead, closure[j].lookahead
                    )
                    closure.pop(j)
                else:
                    j += 1
        return closure

    def _build_canon_collection_and_analysis_table(
        self,
    ) -> Tuple[List[State], List[Dict[str, Optional[Tuple[str, Optional[int]]]]]]:
        starting_symbol = self._grammar.starting_symbol
        canon_collection = [
            self._build_closure(
                [
                    ExtendedProduction(
                        idx=self._grammar.productions[starting_symbol][0].idx,
                        lookahead=["$"],
                    )
                ]
            )
        ]
        table: List[Dict[str, Optional[Tuple[str, Optional[int]]]]] = []
        while (state_idx := len(table)) < len(canon_collection):
            state = canon_collection[state_idx]
            current_row = {}
            for symbol in self._all_symbols:
                symbol_states = []
                reduce_production_idx = None
                for production in state:
                    transition, point_idx = (
                        self._grammar.raw_productions[production.idx].transition,
                        production.point_idx,
                    )
                    if point_idx == len(transition):
                        if symbol in production.lookahead:
                            if reduce_production_idx is not None:
                                raise ValueError(
                                    "Invalid grammar! Reduce-reduce conflict."
                                )
                            reduce_production_idx = production.idx
                        continue
                    current_symbol = transition[point_idx]
                    if current_symbol != symbol:
                        continue
                    if reduce_production_idx is not None:
                        raise ValueError("Invalid grammar! Shift-reduce conflict.")
                    for symbol_state in symbol_states:
                        if (
                            symbol_state.idx == production.idx
                            and symbol_state.point_idx == point_idx + 1
                        ):
                            symbol_state.lookahead = self._merge_arrays_unique(
                                symbol_state.lookahead, production.lookahead
                            )
                            break
                    else:
                        symbol_states.append(
                            production.model_copy(
                                update={
                                    "point_idx": point_idx + 1,
                                },
                                deep=True,
                            )
                        )
                if reduce_production_idx is not None:
                    current_row[symbol] = ("reduce", reduce_production_idx)
                elif len(symbol_states) > 0:
                    symbol_states = self._build_closure(symbol_states)
                    for i, canon_collection_elem in enumerate(canon_collection):
                        if canon_collection_elem == symbol_states:
                            current_row[symbol] = ("shift", i)
                            break
                    else:
                        current_row[symbol] = ("shift", len(canon_collection))
                        canon_collection.append(symbol_states)
                else:
                    current_row[symbol] = None

            dollar_value = None
            for production in state:
                transition, point_idx = (
                    self._grammar.raw_productions[production.idx].transition,
                    production.point_idx,
                )
                if point_idx == len(transition) and "$" in production.lookahead:
                    if "$" in current_row:
                        raise ValueError("Invalid grammar! Reduce-reduce conflict.")
                    elif (
                        self._grammar.raw_productions[production.idx].non_terminal
                        == starting_symbol
                    ):
                        dollar_value = ("accept", None)
                    else:
                        dollar_value = ("reduce", production.idx)
            current_row["$"] = dollar_value
            table.append(current_row)
        return canon_collection, table

    def _output_lane_to_tokens(self, output_lane: List[int]) -> List[str]:
        tokens = self._grammar.productions[self._grammar.starting_symbol][0].transition
        for production_idx in output_lane:
            production = self._grammar.raw_productions[production_idx]
            for idx in range(len(tokens) - 1, -1, -1):
                if tokens[idx] == production.non_terminal:
                    tokens = tokens[:idx] + production.transition + tokens[idx + 1 :]
                    break
            else:
                raise ValueError("Invalid output lane!")
        return tokens

    def _parse(self, tokens: List[str]) -> bool:
        work_stack = ["$", 0]
        input_lane = tokens + ["$"]
        output_lane = []
        while True:
            print(work_stack, input_lane, output_lane)
            action = self._analysis_table[work_stack[-1]][input_lane[0]]
            if action is None:
                return False
            elif action[0] == "accept":
                new_tokens = self._output_lane_to_tokens(output_lane)
                print(
                    f"Input tokens:\t\t\t\t{tokens}\nTokens from output lane:\t{new_tokens}"
                )
                if tokens != new_tokens:
                    raise ValueError("Invalid output lane!")
                return True
            elif action[0] == "shift":
                work_stack.append(input_lane.pop(0))
                work_stack.append(action[1])
            elif action[0] == "reduce":
                production = self._grammar.raw_productions[action[1]]
                for _ in range(2 * len(production.transition)):
                    work_stack.pop()
                work_stack.append(production.non_terminal)
                if self._analysis_table[work_stack[-2]][work_stack[-1]] is None:
                    return False
                work_stack.append(
                    self._analysis_table[work_stack[-2]][work_stack[-1]][1]
                )
                output_lane.insert(0, action[1])

    def parse_string(self, string: str):
        return self._parse(list(string))

    def parse_file(self, file_path: str):
        with open(file_path, "r") as file:
            items = []
            for line in file:
                line = line.strip()
                if line == "":
                    continue
                items += line.split(" ")
            return self._parse(items)

    def _format_production(self, production: ExtendedProduction):
        raw_production = self._grammar.raw_productions[production.idx]
        before_point = " ".join(raw_production.transition[: production.point_idx])
        after_point = " ".join(raw_production.transition[production.point_idx :])
        lookahead = "/".join(production.lookahead)
        return (
            f"[{raw_production.non_terminal} -> {before_point} "
            f".{'' if after_point == '' else ' '}{after_point}, {lookahead}]"
        )

    def __str__(self) -> str:
        elems = ["Canon collection:"]
        for idx, canon_collection_elem in enumerate(self._canon_collection):
            formatted_canon_collection_elem = list(
                map(self._format_production, canon_collection_elem)
            )
            elems.append(f"I{idx}: ({', '.join(formatted_canon_collection_elem)})")

        elems.append("\nAnalysis table:")
        table = PrettyTable(["State", *self._all_symbols, "$"])
        for idx, row in enumerate(self._analysis_table):
            table.add_row(
                [f"I{idx}"]
                + list(
                    map(
                        lambda action: ""
                        if action is None
                        else "acc"
                        if action[0] == "accept"
                        else action[0][0] + str(action[1]),
                        row.values(),
                    )
                )
            )
        elems.append(str(table))
        return "\n".join(elems)
