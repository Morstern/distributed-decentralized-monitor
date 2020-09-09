# distributed-decentralized-monitor
University project written in C++  [C++, ØMQ].

## Compiling & launching

__The easy way:__ To compile you need an environment where you can use the make command. (for example Linux)

__The hard way:__ You can compile all of those files in one line in your console, but it is tiresome (especially during the development phase)

### __Make sure you have installed the ZMQ library and you link them when you compile the code (I used the one for C language)__

After compiling code you should end up with "a.out" file, you can launch the code as presented below:

./a.out monitor MODE{1,2,3} OWN_PORT OTHER_PORT_1 OTHER_PORT_2...

* [console_1] &nbsp;&nbsp;&nbsp;./a.out monitor 1 10000 10001 10002
* [console_2] &nbsp;&nbsp;&nbsp;./a.out monitor 2 10001 10000 10002
* [console_3] &nbsp;&nbsp;&nbsp;./a.out monitor 3 10002 10000 10001


## Main idea

Create a solution to communicate between processes with shared objects (Since it has to be a simulation I didn't create shared object – I misnamed the variable which acts like a shared object as "memoryAddress", but since those processes could work on different hosts, they couldn't have shared memory).

Solution has to implement:
  - communication between processes – by using ZMQ library,
  - mutual exclusion algorithm (I decided to implement Ricart-Agrawala algorithm).

## What this program do
- It communicates with processes on localhost, by using ZMQ library,
- It sends REQUEST/REPLY messages accordingly to Ricart-Agrawala algorithm,
- It sends REMOVE message (when using Monitor::tryEnter function, although it isn't necessary),
- It does check if some process has crashed (UPDATED: previously unimplemented),

## What this program doesn't do
- It doesn't really do anything (except communicating and managing mutual exclusion between processes).

## Possible future developments/improvements
 - receivedQueue could hold std::string (memoryAddress) instead of long(timestamp) – it could perform better when it comes about sending replies (since now after exiting from critical section, I check for every message in the receivedQueue),
 - real shared objects – another MessageType for example MessageType::CREATE, all processes would create an object with the ID given in "memoryAddress" field. There should be also another MessageType for updating fields, such as MessageType::UPDATE (and every process would re-send the message with MessageType::RECEIVED) – process which currently holds the lock, wouldn't notify other processes until he gets all replies. 
 
