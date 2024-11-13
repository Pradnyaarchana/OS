#include <stdio.h>      // Standard input-output library for printf, fopen, fclose, etc.
#include <unistd.h>     // UNIX standard library for system calls like read, write, close, and unlink
#include <sys/stat.h>   // Library for file permissions, used with mkfifo
#include <fcntl.h>      // Library for file control options, used with open
#include <stdlib.h>     // Standard library for system calls, including system()

#define MAX_BUF 1024    // Define a constant for the maximum buffer size

int main() {
    int words = 0, lines = 0, chars = 0;    // Variables to store counts for words, lines, and characters
    FILE *fp;                               // File pointer for writing data to a text file
    char buf[MAX_BUF];                      // Buffer to store the received message
    int fd, fd1, i = 0;                     // File descriptors for FIFOs and loop index `i`

    char myfifo1[] = "myfifo1";               // Name of the first FIFO (pipe) to receive data
    char myfifo2[] = "myfifo2";               // Name of the second FIFO (pipe) to send data back

    // Create the second FIFO with read/write/execute permissions for all
    mkfifo(myfifo2, 0777);

    // Open the first FIFO (myfifo1) in read-only mode
    fd = open(myfifo1, O_RDONLY);

    // Read data from myfifo1 into the buffer `buf`
    read(fd, buf, MAX_BUF);

    // Print the received message
    printf("\nMessage received: %s", buf);

    // Loop through the buffer to count lines, words, and characters
    while (buf[i] != '\0') {                  // Loop until the end of the buffer
        if (buf[i] == ' ' || buf[i] == '\n') {
            words++;                          // Increment word count when encountering a space or newline
        } else {
            chars++;                          // Increment character count for any other character
        }
        if (buf[i] == '\n') {
            lines++;                          // Increment line count when encountering a newline
        }
        i++;                                  // Move to the next character in the buffer
    }
    words++;                                  // Increment word count for the last word
    lines++;                                  // Increment line count for the last line if no newline at the end

    // Open (or create) a file named "a.txt" for writing
    fp = fopen("a.txt", "w+");
    // Write line count to the file
    fprintf(fp, "No. of lines: %d\n", lines);
    // Write word count to the file
    fprintf(fp, "No. of words: %d\n", words);
    // Write character count to the file
    fprintf(fp, "No. of chars: %d\n", chars);
    // Close the file after writing
    fclose(fp);

    // Close the file descriptor for myfifo1
    close(fd);
    // Delete myfifo1 from the filesystem
    unlink(myfifo1);

    // Open the second FIFO (myfifo2) in write-only mode
    fd1 = open(myfifo2, O_WRONLY);
    // Use the system call to send the contents of "a.txt" into myfifo2
    system("cat a.txt > myfifo2");
    // Close the file descriptor for myfifo2
    close(fd1);

    return 0;                                 // End the program
}
