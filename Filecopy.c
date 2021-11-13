#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int file_exists(char *file_name) {
    FILE *file_ptr = fopen(file_name, "r");

    if (!file_ptr) {
        return 0;
    }

    return 1;
}

 
int main() {
 
    int input_fd, output_fd;    /* Input and output file descriptors */
    ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */
    char str[32], in_str[32], out_str[32];
    char *str_ptr = str;

    // get name of source file 
    while (strcmp(in_str, "")) { // while in_str is empty
        printf("Enter name of source file: ");
        scanf("%s", str_ptr); // get input from keyboard (stdin)
        
        if (file_exists(str_ptr)) {
            strcpy(in_str, str);
            break;
        }
        else {
            printf("File can't be opened!\n");
            continue;
        }
    }

    // get name of destination file 
    while (strcmp(out_str, "")) { // while out_str is empty
        printf("Enter name of destination file: ");
        scanf("%s", str_ptr); // get input from keyboard (stdin)
        
        if (!file_exists(str_ptr)) {
            strcpy(out_str, str);
            break;
        }
        else {
            printf("File already exists!\n");
            continue;
        }
    }
 
    /* Create input file descriptor */
    input_fd = open (in_str, O_RDONLY);
    if (input_fd == -1) {
            perror ("open");
            return 2;
    }

    struct stat fileStat;
    fstat(input_fd, &fileStat); // Don't forget to check for an error return in real code
    // Allocate enough to hold the whole contents plus a '\0' char.
    char *buff = malloc((fileStat.st_size + 1)*sizeof(char));
 
    /* Create output file descriptor */
    output_fd = open(out_str, O_WRONLY | O_CREAT, 0644);
    if(output_fd == -1){
        perror("open");
        return 3;
    }
 
    /* Copy process */
    while((ret_in = read (input_fd, buff, (fileStat.st_size + 1)*sizeof(char))) > 0){
            ret_out = write (output_fd, buff, (ssize_t) ret_in);
            if(ret_out != ret_in){
                /* Write error */
                perror("write");
                return 4;
            }
    }
 
    /* Close file descriptors */
    close (input_fd);
    close (output_fd);
 
    return (EXIT_SUCCESS);
}
