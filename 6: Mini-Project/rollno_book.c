#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "book.h"

// Load all the books from a CSV file
int store_books( char *book_data_file )
{
	FILE *cfptr;
	char book_line[500], token;
	struct Book c, dummy;

	cfptr = (FILE *) fopen(book_data_file, "r");
	while(fgets(book_line, sizeof(book_line)-1, cfptr)){
		//printf("line:%s",book_line);
		sscanf(book_line, "%d%s%s", &(c.unique_book_number),c.author_name,c.book_name);
		print_book( &c );
		add_book( &c );
	}
}

void print_book( struct Book *c )
{
	printf("%d,%s,%s\n", c->unique_book_number,c->author_name,c->book_name);
}

// Use get_rec_by_key function to retrieve book
int search_book( int unique_book_number, struct Book *c )
{
	return get_rec_by_ndx_key( unique_book_number, c );
}

// Add the given book into the repository by calling put_rec_by_key
int add_book( struct Book *c )
{
	int status;

	status = put_rec_by_key( c->unique_book_number, c );

	return status;
}

// Use get_rec_by_non_ndx_key function to retrieve book
// Hint: get_rec_by_non_ndx_key( book_name, c, &match_book_book_name, io_count );
int search_book_by_book_name( char *book_name, struct Book *c, int *io_count )
{
	int status;

	status = get_rec_by_non_ndx_key( book_name, c, &match_book_book_name, io_count );

	if( status != PDS_SUCCESS ){
		// TODO you may need to romove this statement
		//fprintf(stderr, "Unable to add book with key %d. Error %d", c->unique_book_number, status );
		return BOOK_FAILURE;
	}
	return status;

	// Call function
}

/* Return 0 if book_name of the book matches with book_name parameter */
/* Return 1 if book_name of the book does NOT match */
/* Return > 1 in case of any other error */
int match_book_book_name( void *rec, void *key )
{
	if(rec == NULL || key ==NULL)
		return 2;

	struct Book *bookPtr = (struct Book *)rec;
	char *bookName = (char *)key;
	
	if(!strcmp(bookPtr->book_name,key))
	{
		return 0;
	}
	else
	{
		return 1;
	}

	// Store the rec in a struct book pointer
    // Store the key in a char pointer
    // Compare the book_name values in key and record
    // Return 0,1,>1 based on above condition
}

// Function to delete a record based on ndx_key
int delete_book ( int unique_book_number )
{
	int status = delete_rec_by_ndx_key(unique_book_number);
	if( status == PDS_SUCCESS)
		return BOOK_SUCCESS;
	else
		return status;
	// Call the delete_book_ndx_key function
	// Return BOOK_SUCCESS or BOOK_FAILURE based on status of above call
}

int overwrite_book( struct Book *b )
{
	int override = pds_overwrite(b->unique_book_number,b);
	if(override == PDS_SUCCESS)
		return BOOK_SUCCESS;
	else
		return override;
}