# CSE221-OS-Benchmarks

This is my repository for CSE-221 OS's project @ UCSD

# Project Overview
Taken from the project description:
> In building an operating system, it is important to be able to determine the performance characteristics of underlying hardware components (CPU, RAM, disk, network, etc.), and to understand how their performance influences or constrains operating system services. Likewise, in building an application, one should understand the performance of the underlying hardware and operating system, and how they relate to the user's subjective sense of that application's "responsiveness". While some of the relevant quantities can be found in specs and documentation, many must be determined experimentally. While some values may be used to predict others, the relations between lower-level and higher-level performance are often subtle and non-obvious.
In this project, you will create, justify, and apply a set of experiments to a system to characterize and understand its performance. In addition, you may explore the relations between some of these quantities. In doing so, you will study how to use benchmarks to usefully characterize a complex system. You should also gain an intuitive feel for the relative speeds of different basic operations, which is invaluable in identifying performance bottlenecks.
You have complete choice over the operation system and hardware platform for your measurements. You can use your laptop that you are comfortable with, an operating system running in a virtual machine monitor, or even a supercomputer.
You may work either alone or in 2-3 person groups. Groups do the same project as individuals. All members receive the same grade. Note that working in groups may or may not make the project easier, depending on how the group interactions work out. If collaboration issues arise, contact me as soon as possible: flexibility in dealing with such issues decreases as the deadline approaches.
This project has two parts. First, you will implement and perform a series of experiments. Second, you will write a report documenting the methodology and results of your experiments. When you finish, you will submit your report as well as the code used to perform your experiments.

# Operations
## 1. CPU, Scheduling, and OS Services
- Measurement overhead: Report the overhead of reading time, and report the overhead of using a loop to measure many iterations of an operation.
- Procedure call overhead: Report as a function of number of integer arguments from 0-7. What is the increment overhead of an argument?
- System call overhead: Report the cost of a minimal system call. How does it compare to the cost of a procedure call? Note that some operating systems will cache the results of some system calls (e.g., idempotent system calls like getpid), so only the first call by a process will actually trap into the OS.
- Task creation time: Report the time to create and run both a process and a kernel thread (kernel threads run at user-level, but they are created and managed by the OS; e.g., pthread_create on modern Linux will create a kernel-managed thread). How do they compare?
- Context switch time: Report the time to context switch from one process to another, and from one kernel thread to another. How do they compare? In the past students have found using blocking pipes to be useful for forcing context switches.
 

## 2. Memory
- RAM access time: Report latency for individual integer accesses to main memory and the L1 and L2 caches. Present results as a graph with the x-axis as the log of the size of the memory region accessed, and the y-axis as the average latency. Note that the lmbench paper is a good reference for this experiment. In terms of the lmbench paper, measure the "back-to-back-load" latency and report your results in a graph similar to Fig. 1 in the paper. You should not need to use information about the machine or the size of the L1, L2, etc., caches when implementing the experiment; the experiment will reveal these sizes. In your graph, label the places that indicate the different hardware regimes (L1 to L2 transition, etc.).
- RAM bandwidth: Report bandwidth for both reading and writing. Use loop unrolling to get more accurate results, and keep in mind the effects of cache line prefetching (e.g., see the lmbench paper).
- Page fault service time: Report the time for faulting an entire page from disk (mmap is one useful mechanism). Dividing by the size of a page, how does it compare to the latency of accessing a byte from main memory?
 

## 3. Network
- Round trip time. Compare with the time to perform a ping (ICMP requests are handled at kernel level).
- Peak bandwidth.
- Connection overhead: Report setup and tear-down.
- Evaluate for the TCP protocol. For each quantity, compare both remote and loopback interfaces. Comparing the remote and loopback results, what can you deduce about baseline network performance and the overhead of OS software? For both round trip time and bandwidth, how close to ideal hardware performance do you achieve? In describing your methodology for the remote case, either provide a machine description for the second machine (as above), or use two identical machines.
 
## 4. File System
- Size of file cache: Note that the file cache size is determined by the OS and will be sensitive to other load on the machine; for an application accessing lots of file system data, an OS will use a notable fraction of main memory (GBs) for the file system cache. Report results as a graph whose x-axis is the size of the file being accessed and the y-axis is the average read I/O time. Do not use a system call or utility program to determine this metric except to sanity check.
- File read time: Report for both sequential and random access as a function of file size. Discuss the sense in which your "sequential" access might not be sequential. Ensure that you are not measuring cached data (e.g., use the raw device interface). Report as a graph with a log/log plot with the x-axis the size of the file and y-axis the average per-block time.
- Remote file read time: Repeat the previous experiment for a remote file system. What is the "network penalty" of accessing files over the network? You can either configure your second machine to provide remote file access, or you can perform the experiment on a department machine (e.g., APE lab). On these machines your home directory is mounted over NFS, so accessing a file under your home directory will be a remote file access (although, again, keep in mind file caching effects).
- Contention: Report the average time to read one file system block of data as a function of the number of processes simultaneously performing the same operation on different files on the same disk (and not in the file buffer cache).
