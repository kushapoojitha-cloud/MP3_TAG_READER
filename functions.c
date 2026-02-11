/*
NAME        : K.Poojitha
DATE        : 6 JAN 2026
DESCRIPTION : This project implements a command-line based MP3 Tag Reader and Editor in C programming, designed to read and modify ID3v2 metadata present in MP3 audio files.
              ID3v2 tags store important information such as song title, artist name, album name, year, genre, and comments, which help in organizing and identifying audio files.
*/
#include "mp3_header.h"

int validate_cla(int argc, char *argv[], struct MP3 *mp3)												// Function to validate command line arguments
{
    if( argc == 1 )																						// Check if no command line arguments are passed
    {
		printf("------------------------------------------------------------------------------\n");
		printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
		printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
		printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
		printf("To get help pass like : ./a.out --help\n");
		printf("------------------------------------------------------------------------------\n");
		return 0;
    }

    if( (strcmp(argv[1], "--help") == 0) )																// Check if help option is passed
    {
		printf("------------------------------->HELP<-----------------------------------------\n");
		printf("1. -v -> to view mp3 file contents\n");
		printf("2. -e -> to edit mp3 file contents\n");
		printf("\t\t2.1. -t -> to edit song title\n");
		printf("\t\t2.2. -a -> to edit artist name\n");
		printf("\t\t2.3. -A -> to edit album name\n");
		printf("\t\t2.4. -y -> to edit year\n");
		printf("\t\t2.5. -m -> to edit content\n");
		printf("\t\t2.6. -c -> to edit comment\n");
		printf("------------------------------------------------------------------------------\n");
		return 0; 
    }
	if(!strcmp(argv[1], "-v"))																			// Check if view option is selected
    {
		if(argc != 3)																					// Validate argument count for view
		{   
			printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
			return 0;
		}
		else if(argc==3)
		{
			char *str=strstr(argv[2], ".mp3");															// Check for .mp3 extension
			if(str==NULL)
			{
				printf("Invalid mp3 file\n");															// Invalid file format
				return 0;
			}
			if(strcmp(str, ".mp3")==0 && argv[2][0]!='.')												//check for after .mp3 and first character not '.'
        		mp3->mp3_filename = argv[2];															// Store MP3 file name
			else
			{
				printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");					// Invalid file format
				return 0;
			}
		}
		return VIEW;
    }
    
    if(!strcmp(argv[1], "-e"))																			// Check if edit option is selected
    {
		if(argc != 5)																					// Validate argument count for edit
		{   
			printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
			return 0;
		}
		if(strcmp(argv[2], "-t")==0 || strcmp(argv[2], "-a")==0 || strcmp(argv[2], "-A")==0 || strcmp(argv[2], "-y")==0 || strcmp(argv[2], "-m")==0 || strcmp(argv[2],"-c")==0)
		{
			if (!strcmp(argv[2], "-t"))           // If title edit option
            	strcpy(mp3->given_tag, "TIT2");   // Store title tag
        	else if (!strcmp(argv[2], "-a"))      // If artist edit option
           		strcpy(mp3->given_tag, "TPE1");   // Store artist tag
        	else if (!strcmp(argv[2], "-A"))      // If album edit option
            	strcpy(mp3->given_tag, "TALB");   // Store album tag
        	else if (!strcmp(argv[2], "-y"))      // If year edit option
            	strcpy(mp3->given_tag, "TYER");   // Store year tag
        	else if (!strcmp(argv[2], "-m"))      // If music edit option
            	strcpy(mp3->given_tag, "TCON");   // Store music tag
        	else if (!strcmp(argv[2], "-c"))      // If comment edit option
            	strcpy(mp3->given_tag, "COMM");   // Store comment tag
        	else
        	{
            	printf("Invalid edit option\n");  // Invalid edit argument
            	return 0;
        	}

        	mp3->given_tag[4] = '\0';  			 	// Null terminate tag string

			char *str=strstr(argv[4], ".mp3");		// Check MP3 file extension
			if (str == NULL || strcmp(str, ".mp3") != 0 || argv[4][0] == '.')
        	{
            	printf("Invalid mp3 file\n"); 		// Invalid file format
        		return 0;
        	}
		}
		else
		{
			printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
			return 0;
		}
		mp3->mp3_filename = argv[4];			   // Store MP3 file name
		mp3->edit_opt=argv[2];					   // Store edit option
		mp3->new_name = argv[3];				   // Store new tag value
		return EDIT;
    }
}
// Function to convert integer endianess
void toggle_endianess(struct MP3 *mp3, int *size)
{
	char *ptr=(char*)size;							// Treat integer as byte array
	for(int i=0;i<2;i++)							// Loop to swap bytes
	{
		char temp=ptr[4-1-i];
		ptr[4-1-i]=ptr[i];
		ptr[i]=temp;
	}
}