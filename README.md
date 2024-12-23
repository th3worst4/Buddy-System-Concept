# ATTENTION

This repository contains a [Buddy System](https://en.wikipedia.org/wiki/Buddy_system) malware concept. This software will not harm your hardware or your data, but will annoy you a lot.

To kill the application, use the [Process Explorer](https://learn.microsoft.com/en-us/sysinternals/downloads/process-explorer) suspend process feature. If the processes spawned by this application are suspended, they will not be able to spawn other buddies while you kill them.

# Buddy System Concept

This is a simple buddy system application built in C for Windows platform. The application spawns a message box and creates another two buddies to do the same; so if the user kills one process, another is spawned and the application continues to run.

# Compiling

To compile the project you will need the following tools:
- GNU C Compiler (GCC)
- Make

To compile, run

```
make build
```

This will create a new directory called `build` with the binary inside it.
