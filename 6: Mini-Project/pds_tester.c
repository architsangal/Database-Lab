#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

#include "pds.h"
#include "book.h"

#define clear() printf("\033[H\033[J")

void printErrors(int errorCode)
{
	if(errorCode != 0)
		printf("Error:");
	if(errorCode == 1)
		printf("PDS_FILE_ERROR");
	else if(errorCode == 2)
		printf("PDS_ADD_FAILED");
	else if(errorCode == 3)
		printf("PDS_REC_NOT_FOUND");
	else if(errorCode == 4)
		printf("PDS_LOAD_NDX_FAILED");
	else if(errorCode == 12)
		printf("PDS_REPO_ALREADY_OPEN");
	else if(errorCode == 13)
		printf("PDS_NDX_SAVE_FAILED");
	else if(errorCode == 14)
		printf("PDS_REPO_NOT_OPEN");
	else if(errorCode == 15)
		printf("PDS_DELETE_FAILED");
	else if(errorCode == 16)
		printf("PDS_UPDATE_FAILED");
	
	//printf("\n					");
}

int add_book_main()
{
	clear();
	char temp_id[30];
	struct Book book_temp;

	strcpy(book_temp.student_name,"None");

	printf("\n\n\n			Enter the Book Unique Number (Max length:7; Min length:2) : ");
	scanf("%s",temp_id);

	for (int i = 0; temp_id[i]!= '\0'; i++)
    {
        if (isdigit(temp_id[i]) == 0)
		{
			printf("Must contain digits only");
			return add_book_main();
		}
    }

	if(!(strlen(temp_id)>=2 && strlen(temp_id)<=7))
	{
		printf("Minimum length should be 2 and maximum length should be 7");
		return add_book_main();
	}

	book_temp.unique_book_number = atoi(temp_id);

	printf("\n			Enter the Book Name: ");
	scanf("%s",book_temp.book_name);

	printf("\n			Enter the Author Name: ");
	scanf("%s",book_temp.author_name);

	int status = add_book(&book_temp);

	clear();
	if(status == BOOK_SUCCESS)
		printf("\n\n\n\n				Book Details Added");
	else
	{
		printf("\n\n\n\n					");
		printErrors(status);
	}
	return 0;
}

int search_book_by_ID_main()
{
	clear();
	char temp_id[30];
	struct Book book_temp;

	printf("\n\n\n			Enter the Book Unique Number (Max length:7; Min length:2) : ");
	scanf("%s",temp_id);

	for (int i = 0; temp_id[i]!= '\0'; i++)
    {
        if (isdigit(temp_id[i]) == 0)
		{
			printf("Must contain digits only");
			return search_book_by_ID_main();
		}
    }

	if(!(strlen(temp_id)>=2 && strlen(temp_id)<=7))
	{
		printf("Minimum length should be 2 and maximum length should be 7");
		return search_book_by_ID_main();
	}

	int ID = atoi(temp_id);
	book_temp.unique_book_number =-1;

	int status = search_book( ID, &book_temp );
	clear();
	if(status == BOOK_SUCCESS)
		printf("\n\n\n\n				Book Found with details: \n\n\n\n				Book ID: %d\n				Book Name:  %s\n				Author Name: %s\n				Issued to: %s",book_temp.unique_book_number,book_temp.book_name,book_temp.author_name,book_temp.student_name);
	else
	{
		printf("\n\n\n\n				");
		printErrors(status);
	}

	return 0;
}

int search_book_by_book_name_main()
{
	clear();
	struct Book book_temp;
	char book_name_temp[100];

	printf("\n\n\n			Enter the Book Name: ");
	scanf("%s",book_name_temp);

	book_temp.unique_book_number =-1;
	int actual_io = 0;
	int status = search_book_by_book_name( book_name_temp, &book_temp, &actual_io );
	
	clear();
	if(status == BOOK_SUCCESS)
		printf("\n\n\n\n				Book Found with details: \n\n\n\n				Book ID: %d\n				Book Name:  %s\n				Author Name: %s\n				Issued to: %s\n				Actual IO: %d",book_temp.unique_book_number,book_temp.book_name,book_temp.author_name,book_temp.student_name,actual_io);
	else
	{
		printf("\n\n\n\n				");
		printErrors(status);
	}

	return 0;
}

int delete_book_by_unique_id_main()
{

	clear();
	char temp_id[30];

	printf("\n\n\n			Enter the Book Unique Number (Max length:7; Min length:2) : ");
	scanf("%s",temp_id);

	for (int i = 0; temp_id[i]!= '\0'; i++)
    {
        if (isdigit(temp_id[i]) == 0)
		{
			printf("Must contain digits only");
			return delete_book_by_unique_id_main();
		}
    }

	if(!(strlen(temp_id)>=2 && strlen(temp_id)<=7))
	{
		printf("Minimum length should be 2 and maximum length should be 7");
		return delete_book_by_unique_id_main();
	}

	int ID = atoi(temp_id);

	int status = delete_book( ID );

	clear();
	if(status == BOOK_SUCCESS)
		printf("\n\n\n\n				Book delete from record");
	else
	{
		printf("\n\n\n\n				");
		printErrors(status);
	}

	return 0;
}

int update_book_student_info(int isGivenToStudent)
{
	clear();
	char temp_id[30];
	struct Book book_temp;

	printf("\n\n\n			Enter the Book Unique Number (Max length:7; Min length:2) : ");
	scanf("%s",temp_id);

	for (int i = 0; temp_id[i]!= '\0'; i++)
    {
        if (isdigit(temp_id[i]) == 0)
		{
			printf("Must contain digits only");
			return update_book_student_info(isGivenToStudent);
		}
    }

	if(!(strlen(temp_id)>=2 && strlen(temp_id)<=7))
	{
		printf("Minimum length should be 2 and maximum length should be 7");
		return update_book_student_info(isGivenToStudent);
	}

	int ID = atoi(temp_id);

	book_temp.unique_book_number =-1;
	search_book( ID, &book_temp );

	int status;

	if(isGivenToStudent == 0)
	{
		strcpy(book_temp.student_name,"None");
		status = overwrite_book( &book_temp );
	}
	else
	{
		char student_name_temp[100];

		printf("\n\n\n			Enter the Student Name: ");
		scanf("%s",student_name_temp);

		strcpy(book_temp.student_name,student_name_temp);
		status = overwrite_book( &book_temp );
	}

	clear();
	if(status == BOOK_SUCCESS)
	{
		printf("\n\n\n\n				Book Issued Details Updated");
	}
	else
	{
		printf("\n\n\n\n				");
		printErrors(status);
	}

	return 0;
}

void input_request()
{
	int rec_size = sizeof(struct Book);
	int status;
	printf("\n\n\n\n			You can do the following operations:\n");
	printf("			  1. Create PDS Library\n");
	printf("			  2. Open PDS Library\n");
	printf("			  3. Add a new book to Library.\n");
	printf("			  4. Search for a book by its unique ID.\n");
	printf("			  5. Search for a book by its name.\n");
	printf("			  6. Delete a book by its unique ID.\n");
	printf("			  7. Issue the book by its unique ID to a student.\n");
	printf("			  8. Update record of a book returned by a student by its unique ID.\n");
	printf("			  9. Close PDS Library\n");
	printf("			  0. Exit the session.\n\n");
	printf("			  Enter your desired option: ");

	int option_selected;
	scanf("%d",&option_selected);

	int result;

	if(option_selected == 0)
	{
		clear();
		printf("\n\n\n\n				Program Reached its end\n\n\n\n\n\n");
		exit(0);
	}
	else if(option_selected == 1)
	{
		clear();
		result = 0;
		char repo_name[30];
		strcpy(repo_name, "Book_Store");
		status = pds_create( repo_name );
		if( status == BOOK_SUCCESS ){
			printf("\n\n\n\n				PDS file created\n\n\n");
		}
		else{
			printf("\n\n\n\n				");
			printErrors(status);
		}
	}
	else if(option_selected == 2)
	{
		clear();
		result = 0;
		char repo_name[30];
		strcpy(repo_name, "Book_Store");
		status = pds_open( repo_name, rec_size );
		
		if(status == BOOK_SUCCESS)
			printf("\n\n\n\n				PDS file opened\n\n\n");
		else
		{
			printf("\n\n\n\n				");
			printErrors(status);
		}
	}
	else if(option_selected == 3)
	{
		result = add_book_main();
	}
	else if(option_selected == 4)
	{
		result = search_book_by_ID_main();		
	}
	else if(option_selected == 5)
	{
		result = search_book_by_book_name_main();
	}
	else if(option_selected == 6)
	{
		result = delete_book_by_unique_id_main();
	}
	else if(option_selected == 7)
	{
		result = update_book_student_info(1);
	}
	else if(option_selected == 8)
	{
		result = update_book_student_info(0);
	}
	else if(option_selected == 9)
	{
		clear();
		result = 0;
		status = pds_close();
		if(status == BOOK_SUCCESS)
			printf("\n\n\n\n				PDS Closed\n\n\n");
		else
			printf("\n\n\n\n				Not able to close PDS\n\n\n");
	}

	if(result == 0)
	{	// Everything OK
	}
	else
	{
		printf("Error occured");
	}
	input_request();
}

int main()
{
	clear();
	printf("\n\n\n\n			Hello User !!\n");
	input_request();
	return 0;
}