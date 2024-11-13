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

#include "main.h"

// function defination to create database 
int create_database(file_list **initial_file_name_head, main_node **hash_table)
{
    // creating pointer
    file_list *list_ptr = malloc(sizeof(file_list));

    // assigning pointer to the file name list
    list_ptr = *initial_file_name_head;

    while(list_ptr)
    {
        char str[20];

        // file ptr to open the file in read mode
        FILE *fptr = fopen(list_ptr->file_name,"r");

        if(fptr != NULL)
        {
            // scaning file name from the back up file
            while((fscanf(fptr,"%s",str)) > 0)
            {
                // function call to calculate index value
                int index = (to_lower(str[0])) % 97;

                // copying file name from the back up file
                char name_of_file[20];
                strcpy(name_of_file,list_ptr->file_name);

                // function call to insert the data to the hash table
                hash_table_insertion(str,index,hash_table, name_of_file);
            }
        }
        else
        {
            // Error msg upon not openong the file 
            printf("Unable to open %s file\n",list_ptr->file_name);
        }
        // moving to the next node by node link
        list_ptr = list_ptr->link;
    }
    return SUCCESS;
}

// function defination to insert data to the hash table
int hash_table_insertion(char *str,int index,main_node **hash_table, char *name_of_file)
{
    // initially taking file count and word count as 1
    int file_cnt = 1, word_cnt = 1;

    // checking wether hash table is index is NULL or not
    if(hash_table[index] == NULL)
    {
        // creating new main node here
        main_node *new_main_node = malloc(sizeof(main_node));
        if(new_main_node == NULL)
        {
            return FAILURE;
        }

        // creating new sub node here
        sub_node *new_sub_node = malloc(sizeof(sub_node));
        if(new_sub_node == NULL)
        {
            return FAILURE;
        }

        // updatind all the data to the new main node
        hash_table[index] = new_main_node;
        new_main_node->file_count = file_cnt;
        strcpy(new_main_node->word,str);
        new_main_node->next_main_node_link = NULL;
        new_main_node->sub_node_link = new_sub_node;

        // updating all the data to the new sub node
        new_sub_node->word_count = word_cnt;
        strcpy(new_sub_node->file_name,name_of_file);
        new_sub_node->next_sub_node_link = NULL;
    }
    else
    {
        // creating pointer to the main node to traverse through the node
        main_node *main_temp = malloc(sizeof(main_node));

        // assiging pointer to the hash index
        main_temp = hash_table[index];
        while(main_temp != NULL)
        {
            // checking wether the word is already exist or not
            if(strcmp(str,main_temp->word) == 0)
            {
                sub_node *sub_temp = malloc(sizeof(sub_node));
                sub_temp = main_temp->sub_node_link;
                while(sub_temp != NULL)
                {
                    // checking wether the file name already exist or not
                    if(strcmp(name_of_file,sub_temp->file_name) == 0)
                    {
                        sub_temp->word_count++;
                        return SUCCESS;
                    }
                    else if(sub_temp->next_sub_node_link == NULL)
                    {
                        // creating new sub node to insert at last
                        sub_node *new_sub_node = malloc(sizeof(sub_node));
                        if(new_sub_node == NULL)
                        {
                            return FAILURE;
                        }

                        // updatind all the data to the sub node
                        new_sub_node->word_count = word_cnt;
                        strcpy(new_sub_node->file_name,name_of_file);
                        sub_temp->next_sub_node_link = new_sub_node;
                        main_temp->file_count++;
                        return SUCCESS;
                    }
                    else
                    {
                        // moving to the next sub node by sub node link
                        sub_temp = sub_temp->next_sub_node_link;
                    }
                }
            }
            else if(main_temp->next_main_node_link == NULL)
            {
                // creating new main node of isze main_node
                main_node *new_main_node = malloc(sizeof(main_node));
                if(new_main_node == NULL)
                {
                    return FAILURE;
                }

                // creating new sub node of size sub_node
                sub_node *new_sub_node = malloc(sizeof(sub_node));
                if(new_sub_node == NULL)
                {
                    return FAILURE;
                }

                // updatind all the data to the new main node
                new_main_node->file_count = file_cnt;
                new_main_node->next_main_node_link = NULL;
                new_main_node->sub_node_link = new_sub_node;
                strcpy(new_main_node->word,str);
                main_temp->next_main_node_link = new_main_node;

                // updating all the data to the new sub node
                strcpy(new_sub_node->file_name,name_of_file);
                new_sub_node->word_count = word_cnt;
                new_sub_node->next_sub_node_link = NULL;
                return SUCCESS;
            }
            else
            {
                // moving to the next main node by main node link
                main_temp = main_temp->next_main_node_link;
            }
        }
    }
    return SUCCESS;
}
