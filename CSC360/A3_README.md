A3 shows my solution to the assignment description.
My solution only uses semifores (3 to facilitate the problem) 
It uses one semiphore as a mutex to protect critical sections. 
The next semiphore is used as a barrier to provent the threads from leaving before all n bobofets have arrived.
The last semiphore is used to count the waiting threads.
