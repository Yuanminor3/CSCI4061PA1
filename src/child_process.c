#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "hash.h"

#define PATH_MAX 1024

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: ./child_process <blocks_folder> <hashes_folder> <N> <child_id>\n");
        return 1;
    }
    

    char *blocks_folder = argv[1];
    char *hashes_folder = argv[2];
    int N = atoi(argv[3]);
    int child_id = atoi(argv[4]);
    //printf("%d", child_id);

    char block_filename[PATH_MAX];
    char hash_filename[PATH_MAX];

    // Create filename.txt associated with this process
    snprintf(block_filename, sizeof(block_filename), "%s/%d.txt", blocks_folder, child_id - N + 1);

    // TODO: If the current process is a leaf process, read in the associated block file 
    // and compute the hash of the block.


    if (child_id >= N - 1) { // Start from N-1 to 2N-2

        // Perform hash computation for leaf process

        // Each byte of the hash is represented by two characters in hex
        //So we need twice as much space to store the hash as the number of bytes in the hash.
        char block_hash[SHA256_BLOCK_SIZE * 2 + 1];
        // Hashes the data in block_filename and stores the result in result_hash based on hash.h
        hash_data_block(block_hash, block_filename);

        // Create the filename for the hash file in filename.out
        snprintf(hash_filename, sizeof(hash_filename), "%s/%d.out", hashes_folder, child_id);

        // Write the computed hash to the hash file
        FILE *hash_file = fopen(hash_filename, "w");

        if (hash_file == NULL) {
            perror("Error opening hash_file");
            exit(-1);
        }
        fwrite(block_hash, 1, SHA256_BLOCK_SIZE * 2 + 1, hash_file);
        fclose(hash_file);
    }
    else{
        // TODO: If the current process is not a leaf process, spawn two child processes using  
        // exec() and ./child_process. 
        pid_t left_child, right_child;
        left_child = fork(); // fork() left first

        if (left_child == 0) { // Child process (left)
            
            char left_child_id[32];
            snprintf(left_child_id, sizeof(left_child_id), "%d", 2 * child_id + 1);
            execl("./child_process", "./child_process", blocks_folder, hashes_folder, argv[3], left_child_id, NULL);

        } else {
            // Parent process, now fork() right
            right_child = fork();

            if (right_child == 0) {
                // Child process (right)
                char right_child_id[32];
                snprintf(right_child_id, sizeof(right_child_id), "%d", 2 * child_id + 2);
                execl("./child_process", "./child_process", blocks_folder, hashes_folder, argv[3], right_child_id, NULL);

            } else {
                // Parent process back again

                // TODO: Wait for the two child processes to finish
                waitpid(left_child, NULL, 0);
                waitpid(right_child, NULL, 0);


                // TODO: Retrieve the two hashes from the two child processes from output/hashes/
                char left_hash_filename[PATH_MAX];
                char right_hash_filename[PATH_MAX];
                char combine_hash_filename[PATH_MAX];
                
                snprintf(left_hash_filename, sizeof(left_hash_filename), "%s/%d.out", hashes_folder, 2 * child_id + 1);
                snprintf(right_hash_filename, sizeof(right_hash_filename), "%s/%d.out", hashes_folder, 2 * child_id + 2);


                
                // Compute and output the hash of the concatenation of the two hashes
                // Read hash values from left and right child files and compute the combined hash

                char left_hash_data[SHA256_BLOCK_SIZE * 2 + 1];
                char right_hash_data[SHA256_BLOCK_SIZE * 2 + 1];
                char combined_hash_data[SHA256_BLOCK_SIZE * 2 + 1];

                // Read and store left hash value
                FILE *left_hash_file = fopen(left_hash_filename, "r");

                if (left_hash_file == NULL) {
                    perror("Error opening hash_file");
                    exit(-1);
                }
                fread(left_hash_data, 1, SHA256_BLOCK_SIZE * 2 + 1, left_hash_file);
                fclose(left_hash_file);

                // Read and store right hash value
                FILE *right_hash_file = fopen(right_hash_filename, "r");

                if (right_hash_file == NULL) {
                    perror("Error opening hash_file");
                    exit(-1);
                }
                fread(right_hash_data, 1, SHA256_BLOCK_SIZE * 2 + 1, right_hash_file);
                fclose(right_hash_file);


                // Combined the hash data
                compute_dual_hash(combined_hash_data, left_hash_data, right_hash_data);

                // Construct the filename for the hash file of the current node
                snprintf(combine_hash_filename, sizeof(combine_hash_filename), "%s/%d.out", hashes_folder, child_id);

                // Write the computed hash to the hash file
                FILE *hash_file = fopen(combine_hash_filename, "w");

                if (hash_file == NULL) {
                    perror("Error opening hash_file");
                    exit(-1);
                }
                fwrite(combined_hash_data, 1, SHA256_BLOCK_SIZE * 2 + 1, hash_file);
                fclose(hash_file);
            }
        }

    }


    
}

