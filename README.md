# Get Next Line

## Project Overview

The goal of the Get Next Line project at 42 school is to create a function that reads a file line by line. The project introduces concepts such as handling files using open and close system calls, working with file descriptors (`fd`), and the use of static variables.

## Functionality

The Get Next Line function reads a file, returning each line successively with each function call until the end of the file is reached.

### Steps

1. **Open File with `open` Function:**
   ```c
   int fd = open("example.txt", O_RDONLY);
   ```
   The `open` function is used to open a file and returns a file descriptor (`fd`). Different flags can be used to control file access (read-only, write-only, or read/write) and other properties.

2. **Read File Using `read` Function:**
   ```c
   ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);
   ```
   The `read` function is employed to read data from the file descriptor (`fd`) into a buffer. It returns the number of bytes read or -1 on failure. The reading process is iterative until the end of the file.

3. **Static Variable to Track Line Position:**
   A static variable is used to keep track of the position within the line across successive `read` calls. This ensures that the function resumes reading from where it left off.

4. **Loop Conditions:**
   - Characters in the buffer are not equal to `\n`.
   - Bytes read is greater than 0.

5. **Handling Files - Open/Close System Calls:**
   ```c
   int fd = open("example.txt", O_RDONLY);
   if (fd == -1) {
       perror("Error opening file");
       return 1;
   }
   // Perform file operations
   close(fd);
   ```
   The `open` system call is used to open a file, returning a file descriptor (`fd`). The `close` system call is used to close the file when operations are completed.

6. **File Descriptor (`fd`):**
   - It is a number that the system uses to keep track of an open file.
   - Every open file has a unique file descriptor number.
   - Flags (O_RDONLY, O_WRONLY, O_RDWR) determine file access mode.
   - Other flags control file creation, truncation, and behavior.

7. **Static Variables:**
   - A static variable in C retains its value between function calls.
   - Declared using the `static` keyword.
   - Initialized only once, and its value persists throughout program execution.

8. **Function `read`:**
   - Defined in `<unistd.h>`.
   - Syntax: `ssize_t read(int fd, void *buf, size_t count);`.
   - Parameters: `fd` - file descriptor, `buf` - buffer to store data, `count` - number of bytes to read.
   - Returns: Number of bytes read on success, -1 on failure, and 0 if the end of the file is reached.


## Learnings

- **Handling Files:**
  - Utilizing open and close system calls to interact with files.
  - File descriptor (`fd`) as a unique identifier for open files.

- **Static Variables:**
  - Understanding and implementing static variables in C.
  - Initialization and persistence of values throughout program execution.

- **Function `read`:**
  - The role of `read` in reading data from a file descriptor into a buffer.
  - Parameters and return values of the `read` function.

This project enhances understanding of file Input/Output, static variables, and the utilization of system calls in C programming.
