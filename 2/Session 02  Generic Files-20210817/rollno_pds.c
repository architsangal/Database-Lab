#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#include "pds.h"

// Define the global variable
struct PDS_RepoInfo repo_handle;

int pds_create(char *repo_name)
{
    FILE *file_ptr = fopen(repo_name,"wb");
    if(file_ptr == NULL)
    {
        return PDS_FILE_ERROR;
    }
    else
    {
        int error_status = fclose(file_ptr);
        if(error_status != 0)
            return PDS_FILE_ERROR;
        else
        {
            repo_handle.repo_status = PDS_REPO_CLOSED;
            return PDS_SUCCESS;
        }

    }

    // open file 
    //handle file error
    //close file
    //return PDS_SUCCESS
}

int pds_open( char *repo_name, int rec_size )
{
    if(repo_handle.repo_status != PDS_REPO_CLOSED)
    {
        return PDS_REPO_ALREADY_OPEN;
    }

    FILE *file_ptr = fopen(repo_name,"rb+");
    if(file_ptr == NULL)
    {
        return PDS_FILE_ERROR;
    }
    else
    {
        // stored pointer to repo_handle
        repo_handle.pds_data_fp = file_ptr;

        // updated pds_name
        strcpy(repo_handle.pds_name, repo_name);

        // updated repo_status
        repo_handle.repo_status = PDS_REPO_OPEN;

        //update rec_size
        repo_handle.rec_size = rec_size;

        return PDS_SUCCESS;

    }

    //open file and store pointer to repo_handle
    //handle file pointer error
    //if successful update pds_name
    //update  repo_status
    //update rec_size
    //return PDS_SUCCESS
}


int put_rec_by_key( int key, void *rec )
{
    if(repo_handle.repo_status == PDS_REPO_OPEN)
    {
        //set file pointer towards end of file
        fseek(repo_handle.pds_data_fp, 0, SEEK_END);

        //write key to file
        int key_write = fwrite(&key,sizeof(int),1,repo_handle.pds_data_fp);

        //write record to file
        int rec_write = fwrite(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);

        //if write is successful return PDS_SUCCESS 
        //Else return error status accordingly
        if(key_write == 0 || rec_write == 0)
        {
            return PDS_ADD_FAILED;
        }
        else
        {
            return PDS_SUCCESS;
        }
    }
    else
    {
        return PDS_REPO_CLOSED;
    }

    //check repo_status
    //set file pointer towards end of file
    //write key to file
    //write record to file
    //if write is successful return PDS_SUCCESS 
    //Else return error status accordingly

}


int get_rec_by_key( int key, void *rec )
{

    if(repo_handle.repo_status == PDS_REPO_OPEN)
    {
        //read file from begining
        fseek(repo_handle.pds_data_fp, 0, SEEK_SET);

        int temp_key;

        while(1 == 1) // always true
        {            
            // read key
            int key_read = fread(&temp_key,sizeof(int),1,repo_handle.pds_data_fp);

            int rec_read = fread(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);

            if(key_read == 0 || rec_read == 0)
            {
                return PDS_REC_NOT_FOUND;
            }
            else
            {
                if(temp_key == key)
                    return PDS_SUCCESS;
            }
        }
    }
    else
    {
        return PDS_REPO_CLOSED;
    }

    //check repo status
    //read file from begining
    // read key
    //compare key 
    //if key is found read the record into rec 
    // return success
    //else return error

}

int pds_close()
{
    if(repo_handle.repo_status != PDS_REPO_OPEN)
    {
        return PDS_REPO_CLOSED;
    }
    else
    {
        int error_status = fclose(repo_handle.pds_data_fp);
        if(error_status != 0)
            return PDS_FILE_ERROR;
        else
        {
            // reset repo_handle name
            repo_handle.pds_name[0]='\0';
            
            // updated repo_status
            repo_handle.repo_status = PDS_REPO_CLOSED;
            return PDS_SUCCESS;
        }
    }

//check repo status
//close file
//reset repo_handle name
//update repo_status
//return PDS_SUCCESS
}

