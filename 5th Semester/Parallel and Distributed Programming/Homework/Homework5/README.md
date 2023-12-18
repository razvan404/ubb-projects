# Homework 5 - Producer Consumer Pattern with Conditional Variabiles

The problem is the same as before, but we are allowed to use conditional variables, we must limit the size of the queue and we needed to do node synchronization instead of list synchronization for the participants list.

## Approach

For the producer consumer queue management, we needed two conditional variables:

- readers conditional variable, where the consumers are waiting and are being notified by the producers when there is a new entity added to the queue or when there are no producers left
- writers conditional variable, where the producers are waiting and are being notified by the consumers when an entity was removed (so that the queue isn't full)

For the participants list management, the requirement of mentaining the list sorted was removed (but I still mentained the list sorted, but this time by the identifiers to go through it faster), but we needed to do node synchronization, this was achieved by locking 2 nodes at a time (the previous one and the current one) and threating the following cases:

- when the current participant id is bigger than the searched participant, this means we need to continue searching, so we will unlock the previous node (which is not used anymore), update the previous and the current node to their next values and lock the new current node, so we are mentaining the two nodes locked.
- when the current participant id is equal to the searched participant, that means that we need to update the current participant, so we unlock the previous node as there is no need to keep it locked, we check if it should be disqualified, otherwise we just add to their score the new score, then we free up the memory, unlock the current participant node and stop the algorithm.
- when the current participant id is bigger than the searched participant (or the current participant doesn't exist), this means that we passed by the position the searched participant should be inserted in, so we should update the previous node to point to a new node containing the participant, then this new node will point to the old next of the previous node (so the current node in our case), after these steps we unlock the current and the previous node and stop the algorithm.

To avoid some extra cases, I used sentinels for the first and last node of the list (so the first and last node were there, but without any information).

## Results

| Type       | Read Threads | Worker Threads |    Time |
| :--------- | :----------- | :------------- | ------: |
| Sequential | -            | -              |  9.0363 |
| Threads    | 1            | 4              | 25.0978 |
| Threads    | 1            | 6              | 29.6103 |
| Threads    | 1            | 8              | 31.6941 |
| Threads    | 1            | 16             | 32.9071 |
| Threads    | 2            | 4              | 28.6851 |
| Threads    | 2            | 6              | 34.0425 |
| Threads    | 2            | 8              | 35.6984 |
| Threads    | 2            | 16             | 36.7242 |

## Observations

As in the previous assignment, we observe that we also obtain worse times for the non-parallel tasks, but this is expected as many concurency problems may appear, and locking and unlocking some mutexes isn't really the most fast operation. We can observe that as increasing the number of worker threads, the results becomes worse, and this may be because of the same reason. Another reason of this happening is the fact that we limited the queue size, I tested the approach without some limits and it performed a lot better than the last tasks, but with this extra overhead, it performs slightly worse.
