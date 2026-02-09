[Make]
file=blog.html
directory=<!--#main.dat:directory#-->
template=main.tpl
default=blog.mk

[title]
Blog

[keywords]
<!--#main.dat:keywords#-->

[lastupdated]
<!--#blog.dat:lastupdated#-->

[description]
<!--#main.dat:description#-->

[javascript]
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="-1">
<script src="commentscript.js" language="JavaScript1.2"></script>
<!--#main.dat:javascript#-->

[sidebar]
<!--#main.dat:sidebarstart#-->
<!--#blog.dat:SideLinks#-->
<!--#main.dat:sidebarstop#-->

[content]
<!--#pageTop#-->
<!--#blog.dat:Blog#-->
<div align="right"><reg>
<!--#blog.dat:pLink#--></reg></div>
<!--#pageBottom#-->

[pageTop]
<!--#main.dat:rssfeed#-->

[pageBottom]
<script src="showComments.js" language="JavaScript1.2"></script>

[commentsA]
<table width=100%>
<tr>
<td width=75% align="left">
<p id=

[commentsB]
 onclick="showHideComments(

[commentsC]
, 

[commentsD]
, 

[commentsE]
)">
	<script type="text/javascript">document.write(countComments(

[commentsF]
)); dispContents[

[commentsG]
] = 0;</script>
</p>
</tr>
</table>
<br>
<span id=

[commentsH]
>
</span>

[eStart]


[eDescription]
<!--

[eLink]


[endc]
</p>

[endp]
<br><br>

[eGuid]


[eTitle]
<h4><a href="

[eTitleEnd]
">

[eDate]
</a></b>&nbsp;&nbsp;<span class="commentDate"><b>

[eContent]
--></b></span></h4>

