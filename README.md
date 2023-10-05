Project group number: 33

Group Member:
    Yuan Jiang ( jian0655 )
    Matthew Olson ( olso9444 )
    Thomas Nicklaus ( nickl098 )

CSELabs computer: csel-kh1250-05.cselabs.umn.edu

Plan outlining individual contributions for each member of your group:

    Yuan: 3.1 3.2.1 3.2.2
    Matt: 3.1 3.2.1 3.2.2
    Thomas: 3.1

Any changes you made to the Makefile or existing files that would affect grading: N/A

Any assumptions that you made that weren’t outlined in 7. Assumptions / Notes: N/A

How you designed your program for creating the process tree (again, high-level pseudocode would be acceptable/preferred for this part):

    utils.c:
        setup_output_directory(parameters){
            read(input_file);
            calculated_file_data_size(input_file);
            for (i, N){
                if (last_block_file){
                    last_block_size = block_size + (file_size % n);
                }else{
                    block_size = file_size / n;
                }
                create_and_write_txt(parameters);
            }
        }

        create_all_txt_file(parameters){
            # XXXXXXX
        }

    merkle.c:
        // Here we setup directories needed to include output files
        // Here we created all txt files to distribute input file
        setup_output_directory(parameters);
        create_all_txt_file(parameters);

        // 
        // 
        fork();
        if (child){
            execute(child_process.c);
        }else{
            wait;
            print_markle_tree(parameters);
        }
    
    child_process.c:

        if (leaf_process){
            create_hash_file(parameters);
            write_txt_to_hash(parameters);
        }else{
            left_fork();
            if(left child){
                execute(child_process.c);
            }else{
                right_fork();
                if (right child){
                    execute(child_process.c);
                }else{
                    wait(left child);
                    wait(right child);

                    read(left_child.out);
                    read(right_child.out);
                    combine_hash(combinedHash,left_child.out, right_child.out);

                    creat_and_write_current_outFile(combinedhash)
                }
            }
        }


If your original design (intermediate submission) was different, explain how it changed:
    1. Compeleted merkle.c to create Merkle Process Tree and Visualizing Merkle Tree
    2. Completed child_process.c to read and create Hash files and Merkle Process Tree

Any code that you used AI helper tools to write with a clear justification and explanation of the code (Please see below for the AI tools acceptable use policy):

    1. Googled how to use snprintf()
    2. Googled how to malloc(size)