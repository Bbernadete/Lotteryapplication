# Lotteryapplication

This simple user-friendly application begins with a list of processes. Each process is equipped with its own set of tickets, distributed based on priority or other criteria.

To determine the next process for execution, our application calculates the total number of tickets across all processes currently in the scheduler. A random number, bounded by the total number of tickets, is then generated.

Next, we iterate through each process in the scheduler. If any process holds a ticket that corresponds to the randomly generated number, that process is selected as the one to execute next.
