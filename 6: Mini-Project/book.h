#ifndef BOOK_H
#define BOOK_H

#define BOOK_SUCCESS 0
#define BOOK_FAILURE 1
 
struct Book{
	int unique_book_number;
	char author_name[100];
	char book_name[100];
	char student_name[100];
};

extern struct PDS_RepoInfo *repoHandle;

// Add the given book into the repository by calling put_rec_by_key
int add_book( struct Book *c );

// Display book info in a single line as a CSV without any spaces
void print_book( struct Book *c );

// Use get_rec_by_key function to retrieve book
int search_book( int unique_book_number, struct Book *c );

// Load all the books from a CSV file
int store_books( char *book_data_file );

// Use get_rec_by_non_ndx_key function to retrieve book
int search_book_by_book_name( char *book_name, struct Book *c, int *io_count );

/* Return 0 if book_name of the book matches with book_name parameter */
/* Return 1 if book_name of the book does NOT match */
/* Return > 1 in case of any other error */
int match_book_book_name( void *rec, void *key );

// Function to delete book by ID
int delete_book ( int unique_book_number );

int overwrite_book( struct Book *b );

#endif
