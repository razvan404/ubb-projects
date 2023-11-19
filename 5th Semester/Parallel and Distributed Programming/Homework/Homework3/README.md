# Homework 3 - Processes

## Approach

The approach is simillar to the lines approach from the previous homework, but instead of creating threads, we are now creating processes. These should work faster, because now there are P independent programs (that are communicating through different). So the master would read and send each worker [N / P] lines, each worker will process its lines, and send the master the results, which will accumulate them and put them into the output file.

## Results

| Approach         | Processes |  Result |
| :--------------- | --------: | ------: |
| send & receive   |         5 |  96.076 |
| send & receive   |         9 | 93.9905 |
| send & receive   |        21 |  114.25 |
| scatter & gatter |         4 | 95.4296 |
| scatter & gatter |         8 | 91.8635 |
| scatter & gatter |        20 |   98.59 |

## Observations

We can see that the scatter & gatter approach is faster for each number of processes than the send & receive approach, proving that MPI manages the communication between the processes better. In the scatter & gatter approach, each thread would be useful, because the master will work too. The best number of processes for my system is 8 processes, maybe because the communication is slower and not worth the time for our input data (1000 x 1000 matrice).

Between this approach and the last one, we cannot see that much of an improvmenet, and a reason for that is the fact that in this approach times were meassured differently, because here we read the data and pass to each process at the same time, so we need to start the time either before sending the data or after, which would not be fair for either the approaches. But, in the scatter & gatter approach, an experiment was done were the data was read first and sent after that, and there I obtained much better results, proving that the approach with the processes is faster.
