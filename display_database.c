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

// function defination to display database 
int display_database(main_node **hash_table)
{
    // main index menu displaying
    printf("Index\tword  file cnt  file name  word count\n");

    // running the loop from index 0 to index 16 in the hash table
    for(int i=0;i<27;i++)
    {
        // checking hash table is NULL or not
        if(hash_table[i] != NULL)
        {
            // creating pointer to the main node assigning to the hash index 
            main_node *main_temp = malloc(sizeof(main_node)); 
            main_temp = hash_table[i];

            // traversing through main node
            while(main_temp != NULL)
            {
                // displaying data from the hash table
                printf("%d\t%s\t%d\t",i,main_temp->word,main_temp->file_count);

                // creating pointer to the sub node and assingning to the sub node 
                sub_node *sub_temp = malloc(sizeof(sub_node));
                sub_temp = main_temp->sub_node_link;

                // traversing through the sub node
                while(sub_temp != NULL)
                {
                    // displaying the sub node data 
                    printf("%s\t%d\t",sub_temp->file_name,sub_temp->word_count);

                    // moving to the next sub node by sub node link
                    sub_temp = sub_temp->next_sub_node_link;
                }
                printf("\n");

                // moving to the next main node by main node link
                main_temp = main_temp->next_main_node_link;
            }
        }
    }
    return SUCCESS;
}
