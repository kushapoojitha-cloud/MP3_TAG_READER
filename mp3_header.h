#ifndef MP3_HEADER_H
#define MP3_HEADER_H

#include <stdio.h>
#include <string.h>

#define VIEW 	1
#define EDIT 	2


struct MP3
{
    char *mp3_filename;                                         // Pointer to MP3 file name
    char *new_name;                                             // Pointer to new tag data for editing
    FILE *org_mp3_fptr;                                         // File pointer for original MP3 file
    FILE *dup_mp3_fptr;                                         // File pointer for duplicate MP3 file (editing)
    char given_tag[5];                                          // Buffer to store selected ID3 tag
    char *edit_opt;                                             // Pointer to edit option argument
};

int validate_cla(int argc, char *argv[], struct MP3 *mp3);      // Function to validate command line arguments
void view(struct MP3 *mp3);                                     // Function to display MP3 tag information
void edit(struct MP3 *mp3);                                     // Function to edit MP3 tag information
void toggle_endianess(struct MP3 *mp3, int *size);              // Function to convert integer endianess
void print_tag_data(struct MP3*);                               // Function to print tag data (used during editing)
void tag_to_name(char TAG[]);                                   // Function to convert tag ID to readable tag name

#endif