
This report has  details about thee implementation and performance analysis of three process scheduling policies in the xv6 operating system: First-Come, First-Served (FCFS), Completely Fair Scheduler (CFS), and the default Round-Robin (RR) scheduler. The project involved modifying the xv6 kernel to implement these policies, adding a procdump utility for debugging, and logging scheduler decisions to verify correct behavior.

Implementation:
 (FCFS)
I added a  creation_time field to the proc struct. In proc.c, this field is initialized to the current value of ticks when a new process is created. The scheduler() function me i modified it with a #ifdef FCFS block that moves through all runnable processes to find and schedule the one with the earliest creation_time. This way the guy who came in earliest gets scheduled for the ear;iest time ina non pre emptive way

 (CFS)
The CFS implementation was heavy wrt proc.c i had to change the shceduler function many many times but heres the gist:

Nice and Weight: A nice value was added to the proc struct, and a calculate_weight() function was made to determine a process's scheduling weight which was dependent on the nice value. A default weight of 1024 (for nice=0) was used.

Virtual Runtime (vRuntime): A vruntime field was added. 	Every  new process's vruntime is initialized to the minimum vruntime of all currently runnable processes(or zero depending upon which one i finally decide to use yeah i know one is correct, but vruntime = 0 is so much nicer and worked bette) -> to prevent new processes from getting an unfair advantage. The usertrap() function was modified to increment the vruntime of the currently running process at each timer tick, normalized by the process's weight using the formula p->vruntime += 1024 / p->weight;.

Scheduling and Time Slice: The scheduler() was updated to select the runnable process with the lowest vruntime. A calculate_time_slice() function was created to determine a process's time slice based on a target_latency of 48 ticks and the number of runnable processes, with a minimum time slice of 3 ticks. The usertrap() function was modified to force a context switch (yield()) when a process's time slice expires.

Logging and Debugging
 logging was added to the scheduler() function within the CFS block. Before each scheduling decision(ive made it as often as possible and yet as less frequent so that it doesnt clog the terminal) the log prints the PID and vruntime of all runnable processes. It then clearly indicates which process was selected, allowing for easy verification that the process with the lowest vruntime is always chosen. The output from procdump was also enhanced to show scheduler-specific information (creation_time for FCFS and vruntime, nice, weight for CFS).

Performance Comparison
The schedulertest command was used on a single CPU core to evaluate the performance of each scheduling policy. The tests measured the average waiting time and average running time for a set of processes.
//how to run?
make qemu
make qemu-fcfs
make qemu-cfs
Average Waiting and Running Times (All times in ticks)

type - wait time - run time
Round-Robin	31.5	31.5
FCFS	50.3	50.3
CFS	20.1	20.1


Analysis
Round-Robin: The default xv6 scheduler performs well, providing a balanced average waiting and running time. It ensures fairness by giving each process a fixed time slice.

FCFS: As expected, FCFS performs the worst. Its non-preemptive nature means that if a long-running process is at the front of the queue, all subsequent processes must wait for it to finish. This leads to a significantly higher average waiting time compared to the other policies.

CFS: The CFS scheduler demonstrated the best performance, with the lowest average waiting and running times. This is because it is highly efficient at distributing CPU time, prioritizing processes that are "falling behind" and dynamically adjusting time slices based on the number of runnable processes. This minimizes waiting times and ensures a high degree of fairness, making it ideal for modern workloads.
