/**
 * Project 1 
 * Assembler code fragment for LC-2K 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINELENGTH 1000

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);

int main(int argc, char *argv[])
{
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
        arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

    if (argc != 3)
    {
        printf("error: usage: %s <assembly-code-file> <machine-code-file>\n", argv[0]);
        exit(1);
    }

    inFileString = argv[1];
    outFileString = argv[2];

    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr == NULL)
    {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }
    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr == NULL)
    {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }

    char labelcheck[1000][MAXLINELENGTH];
    // char empty[] = "";
    char add[] = "add";
    char nor[] = "nor";
    char lw[] = "lw";
    char sw[] = "sw";
    char beq[] = "beq";
    char jalr[] = "jalr";
    char halt[] = "halt";
    char noop[] = "noop";
    char fill[] = ".fill";
    // storing labels
    for (int i = 0; i < 1000; ++i)
    {
        if (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) == 1)
        {
            // checking for duplicate labels
            for (int k = 0; k < 1000; ++k)
            {
                if (strlen(labelcheck[k]) != 0)
                {
                    if (strcmp(labelcheck[k], label) == 0)
                    {
                        // printf("%s", "duplicate label error\n");
                        exit(1);
                    }
                }
            }

            for (int j = 0; j < strlen(label); ++j)
            {
                labelcheck[i][j] = label[j];
            }

            // checking for unrecongnized opcode
            if ((strcmp(opcode, add)) && (strcmp(opcode, nor)) &&
                (strcmp(opcode, lw)) && (strcmp(opcode, sw)) &&
                (strcmp(opcode, beq)) && (strcmp(opcode, jalr)) &&
                (strcmp(opcode, halt)) && (strcmp(opcode, noop)) &&
                (strcmp(opcode, fill)))
            {
                // printf("%s", "unrecognised opcode\n");
                exit(1);
            }
        }
    }

    rewind(inFilePtr);
    for (int l = 0; l < 1000; ++l)
    {
        if (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) == 1)
        {
            // implementation for beq command
            if (strcmp(opcode, beq) == 0)
            {
                int argu1 = atoi(arg1);
                int argu0 = atoi(arg0);
                int beqcode = 0;
                int undefinedvalueornot = 0;
                int address = 0;
                int offsetvalue = 0;
                if (isNumber(arg2) == 1)
                {
                    if (atoi(arg2) < -32768 || atoi(arg2) > 32767)
                    {
                        // printf("%s", "unrecognised offset\n");
                        exit(1);
                    }
                    offsetvalue = atoi(arg2);
                }
                else
                {
                    for (int h = 0; h < 1000; ++h)
                    {
                        if (strcmp(labelcheck[h], arg2) == 0)
                        {
                            address = h;
                            undefinedvalueornot = 1;
                        }
                    }
                    if (undefinedvalueornot == 0)
                    {
                        // printf("%s", "unrecognised file\n");
                        exit(1);
                    }
                    offsetvalue = address - 1 - l;
                    if (offsetvalue < -32768 || offsetvalue > 32767)
                    {
                        // printf("%s", "unrecognised offset\n");
                        exit(1);
                    }
                }
                if (offsetvalue < 0)
                {
                    offsetvalue = offsetvalue & 0b1111111111111111;
                }
                beqcode = 0b100 << 22;
                argu0 = argu0 << 19;
                argu1 = argu1 << 16;
                beqcode = beqcode | argu0;
                beqcode = beqcode | argu1;
                beqcode = beqcode | offsetvalue;
                fprintf(outFilePtr, "%d\n", beqcode);
            }
            // implementation for lw command
            else if (strcmp(opcode, lw) == 0)
            {
                int argu1 = atoi(arg1);
                int argu0 = atoi(arg0);
                int lwcode = 0;
                int offsetvalue = 0;
                int undefinedvalueornot = 0;
                int address = 0;
                if (isNumber(arg2) == 1)
                {
                    if (atoi(arg2) < -32768 || atoi(arg2) > 32767)
                    {
                        // printf("%s", "unrecognised offset\n");
                        exit(1);
                    }
                    offsetvalue = atoi(arg2);
                }
                else
                {
                    for (int h = 0; h < 1000; ++h)
                    {
                        if (strcmp(labelcheck[h], arg2) == 0)
                        {
                            address = h;
                            undefinedvalueornot = 1;
                        }
                    }
                    if (undefinedvalueornot == 0)
                    {
                        // printf("%s", "unrecognised file\n");
                        exit(1);
                    }
                    offsetvalue = address;
                    if (offsetvalue < -32768 || offsetvalue > 32767)
                    {
                        // printf("%s", "unrecognised offset\n");
                        exit(1);
                    }
                }
                if (offsetvalue < 0)
                {
                    offsetvalue = offsetvalue & 0b1111111111111111;
                }
                lwcode = 0b010 << 22;
                argu0 = argu0 << 19;
                argu1 = argu1 << 16;
                lwcode = lwcode | argu0;
                lwcode = lwcode | argu1;
                lwcode = lwcode | offsetvalue;
                fprintf(outFilePtr, "%d\n", lwcode);
            }
            // implementation for sw command
            else if (strcmp(opcode, sw) == 0)
            {
                int argu1 = atoi(arg1);
                int argu0 = atoi(arg0);
                int swcode = 0;
                int offsetvalue = 0;
                int undefinedvalueornot = 0;
                int address = 0;
                if (isNumber(arg2) == 1)
                {
                    if (atoi(arg2) < -32768 || atoi(arg2) > 32767)
                    {
                        // printf("%s", "unrecognised offset\n");
                        exit(1);
                    }
                    offsetvalue = atoi(arg2);
                }
                else
                {
                    for (int h = 0; h < 1000; ++h)
                    {
                        if (strcmp(labelcheck[h], arg2) == 0)
                        {
                            address = h;
                            undefinedvalueornot = 1;
                        }
                    }
                    if (undefinedvalueornot == 0)
                    {
                        // printf("%s", "unrecognised file\n");
                        exit(1);
                    }
                    offsetvalue = address;
                    if (offsetvalue < -32768 || offsetvalue > 32767)
                    {
                        // printf("%s", "unrecognised offset\n");
                        exit(1);
                    }
                }
                if (offsetvalue < 0)
                {
                    offsetvalue = offsetvalue & 0b1111111111111111;
                }
                swcode = 0b011 << 22;
                argu0 = argu0 << 19;
                argu1 = argu1 << 16;
                swcode = swcode | argu0;
                swcode = swcode | argu1;
                swcode = swcode | offsetvalue;
                fprintf(outFilePtr, "%d\n", swcode);
            }
            // implemenation for .fill
            else if (strcmp(opcode, fill) == 0)
            {
                int undefinedvalueornot = 0;
                int address = 0;
                if (isNumber(arg0) == 1)
                {
                    address = atoi(arg0);
                }
                else
                {
                    for (int h = 0; h < 1000; ++h)
                    {
                        if (strcmp(labelcheck[h], arg0) == 0)
                        {
                            address = h;
                            undefinedvalueornot = 1;
                        }
                    }
                    if (undefinedvalueornot == 0)
                    {
                        // printf("%s", "unrecognised file\n");
                        exit(1);
                    }
                }
                fprintf(outFilePtr, "%d\n", address);
            }
            // implementation for jalr
            else if (strcmp(opcode, jalr) == 0)
            {
                int argu1 = atoi(arg1);
                int argu0 = atoi(arg0);
                int jalcode = 0;
                jalcode = 0b101 << 22;
                argu0 = argu0 << 19;
                argu1 = argu1 << 16;
                jalcode = jalcode | argu0;
                jalcode = jalcode | argu1;
                fprintf(outFilePtr, "%d\n", jalcode);
            }
            // implementation for add
            else if (strcmp(opcode, add) == 0)
            {
                int argu1 = atoi(arg1);
                int argu0 = atoi(arg0);
                int argu2 = atoi(arg2);
                int addcode = 0;
                addcode = 0b000 << 22;
                argu0 = argu0 << 19;
                argu1 = argu1 << 16;
                addcode = addcode | argu0;
                addcode = addcode | argu1;
                addcode = addcode | argu2;
                fprintf(outFilePtr, "%d\n", addcode);
            }
            // implementation for nor
            else if (strcmp(opcode, nor) == 0)
            {
                int argu1 = atoi(arg1);
                int argu0 = atoi(arg0);
                int argu2 = atoi(arg2);
                int norcode = 0;
                norcode = 0b001 << 22;
                argu0 = argu0 << 19;
                argu1 = argu1 << 16;
                norcode = norcode | argu0;
                norcode = norcode | argu1;
                norcode = norcode | argu2;
                fprintf(outFilePtr, "%d\n", norcode);
            }
            // implementation for halt
            else if (strcmp(opcode, halt) == 0)
            {
                int halcode = 0b110 << 22;
                fprintf(outFilePtr, "%d\n", halcode);
            }
            // implementation for noop
            else if (strcmp(opcode, noop) == 0)
            {
                int noocode = 0b111 << 22;
                fprintf(outFilePtr, "%d\n", noocode);
            }
        }
    }
    /* here is an example for how to use readAndParse to read a line from
        inFilePtr */
    // if (!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2))
    // {
    /* reached end of file */
    // }

    /* this is how to rewind the file ptr so that you start reading from the
        beginning of the file */
    //rewind(inFilePtr);

    /* after doing a readAndParse, you may want to do the following to test the
        opcode */
    //if (!strcmp(opcode, "add"))
    //{
    /* do whatever you need to do for opcode "add" */
    //}

    return (0);
}

/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if all went well
 *
 * exit(1) if line is too long.
 */
int readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
                 char *arg1, char *arg2)
{
    char line[MAXLINELENGTH];
    char *ptr = line;

    /* delete prior values */
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

    /* read the line from the assembly-language file */
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL)
    {
        /* reached end of file */
        return (0);
    }

    /* check for line too long */
    if (strlen(line) == MAXLINELENGTH - 1)
    {
        printf("error: line too long\n");
        exit(1);
    }

    /* is there a label? */
    ptr = line;
    if (sscanf(ptr, "%[^\t\n ]", label))
    {
        /* successfully read label; advance pointer over the label */
        ptr += strlen(label);
    }

    /*
     * Parse the rest of the line.  Would be nice to have real regular
     * expressions, but scanf will suffice.
     */
    sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",
           opcode, arg0, arg1, arg2);
    return (1);
}

int isNumber(char *string)
{
    /* return 1 if string is a number */
    int i;
    return ((sscanf(string, "%d", &i)) == 1);
}