[file]
blogpost2.html

[number]
2

[nLink]
<a href="<!--#blogpost3.mk:link#-->"><< Next</a>&nbsp;&nbsp;|&nbsp;&nbsp;

[pLink]
<a href="<!--#blogpost1.mk:link#-->">Prev >></a>

[name]
BlogPost2

[title]
Description

[lastupdated]
2012 Aug 29

[date]
Mon, 20 Aug 2012 15:19:00 EST

[descript]
A make file (*.mk) defines an HTML page to be generated.  It is a standard
ASCII text file that defines the HTML file to be generated it in the
section of the file called Make.  Make contains four values: 

file=output filename
directory=output directory
template=input template
default=file defining sections not included in the make file.

The template file will contain HTML code for the file to be generated and it
includes special comment tags like #ATag#.  The additional pound
sign indicates the Make file should be referenced for the information.  In
the case above the tag will be replaced with everything in the ATag
section of the make file.  Additionally, the section ATag in the make file
may have additional tags like #BTag# that are also processed in the
during the parse.

Now, tags can be formatted in three cases:

#ATag# is a general format.  It causes the parser to check for the 
section ATag in the make file first, then in the file the tag appear in, 
then in the file noted as the default.  Default is used to cause the current
make file to inherit some sections from the default.

#filename:ATag# is a more specific format.  It causes the parser
to look in the filename denoted before the colon.

#this:ATag# tells the parser to only look in the file the tag appears 
in for the section ATag.

Build will process all make files to generate all HTML pages.  The power in
the program is that shared information or HTML code can be placed in
common files.  I also use it to format the same information in different 
files (such as generating an XML RSS Feed from a list of HTML files by
having a make file that generates the RSS Feed).  For instance, if the data
needs to be reformatted and #ATag# is used within the data, and
the data is referred to by two different make files that define section 
ATag differently, the correct section will replace ATag in the data.  It 
doesn't sound that powerful, but my experience is it makes for some pretty
cool possibilities.

[post]
<p>A make file (*.mk) defines an HTML page to be generated.  It is a standard
ASCII text file that defines the HTML file to be generated it in the
section of the file called <code>&#91;Make&#93;</code>.  <code>&#91;Make&#93;</code> contains four values:</p>

<code>file=&lt;output filename&gt;</br>
directory=&lt;output directory&gt;</br>
template=&lt;input template&gt;</br>
default=&lt;file defining sections not included in the make file&gt</br></code>

<p>The template file will contain HTML code for the file to be generated and it
includes special comment tags like <code>&lt;!--#ATag#--&gt;</code>.  The additional pound
sign indicates the Make file should be referenced for the information.  In
the case above the tag will be replaced with everything in the <code>&#91;ATag&#93; </code>
section of the make file.  Additionally, the section <code>&#91;ATag&#93;</code> in the make file
may have additional tags like <code>&lt;!--#BTag#--&gt;</code> that are also processed in the
during the parse.</p>

<p>Now, tags can be formatted in three cases:</p>

<p><code>&lt;!--#ATag#--&gt;</code> is a general format.  It causes the parser to check for the 
section &#91;ATag&#93; in the make file first, then in the file the tag appear in, 
then in the file noted as the default.  Default is used to cause the current
make file to inherit some sections from the default.</p>

<p><code>&lt;!--#filename:ATag#--&gt;</code> is a more specific format.  It causes the parser
to look in the filename denoted before the colon.</p>

<p><code>&lt;!--#this:ATag#--&gt;</code> tells the parser to only look in the file the tag appears 
in for the section <code>&#91;ATag&#93;</code>.</p>

<p>Build will process all make files to generate all HTML pages.  The power in
the program is that shared information or HTML code can be placed in
common files.  I also use it to format the same information in different 
files (such as generating an XML RSS Feed from a list of HTML files by
having a make file that generates the RSS Feed).  For instance, if the data
needs to be reformatted and <code>&lt;!--#ATag#--&gt</code>; is used within the data, and
the data is referred to by two different make files that define section 
&#91;ATag&#93; differently, the correct section will replace ATag in the data.  It 
doesn't sound that powerful, but my experience is it makes for some pretty
cool possibilities.  </p>

[Make]
file=<!--#file#-->
directory=<!--#main.dat:directory#-->
template=main.tpl
default=blog.mk

[content]
<!--#pageTop#-->
<!--#Entry#-->
<div align="right"><reg><!--#nLink#--><!--#pLink#--></reg></div>
<!--#pageBottom#-->

[link]
<!--#this:file#-->?c=<!--#this:number#-->

[Entry]
<!--#eStart#-->
<a name="<!--#this:name#-->"></a>
<script src="commentdata<!--#number#-->.js?v=1" language="JavaScript1.2"></script>
<!--#eTitle#--><!--#this:link#--><!--#eTitleEnd#--><!--#this:title#--><!--#eDate#--><!--#this:date#-->
<!--#eDescription#-->
<!--#this:descript#-->
<!--#eLink#--><!--#main.dat:url#-->/<!--#this:link#-->
<!--#eGuid#--><!--#main.dat:url#-->/<!--#this:link#-->
<!--#eContent#-->
<!--#this:post#-->
<!--#endpost#-->

[endpost]
<!--#endc#-->
<!--#commentsA#-->"button<!--#number#-->"<!--#commentsB#-->'button<!--#number#-->'<!--#commentsC#-->'content<!--#number#-->'<!--#commentsD#--><!--#number#--><!--#commentsE#--><!--#number#--><!--#commentsF#--><!--#number#--><!--#commentsG#-->"content<!--#number#-->"<!--#commentsH#--><!--#endp#-->

