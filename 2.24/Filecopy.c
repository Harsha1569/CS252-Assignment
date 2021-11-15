#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int file_exists(char *file_name) {
    int fd = open (file_name, O_RDONLY);

    if (fd == -1) {
        return 0;
    }

    return 1;
}

 
int main() {
 
    int input_fd, output_fd;    // The file descriptors to from which data has to be read & written to respectively 
    ssize_t ret_in, ret_out;    // The maximum number of bytes to be read into the buffer by read() and write() 
    char str[32], in_str[32], out_str[32]; // Temporary string to use for comparision for error checking & strings to hold the names of the source & destination files respectively
    char *str_ptr = str;

    // get name of source file 
    while (strcmp(in_str, "")) { 
        printf("Enter name of source file: ");
        scanf("%s", str_ptr); 
        
        if (file_exists(str_ptr)) {
            strcpy(in_str, str);
            break;
        }
        else {
            printf("Source File of this name does not exist!\n");
            continue;
        }
    }

    // get name of destination file 
    while (strcmp(out_str, "")) { 
        printf("Enter name of destination file: ");
        scanf("%s", str_ptr); 
        
        if (!file_exists(str_ptr)) {
            strcpy(out_str, str);
            break;
        }
        else {
            printf("Destination File of this name already exists!\n");
            continue;
        }
    }
 
    // Create input file descriptor
    input_fd = open (in_str, O_RDONLY);
    if (input_fd == -1) {
            perror ("open");
            return 2;
    }

    // Dyanamically alocate memory to buffer into which data will be read
    struct stat fileStat;
    fstat(input_fd, &fileStat); 
    char *buff = malloc((fileStat.st_size + 1)*sizeof(char)); // Allocate enough to hold the whole contents plus a '\0' char.
 
    // Create output file descriptor
    output_fd = open(out_str, O_WRONLY | O_CREAT, 0644);
    if(output_fd == -1){
        perror("open");
        return 3;
    }
 
    // Copy process 
    while((ret_in = read (input_fd, buff, (fileStat.st_size + 1)*sizeof(char))) > 0){
            ret_out = write (output_fd, buff, (ssize_t) ret_in);
            if(ret_out != ret_in){
                /* Write error */
                perror("write");
                return 4;
            }
    }
 
    // Close file descriptors 
    close (input_fd);
    close (output_fd);
 
    return (EXIT_SUCCESS);
}
