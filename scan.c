/**
 *	Projekt geforked von https://github.com/bjoekeldude/fscanf
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char const* const VERSIONSNR = "1.1.0";

int const DB_SIZE = 20;

struct person
{
    char name[20];
    char geschlecht;
    int  alter;
    char partner[20];
    char kind_1[20];
    char kind_2[20];
    char kind_3[20];
    char kind_4[20];
    char mutter[20];
    char vater[20];
};
typedef struct person person_t;

void readcsv(char const* const datei)
{
    FILE* filepointer = NULL;
    int   zaehler     = 0;

    filepointer = fopen(datei, "r");
    if(NULL == filepointer)
    {
        fprintf(stderr, "Couldnt open file '%s'\n", datei);
        exit(2);
    }
    person_t database[DB_SIZE];
    while(fscanf(filepointer,
                 "%[^,], %c, %d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^.]",
                 database[zaehler].name,
          	 &database[zaehler].geschlecht,
                 &database[zaehler].alter,
		 database[zaehler].partner,
		 database[zaehler].kind_1,
		 database[zaehler].kind_2,
		 database[zaehler].kind_3,
		 database[zaehler].kind_4,
		 database[zaehler].mutter,
		 database[zaehler].vater)
          != EOF)
    {
        printf("%s, %c, %d, %s, %s, %s, %s, %s, %s, %s \n",
                 database[zaehler].name,
                 database[zaehler].geschlecht,
                 database[zaehler].alter,
                 database[zaehler].partner,
                 database[zaehler].kind_1,
                 database[zaehler].kind_2,
                 database[zaehler].kind_3,
                 database[zaehler].kind_4,
                 database[zaehler].mutter,
                 database[zaehler].vater);
        zaehler++;
        if(zaehler == DB_SIZE)
        {
            fprintf(stderr, "Datenbank voll! \n");
            break;
        }
    }
    // check if file closed correctly
    if(fclose(filepointer) == EOF)
    {
        fprintf(stderr, "Fehler beim schließen der Datei! \n");
        exit(2);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "No option recognized. Wrong Usage. Please try -h\n");
    }

    while(true)
    {
        int option = getopt(argc, argv, "hvf:");
        switch(option)
        {
        case 'h':
            printf("Bitte -f nutzen um einen File-Path anzugeben\n");
            exit(0);

        case 'v':
            printf("Version %s\n", VERSIONSNR);
            exit(0);

        case 'f':
            readcsv(optarg);
            break;

        case '?':
            fprintf(stderr, "Please try -h\n");
            exit(1);

        case -1:
            exit(0);
        }
    }

    return 0;
}
