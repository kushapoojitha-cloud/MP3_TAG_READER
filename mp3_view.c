/*
NAME        : K.Poojitha
DATE        : 6 JAN 2026
DESCRIPTION : This project implements a command-line based MP3 Tag Reader and Editor in C programming, designed to read and modify ID3v2 metadata present in MP3 audio files.
              ID3v2 tags store important information such as song title, artist name, album name, year, genre, and comments, which help in organizing and identifying audio files.
*/
#include "mp3_header.h"
// Header file containing MP3 structure and function declarations
void view(struct MP3 *mp3)											// Function to view ID3v2 tags from the MP3 file
{
    mp3->org_mp3_fptr=fopen(mp3->mp3_filename,"r");					// Open MP3 file in read mode
    if(mp3->org_mp3_fptr==NULL)										// Check if file opening failed
    {
        printf("File not Found\n");
        return;
    }
    fseek(mp3->org_mp3_fptr,10,SEEK_CUR);							// Skip ID3 header (10 bytes)
    char TAG[5];													// Buffer to store frame ID
    for(int i=0;i<6;i++)											// Loop to read first 6 ID3 frames
    {
        fread(TAG,4,1,mp3->org_mp3_fptr);							// Read frame ID (4 bytes)
        TAG[4]='\0';												// Null terminate frame ID string
        int frame_size;												// Variable to store frame size
        fread(&frame_size,sizeof(int),1,mp3->org_mp3_fptr);			// Read frame size from file
        toggle_endianess(mp3,&frame_size);							// Convert frame size from big endian to little endian
        fseek(mp3->org_mp3_fptr,3,SEEK_CUR);						// Skip the frame flag bytes
        tag_to_name(TAG);											// Print the tag name corresponding to the frame ID
        for(int i=0;i<frame_size-1;i++)								//Read and print the frame content character by character
        {
            char ch;
            fread(&ch,1,1,mp3->org_mp3_fptr);
            printf("%c",ch);
        }
        printf("\n");
    }
	fclose(mp3->org_mp3_fptr);										// Close the MP3 file after reading all frames
}

// Function to map frame ID to its corresponding tag name
void tag_to_name(char TAG[])
{
	// Identify frame ID and print matching tag label
	if(!(strcmp(TAG,"TIT2")))
		printf("%-20s%-5s","Title",":");
	else if(!(strcmp(TAG,"TPE1")))
		printf("%-20s%-5s","Artist",":");
	else if(!(strcmp(TAG,"TALB")))
		printf("%-20s%-5s","Album",":");
	else if(!(strcmp(TAG,"TYER")))
		printf("%-20s%-5s","Year",":");
	else if(!(strcmp(TAG,"TCON")))
		printf("%-20s%-5s","Music",":");
	else if(!(strcmp(TAG,"COMM")))
		printf("%-20s%-5s","Comment",":");
	else
		printf("TAG not found");									// Display message for unknown tags
		return ;
}