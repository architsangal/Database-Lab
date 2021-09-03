#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include "pds.h"
#include "bst.h"

struct PDS_RepoInfo repo_handle;

int pds_create(char *repo_name)
{
    char *data_file_name = (char *)malloc(sizeof(char)*30);
    strcpy(data_file_name, repo_name);
    int len = strlen(repo_name);
    data_file_name[len] = '.';
    data_file_name[len+1] = 'd';
    data_file_name[len+2] = 'a';
    data_file_name[len+3] = 't';
    data_file_name[len+4] = '\0';

    char *ndx_file_name = (char *)malloc(sizeof(char)*30);
    strcpy(ndx_file_name, repo_name);
    ndx_file_name[len] = '.';
    ndx_file_name[len+1] = 'n';
    ndx_file_name[len+2] = 'd';
    ndx_file_name[len+3] = 'x';
    ndx_file_name[len+4] = '\0';

    FILE *file_ptr = fopen(data_file_name,"wb");
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
        }
    }

    file_ptr = fopen(ndx_file_name,"wb");
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

int pds_open(char* repo_name, int rec_size)
{
    if(repo_handle.repo_status != PDS_REPO_CLOSED)
    {
        return PDS_REPO_ALREADY_OPEN;
    }

    char *data_file_name = (char *)malloc(sizeof(char)*30);
    strcpy(data_file_name, repo_name);
    int len = strlen(repo_name);
    data_file_name[len] = '.';
    data_file_name[len+1] = 'd';
    data_file_name[len+2] = 'a';
    data_file_name[len+3] = 't';
    data_file_name[len+4] = '\0';

    char *ndx_file_name = (char *)malloc(sizeof(char)*30);
    strcpy(ndx_file_name, repo_name);
    ndx_file_name[len] = '.';
    ndx_file_name[len+1] = 'n';
    ndx_file_name[len+2] = 'd';
    ndx_file_name[len+3] = 'x';
    ndx_file_name[len+4] = '\0';

    FILE *file_ptr = fopen(data_file_name,"ab+");
    FILE *ndx_ptr = fopen(ndx_file_name,"ab+");
    
    if(file_ptr == NULL || ndx_ptr == NULL)
    {
        return PDS_FILE_ERROR;
    }
    else
    {
        // stored pointer to repo_handle
        repo_handle.pds_data_fp = file_ptr;

        // stored pointer to repo_handle
        repo_handle.pds_ndx_fp = ndx_ptr;

        // updated pds_name
        strcpy(repo_handle.pds_name, repo_name);

        // updated repo_status
        repo_handle.repo_status = PDS_REPO_OPEN;

        //update rec_size
        repo_handle.rec_size = rec_size;

        repo_handle.pds_bst = NULL;

        pds_load_ndx();

        int error_status = fclose(repo_handle.pds_ndx_fp);

        if(error_status != 0)
            return PDS_FILE_ERROR;
        else
        {
            return PDS_SUCCESS;
        }
    }

    // Open the data file and index file in rb+ mode
    // Update the fields of PDS_RepoInfo appropriately
    // Build BST and store in pds_bst by reading index entries from the index file
    // Close only the index file
}

int pds_load_ndx()
{
    //read file from begining
    fseek(repo_handle.pds_ndx_fp, 0, SEEK_SET);

    // read key
    struct PDS_NdxInfo *temp;

    while(1 == 1) // always true
    {
        temp = (struct PDS_NdxInfo *) malloc(sizeof(struct PDS_NdxInfo));
        int ndx_read = fread(temp,sizeof(struct PDS_NdxInfo),1,repo_handle.pds_ndx_fp);
        if(!feof(repo_handle.pds_ndx_fp) && ndx_read == 0)
        {
            return PDS_FILE_ERROR;
        }
        else if(!feof(repo_handle.pds_ndx_fp))
        {
            bst_add_node(&repo_handle.pds_bst,temp->key,temp);
        }
        else
        {
            return PDS_SUCCESS;
        }
    }

    // Internal function used by pds_open to read index entries into BST
}

int put_rec_by_key(int key, void*rec)
{
    
    if(repo_handle.repo_status == PDS_REPO_OPEN)
    {
        if(bst_search(repo_handle.pds_bst,key) != NULL)
            return BST_DUP_KEY;

        //set file pointer towards end of file
        fseek(repo_handle.pds_data_fp, 0, SEEK_END);

        struct PDS_NdxInfo *temp;
        temp = (struct PDS_NdxInfo *) malloc(sizeof(struct PDS_NdxInfo));
        temp->key = key;
        temp->offset = (int) ftell(repo_handle.pds_data_fp);

        //write key to file
        int key_write = fwrite(&key,sizeof(int),1,repo_handle.pds_data_fp);

        //write record to file
        int rec_write = fwrite(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);

        int temp_key;
        fseek(repo_handle.pds_data_fp, 0, SEEK_SET);
        // read key
        int key_read = fread(&temp_key,sizeof(int),1,repo_handle.pds_data_fp);

        //if write is successful return PDS_SUCCESS 
        //Else return error status accordingly
        if(key_write == 0 || rec_write == 0)
        {
            return PDS_ADD_FAILED;
        }
        else
        {
            bst_add_node(&repo_handle.pds_bst,key,temp);
            return PDS_SUCCESS;
        }
    }
    else
    {
        return PDS_REPO_CLOSED;
    }

    // Seek to the end of the data file
    // Create an index entry with the current data file location using ftell
    // Add index entry to BST using offset returned by ftell
    // Write the key at the current data file location
    // Write the record after writing the key
}

int get_rec_by_key(int key, void*rec)
{
    if(repo_handle.repo_status == PDS_REPO_OPEN)
    {
        struct BST_Node *node;
        
        node = bst_search(repo_handle.pds_bst,key);
        
        if(node == NULL)
            return PDS_REC_NOT_FOUND;

        struct PDS_NdxInfo *temp;
        temp = (struct PDS_ *)node->data;
        int position = temp->offset;

        fseek(repo_handle.pds_data_fp, position, SEEK_SET);
        
        int temp_key;

        // read key
        int key_read = fread(&temp_key,sizeof(int),1,repo_handle.pds_data_fp);
        int rec_read = fread(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);

        if(key_read == 0 || rec_read == 0)
        {
            return PDS_NDX_SAVE_FAILED;
        }
        else
        {
            if(temp_key == key)
            {
                return PDS_SUCCESS;
            }
            else
            {
                return PDS_REC_NOT_FOUND;
            }
        }
    }
    else
    {
        return PDS_REPO_CLOSED;
    }

    // Search for index entry in BST
    // Seek to the file location based on offset in index entry
    // Read the key at the current file location 
    // Read the record after reading the key
}

int bst_tree_transfer( struct BST_Node *root )
{
	if( root == NULL )
		return 0;
	else
    {
        struct PDS_NdxInfo temp;
        temp.key = root->key;

        struct PDS_NdxInfo *tempndx = (struct PDS_NdxInfo *) root->data;

        temp.offset = tempndx->offset;

        int ndx_write = fwrite(&temp,sizeof(struct PDS_NdxInfo),1,repo_handle.pds_ndx_fp);

        if(ndx_write == 0)
            return PDS_NDX_SAVE_FAILED;

		int l = bst_tree_transfer( root->left_child );
		int r = bst_tree_transfer( root->right_child );

        if(l!=0 || r!=0)
            return PDS_NDX_SAVE_FAILED;
        else
            return 0;
	}
}

int pds_close()
{

    char *data_file_name = (char *)malloc(sizeof(char)*30);
    strcpy(data_file_name, repo_handle.pds_name);
    int len = strlen(repo_handle.pds_name);
    data_file_name[len] = '.';
    data_file_name[len+1] = 'd';
    data_file_name[len+2] = 'a';
    data_file_name[len+3] = 't';
    data_file_name[len+4] = '\0';

    char *ndx_file_name = (char *)malloc(sizeof(char)*30);
    strcpy(ndx_file_name, repo_handle.pds_name);
    ndx_file_name[len] = '.';
    ndx_file_name[len+1] = 'n';
    ndx_file_name[len+2] = 'd';
    ndx_file_name[len+3] = 'x';
    ndx_file_name[len+4] = '\0';


    if(repo_handle.repo_status != PDS_REPO_OPEN)
    {
        return PDS_REPO_CLOSED;
    }

    FILE *ndx_ptr = fopen(ndx_file_name,"wb");
    repo_handle.pds_ndx_fp = ndx_ptr;
    
    if(ndx_ptr == NULL)
    {
        return PDS_FILE_ERROR;
    }
    else
    {
        int error_code = bst_tree_transfer(repo_handle.pds_bst);
        
        if(error_code != 0)
            return error_code;

        int error_status = fclose(repo_handle.pds_data_fp);
        if(error_status != 0)
            return PDS_FILE_ERROR;
        else
        {
            // reset repo_handle name
            repo_handle.pds_name[0]='\0';
            
            // updated repo_status
            repo_handle.repo_status = PDS_REPO_CLOSED;
        }
        
        error_status = fclose(ndx_ptr);
        if(error_status != 0)
            return PDS_FILE_ERROR;
        else
        {
            return PDS_SUCCESS;
        }
    }

    bst_destroy(repo_handle.pds_bst);

    // Open the index file in wb mode (write mode, not append mode)
    // Unload the BST into the index file by traversing it in PRE-ORDER (overwrite the entire index file)
    // Free the BST by calling bst_destroy()
    // Close the index file and data file
}