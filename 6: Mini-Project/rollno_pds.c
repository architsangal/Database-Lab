#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include "pds.h"
#include "bst.h"

struct PDS_RepoInfo repo_handle;


int pds_create(char *repo_name) 
{
  char filename[30], indexfile[30];
  strcpy(filename,repo_name);
  strcpy(indexfile,repo_name);
  strcat(filename,".dat");
  strcat(indexfile,".ndx");
  FILE *fp = fopen(filename,"wb+");
  FILE *ifp = fopen(indexfile,"wb+");
  if(fp  == NULL || ifp == NULL) return PDS_FILE_ERROR;\
  fclose(fp);
  fclose(ifp);

  repo_handle.repo_status = PDS_REPO_CLOSED;
  
  return PDS_SUCCESS;
}



int pds_open(char* repo_name, int rec_size) // Same as before
{
    if(repo_handle.repo_status != PDS_REPO_CLOSED)
    {
        return PDS_REPO_ALREADY_OPEN;
    }

    // naming of files with extensions
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

// Open the data file and index file in rb+ mode
// Update the fields of PDS_RepoInfo appropriately
// Build BST and store in pds_bst by reading index entries from the index file
// Close only the index file
}

int pds_load_ndx() // Same as before
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
            return 4;// PDS_LOAD_NDX_FAILED
        }
        else if(!feof(repo_handle.pds_ndx_fp))
        {
            bst_add_node(&repo_handle.pds_bst,temp->key,temp);
        }
        else
        {
            return BST_SUCCESS;
        }
    }

    // Internal function used by pds_open to read index entries into BST
}

int put_rec_by_key(int key, void*rec)
{
      if(repo_handle.repo_status == PDS_REPO_OPEN)
    {
        if(bst_search(repo_handle.pds_bst,key) != NULL)
            return PDS_ADD_FAILED;

        //set file pointer towards end of file
        fseek(repo_handle.pds_data_fp, 0, SEEK_END);

        struct PDS_NdxInfo *temp;
        temp = (struct PDS_NdxInfo *) malloc(sizeof(struct PDS_NdxInfo));
        temp->key = key;
        temp->offset = (int) ftell(repo_handle.pds_data_fp);
        temp->is_deleted = 0;

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
            bst_add_node(&repo_handle.pds_bst,key,temp);
            return PDS_SUCCESS;
        }
    }
    else
    {
        return PDS_REPO_NOT_OPEN;
    }

    // Seek to the end of the data file
    // Create an index entry with the current data file location using ftell
    // Add index entry to BST using offset returned by ftell
    // Write the key at the current data file location
    // Write the record after writing the key

  // Seek to the end of the data file
  // Create an index entry with the current data file location using ftell
  // (NEW) ENSURE is_deleted is set to 0 when creating index entry
  // Add index entry to BST using offset returned by ftell
  // Write the key at the current data file location
  // Write the record after writing the key
}

int get_rec_by_ndx_key(int key, void*rec)
{
    if(repo_handle.repo_status == PDS_REPO_OPEN)
    {
        struct BST_Node *node;
        
        node = bst_search(repo_handle.pds_bst,key);
        
        if(node == NULL)
            return PDS_REC_NOT_FOUND;

        struct PDS_NdxInfo *temp;
        temp = (struct PDS_NdxInfo *)node->data;
        int position = temp->offset;

        if(temp->is_deleted == 1)
            return PDS_REC_NOT_FOUND;

        fseek(repo_handle.pds_data_fp, position, SEEK_SET);
        
        int temp_key;

        // read key
        int key_read = fread(&temp_key,sizeof(int),1,repo_handle.pds_data_fp);
        int rec_read = fread(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);

        if(key_read == 0 || rec_read == 0)
        {
            return PDS_FILE_ERROR;
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
        return PDS_REPO_NOT_OPEN;
    }

    // Search for index entry in BST
    // Seek to the file location based on offset in index entry
    // Read the key at the current file location 
    // Read the record after reading the key

  // Search for index entry in BST
  // (NEW) Check if the entry is deleted and if it is deleted, return PDS_REC_NOT_FOUND
  // Seek to the file location based on offset in index entry
  // Read the key at the current file location 
  // Read the record after reading the key
}

int bst_tree_transfer( struct BST_Node *root )
{
	if( root == NULL)
		return 0;
	else
    {
        struct PDS_NdxInfo temp;
        temp.key = root->key;

        struct PDS_NdxInfo *tempndx = (struct PDS_NdxInfo *) root->data;

        temp.offset = tempndx->offset;
        temp.is_deleted=0;

        if(tempndx->is_deleted == 0)
        {
            int ndx_write = fwrite(&temp,sizeof(struct PDS_NdxInfo),1,repo_handle.pds_ndx_fp);

            if(ndx_write == 0)
                return PDS_NDX_SAVE_FAILED;
        }

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
        return PDS_REPO_NOT_OPEN;
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

// Open the index file in wb mode (write mode, not append mode)
// Unload the BST into the index file by traversing it in PRE-ORDER (overwrite the entire index file)
// (NEW) Ignore the index entries that have already been deleted. 
// Free the BST by calling bst_destroy()
// Close the index file and data file

}

int get_rec_by_non_ndx_key(void *key, void *rec, int (*matcher)(void *rec, void *key), int *io_count)
{
    if(repo_handle.repo_status == PDS_REPO_OPEN)
    {

        struct BST_Node *node;

        //read file from begining
        fseek(repo_handle.pds_data_fp, 0, SEEK_SET);

        int temp_key;
        int i=0;
        int f=0;

        while(1 == 1) // always true
        {            
            // read key
            int key_read = fread(&temp_key,sizeof(int),1,repo_handle.pds_data_fp);
            int rec_read = fread(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);

            node = bst_search(repo_handle.pds_bst,temp_key);

            if(node == NULL)
            {
                i++;
                continue;
            }

            struct PDS_NdxInfo *temp_data;

            temp_data = (struct PDS_NdxInfo *)node->data;

            if(key_read == 0 || rec_read == 0)
            {
                break;
            }
            else
            {
                if(!matcher(rec,key))
                {
                    if(temp_data->is_deleted==0)
                    {
                        *io_count = i+1;
                        f=1;
                    }
                }
                i++;
            }
        }

        if(f==1)
        {
            return PDS_SUCCESS;
        }
        else
        {
            return PDS_REC_NOT_FOUND;
        }
        return PDS_REC_NOT_FOUND;
    }
    else
    {
        return PDS_REPO_CLOSED;
    }

  // Seek to beginning of file
  // Perform a table scan - iterate over all the records
  //   Read the key and the record
  //   Increment io_count by 1 to reflect count no. of records read
  //   Use the function in function pointer to compare the record with required key
  //   (NEW) Check the entry of the record in the BST and see if it is deleted. If so, return PDS_REC_NOT_FOUND
  // Return success when record is found
}

int delete_rec_by_ndx_key( int key) // New Function
{

    if(repo_handle.repo_status == PDS_REPO_OPEN)
    {
        struct BST_Node *node;
        
        node = bst_search(repo_handle.pds_bst,key);
        
        if(node == NULL)
            return PDS_DELETE_FAILED;

        struct PDS_NdxInfo *temp;

        temp = (struct PDS_NdxInfo *)node->data;

        if(temp->is_deleted == 1)
            return PDS_DELETE_FAILED;

        temp->is_deleted = 1;

        return PDS_SUCCESS;
    }
    else
    {
        return PDS_REPO_NOT_OPEN;
    }

  // Search for the record in the BST using the key
  // If record not found, return PDS_DELETE_FAILED
  // If record is found, check if it has already been deleted, if so return PDS_DELETE_FAILED
  // Else, set the record to deleted and return PDS_SUCCESS
}

int pds_overwrite( int key, void *rec )
{
    if(repo_handle.repo_status != PDS_REPO_CLOSED)
    {
        struct BST_Node *node;
        
        node = bst_search(repo_handle.pds_bst,key);
        
        if(node == NULL)
            return PDS_UPDATE_FAILED;

        struct PDS_NdxInfo *temp;

        temp = (struct PDS_NdxInfo *)node->data;

        if(temp->is_deleted == 1)
            return PDS_UPDATE_FAILED;

        //set file pointer towards end of file
        fseek(repo_handle.pds_data_fp, 0, SEEK_END);

        temp->offset = ftell(repo_handle.pds_data_fp);

        int * old_key = malloc(sizeof(int));
        *old_key = temp->key;

        //write key to file
        int key_write1 = fwrite(old_key,sizeof(int),1,repo_handle.pds_data_fp);

        //write record to file
        int rec_write2 = fwrite(rec,repo_handle.rec_size,1,repo_handle.pds_data_fp);

        if(key_write1 == 0 || rec_write2==0)
            return PDS_FILE_ERROR;

        return PDS_SUCCESS;

    }
    else
    {
        return PDS_REPO_NOT_OPEN;
    }

    return 0;
}