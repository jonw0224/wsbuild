[Make]
file=index.html
directory=<!--#main.dat:directory#-->
template=main.tpl
default=indexblog.mk

[title]
Home

[description]
<!--#main.dat:description#--> - <!--#title#-->

[lastupdated]
2012 February 24

[sidebar]
<!--#main.dat:sidebarstart#-->
<!--#sidebarmid#-->
<!--#main.dat:sidebarstop#-->

[sidebarmid]
index.html
<!--#main.dat:tc#-->
Home
<!--#main.dat:tb#-->
<!--#blog.dat:SideLinks#-->
<!--#main.dat:tb#-->
about.html
<!--#main.dat:tc#-->
About

[content]
<!--#intro#-->
<!--#overview#-->
<!--#updates#-->

[intro]
<a name=introduction></a>
<h3>Introduction</h3>
<p>This is an example webpage designed to demonstrate the capabilities of the build application.</p>

[overview]
<a name=overview></a>
<h3>Site Overview</h3>
<table width=100% cellpadding=10>
<tr>
<td>
	<span class="h4"><b><a href="blog.html">Blog</a></b></span><br><br>
	<reg>A web blog</reg>
</td>
</tr><tr>
<td>
	<span class="h4"><b><a href="about.html">About</a></b></span><br><br>
	<reg>About the build application.</reg>
</td>
</tr>
</table>

[updates]
<a name=updates></a>
<h3>Updates</h3>
<table width=100% cellpadding=10>
<tr>
<td>
<!--#blog.dat:Entire#-->
</td>
</tr>
</table>



