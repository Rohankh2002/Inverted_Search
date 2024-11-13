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

// function defination for read and validate argument
int read_validate(int argc, char *argv[], file_list **initial_file_name_head, file_list **later_file_name_head)
{
    // checking argument count is more than 1 or not
    if(argc < 2)
    {
        // Error msg for insufficient arguments
        printf("ERROR: Insufficient arguments - file1.txt file2.txt file3.txt ......\n");
        return FAILURE;
    }

    for(int i=1; i<argc; i++)
    {
        // file pointer for the files passed through CLA
        FILE *fptr = fopen(argv[i],"r");
        
        if(fptr != NULL)
        {
            // checking wether the file has '.txt' extension or not
            if(strcmp(strstr(argv[i],"."),".txt") == 0)
            {
                // checking wether file is empty or not
                fseek(fptr,0,SEEK_END);
                int file_size = ftell(fptr);
                if(file_size != 0)
                {
                    // checking wether the file name already exists in the data list or not
                    if(check_duplicate_file(argv[i],later_file_name_head) == SUCCESS)
                    {
                        // info msg on completion of validation process
                        printf("INFO: %s file is validated successfully\n",argv[i]);

                        //  function call for inserting file name to the list
                        insert_file_to_list(argv[i],initial_file_name_head);
                    }
                    else if(i == (argc-1))
                    {
                        return FAILURE;
                    }
                }
                else
                {
                    // Error msg for empty file
                    printf("ERROR: %s is an empty file\n",argv[i]);
                }
            }
            else
            {
                // Error msg for the file which dont have '.txt' or not
                printf("ERROR: %s is not having '.txt' extension \n",argv[i]);
            }
        }
        else
        {
            // Error msg for the file which doesnt exists
            printf("ERROR: Unable to open %s file because it doesn't exist\n",argv[i]);
        }
    }

    return SUCCESS;
}

// function defination to insert the file name to the list
int insert_file_to_list(char *str, file_list **initial_file_name_head)
{
    // taking new node of size file list
    file_list *new = malloc(sizeof(file_list));
    
    // checking wether node created or not
    if(new == NULL)
    return FAILURE;
    
    // coping file name to the node
    strcpy(new->file_name,str);
    new->link = NULL;
    
    // checking node list is empty or not
    if(*initial_file_name_head == NULL)
    {
        *initial_file_name_head = new;
        return SUCCESS;
    }

    // taking poiter for the list of file name
    file_list *temp = *initial_file_name_head;
    
    while(temp->link != NULL)
    {
        // traversing through the list to check the file name already exist in the file list or not
        if(strcmp(str,temp->file_name) == 0)
        {
            // Error msg for duplicate file name
            printf("Duplicate file name\n");
            return SUCCESS;
        }
        // moving to next node by node link
        temp = temp->link;
    }
        
        temp->link = new;
        return SUCCESS;
}

// Function defination to check deplicate file name in the list
int check_duplicate_file(char *str, file_list **later_file_name_head)
{
    // taking file pointer 
    file_list *temp2 = malloc(sizeof(file_list));

    // assigning file list head to the pointer
    temp2 = *later_file_name_head;

        while(temp2)
        {
            // traversing through the list to check wether the file name exist in the list or not
            if(strcmp(str,temp2->file_name) == 0)
            {
                // Error msg for already existing files
                printf("ERROR: %s file already exist in the database\n",str);
                return FAILURE;
            }
            // moving to the next node by node link
            temp2 = temp2->link;
        }

    return SUCCESS;
}
