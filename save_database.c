/*
      Name : Rohan K H
      Date : 12/11/2024
      Description : Inverted search is a method that allows for efficient querying of a database by creating 
                    an index of keywords or terms, mapping them to relevant records. It enables fast searching 
                    by displaying results based on indexed keywords. The system allows users to save new entries, 
                    update existing records, and retrieve information quickly through optimized queries. 
                    By maintaining an inverted index, it reduces the time complexity for large datasets, 
                    improving overall search performance.
*/

#include"main.h"

// function defination for save database to back up file
int save_database(main_node **hash_table)
{
    // reading file name from the user
    printf("Enter the file name to save the database\n");
    char file_name[20];
    scanf("%s",file_name);

    // checking wether file has '.txt' extention or not
    if(strcmp(strstr(file_name,"."),".txt") != 0)
    {
        printf("ERROR: File name should contain '.txt' extention\n");
        return FAILURE;
    }

    // file pointer for the back up file and opening the file in write mode
    FILE *fptr = fopen(file_name,"w");
    if(fptr == NULL)
    {
        printf("ERROR: Unable to open %s file\n",file_name);
        return FAILURE;
    }
    // creating pointer for main and sub nodes
    main_node *main_temp = malloc(sizeof(main_node));
    sub_node *sub_temp = malloc(sizeof(sub_node));

    // traversing through hash table from index 0 to index 26
    for(int i=0;i<27;i++)
    {
        // checking wether the hash index is NULL or not
        if(hash_table[i] != NULL)
        {
            // assigning pointer to the hash index 
            main_temp = hash_table[i];
            while(main_temp)
            {
                // writing data to the back up file
                fprintf(fptr,"#%d;%s;%d;",i,main_temp->word,main_temp->file_count);

                // creating sub pointer and assigning to the sub node 
                sub_node *sub_temp = malloc(sizeof(sub_node));

                // assigning sub pointer to the sub node
                sub_temp = main_temp->sub_node_link;
                while(sub_temp)
                {
                    // writing sub node data to the back up file
                    fprintf(fptr,"%s;%d;",sub_temp->file_name,sub_temp->word_count);

                    // moving to the next sub node by sub node link
                    sub_temp = sub_temp->next_sub_node_link;
                }
                fprintf(fptr,"#\n");

                // moving to the next main node by node link
                main_temp = main_temp->next_main_node_link;
            }
        }
    }
    fclose(fptr);
    
    // info msg upon completion of successfull database save function
    printf("INFO: Database saved successfully in %s file\n",file_name);

    return SUCCESS;
}
