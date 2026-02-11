/*
NAME        : K.Poojitha
DATE        : 6 JAN 2026
DESCRIPTION : This project implements a command-line based MP3 Tag Reader and Editor in C programming, designed to read and modify ID3v2 metadata present in MP3 audio files.
              ID3v2 tags store important information such as song title, artist name, album name, year, genre, and comments, which help in organizing and identifying audio files.
*/
#include "mp3_header.h"
void edit(struct MP3 *mp3)                                              // Function to edit selected ID3 tag in MP3 file
{
    mp3->org_mp3_fptr=fopen(mp3->mp3_filename,"r");                     // Open original MP3 file in read mode
    mp3->dup_mp3_fptr=fopen("temp.mp3","w");                            // Open temporary file in write mode
    if((mp3->org_mp3_fptr)==NULL || (mp3->dup_mp3_fptr)==NULL)          // Check whether files are opened successfully
    {
        printf("ERROR :  Unable to open file\n");
        return;
    }
    char header[10];                                                    // Buffer to store ID3 header
    fread(header,10,1,mp3->org_mp3_fptr);                               // Read 10-byte ID3 header from original file
    fwrite(header,10,1,mp3->dup_mp3_fptr);                              // Write header to temp file
    // Loop to process first 6 ID3 frames
    for(int i=0;i<6;i++)
    {
        char tag[5]={0};                                                // Buffer to store frame ID
        fread(tag,4,1,mp3->org_mp3_fptr);                               // Read frame ID from original file
        tag[4]='\0';                                                    // Null terminate frame ID
        fwrite(tag,4,1,mp3->dup_mp3_fptr);                              // Write frame ID to temp file
        if(strcmp(tag,mp3->given_tag)!=0)                               // If tag is NOT found
        {
            int frame_size;                                             // Variable to store frame size
            fread(&frame_size,4,1,mp3->org_mp3_fptr);                   // Read frame size from org file
            fwrite(&frame_size,4,1,mp3->dup_mp3_fptr);                  // Write frame size to temp file
            toggle_endianess(mp3,&frame_size);                          // Convert frame size (big → little endian)
            char flag[3];                                               // Buffer to store frame flags
            fread(flag,3,1,mp3->org_mp3_fptr);                          // Read frame flags from org file
            fwrite(flag,3,1,mp3->dup_mp3_fptr);                         // Write frame flags to temp file
            for(int i=0;i<frame_size-1;i++)                             //copy frame data byte by byte
            {
                char ch;
                fread(&ch,1,1,mp3->org_mp3_fptr);
                fwrite(&ch,1,1,mp3->dup_mp3_fptr);
            }
        }
        else if(!strcmp(tag,mp3->given_tag))                            // If the tag is found
        {
            int size;                                                   // Variable to store old frame size
            fread(&size,4,1,mp3->org_mp3_fptr);                         // Read old frame size from org file
            toggle_endianess(mp3,&size);                                // Convert old frame size from BIG ENDIAN to LITTLE ENDIAN
            int new_len=strlen(mp3->new_name)+1;                        // Calculate new frame size
            toggle_endianess(mp3,&new_len);                             // Convert new frame size from LITTLE ENDIAN to BIG ENDIAN
            fwrite(&new_len,4,1,mp3->dup_mp3_fptr);                     // Write new frame size (big endian)
            char flag[3];                                               // Buffer to store frame flags
            fread(flag,3,1,mp3->org_mp3_fptr);                          // Read frame flags from org file
            fwrite(flag,3,1,mp3->dup_mp3_fptr);                         // write frame flags to temp file
            fwrite(mp3->new_name,strlen(mp3->new_name),1,mp3->dup_mp3_fptr);    // Write new tag content
            fseek(mp3->org_mp3_fptr,size-1,SEEK_CUR);                          // Skip old tag content 
            break;
        }
    }
    print_tag_data(mp3);                                                   // Copy remaining MP3 data
    fclose(mp3->org_mp3_fptr);                                             // Close original MP3 file
    fclose(mp3->dup_mp3_fptr);                                             // Close temporary MP3 file
    remove(mp3->mp3_filename);                                             // Delete original MP3 file
    rename("temp.mp3",mp3->mp3_filename);                                  // Rename temp file as original
    /*---------------------------------To display the status message after editing MP3 tag-----------------------*/
    printf("-----------------------------------Select Edit option--------------------------------------------\n");
    if (strcmp(mp3->edit_opt,"-t")==0)
    {
        printf("-----------------------------------Select Title Change Option------------------------------------\n");
        printf("%-20s%-10s%s\n","Title",":",mp3->new_name);
        printf("-----------------------------------Title Changed Successfully------------------------------------\n");
    }
    else if (strcmp(mp3->edit_opt,"-a")==0)
    {
        printf("-----------------------------------Select Artist Name Change Option------------------------------\n");
        printf("%-20s%-10s%s\n","Artist",": ",mp3->new_name);
        printf("-----------------------------------Artist Name Changed Successfully------------------------------\n");
    }
    else if (strcmp(mp3->edit_opt,"-A")==0)
    {
        printf("-----------------------------------Select Album Change Option------------------------------------\n");
        printf("%-20s%-10s%s\n","Album",":",mp3->new_name);
        printf("-----------------------------------Album Changed Successfully------------------------------------\n");
    }
    else if (strcmp(mp3->edit_opt,"-y")==0)
    {
        printf("-----------------------------------Select Year Change Option-------------------------------------\n");
        printf("%-20s%-10s%s\n","Year",":",mp3->new_name);
        printf("-----------------------------------Year Changed Successfully-------------------------------------\n");
    }
    else if (strcmp(mp3->edit_opt,"-m")==0)
    {
        printf("-----------------------------------Select Music name Change Option-------------------------------\n");
        printf("%-20s%-10s%s\n","Music",":",mp3->new_name);
        printf("-----------------------------------Music name Changed Successfully-------------------------------\n");
    }
    else if (strcmp(mp3->edit_opt,"-c")==0)
    {
        printf("-----------------------------------Select Comment Change Option----------------------------------\n");
        printf("%-20s%-10s%s\n","Comment",":",mp3->new_name);
        printf("-----------------------------------Comment Changed Successfully----------------------------------\n");
    }
}
void print_tag_data(struct MP3 *mp3)
{
    char ch;
    while (fread(&ch, 1, 1,mp3->org_mp3_fptr)==1)        //while(!feof(mp3->org_file_mp3_fptr))
        fwrite(&ch, 1, 1, mp3->dup_mp3_fptr);
}