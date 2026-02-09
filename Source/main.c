/* =============================================================================
 * Author:  Jonathan Weaver, jonw0224@gmail.com
 * E-mail Contact: jonw0224@gmail.com
 * Description:  File parser and website builder (build.exe)
 * Version: 1.01
 * Date: 2/8/2026
 * Filename:  main.c
 *
 * Version History:
 * ----------------
 *
 *      2/16/2012 through 2/17/2012 - Created and tested
 *
 *      4/11/2012 - Incorporated processSection routine to remove string length
 *          limitation
 * 
 *      2/8/2026 - Modified code to run on Linux instead of Windows. Tested and
 *          fixed bugs introduced.
 *
 * Program History:
 * ----------------
 *
 * This program is called "build".  I use it to create static webpages using
 * shared data referred to across several files.  The original program was
 * developed in 2000 when I was in college and administered a couple of
 * websites.  The problem was my clients (family) requested changes that spanned
 * multiple webpages and the static HTML was difficult to maintain.  That is
 * why many people use PHP.  However, the servers did not support PHP since
 * they were free webhosts.  So, I wrote a parser in PowerBasic.  Since then, I
 * lost the source code but liked using the parser and continued to use it.
 * Now I can no longer use it because it was compiled in 16 bit code for a 386
 * and Windows 7 no longer supports it.  So this is a rewrite in C with some
 * improvements from the original parser (examples are lifted filename
 * limitations, input and output file size limitations removed, and the addition
 * of a default value in the make file).
 *
 * Description:
 * ------------
 *
 * A make file (*.mk) defines an HTML page to be generated.  It is a standard
 * ASCII text file that defines the HTML file to be generated it in the
 * section of the file called [Make].  [Make] contains four values:
 *
 * [Make]
 * file=<output filename>
 * directory=<output directory>
 * template=<input template>
 * default=<file defining sections not included in the make file>.
 *
 * The template file will contain HTML code for the file to be generated and it
 * includes special comment tags like <!--#ATag#-->.  The additional pound
 * sign indicates the Make file should be referenced for the information.  In
 * the case above the tag will be replaced with everything in the [ATag]
 * section of the make file.  Additionally, the section [ATag] in the make file
 * may have additional tags like <!--#BTag#--> that are also processed in the
 * during the parse.
 *
 * Now, tags can be formatted in three cases:
 *
 * <!--#ATag#--> is a general format.  It causes the parser to check for the
 * section [ATag] in the make file first, then in the file the tag appear in,
 * then in the file noted as the default.  Default is used to cause the current
 * make file to inherit some sections from the default.
 *
 * <!--#filename:ATag#--> is a more specific format.  It causes the parser
 * to look in the filename denoted before the colon.
 *
 * <!--#this:ATag#--> tells the parser to only look in the file the tag appears
 * in for the section [ATag].
 *
 * Build will process all make files to generate all HTML pages.  The power in
 * the program is that shared information or HTML code can be placed in
 * common files.  I also use it to format the same information in different
 * files (such as generating an XML RSS Feed from a list of HTML files by
 * having a make file that generates the RSS Feed).  For instance, if the data
 * needs to be reformatted and <!--#ATag#--> is used within the data, and
 * the data is referred to by two different make files that define section
 * [ATag] differently, the correct section will replace ATag in the data.  It
 * doesn't sound that powerful, but my experience is it makes for some pretty
 * cool possibilities.  I still use it for my website,
 * http://jonw0224.tripod.com
 *
 * -----------------------------------------------------------------------------
 *
 * MIT License
 *
 * Copyright (c) 2026 Jonathan Weaver, jonw0224@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the “Software”), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * =============================================================================
 */

/* Include files for Windows version
#define WINVER 0x0500
#define _WIN32_IE 0x0500

#include <windows.h>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define SEARCHSTR       ".mk"             // File search criteria
#define STR_MAX         40000             // Maximum length for a string

/* Global files */
static FILE* makefile;  // *.mk file currently being processed
static FILE* deffile;   // File referred to as "default" in the make section

/* Explicit definition for recursive call */
char* processString(FILE *mkfile, char* outputStr, char* inputStr);
int processSection(FILE *mkfile, FILE *opfile);

/*******************************************************************************
 * Handles file errors.  Right now, this function does nothing.
 ******************************************************************************/
/* void ErrorHandler(LPTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

}
*/

/*******************************************************************************
 * Sets the file pointer to the beginning of the section given by [sectionName]
 *
 * mkfile: the file to process
 * sectionName: the name of the section to point to
 * returns: 1 if the section if found, 0 if the end of file was reached
 ******************************************************************************/
int gotoSection(FILE *mkfile, char* sectionName)
{
    int c;
    char* ip;
    char flag;
    fseek(mkfile, 0, SEEK_SET);
    while((c = getc(mkfile)) != EOF)
    {
        if(c == '[')  // Opening character
        {
             flag = 0;
             ip = sectionName;  // Section Name
             while(*ip)
             {
                 if(getc(mkfile) != *ip)
                 {
                     flag = 1;
                     break;
                 }
                 ip++;
             }
             if(flag == 0)
             {
                 if(getc(mkfile) == ']') // Ending character
                 {
                     while((c = getc(mkfile)) != '\n'); // Read to next line
                     return 1;
                 }
             }
        }
    }
    return 0;
}

/*******************************************************************************
 * Gets a value.  This is to help process the [Make] section of a *.mk file.
 * The [Make] section contains a list of parameters in the following format:
 * valueName=value
 * getValue finds the requested parameter and returns everything after the
 * equals sign as a string in value.
 *
 * mkfile: file to look in.  The file pointer should already be set to the
 *     beginning of the make section.
 * valueName: the name of the value to retrieve
 * value: a string to store the value in.  Will be '\0' terminated.
 * returns: 1 if the value is found and 0 if the value is not found
 ******************************************************************************/
int getValue(FILE *mkfile, char* valueName, char* value)
{
    int c;
    char *ip, *iv;
    char flag;
    flag = 0;
    ip = valueName;
    iv = value;
    while((c = getc(mkfile)) != EOF)
    {
        if(flag == 2)
        {
            if(c == '\r')
                 ;
            else if(c == '\n')
            {
               *iv = 0;
               return 1;
            }
            else
            {
               *iv = c;
               iv++;
            }
        }
        if((*ip == 0) && (c == '='))
            flag = 2;
        else if(c != *ip)
            ip = valueName;
        else
            ip++;
    }
    return 0;
}

/*******************************************************************************
 * Retrieves the section designated by sectionName in the outputStr.
 * mkfile: file to look in
 * sectionName: the name of the section to retrieve.  I.e. if the sectionName=
 *   "name", getSection returns everything after "[name]\n" or "[name]\r\n"
 *   until it reaches either the next section indicated by "\n\n[" (carriage
 *   returns are ignored and may be included" or the end of the file.
 * outputStr: a string to store the section from the file.  Will be terminated
 *   with '\0'
 * returns: a pointer to the end of outputStr (points to the '\0' character)
 ******************************************************************************/
char* getSection(FILE *mkfile, char* sectionName, char* outputStr)
{
    char inputStr[STR_MAX];
    int c;
    char state;
    char *op;
    op = outputStr;
    state = 0;

    gotoSection(mkfile, sectionName);
    while((c = getc(mkfile)) != EOF)
    {
        switch(state)
        {
        case 0:
            if(c == '\n')
                state = 1;
            else if(c== '\r')
                ;
            else
            {
                *op = c;
                op++;
            }
            break;
        case 1:
            if(c == '\r')
                ;
            else if(c == '\n')
                state = 2;
            else
            {
                *op = '\n';
                op++;
                *op = c;
                op++;
                state = 0;
            }
            break;
        case 2:
            if(c == '\r' || c == '\n')
                ;
            else if(c == '[')
            {
                 *op = 0;
                 strcpy(inputStr, outputStr);
                 return processString(mkfile, outputStr, inputStr);
            }
            else
            {
                *op = '\n';
                op++;
                *op = '\n';
                op++;
                *op = c;
                op++;
                state = 0;
            }
            break;
        }
    }
    *op = 0;
    strcpy(inputStr, outputStr);
    return processString(mkfile, outputStr, inputStr);
}

/*******************************************************************************
 * Produces an output string based on an input string by parsing the tokens and
 * replacing them with the information from the appropriate file.
 *
 * For example, the expression <!--#filename:name#--> will be replaced from
 * the section [name] from filename.
 *
 * Another example, the expression <!--#this:name#--> will be replaced from
 * the section [name] from the mkfile (i.e. the current file).
 *
 * Another example, the expression <!--#name#--> will be replaced from the
 * section [name] from the make file (i.e. the *.mk file being processed,
 * no matter which file the expression occurs).  If the section [name] is not
 * contained in the make file, the current file is checked (mkfile).  If neither
 * of those files contain section [name], then the default file indicated by the
 * make file is checked.
 *
 * In all of the above examples, if no section [name] is found in any file
 * indicated by the expression, the outputStr will be an empty string.
 *
 * mkfile: make file
 * outputStr: the output after parsing the string
 * inputStr: the input string to parse
 * returns: a character pointer to the END of the outputStr
 ******************************************************************************/
char* processString(FILE *mkfile, char* outputStr, char* inputStr)
{
    FILE *openFile;
    char* workStr;
    char* workStr2;
    char* workStr3;
    char* outpt;
    char* oldWorkStr;
    int incr;
    outpt = outputStr;
    workStr = inputStr;
    oldWorkStr = inputStr;

    while((workStr = strstr(oldWorkStr, "<!--#")) != NULL)
    {
        incr = workStr - oldWorkStr;
        strncpy(outpt, oldWorkStr, incr);
        outpt += incr;
        workStr += 5;
        workStr3 = strstr(workStr, "#-->");
        *workStr3 = 0;
        if((workStr2 = strchr(workStr, ':')) != NULL)
        {
            *workStr2 = 0;  // workStr contains filename
            workStr2++;     // workStr2 contains value
            if(strcmp(workStr, "this") == 0)
            {
                outpt = getSection(mkfile, workStr2, outpt);
            }
            else
            {
                openFile = fopen(workStr, "rb");
                outpt = getSection(openFile, workStr2, outpt);
                fclose(openFile);
            }
            workStr2--;
            *workStr2 = ':';
        }
        else
        {
            workStr2 = workStr;  // workStr2 contains value
            // Look in makefile first
            oldWorkStr = getSection(makefile, workStr2, outpt);
            // Look in current file next
            if(oldWorkStr == outpt)  // Found nothing
                oldWorkStr = getSection(mkfile, workStr2, outpt);
            // Look in default file next
            if(oldWorkStr == outpt)  // Found nothing
                oldWorkStr = getSection(deffile, workStr2, outpt);
            outpt = oldWorkStr;
        }
        *workStr3 = '#';
        workStr = workStr3 + 4;
        oldWorkStr = workStr;
    }
    strcpy(outpt, oldWorkStr);
    return strchr(outpt, 0);
}

/*******************************************************************************
 * Produces an output string based on an input string by parsing the tokens and
 * replacing them with the information from the appropriate file.
 *
 * For example, the expression <!--#filename:name#--> will be replaced from
 * the section [name] from filename.
 *
 * Another example, the expression <!--#this:name#--> will be replaced from
 * the section [name] from the mkfile (i.e. the current file).
 *
 * Another example, the expression <!--#name#--> will be replaced from the
 * section [name] from the make file (i.e. the *.mk file being processed,
 * no matter which file the expression occurs).  If the section [name] is not
 * contained in the make file, the current file is checked (mkfile).  If neither
 * of those files contain section [name], then the default file indicated by the
 * make file is checked.
 *
 * In all of the above examples, if no section [name] is found in any file
 * indicated by the expression, the outputStr will be an empty string.
 *
 * mkfile: make file
 * opfile: the output file that recieves the results of parsing the string
 * returns: 0
 ******************************************************************************/
int processSection(FILE *mkfile, FILE *opfile)
{

    FILE *openFile;
    char* workStr;
    char* workStr2;
    char pStr[STR_MAX];
    char* ip;
    long i, j, k;

    char c;
    char state;
    state = 0;
    while((c = getc(mkfile)) != EOF)
    {
        switch(state)
        {
        case 0:
             if(c == '<')
                 state = 1;
             else if(c== '\r')
                 ;
             else if(c == '\n')
                 state = 9;
             else
                 putc(c, opfile);
             break;
        case 1:
             if(c == '!')
                 state = 2;
             else
             {
                 putc('<', opfile);
                 putc(c, opfile);
                 state = 0;
             }
             break;
        case 2:
             if(c == '-')
                 state = 3;
             else
             {
                 putc('<', opfile);
                 putc('!', opfile);
                 putc(c, opfile);
                 state = 0;
             }
             break;
        case 3:
             if(c == '-')
                 state = 4;
             else
             {
                 putc('<', opfile);
                 putc('!', opfile);
                 putc('-', opfile);
                 putc(c, opfile);
                 state = 0;
             }
             break;
        case 4:
             if(c == '#')
             {
                 state = 5;
                 sprintf(pStr, "<!--#");
                 ip = pStr + 5;
             }
             else
             {
                 putc('<', opfile);
                 putc('!', opfile);
                 putc('-', opfile);
                 putc('-', opfile);
                 putc(c, opfile);
                 state = 0;
             }
             break;
        case 5:
             *ip = c;
             ip++;
             if(c == '#')
                 state = 6;
             break;
        case 6:
             *ip = c;
             ip++;
             if(c == '-')
                 state = 7;
             else
                 state = 5;
             break;
        case 7:
             *ip = c;
             ip++;
             if(c == '-')
                 state = 8;
             else
                 state = 5;
             break;
        case 8:
             *ip = c;
             ip++;
             if(c == '>')
             {
                  workStr = pStr+5;
                  workStr2 = ip - 4;
                  *workStr2 = 0;
                    if((workStr2 = strchr(workStr, ':')) != NULL)
                    {
                        *workStr2 = 0;  // workStr contains filename
                        workStr2++;     // workStr2 contains value
                        if(strcmp(workStr, "this") == 0)
                        {
                            i = ftell(mkfile);
                            if(gotoSection(mkfile, workStr2))
                            {
                                processSection(mkfile, opfile);
                                fseek(mkfile, i, SEEK_SET);
                            }
                        }
                        else
                        {
                            openFile = fopen(workStr, "rb");
                            if(gotoSection(openFile, workStr2))
                            {
                                processSection(openFile, opfile);
                            }
                            fclose(openFile);
                        }
                    }
                    else
                    {
                        // Look in makefile first
                        i = ftell(mkfile);
                        j = ftell(makefile);
                        k = ftell(deffile);
                        if(gotoSection(makefile, workStr))
                        {
                             processSection(makefile, opfile);
                        }
                        // Look in current file next
                        else if(gotoSection(mkfile, workStr))
                        {
                             processSection(mkfile, opfile);
                        }
                        // Look in default file next
                        else if(gotoSection(deffile, workStr))
                        {
                             processSection(deffile, opfile);
                        }
                        fseek(mkfile, i, SEEK_SET);
                        fseek(makefile, j, SEEK_SET);
                        fseek(deffile, k, SEEK_SET);

                    }
                  state = 0;
             }
             else
                 state = 5;
             break;
        case 9:
            if(c == '\r')
                ;
            else if(c == '\n')
                state = 10;
            else if(c == '<')
            {
                putc('\n', opfile);
                state = 1;
            }
            else
            {
                putc('\n', opfile);
                putc(c, opfile);
                state = 0;
            }
            break;
        case 10:
            if(c == '\r' || c == '\n')
                ;
            else if(c == '[')
            {
                 return 0;
            }
            else if(c == '<')
            {
                putc('\n', opfile);
                putc('\n', opfile);
                state = 1;
            }
            else
            {
                putc('\n', opfile);
                putc('\n', opfile);
                putc(c, opfile);
                state = 0;
            }
            break;
        }
    }
    return 0;
}


/*******************************************************************************
 * Creates the output file using information from the template file and the
 * make file.
 * opfile: output file
 * tpfile: template file
 * mkfile: make file
 ******************************************************************************/
int createOutput(FILE* opfile, FILE* tpfile, FILE* mkfile)
{
    processSection(tpfile, opfile);
    return 0;
}

/*******************************************************************************
 * Processes the make file
 ******************************************************************************/
int processFile(char* filename)
{

    char inpStr[FILENAME_MAX];
    char fileStr[FILENAME_MAX], dirStr[FILENAME_MAX];
    char templateStr[FILENAME_MAX], defaultStr[FILENAME_MAX];

    // Open the file

    printf("Processing %s...\n", filename);

    static FILE *mkfile;
    mkfile = fopen(filename, "rb");
    if(mkfile == NULL)
        return 0;
    makefile = mkfile;

    // Get initial values
    if(gotoSection(mkfile, "Make"))
    {
        getValue(mkfile, "file", inpStr);
        processString(mkfile, fileStr, inpStr);
    }
    if(gotoSection(mkfile, "Make"))
    {
        getValue(mkfile, "directory", inpStr);
        processString(mkfile, dirStr, inpStr);
    }
    if(gotoSection(mkfile, "Make"))
    {
        getValue(mkfile, "template", inpStr);
        processString(mkfile, templateStr, inpStr);
    }
    if(gotoSection(mkfile, "Make"))
    {
        if(getValue(mkfile, "default", inpStr))
            processString(mkfile, defaultStr, inpStr);
        else
            strcpy(defaultStr, filename);
    }

    // Open the template
    static FILE *tpfile;
    tpfile = fopen(templateStr, "rb");
    sprintf(dirStr, "%s%s", dirStr, fileStr);
    printf("Creating %s...\n", dirStr);

    printf("defaultStr: %s\n", defaultStr);

    // Open the default template
    deffile = fopen(defaultStr, "rb");

    // Open the output file
    static FILE *opfile;
    opfile = fopen(dirStr, "wb");
    
    printf("dirStr: %s, templateStr: %s, filename: %s\n", dirStr, templateStr, filename);
    printf("Success\n");

    createOutput(opfile, tpfile, mkfile);

    fclose(mkfile);
    fclose(tpfile);
    fclose(opfile);
    fclose(deffile);
    return 0;

}

/*******************************************************************************
 * Main Program
 ******************************************************************************/
int main(int argc, char *argv[])
{
/*  This is the main program as written for Linux. Comment out for a Windows Version */
    DIR *dp;
    struct dirent *ep;

    printf("\n");
    // Traverse make files

    // Find the first make file in the directory
    dp = opendir (".");
    if (dp != NULL)
    {
        // Enumerate all of the files in the directory
        while (ep = readdir (dp))
        {
            // Check if the file name contains the mask string
            printf("%s\n", ep->d_name);
            if (strstr(ep->d_name, SEARCHSTR) != NULL) {
                // Process the file
                processFile(ep->d_name);
  
            }
        }
        (void) closedir (dp);
    }
    else
        perror ("Couldn't open the directory");
    
/* End of Linux implementation. */

/*  This is the main program as written for Windows. Uncomment to for a Windows version

    WIN32_FIND_DATA ffd;                    // File returned from directory
    HANDLE hFind = INVALID_HANDLE_VALUE;    // Handle for file find
    DWORD dwError=0;                        // Error code holder

    printf("\n");
    // Traverse make files

    // Find the first file in the directory.
    hFind = FindFirstFile(SEARCHSTR, &ffd);
    if (INVALID_HANDLE_VALUE == hFind)
    {
       ErrorHandler(TEXT("FindFirstFile"));
       return dwError;
    }
    // Enumerate all the files in the directory
    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            ;   // Directory, do nothing
        else
        {
            processFile(ffd.cFileName);
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);

    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
        ErrorHandler(TEXT("FindFirstFile"));
    }

    FindClose(hFind);

  */
  /* End Windows Version of the main program.  */


  return 0;
}

