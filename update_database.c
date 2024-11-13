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

// function defination to update database to the hash table
int update_database(main_node **hash_table, file_list **later_file_name_head)
{
    // running the loop from index 0 to index 16 to check wether the hash table is empty or not to perform update operation
    for(int i=0;i<27;i++)
    {
        if(hash_table[i] != NULL)
        {
            // Error msg if the hash table is not empty
            printf("ERROR: Hash table is not empty, Unable to update database\n");
            return FAILURE;
        }
    }

    // reading the back up file name from the user
    char back_up_file_name[20];
    printf("INFO: Enter the back up file name\n");
    scanf("%s",back_up_file_name);

    // function call to validate the back up file name
    if(validate_back_up_file(back_up_file_name) != SUCCESS)
    {
        return FAILURE;
    }

    // file pointer to the back up file
    FILE *fptr = fopen(back_up_file_name,"r");
    if(fptr == NULL)
    {
        // Error msg upon not opening back up file
        printf("ERROR: Unable to open %s file\n",back_up_file_name);
        return FAILURE;
    }

    char back_up_arr[100];

    while(fscanf(fptr,"%s",back_up_arr) && !feof(fptr)) 
    {
       // printf("back up arr = %s\n",back_up_arr);
        insert_data_from_back_up_file(back_up_arr,hash_table,later_file_name_head);
    }

   // print_list(later_file_name_head);

    printf("INFO: Database updated successfully\n");

    return SUCCESS;
}

int insert_data_from_back_up_file(char *back_up_arr, main_node **hash_table, file_list **later_file_name_head)
{
        // taking string and delimater for string token function with index, word, file count, word count and file name
        char str[20];
        char delim[] = ";#";
        char *tok;
        int index;
        char word[20];
        char file_name[20];
        int file_count;
        int word_count;
        
        // function call to get index by strtok funtion
        tok = strtok(back_up_arr,delim);
        index = atoi(tok);
        // function call to get word by strtok funtion
        tok = strtok(0,delim);
        strcpy(word,tok);
        // function call to get file count by strtok funtion
        tok = strtok(0,delim);
        file_count = atoi(tok);
        for(int i=0;i<file_count;i++)
        {
            // function call to get file name by strtok funtion
            tok = strtok(0,delim);
            strcpy(file_name,tok);
            // function call to insert the file name list to the later_file_name_head
            later_insert_file_to_list(file_name,later_file_name_head);
            // function call to get word count by strtok funtion
            tok = strtok(0,delim);
            word_count = atoi(tok);
            update_data_insertion(word,index,hash_table,file_name,file_count,word_count);
        }
    
        return SUCCESS;
}

int update_data_insertion(char *str,int index,main_node **hash_table, char *name_of_file,int file_cnt, int word_cnt)
{
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

// function defination insert the file names to the list
int later_insert_file_to_list(char *str, file_list **later_file_name_head)
{
    // creatinf new node for list of size file_list
    file_list *new = malloc(sizeof(file_list));
    
    if(new == NULL)
    return FAILURE;
    
    // copying the file name to the list
    strcpy(new->file_name,str);
    new->link = NULL;
    
    // checking wether the list is empty or not
    if(*later_file_name_head == NULL)
    {
        *later_file_name_head = new;
        return SUCCESS;
    }
    
    // pointer to the list to traverse
    file_list *temp = *later_file_name_head;
    
    // traversing to the last node
    while(temp->link != NULL)
    {
        // checking wether the file name is duplicate or not
        if(strcmp(str,temp->file_name) != 0)
        {
            temp = temp->link;
        }
        else
        {
            return SUCCESS;
        }
    }
        // inserting the file name at the last
        temp->link = new;
        return SUCCESS;
}

// function defination to check back up file 
int validate_back_up_file(char *back_up_file_name)
{
    // checking wether the back up file has '.txt' extension or not
    if(strcmp(strstr(back_up_file_name,"."),".txt") != 0)
    {
        // Error msg upon not having '.txt' extension
        printf("ERROR: Entered file dont have '.txt' extention\n");
        return FAILURE;
    }

    // opening the back up file
    FILE *fptr = fopen(back_up_file_name,"r");
    if(fptr == NULL)
    {
        // checking wether the back up file is opened or not
        printf("ERROR: Unable to open %s file",back_up_file_name);
        return FAILURE;
    }

    // checking wether the back up file is empty or not
    fseek(fptr,0,SEEK_END);
    if(ftell(fptr) == 0)
    {
        printf("ERROR: Opened file is empty\n");
        return FAILURE;
    }

    // checking wether the back up file starts with '#' or not
    rewind(fptr);
    char ch;
    if((ch = getc(fptr)) != '#')
    {
        printf("ERROR: Fetched file is wrong\n");
        return FAILURE;
    }

    // closing the back up file
    fclose(fptr);

    return SUCCESS;
}
