/*
NAME        : K.Poojitha
DATE        : 6 JAN 2026
DESCRIPTION : This project implements a command-line based MP3 Tag Reader and Editor in C programming, designed to read and modify ID3v2 metadata present in MP3 audio files.
              ID3v2 tags store important information such as song title, artist name, album name, year, genre, and comments, which help in organizing and identifying audio files.
*/
#include "mp3_header.h"
// Header file containing MP3 structure and function declarations
int main(int argc, char *argv[])
{
    /* structure variable declaration */
    struct MP3 mp3;
    // Validate command line arguments and get operation type
    int ret = validate_cla(argc,argv,&mp3);
    printf("It is mp3 file\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("MP3 TAG READER AND EDITOR FOR ID3v2\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    if(ret == VIEW)             //if user selects view option
    {
        view(&mp3);             // Call function to view MP3 tag details
    }
    else if(ret == EDIT)        //if user selects view option
    {
       edit(&mp3);              // Call function to edit MP3 tag details
    }
    printf("-------------------------------------------------------------------------------------------------\n");
    return 0;

}