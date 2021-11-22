
# Filecopy.c

**Instructions to follow while compiling this code:**  
Enter the following on the command line  
1. ``` gcc -o Filecopy Filecopy.c ```
2. ```./Filecopy ```
3. Then follow the on-screen promts to copy your file

**Note: Remember to have your source file whose contents have to be copied ready before running these commands.**  
Also the destination file is crated at run-time & one has to provide a new destination file when prompted

**Test cases**
1. Copying the files from msorce to destination depicting prompting

   ![image](https://user-images.githubusercontent.com/75844961/142866623-82c761dd-9759-4f26-ac02-0010a401f3b7.png)
2. Error checking when name of destination file provided already exists

   ![image](https://user-images.githubusercontent.com/75844961/142867377-63a7fd1b-f802-4550-8090-ce8af53a8af8.png)

3. Error checking when name of source file entered is wrong
   
   ![image](https://user-images.githubusercontent.com/75844961/142867663-6082d6a3-1112-48a9-8cf0-32824dbcb2cb.png)

To view the system calls the operating system makes while running this program, run the following on the command line:
```
strace ./Filecopy.c
```
Run the command:

```
strace -o strace_log ./Filecopy.c
```
To copy the contents of strace to an output file named **strace_log**
The **strace_log** file has been uploaded for reference.   
List of system calls listed in ```strace_log``` in order of occurrence are as follows:

1. `int execve(const char *filename, char *const argv[], char *const envp[]);`

  * Line 1: `execve("./Filecopy", ["./Filecopy"], 0x7ffe271eddc8 /* 73 vars */) = 0`
  * Executes the program pointed to by the filename.

2. `int brk(void *addr);`

  * Line 2: `brk(NULL) = 0x5567be96a000`
  *  changes the space alloacated for the calling process
3. `int access(const char *pathname, int mode);`

  * Line 3: `access("/etc/ld.so.nohwcap", F_OK)  = -1 ENOENT (No such file or directory)`
  * Check a user's permissions for a file.

4. `void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);`

  * Line 39: `mmap(NULL, 261976, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f615257d000`
  * Map or unmap files or devices into memory. The mmap() function asks to map length bytes starting at offset offset from the file specified by the file descriptor fd into memory, preferably at address start.

5. `int openat(int dirfd, const char *pathname, int flags", mode_t " mode );`

  * Line 5: `openat(AT_FDCWD, "/home/harsha/simulation_ws/devel/lib/tls/x86_64/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)`
  * If the pathname given in pathname is relative, then it is interpreted relative to the directory referred to by the file descriptor dirfd rather than relative to the current working directory of the calling process. However, in our case if the pathname given in pathname is relative and dirfd is the special value AT_FDCWD, then pathname is interpreted relative to the current working directory of the calling process

6. `int fstat(int fd, struct stat *buf);`

  * Line 38: `fstat(3, {st_mode=S_IFREG|0644, st_size=261976, ...}) = 0`
  * Gets file status.

7. `int close(int fd);`

  * Line 40: `close(3) = 0`
  * Closes a file descriptor so that it no longer refers to any file.

8. `int mprotect(void *addr, size_t len, int prot);`

  * Line 47: `mprotect(0x7f615218a000, 2097152, PROT_NONE) = 0`
  * The function mprotect() specifies the desired protection for the memory page(s) containing part or all of the interval [addr,addr+len-1]

9. `int arch_prctl(int code, unsigned long addr);`

  * Line 51: `arch_prctl(ARCH_SET_FS, 0x7f615257c500) = 0`
  * Set architecture-specific thread state.


10. `ssize_t write(int fd, const void *buf, size_t count);`

  * Line 60: `write(1, "Enter name of source file: ", 27) = 27`
  * Line 63: `write(1, "Enter name of destination file: ", 32) = 32`
  * Line 70: `write(5, "The message to be copied is \"Hel"..., 46) = 46`
  * Write to a file descriptor

11. `ssize_t read(int fd, void *buf, size_t count);`

  * Line 61: `read(0, "source_file.txt\n", 1024) = 16`
  * Line 64: `read(0, "destination_file.txt\n", 1024) = 21`
  * Line 69: `read(4, "The message to be copied is \"Hel"..., 47) = 46`
  * Read from a file descriptor.

12. `void exit_group(int status);`

  * Line 75: `exit_group(0)`
  * This system call terminates not only the present thread, but all threads in the current thread group.

The **source_file.txt** file has also been uploaded that contains the message "The message to be copied is "Hello World!"" for reference. 

## References

* [https://www.tutorialspoint.com/unix_system_calls/index.htm](https://www.tutorialspoint.com/unix_system_calls/index.htm)
* [https://github.com/mattlevan/copy.c](https://github.com/mattlevan/copy.c)
