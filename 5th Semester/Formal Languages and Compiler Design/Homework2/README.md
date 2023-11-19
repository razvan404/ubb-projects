# Syntax

## BNF
    <file> ::= States: <states>
                Alphabet: <alphabet>
                Transitions: <transitions>
                Start state: <start>
                Accept states: <accept>
    <states> ::= <state> | <state> , <states>
    <state> ::= ID
    <alphabet> ::= <symbol> | <symbol> , <alphabet>
    <symbol> ::= <char>
    <transitions> ::= <transition> | <transition> <transitions>
    <transition> ::= <state> , <symbols> , <state>
    <symbols> ::= <symbol> | <symbol> , <symbols>
    <start> ::= <state>
    <accept> ::= <state> | <state> , <accept>
    <char> ::= a | b | c ... x | y | z | 0 | 1 | 2 ... 8 | 9

## EBNF
    file = "States:" states
            "Alphabet:" alphabet
            "Transitions:" transitions
            "Start state:" start
            "Accept states:" accept
    states = state | state "," states
    state = ID
    alphabet = symbol | symbol "," alphabet
    symbol = char
    transitions = transition | transition transitions
    transition = state "," symbols "," state
    symbols = symbol | symbol "," symbols
    start = state
    accept = state | state "," accept
    char = "a" | "b" | "c" ... "x" | "y" | "z" | "0" | "1" | "2" ... "8" | "9"