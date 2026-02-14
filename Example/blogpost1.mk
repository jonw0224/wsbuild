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
2026 FEb 13

[date]
Fri, 13 Feb 2026 22:14:00 EST

[descript]
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


[post]
<p>Author:  Jonathan Weaver, jonw0224@gmail.com</p>
<p>E-mail Contact: jonw0224@gmail.com</p>
<p>Description:  File parser and website builder (wsbuild)</p>
<p>Version: 1.01</p>
<p>Date: 2/7/2026</p>

<p><b>Version History:</b></p>  
<ul>

<li>     2/16/2012 through 2/17/2012 - Created and tested</li>

<li>     4/11/2012 - Incorporated processSection routine to remove string length
        limitation</li>

<li>    2/8/2026 - Modified code to run on Linux instead of Windows. Tested and
        fixed bugs introduced.</li>
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

