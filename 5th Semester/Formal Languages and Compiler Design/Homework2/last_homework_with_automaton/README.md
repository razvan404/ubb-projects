# Specifications

## Grammar

### program

- [&lt;global-blocks&gt;](#global-blocks) [&lt;main-function&gt;](#main-function) [&lt;global-blocks&gt;](#global-blocks)

### global-blocks

- ɛ
- [&lt;global-block&gt;](#global-block) [&lt;global-blocks&gt;](#global-blocks)

### global-block

- [&lt;declaration&gt;](#declaration)
- [&lt;struct-definition&gt;](#struct-definition)

### main-function

- int main() { [&lt;instructions&gt;](#instructions) }

### instructions

- ɛ
- [&lt;instruction&gt;](#instruction); [&lt;instructions&gt;](#instructions)
- [&lt;special-instruction&gt;](#special-instruction) [&lt;instructions&gt;](#instructions)

### instruction

- [&lt;declaration&gt;](#declaration)
- [&lt;operation&gt;](#operation)
- [&lt;expression&gt;](#expression)
- [&lt;input-statement&gt;](#input-statement)
- [&lt;output-statement&gt;](#output-statement)

### special-instruction

- [&lt;conditional-statement&gt;](#conditional-statement)
- [&lt;loop-statement&gt;](#loop-statement)
- [&lt;struct-definition&gt;](#struct-definition)

### declaration

- [&lt;type&gt;](#type) [&lt;declaration-sequence&gt;](#declaration-sequence)

### declaration-sequence

- [&lt;declaration-term&gt;](#declaration-term)
- [&lt;declaration-term&gt;](#declaration-term), [&lt;declaration-sequence&gt;](#declaration-sequence)

### declaration-term

- ID
- [&lt;assignment&gt;](#assignment)

### type

- int
- char
- float
- double
- string
- struct ID

### assignment

- [&lt;accessible-term&gt;](#accessible-term) = [&lt;expression&gt;](#expression)

### operation

- [&lt;assignment&gt;](#assignment)
- [&lt;accessible-term&gt;](#accessible-term) [&lt;mathematical-operator&gt;](#mathematical-operator)= [&lt;expression&gt;](#expression)

### accessible-term

- ID
- ID.[&lt;accessible-term&gt;](#accessible-term)

### struct-definition

- struct ID { [&lt;struct-members&gt;](#struct-members) };

### struct-members

- [&lt;declaration&gt;](#declaration);
- [&lt;declaration&gt;](#declaration); [&lt;struct-members&gt;](#struct-members)

### expression

- [&lt;expression-term>](#expression-term)
- [&lt;expression-term>](#expression-term) [&lt;operator>](#operator) [&lt;expression&gt;](#expression)

### expression-term

- [&lt;accessible-term&gt;](#accessible-term)
- CONST

### operator

- [&lt;mathematical-operator&gt;](#mathematical-operator)
- [&lt;logical-operator&gt;](#logical-operator)
- [&lt;relational-operator&gt;](#relational-operator)

### mathematical-operator

- [&lt;arithmetic-operator&gt;](#arithmetic-operator)
- [&lt;bitwise-operator&gt;](#bitwise-operator)

### arithmetic-operator

- \+
- \-
- \*
- /
- %

### bitwise-operator

- &
- |
- ^
- &lt;&lt;
- &gt;&gt;

### logical-operator

- &&
- ||

### relational-operator

- ==
- !=
- &gt;
- &gt;=
- <
- <=

### input-statement

- std::cin &gt;> [&lt;input-sequence&gt;](#input-sequence)

### input-sequence

- ID
- ID &gt;&gt; [&lt;input-sequence&gt;](#input-sequence)

### output-statement

- std::cout &lt;&lt; [&lt;output-sequence&gt;](#output-sequence)

### output-sequence

- [&lt;expression&gt;](#expression)
- [&lt;expression&gt;](#expression) &lt;&lt; [&lt;output-sequence&gt;](#output-sequence)

### conditional-statement

- [&lt;if-statement&gt;](#if-statement)
- [&lt;switch-statement&gt;](#switch-statement)

### if-statement

- if ( [&lt;conditions&gt;](#conditions) ) { [&lt;instructions&gt;](#instructions) } else { [&lt;instructions&gt;](#instructions) }

### conditions

- [&lt;condition&gt;](#condition)
- [&lt;condition&gt;](#condition) [&lt;logical-operator&gt;](#logical-operator) [&lt;conditions&gt;](#conditions)

### condition

- [&lt;expression&gt;](#expression) [&lt;relational-operator&gt;](#relational-operator) [&lt;expression&gt;](#expression)

### loop-statement

- [&lt;while-loop&gt;](#while-loop)
- [&lt;for-loop&gt;](#for-loop)

### while-loop

- while ( [&lt;conditions&gt;](#conditions) ) { [&lt;instructions&gt;](#instructions) }

### for-loop

- for ( [&lt;declaration&gt;](#declaration); [&lt;conditions&gt;](#conditions); [&lt;operation&gt;](#operation) ) { [&lt;instructions&gt;](#instructions) }

### switch-statement

- switch ( [&lt;expression&gt;](#expression) ) { [&lt;case-instructions&gt;](#cases) [&lt;default-instruction&gt;](#default-instruction) }

### case-instructions

- [&lt;case-instruction&gt;](#case-instruction)
- [&lt;case-instruction&gt;](#case-instruction) [&lt;case-instructions&gt;](#case-instructions)

### case-instruction

- case CONST: [&lt;instructions&gt;](#instructions) break;

### default-instruction

- default: [&lt;instructions&gt;](#instructions)

## Restrictions

### Identifiers

- must have at most 250 characters.
- shouldn't be one of the other keywords.
- should start with a letter, it must contain only letters, numbers or underscores, regex: `^[A-Za-z][A-Za-z0-9_]{0,249}$`

### Constants

- should be numbers, a character or a string, regex: `^([0-9]*)|('\\?[0-9a-zA-Z]')|("[^"]*")$`

## Table of Symbols

| Symbol    | Code |
| :-------- | ---: |
| ID        |    0 |
| CONST     |    1 |
| main      |    2 |
| (         |    3 |
| )         |    4 |
| {         |    5 |
| }         |    6 |
| ;         |    7 |
| ,         |    8 |
| int       |    9 |
| char      |   10 |
| float     |   11 |
| double    |   12 |
| string    |   13 |
| =         |   14 |
| +         |   15 |
| -         |   16 |
| \*        |   17 |
| /         |   18 |
| %         |   19 |
| &         |   20 |
| \|        |   21 |
| ^         |   22 |
| &&        |   23 |
| \|\|      |   24 |
| ==        |   25 |
| !=        |   26 |
| \<        |   27 |
| \>        |   28 |
| \<=       |   29 |
| \>=       |   30 |
| \<\<      |   31 |
| \>\>      |   32 |
| !         |   33 |
| if        |   34 |
| else      |   35 |
| while     |   36 |
| for       |   37 |
| struct    |   38 |
| .         |   39 |
| std::cin  |   40 |
| std::cout |   41 |
