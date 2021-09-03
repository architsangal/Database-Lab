#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pds.h"
#include "contact.h"

int main(int argc, char *argv[])
{
	char *repo_name = "demo";
	pds_create(repo_name);
	int status, rec_size;
	struct Contact testContact;

	testContact.contact_id = 10000;
	strcpy(testContact.contact_name, "dummy name");
	strcpy(testContact.phone, "dummy number");

	rec_size = sizeof(struct Contact);

	status = pds_open( repo_name, rec_size);
	if( status == PDS_SUCCESS ){
        printf("Success\n");
	}
	else{
        printf("Fail\n");
	}

	status = put_rec_by_key( 10000, &testContact);
	if( status == PDS_SUCCESS ){
        printf("Success\n");
	}
	else{
        printf("Fail\n");
	}

	struct Contact testContact2;
	status = get_rec_by_key( 10000, &testContact2);
	if( status == PDS_SUCCESS ){
        printf("Success\n");
	}
	else{
        printf("Fail\n");
	}

    printf("%d %d\n",testContact.contact_id,testContact2.contact_id);

    if( testContact.contact_id == testContact2.contact_id ){
        printf("Success\n");
	}
	else{
        printf("Fail\n");
	}

    return 0;
}