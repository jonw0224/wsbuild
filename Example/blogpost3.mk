[file]
blogpost3.html

[number]
3

[nLink]
<!-- <a href="<!--#blogpost3.mk:link#-->"><< Next</a>&nbsp;&nbsp;|&nbsp;&nbsp; -->

[pLink]
<a href="<!--#blogpost2.mk:link#-->">Prev >></a>

[name]
BlogPost3

[title]
Program History

[lastupdated]
2012 Aug 29

[date]
Mon, 20 Aug 2012 15:19:00 EST

[descript]
This program is called "build".  I use it to create static webpages using
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

[post]
<p>This program is called "build".  I use it to create static webpages using
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
of a default value in the make file).</p>




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

