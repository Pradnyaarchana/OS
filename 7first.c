#include <stdio.h>      // Standard input-output library for printf, getchar, etc.
#include <unistd.h>     // UNIX standard library for system calls like read, write, close
#include <sys/stat.h>   // Library for file permissions (used with mkfifo)
#include <fcntl.h>      // Library for file control options (used with open)

// Define a buffer size of 1024 bytes to hold data
#define Max_Buff 1024   

int main() {
    int fd1, fd2, c = 0;       // Declare file descriptors for pipes and a counter
    char myfifo1[] = "myfifo1";  // Name of the first FIFO (pipe)
    char myfifo2[] = "myfifo2";  // Name of the second FIFO (pipe)

    char buff[Max_Buff];        // Buffer to store user input to send via pipe 1
    char buff2[Max_Buff];       // Buffer to store data received from pipe 2
    char str;                   // Temporary character variable to read each character of input

    // Create the first FIFO (pipe) with read/write/execute permissions for all
    int res = mkfifo(myfifo1, 0777);
    if (res == -1) {            // Check if pipe creation failed
        printf("\nPipe 1 not created");  // Print error message if FIFO creation fails
        return 0;               // End the program if FIFO creation fails
    }

    // Prompt the user to enter a string
    printf("\nEnter the string:\n");

    // Open the first FIFO in write-only mode
    fd1 = open(myfifo1, O_WRONLY);

    // Read characters from standard input (console) until '#' is entered
    while ((str = getchar()) != '#')
        buff[c++] = str;        // Store each character in the buffer
    buff[c] = '\0';             // Null-terminate the string

    printf("Contents written in pipe \n"); // Inform user that data has been written

    // Write the content of buff to the first FIFO using file descriptor fd1
    write(fd1, buff, sizeof(buff));
    close(fd1);                 // Close the first FIFO after writing data

    // Open the second FIFO in read-only mode to read the response
    fd2 = open(myfifo2, O_RDONLY);
    
    // Read data from the second FIFO into buff2, up to Max_Buff bytes
    read(fd2, &buff2, Max_Buff);

    // Display the content read from the second FIFO
    printf("\nContents of the file:\n%s", buff2);
    close(fd2);                 // Close the second FIFO after reading data

    // Delete the second FIFO from the filesystem after use
    unlink(myfifo2);

    return 0;                   // End the program
}
