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

int main(int argc, char *argv[])
{
      /* checking CLA arguments are provided or not */
  if(argc > 1)
  {
        // initializing file head for initial file name list 
        file_list *initial_file_name_head = NULL;

        // initializing file head for updated file name list 
        file_list *later_file_name_head = NULL;

        // creating hash table of 27 index values
        main_node *hash_table[27] = {NULL};

          char option;
          do
            {
              // displaying user menu to enter their option
              printf("Enter your option\n");
              printf("1. Create database\n");
              printf("2. Display database\n");
              printf("3. Search database\n");
              printf("4. Save database\n");
              printf("5. Update database\n");
              printf("6. Exit\n");
          
            scanf("%c",&option);

              switch (option)
              {
                case '1':
                {
                      // function call to read and validate cammand line arguments
                      if(read_validate(argc,argv,&initial_file_name_head,&later_file_name_head) == FAILURE)
                      {
                          // msg if the given value is already present in the list
                          printf("INFO: Entered data is already present in the database, No need to create again\n");
                          return 0;
                      }
                      // info msg upon completion of insertion function
                      printf("INFO: Insertion of file names to the list is done\n");

                      /* function call to create database */
                      create_database(&initial_file_name_head, hash_table);
                      printf("INFO: Database created successfully\n");
                      printf("Press any button for main menu\n");
                      char ch;
                      getchar();
                      scanf("%c",&ch);
                      break;
                }
                case '2':	
                {
                      /* function call to Display database */
                      display_database(hash_table);
                      printf("Press any button for main menu\n");
                      char ch;
                      getchar();
                      scanf("%c",&ch);
                      break;
                }
                case '3':	
                {
                      /* function call to search the databse */
                      search_database(hash_table);
                      printf("Press any button for main menu\n");
                      char ch;
                      getchar();
                      scanf("%c",&ch);
                      break;  
                }
                case '4':
                {
                      /*function call to save the data*/
                      save_database(hash_table);
                      printf("Press any button for main menu\n");
                      char ch;
                      getchar();
                      scanf("%c",&ch);
                      break;
                }
                case '5':	
                {
                      /* function call to update the database */
                      update_database(hash_table,&later_file_name_head);
                      printf("Press any button for main menu\n");
                      char ch;
                      getchar();
                      scanf("%c",&ch);
                      break;
                }
                default:
                {
                      // Error msg for invalid option
                      printf("Invalid Input:-( Try again...\n)");
                      break;
                }
              }

            }while (option != '6');

  }
  else
  {
    // Error msg for insufficient arguments 
    printf("ERROR: Insufficient argument\n");
    // info msg for the user to execute the operation
    printf("INFO: for execution :-> ./a.out file1.txt file2.txt file3.txt ......\n");
  }

  return 0;

}
