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

// function defination to search database in the hash table
int search_database(main_node **hash_table)
{
    // reading the word to search in the hash table
    printf("Enter the word you wanna search\n");
    char search_word[20];
    scanf("%s",search_word);

    // function call to calculate index value 
    int index = (to_lower(search_word[0])) % 97;

    if(hash_table[index] == NULL)
    {
        // Error msg if hash index is NULL, means no word in that hash index
        printf("ERROR: Entered word's index is NULL\n");
        return SUCCESS;
    }
    else
    {
        // creating pointer to the main node and assigning it to the calculated hash index value 
        main_node *main_temp = malloc(sizeof(main_node));
        main_temp = hash_table[index];

        // traversing to the main node till NULL
        while(main_temp != NULL)
        {
            // checking word is present in the hash index or not by campairing 
            if(strcmp(search_word,main_temp->word) == 0)
            {
                // display msg for the searched word 
                printf("INFO: The word %s is present in %d files\n",search_word,main_temp->file_count);

                // creating pointer to the sub node and assigning to the sub node
                sub_node *sub_temp = malloc(sizeof(sub_node));
                sub_temp = main_temp->sub_node_link;

                // traversing to the sub node till NULL
                while(sub_temp != NULL)
                {
                    // display msg for sub node data
                    printf("\tIn %s for %d times\n",sub_temp->file_name,sub_temp->word_count);

                    // moving to the next sub node
                    sub_temp = sub_temp->next_sub_node_link;
                }
                return SUCCESS;
            }
            else if(main_temp->next_main_node_link == NULL)
            {
                // display msg upon not finding the word in the database
                printf("INFO: Entered word is not present in the list\n");
                return SUCCESS;
            }

            // moving to the next main node
            main_temp = main_temp->next_main_node_link;
        }
    }
    return SUCCESS;
}

// function defination to calculate index value
int to_lower(char str)
{
    // checking if the index is capital letter or not
    if(str >= 65 && str <= 90)
    {
        return str + 32;
    }
    else if( str >= 97 && str <= 122) // checking if the index is small letter or not
    {
        return str;
    }
    else // checking if the index is special character or not
    {
        return 123;
    }
}
