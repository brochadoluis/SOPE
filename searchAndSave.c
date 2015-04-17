#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LINE_MAX_SIZE 1024
#define WORD_MAX_SIZE 256
#define MAX_FILE_NUMBER 4096


//Escrever para os ficheiros com pipes por causa do processos.
void trim(char *input)
{
	int lenght = strlen(input);
	if(input[lenght-1] == '\n')
		input[lenght-1] = '\0';
}
void removeExtension(char *input)
{
	int lenght = strlen(input);
	int i = 0;
	for(i;i < lenght; i++){
		if(input[i] == '.')
			input[i] = '\0';
	}
}

//Criar estrutura com palavra-nomeFicheiro-linha e criar array de estruturas.
//Percorrer o array 1 vez por cada palavra.
int main(int argc, char *argv[])
{


	DIR *dir;
	printf("%s\n", argv[1]);
	struct dirent *dir_entry;    
	dir = opendir (argv[1]);

	FILE *fin, *fout, *fin2;
	char*  fileName = malloc(WORD_MAX_SIZE*sizeof(char));
	char lineBuffer[LINE_MAX_SIZE];
	char wordToSearch[WORD_MAX_SIZE];
	char *aux;
	char* fileNames[LINE_MAX_SIZE];
	int lineNo = 1;
	int file_count = 0;
	int match = 0;
	//Ciclo para abrir o diretorio e começar a procurar ficheiros a começar pelo words.txt
	fin = fopen("words.txt", "rt");
	fin2 = fopen("fileToSearch.txt", "rt"); //fopen(fileNames[numberFiles], rt);
	fout = fopen("output.txt", "wt"); //fopen("temp" + numberFiles, wt);

	if (dir != NULL)
	{
		while ((dir_entry = readdir (dir)) != NULL)
		{
			if (strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..") != 0 )
			{
				strncpy(fileName, dir_entry->d_name, WORD_MAX_SIZE);
				removeExtension(fileName);
				printf("FILE COUNT = %d\n", file_count);
				fileNames[file_count] = malloc(WORD_MAX_SIZE);
				if(strcmp(fileName,"words") != 0)
				{
					strcpy(fileNames[file_count], fileName);
					file_count++;

				}
				
				if(!strcmp(fileName,"words"))
				{
					match = 1;
				}
			}
		}
		if(!match){
			printf("ERROR: File words.txt not found.\n");
			exit(1);
		}
		(void) closedir (dir);
	}
	else
		perror ("Couldn't open the directory");

	
	//char* fileNames= {txt1.txt, txt2.txt};
	/*if (argc != 2) { 
    	printf("Invalid number of arguments. Expected:: %s <dir_name>\n", argv[0]); 
    	return 1; 
	}*/

	//Number of args must be source file

    	int numberFiles= 0;
    	char openTemp[WORD_MAX_SIZE];
    	char finalTemp[WORD_MAX_SIZE];
    	for(numberFiles; numberFiles < file_count; ++numberFiles)
    	{
    		pid_t v , wpid;
    		v = fork();
    		wpid = waitpid(v, NULL,WNOHANG);

    		if(v==0) 
    		{

    			fin = fopen("words.txt", "rt");
    			strcpy(openTemp,fileNames[numberFiles]);
    			strcat(openTemp, ".txt");
    			fin2 = fopen(openTemp, "rt");
    			strcpy(finalTemp,fileNames[numberFiles]);
    			strcat(finalTemp,"temp");
    			fout = fopen(finalTemp,"wt");
 				//Percorrer todo o ficheiro
 				printf("READING FILE %s\n", fileNames[numberFiles]);
    			while(fgets(lineBuffer, LINE_MAX_SIZE, fin) != NULL)
    			{
					strcpy(wordToSearch,lineBuffer); //FAZER SPLIT E TRIM PARA LIMPAR ESPAÇOS E /n
					trim(wordToSearch);
					while(fgets(lineBuffer, LINE_MAX_SIZE, fin2) != NULL)
					{
						if((aux = strstr(lineBuffer, wordToSearch)) != NULL )
						{
							//fprintf(fout, "%s: %s - %d\n", wordToSearch, "output.txt", lineNo);
							fprintf(fout, "%s%s%s %d\n", "word ", wordToSearch, " was found on line ", lineNo);
							while((aux = strstr(aux+1, wordToSearch)) != NULL )
							{ // check the line remains
								fprintf(fout, "%s%s%s %d\n", "word ", wordToSearch, " was found on line ", lineNo);
							}
						}
						lineNo++;
					}
					fclose(fin2);
					lineNo = 1;
					fin2 = fopen(openTemp, "rt");
				}
			}
		
		}
		sleep(1500);
	return 0;
}

//}
/*int openFile(File *fileToOpen){};
int closeFile(File *fileToClose){};
int searchWord(){};
int manageWords(){};*/
