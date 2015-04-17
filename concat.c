#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_SIZE 1024

int main()
{
   // Open two files to be merged
   FILE *fp1 = fopen("TODO.txt", "r");
   FILE *fp2 = fopen("hello.txt", "r");

   // Open file to store the result
   FILE *fp3 = fopen("FinalTest.txt", "w");
   char c;
   char lineBuffer[LINE_MAX_SIZE];

   if (fp1 == NULL || fp2 == NULL || fp3 == NULL)
   {
      puts("Could not open files\n");
      exit(0);
   }
/*
   // Copy contents of first file to file3.txt
   while ((c = fgetc(fp1)) != EOF){
      fputc(c, fp3);
   }
    if((c = fgetc(fp1)) == EOF){

   fprintf(fp3, "\n");
}

   // Copy contents of second file to file3.txt
   while ((c = fgetc(fp2)) != EOF){
      fputc(c, fp3);
   }
    if((c = fgetc(fp2)) == EOF){
      fprintf(fp3, "\n");
}*/

   while(fgets(lineBuffer, LINE_MAX_SIZE, fp1) != NULL){
      fprintf(fp3,"%s",lineBuffer);
   }
   if (fgets(lineBuffer, LINE_MAX_SIZE, fp1) == NULL)
   {
     fprintf(fp3, "\n");

   }
   while(fgets(lineBuffer, LINE_MAX_SIZE, fp2) != NULL){
      fprintf(fp3,"%s",lineBuffer);
   }
   if (fgets(lineBuffer, LINE_MAX_SIZE, fp2) == NULL)
   {
     fprintf(fp3, "\n");

   }

   printf("Merged file1.txt and file2.txt into file3.txt\n");

   fclose(fp1);
   fclose(fp2);
   fclose(fp3);
   return 0;
}