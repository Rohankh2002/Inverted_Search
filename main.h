#ifndef INVERT_H
#define INVERT_H
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
	char file_name[20];
	struct node *link;
}file_list;
typedef struct sub_Node
{
	int word_count;
	char file_name[20];
	struct sub_Node *next_sub_node_link;
}sub_node;
typedef struct main_Node
{
	int file_count;
	char word[50];
	sub_node *sub_node_link;
	struct main_Node *next_main_node_link;
}main_node;


// function call to read and validate CLA
int read_validate(int argc, char *argv[], file_list **initial_file_name_head, file_list **later_file_name_head);

// function call to insert file name to the list
int insert_file_to_list(char *str, file_list **initial_file_name_head);

// function call to create databse
int create_database(file_list **initial_file_name_head, main_node **hash_table);

// function call to check duplicate file names
int check_duplicate_file(char *str,file_list **later_file_name_head);

// function call to calculate index values of the words
int to_lower(char str);

// function call to insert data to the hash table 
int hash_table_insertion(char *str,int index,main_node **hash_table, char *name_of_file);

// function call to display database
int display_database(main_node **hash_table);

// function call to create database
int search_database(main_node **hash_table);

// function call to update database
int update_database(main_node **hash_table, file_list **later_file_name_head);

// function call to insert data from back up file to hash table
int insert_data_from_back_up_file(char *back_up_arr, main_node **hash_table, file_list **later_file_name_head);

// function call to insert data from back up file to hash table
int update_data_insertion(char *str,int index,main_node **hash_table, char *name_of_file,int file_cnt, int word_cnt);

// function call to insert file name to the list from back up file
int later_insert_file_to_list(char *str, file_list **later_file_name_head);

// function call to validate back up file name
int validate_back_up_file(char *back_up_file_name);

// function call to save database to the back up file
int save_database(main_node **hash_table);

#endif
