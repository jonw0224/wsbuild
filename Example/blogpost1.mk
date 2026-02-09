[file]
blogpost1.html

[number]
1

[nLink]
<a href="<!--#blogpost2.mk:link#-->"><< Next</a> <!-- &nbsp;&nbsp;|&nbsp;&nbsp; -->

[pLink]
<!-- <a href="<!--#blogpost2.mk:link#-->">Prev >></a> -->

[name]
BlogPost1

[title]
Version History

[lastupdated]
2012 Aug 29

[date]
Mon, 20 Aug 2012 15:19:00 EST

[descript]
Author:  Jonathan Weaver, jonw0224@aim.com
E-mail Contact: jonw0224@aim.com
Description:  File parser and website builder (build.exe)
Version: 1.0
Date: 4/11/2012

Version History:  
----------------

     2/16/2012 through 2/17/2012 - Created and tested

     4/11/2012 - Incorporated processSection routine to remove string length
         limitation


[post]
<p>Author:  Jonathan Weaver, jonw0224@aim.com</p>
<p>E-mail Contact: jonw0224@aim.com</p>
<p>Description:  File parser and website builder (build.exe)</p>
<p>Version: 1.0</p>
<p>Date: 4/11/2012</p>

<p><b>Version History:</b></p>

<ul>
<li>     2/16/2012 through 2/17/2012 - Created and tested</li>

<li>     4/11/2012 - Incorporated processSection routine to remove string length
         limitation</li>
</ul>



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

