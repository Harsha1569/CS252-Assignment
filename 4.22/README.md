
# Test.c

**Instructions to follow while compiling this code**  
Enter the following on the command line  
1. ``` gcc -o Test Test.c -lpthread -lm ```
2. ```./Test ```
3. Then follow the on-screen promts to find various statistical values

**Note: Here we find statisticals values such as average, maximum, minimum, median & standard deviation for a list of numbers**

**Test cases**
1. Finding statistical values for odd number of elements

   ![image](https://user-images.githubusercontent.com/75844961/142880491-54eaaa18-6980-4757-8c27-69b8430c48b2.png)
2. Finding statistical values for even number of elements

   ![image](https://user-images.githubusercontent.com/75844961/142880879-08e54dc3-75a5-4d27-8b80-5eda05c5839d.png)

List of function calls as encountered in Test.c are as follows:

**Function calls**
1. `int pthread_create(pthread_t * thread, const pthread_attr_t * attr, void * (*start_routine)(void *), void *arg);`
   * Line 118: `pthread_create(&threadHandle[0], NULL, Minimum, (void *)arg);`
   * Used to create a new thread

2. `void pthread_exit(void *retval);`
   * Line 30: `pthread_exit(NULL);`
   * Used to terminate a thread

3. `int pthread_join(pthread_t th, void **thread_return);`
   * Line 124: `pthread_join(threadHandle[i], NULL);`
   * Used to wait for the termination of a thread
   
## References

* [https://gist.github.com/Jabiribn/e58bf13c678953891900e5f982b48037](https://gist.github.com/Jabiribn/e58bf13c678953891900e5f982b48037)
* [https://www.geeksforgeeks.org/thread-functions-in-c-c/](https://www.geeksforgeeks.org/thread-functions-in-c-c/)
   
