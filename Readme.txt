Author:  Jonathan Weaver, jonw0224@gmail.com
E-mail Contact: jonw0224@gmail.com
Description:  File parser and website builder (wsbuild)
Version: 1.01
Date: 2/7/2026

Version History:  
----------------

     2/16/2012 through 2/17/2012 - Created and tested

     4/11/2012 - Incorporated processSection routine to remove string length
        limitation

    2/8/2026 - Modified code to run on Linux instead of Windows. Tested and
        fixed bugs introduced.

Compile:
--------

gcc -o wsbuild Source/main.C

Program History:
----------------

This program is called "wsbuild".  I use it to create static webpages using
shared data referred to across several files.  The original program was
developed in 2000 when I was in college and administered a couple of 
websites.  The problem was my clients (family) requested changes that spanned 
multiple webpages and the static HTML was difficult to maintain.  That is
why many people use PHP.  However, the servers did not support PHP since
they were free webhosts.  So, I wrote a parser in PowerBasic.  Since then, I 
lost the source code but liked using the parser and continued to use it.  
Now I can no longer use it because it was compiled in 16 bit code for a 386
and Windows 7 no longer supports it.  So this is a rewrite in C with some
improvements from the original parser (examples are lifted filename 
limitations, input and output file size limitations removed, and the addition
of a default value in the make file).

Description:
------------

A make file (*.mk) defines an HTML page to be generated.  It is a standard
ASCII text file that defines the HTML file to be generated it in the
section of the file called [Make].  [Make] contains four values:

[Make]
file=<output filename>
directory=<output directory>
template=<input template>
default=<file defining sections not included in the make file>.

The template file will contain HTML code for the file to be generated and it
includes special comment tags like <!--#ATag#-->.  The additional pound
sign indicates the Make file should be referenced for the information.  In
the case above the tag will be replaced with everything in the [ATag] 
section of the make file.  Additionally, the section [ATag] in the make file
may have additional tags like <!--#BTag#--> that are also processed in the
during the parse.

Now, tags can be formatted in three cases:

<!--#ATag#--> is a general format.  It causes the parser to check for the 
section [ATag] in the make file first, then in the file the tag appear in, 
then in the file noted as the default.  Default is used to cause the current
make file to inherit some sections from the default.

<!--#filename:ATag#--> is a more specific format.  It causes the parser
to look in the filename denoted before the colon.

<!--#this:ATag#--> tells the parser to only look in the file the tag appears 
in for the section [ATag].

Build will process all make files to generate all HTML pages.  The power in
the program is that shared information or HTML code can be placed in
common files.  I also use it to format the same information in different 
files (such as generating an XML RSS Feed from a list of HTML files by
having a make file that generates the RSS Feed).  For instance, if the data
needs to be reformatted and <!--#ATag#--> is used within the data, and
the data is referred to by two different make files that define section 
[ATag] differently, the correct section will replace ATag in the data.  It 
doesn't sound that powerful, but my experience is it makes for some pretty
cool possibilities.  I still use it for my website, 
http://jonw0224.tripod.com

-----------------------------------------------------------------------------

MIT License

Copyright (c) 2026 Jonathan Weaver, jonw0224@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

