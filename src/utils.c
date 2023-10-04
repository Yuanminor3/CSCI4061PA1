#include "utils.h"
#define PATH_MAX 1024

// Create N files and distribute the data from the input file evenly among them
// See section 3.1 of the project writeup for important implementation details
void partition_file_data(char *input_file, int n, char *blocks_folder) {
    
    // Hint: Use fseek() and ftell() to determine the size of the file
    FILE *fIn = fopen(input_file, "r");
    if (fIn == NULL) {
        perror("Failed to open input file");
        return;
    }

    // Get the size of input_file
    fseek(fIn, 0, SEEK_END);
    long int file_size = ftell(fIn);
    // Set the pointer back at start
    fseek(fIn, 0, SEEK_SET);

    // Calculate block file size by formula
    long int block_size = file_size / n;
    long int last_block_size = block_size + (file_size % n);

    // Create filename buffer
    char block_filename[PATH_MAX];

    for (int i = 0; i < n; i++) {
        // Create filename.txt
        // snprintf makes sure that the generated string does not exceed the specified size
        // It truncates the string or stops writing to make sure that it does not cause a buffer overflow
        snprintf(block_filename, sizeof(block_filename), "%s/%d.txt", blocks_folder, i);

        // Open block file
        FILE *block_file = fopen(block_filename, "w");
        if (block_file == NULL) {
            perror("Failed to create block file");
            fclose(fIn);
            return;
        }

        // Confirm written data size
        long int current_block_size;
        if (i == n-1){
            current_block_size = last_block_size;
        }else{
            current_block_size = block_size;
        }
        char *buffer = (char *)malloc(current_block_size);
        if (buffer == NULL) {
            perror("Failed to allocate memory for buffer");
            fclose(fIn);
            fclose(block_file);
            return;
        }

        fread(buffer, 1, current_block_size, fIn);
        fwrite(buffer, 1, current_block_size, block_file);

        free(buffer); // free up memory
        fclose(block_file);
    }

    fclose(fIn);
}


// ##### DO NOT MODIFY THIS FUNCTION #####
void setup_output_directory(char *block_folder, char *hash_folder) {
    // Remove output directory
    pid_t pid = fork();
    if (pid == 0) {
        char *argv[] = {"rm", "-rf", "./output/", NULL};
        if (execvp(*argv, argv) < 0) {
            printf("ERROR: exec failed\n");
            exit(1);
        }
        exit(0);
    } else {
        wait(NULL);
    }

    sleep(1);

    // Creating output directory
    if (mkdir("output", 0777) < 0) {
        printf("ERROR: mkdir output failed\n");
        exit(1);
    }

    sleep(1);

    // Creating blocks directory
    if (mkdir(block_folder, 0777) < 0) {
        printf("ERROR: mkdir output/blocks failed\n");
        exit(1);
    }

    // Creating hashes directory
    if (mkdir(hash_folder, 0777) < 0) {
        printf("ERROR: mkdir output/hashes failed\n");
        exit(1);
    }
}
