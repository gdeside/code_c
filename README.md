# code_c

A collection of C programs covering fundamental concepts, data structures, process management, and concurrent programming.

## Repository Structure

```
code_c/
├── basics/          # Fundamental C language features
├── data_structures/ # Data structure implementations
├── processes/       # Process management with fork
└── threads/         # POSIX threads and synchronization
```

---

## basics/

Introductory programs demonstrating core C language features.

| File | Description |
|------|-------------|
| `alphadigit.c` | Uses `isalpha()` and `isdigit()` from `<ctype.h>` to count alphabetic characters and digits in a string. |
| `cmdline.c` | Prints all command-line arguments passed to the program using `argc` and `argv`. |
| `examplestring.c` | Declares, initializes, and prints a character string — a minimal string usage example. |
| `staticvariable.c` | Demonstrates how a `static` local variable persists its value across multiple function calls (implements a running table-of-5 counter). |
| `typesdonnes.c` | Illustrates octal (`0123`) vs hexadecimal (`0x07b`) literal notation and their comparison with decimal values. |

---

## data_structures/

Implementations of common data structures in C.

| File | Description |
|------|-------------|
| `stack.c` | Linked-list based stack with `push`, `pop`, and `peek` operations, using dynamic memory allocation (`malloc`/`free`). |
| `structures.c` | Shows how to declare, initialize, and access `struct` fields via both stack-allocated and heap-allocated (`malloc`) pointers. |

---

## processes/

Programs demonstrating process creation and memory isolation.

| File | Description |
|------|-------------|
| `processusfork.c` | Uses `fork()` to create a child process. Demonstrates that stack, heap, and global memory segments are copied-on-write: modifications in the child are not visible in the parent. |

---

## threads/

Programs demonstrating POSIX thread creation, race conditions, and synchronization primitives.

| File | Description |
|------|-------------|
| `simplethreads.c` | Creates two threads that both increment a shared global variable. Uses a busy-wait spin loop to wait for threads before joining — a basic introduction to `pthread_create` and `pthread_join`. |
| `threadposix.c` | Four threads each perform 1 000 000 increments on a shared global without any synchronization, producing an incorrect final value due to race conditions. |
| `outmutex.c` | Same race condition scenario as `threadposix.c` but with proper error handling, illustrating the problem more clearly before introducing the fix. |
| `withmutex.c` | Fixes the race condition from `outmutex.c` by wrapping the shared increment inside `pthread_mutex_lock` / `pthread_mutex_unlock`, yielding the correct result of 4 000 000. |
| `argthread.c` | Passes integer arguments to threads via `pthread_create`. Each thread negates its argument and returns the result through `pthread_join`, showing how to exchange data with threads. |
| `prodcons.c` | Full producer-consumer implementation using a circular buffer, a mutex to protect buffer access, and two semaphores (`empty`, `full`) to coordinate 7 producer threads and 2 consumer threads. |
