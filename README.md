Project group number: 33

Group Member:
    Yuan Jiang ( jian0655 )
    Matthew Olson ( olso9444 )
    Thomas Nicklaus ( nickl098 )

CSELabs computer: csel-kh1250-01.cselabs.umn.edu

Any changes you made to the Makefile or existing files that would affect grading:
    1. Implemented the partition_file_data() function in src/utils.c
    2. Read in the command line arguments in src/merkle.c

Plan outlining individual contributions for each member of your group:
    Yuan: 3.1, 3.2.1, 3.2.2
    Matt:
    Thomas:

Plan on how you are going to implement the process tree component of creating the Merkle tree (high-level pseudocode would be acceptable/preferred for this part):
    In Merkle the parent process is forked and its child process is sent to child_process.c via the exec function. The child ID starts at the root, so when the when the child process is not a leaf node 
    (Child ID >= N-1) left and right child processes are created. The associated hash filenames are generated based on the child ID of the process. Once the tree has gotten to the leaf nodes, the data is hashed using the hash data function and data is sent to the file.

    Creating the merkle tree in pseudocode
    left/right proccess = fork()
    if(child){
        exec(again)
    }
    else{
        combine hash data
        left and right hash data
    }
    if(is leafnode){
        hashdatablock(block hash, block filename)
        filenames are based of child_id-7 (labeled 0-2n-2)
        wirte block hash to file
    }


    Exec function used to create merkle tree takes the relative form
    execl(childprocess, childprocess, block folder, hash folder, n, RootId (0), NULL)





