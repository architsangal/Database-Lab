# include <stdio.h> 

struct student {
  int rollnum;
  char name[30];
  int age;
};

int save_num_text( char *filename ) {
  FILE *cfPtr;

  if ((cfPtr = fopen(filename,"w"))==NULL)
  {
    printf("File could not be opened for writing\n");
    return 1;//error
  }
  else
  {
    for(int i=0; i<20; i++){
      fprintf(cfPtr,"%d\n", i);//using fprintf to make text file
    }
    fclose(cfPtr);
    return 0;// no error
  }
}

int read_num_text( char *filename ) {
  FILE *cfPtr;

  if ((cfPtr = fopen(filename,"r"))==NULL)
  {
    printf("File could not be read\n");
    return 1;
  }
  else
  {
    char number[5];
    for(int i=0; i<20; i++){
      fscanf( cfPtr, "%s", number);//using fscanf to read text file
      printf("%s\n",number);
    }
    fclose(cfPtr);
    return 0;
  }
}

int save_struct_text( char *filename ) {
  FILE *cfPtr;

  if ((cfPtr = fopen(filename,"w"))==NULL)
  {
    printf("File could not be opened for writing\n");
    return 1;
  }
  else
  {
    struct student array[5]
        = { {1, "rohan second", 23},
            {2, "mohan", 24},
            {3, "tohan", 25},
            {4, "gohan", 26},
            {5, "cohan", 27}};
    for(int i=0;i<5;i++)
    {
      fprintf(cfPtr,"%d %d %s\n", array[i].rollnum,array[i].age,array[i].name);
    }
  }

  fclose(cfPtr);
  return 0;
}

int read_struct_text( char *filename ) {
  FILE *cfPtr;

  if ((cfPtr = fopen(filename,"r"))==NULL)
  {
    printf("File could not be read\n");
    return 1;
  }
  else
  {
    struct student array[5];
    for(int i=0;i<5;i++)
    {
      fscanf(cfPtr,"%d %d %[^\n]", &array[i].rollnum,&array[i].age,array[i].name);
      printf("%d %d %s\n", array[i].rollnum,array[i].age,array[i].name);
    }
  }

  fclose(cfPtr);
  return 0;
}

int save_num_binary( char *filename ) {
  FILE *cfPtr;

  if ((cfPtr = fopen(filename,"wb"))==NULL)
  {
    printf("File could not be opened for writing\n");
    return 1;
  }
  else
  {
    for(int i=0; i<20; i++){
      fwrite(&i,sizeof(int),1,cfPtr);//using fwrite to make binary file
    }
    fclose(cfPtr);
    return 0;
  }
}

int read_num_binary( char *filename ) {
 FILE *cfPtr;

  if ((cfPtr = fopen(filename,"rb"))==NULL)
  {
    printf("File could not be read\n");
    return 1;
  }
  else
  {
    int number;
    for(int i=0; i<20; i++){
      fread(&number,sizeof(int),1,cfPtr);//using fread to read binary file
      printf("%d\n",number);
    }
    fclose(cfPtr);
    return 0;
  }
}

int save_struct_binary( char *filename ) {
  FILE *cfPtr;

  if ((cfPtr = fopen(filename,"wb"))==NULL)
  {
    printf("File could not be opened for writing\n");
    return 1;
  }
  else
  {
    struct student array[5]
        = { {1, "rohan", 23},
            {2, "mohan", 24},
            {3, "tohan", 25},
            {4, "gohan", 26},
            {5, "cohan", 27}};
    fwrite(&array,sizeof(struct student),5,cfPtr);// 5 is number of objects
  }

  fclose(cfPtr);
  return 0;
}

int read_struct_binary( char *filename ) {
 FILE *cfPtr;

  if ((cfPtr = fopen(filename,"rb"))==NULL)
  {
    printf("File could not be read\n");
    return 1;
  }
  else
  {
    struct student array[5];
    fread(&array,sizeof(struct student),5,cfPtr);
    for(int i=0;i<5;i++)
    {
      printf("%d %s %d\n", array[i].rollnum,array[i].name,array[i].age);
    }
  }

  fclose(cfPtr);
  return 0;
}

