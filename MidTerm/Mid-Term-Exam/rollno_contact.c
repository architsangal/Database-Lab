#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "contact.h"

// Load all the contacts from a CSV file
int store_contacts( char *contact_data_file )
{
	FILE *cfptr;
	char contact_line[500], token;
	struct Contact c, dummy;

	cfptr = (FILE *) fopen(contact_data_file, "r");
	while(fgets(contact_line, sizeof(contact_line)-1, cfptr)){
		//printf("line:%s",contact_line);
		sscanf(contact_line, "%d%s%s", &(c.contact_id),c.contact_name,c.phone);
		print_contact( &c );
		add_contact( &c );
	}
}

void print_contact( struct Contact *c )
{
	printf("%d,%s,%s\n", c->contact_id,c->contact_name,c->phone);
}

// Use get_rec_by_key function to retrieve contact
int search_contact( int contact_id, struct Contact *c )
{
	return get_rec_by_ndx_key( contact_id, c );
}

// Add the given contact into the repository by calling put_rec_by_key
int add_contact( struct Contact *c )
{
	int status;

	status = put_rec_by_key( c->contact_id, c );

	if( status != PDS_SUCCESS ){
		fprintf(stderr, "Unable to add contact with key %d. Error %d", c->contact_id, status );
		return CONTACT_FAILURE;
	}
	return status;
}

// Use get_rec_by_non_ndx_key function to retrieve contact
// Hint: get_rec_by_non_ndx_key( phone, c, &match_contact_phone, io_count );
int search_contact_by_phone( char *phone, struct Contact *c, int *io_count )
{
	int status;

	status = get_rec_by_non_ndx_key( phone, c, &match_contact_phone, io_count );

	if( status != PDS_SUCCESS ){
		// TODO you may need to romove this statement
		//fprintf(stderr, "Unable to add contact with key %d. Error %d", c->contact_id, status );
		return CONTACT_FAILURE;
	}
	return status;

	// Call function
}

/* Return 0 if phone of the contact matches with phone parameter */
/* Return 1 if phone of the contact does NOT match */
/* Return > 1 in case of any other error */
int match_contact_phone( void *rec, void *key )
{
	if(rec == NULL || key ==NULL)
		return 2;

	struct Contact *contactPtr = (struct Contact *)rec;
	char *phoneNumber = (char *)key;
	
	if(!strcmp(contactPtr->phone,key))
	{
		return 0;
	}
	else
	{
		return 1;
	}

	// Store the rec in a struct contact pointer
    // Store the key in a char pointer
    // Compare the phone values in key and record
    // Return 0,1,>1 based on above condition
}

// Function to delete a record based on ndx_key
int delete_contact ( int contact_id )
{
	if(delete_rec_by_ndx_key(contact_id) == PDS_SUCCESS)
		return CONTACT_SUCCESS;
	else
		return CONTACT_FAILURE;
	// Call the delete_contact_ndx_key function
	// Return CONTACT_SUCCESS or CONTACT_FAILURE based on status of above call
}

int overwrite_contact( struct Contact *c )
{
	int override = pds_overwrite(c->contact_id,c);
	if(override == PDS_SUCCESS)
		return CONTACT_SUCCESS;
	else
		return CONTACT_FAILURE;
}