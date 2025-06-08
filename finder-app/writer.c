#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    openlog("writer", LOG_PID, LOG_USER);

    if (argc < 3) {
        syslog(LOG_ERR, "Invalid number of arguments. Usage: %s <file> <string>", argv[0]);
        fprintf(stderr, "ERROR: Must enter 2 arguments (file path and text)\n");
        closelog();
        return 1;
    }

    const char *file_path = argv[1];
    const char *write_str = argv[2];

    // Open the file for writing
    // Does not create directories which do not exist 
    // Assumes the directory is created by the caller.
    int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Failed to open file %s: %s", file_path, strerror(errno));
        fprintf(stderr, "ERROR: Could not create or open the file: %s\n", file_path);
        closelog();
        return 1;
    }

    ssize_t bytes_written = write(fd, write_str, strlen(write_str));
    if (bytes_written == -1) {
        syslog(LOG_ERR, "Failed to write to file %s: %s", file_path, strerror(errno));
        fprintf(stderr, "ERROR: Failed to write to the file: %s\n", file_path);
        close(fd);
        closelog();
        return 1;
    }

    // Log success message
    syslog(LOG_DEBUG, "Writing \"%s\" to %s", write_str, file_path);

    // Clean up
    close(fd);
    closelog();
    return 0;
}