dispContents = new Array();
comments = new Array();
entry = new Array();

function getComments(id)
{
	var toRet = "";
	toRet = "<table width=100% border=0 cellspacing=0 cellpadding=5 style=";
	toRet+= String.fromCharCode(34);
	toRet+= "BORDER-LEFT: #8f8f8f 1px solid;BORDER-RIGHT: #8f8f8f 1px solid; BORDER-BOTTOM: #8f8f8f 1px solid"
	toRet+= String.fromCharCode(34);
	toRet+= ">"
	for(var i = 0; i < comments.length; i++)
	{
		if (entry[i] == id)
		{
			toRet+= "<tr><td style=" + String.fromCharCode(34) + "BORDER-TOP: #8f8f8f 1px solid;" + String.fromCharCode(34) 
				+ ">" + comments[i] + "</td></tr>";
		}
	}
	toRet+= "<tr><td style=\"BORDER-TOP: #8f8f8f 1px solid;\">" + 
			"<form name=\"contactme\" method=\"post\" action=\"/cgi-bin/comment.pl\">" +
            "<table border=0 cellpadding=5>" +
            "<tr><td width=20>" +
            "<input type=\"hidden\" name=\"id\" value=\"" + id + "\">" +
			"<input type=\"hidden\" name=\"redirect\" value=\"" + document.URL + "\">" +
            "<p>Name</p></td><td><input type=\"text\" name=\"realname\"></td></tr>" +
			"<tr><td><p>E-mail</p></td><td><p><input type=\"text\" name=\"formmail_mail_email\">(will not be displayed)</p></td></tr>" +
            "<tr><td><p>Website</p></td><td><p><input type=\"text\" name=\"url\">(optional)</p></td></tr>" +
            "<tr><td colspan=2><p><textarea name=\"comments\" cols=60 rows=10></textarea></p>" +
            "</td></tr><tr><td colspan=2 align=\"right\">" +
			"<input type=\"submit\" value=\"Send Comment\">"+
            "&nbsp;&nbsp" +
            "<input type=\"reset\" value=\"Clear\"></td></tr></table></form></td></tr></table>"
	return toRet;
}

function countComments(id)
{
	var toRet = 0;
	for(var i = 0; i < comments.length; i++)
	{
		if (entry[i] == id)
		{
			toRet++;
		}
	}
	if(toRet == 0)
	{
		toRet = "<b>[+] Add Comment</b>";
	}
	else if(toRet == 1)
	{
		toRet = "<b>[+] " + toRet + " Comment / Add Comment</b>";	
	}
	else
	{
		toRet = "<b>[+] " + toRet + " Comments / Add Comment</b>";
	}
	return toRet;
}

function showHideComments(button, content, id)
{
	var x = document.getElementById(button);
	var y = document.getElementById(content);
	if (dispContents[id] == 0)
	{
		y.innerHTML = getComments(id);
		x.innerHTML = "<b>[-] Hide Comments</b>";
		dispContents[id] = 1;
	}
	else
	{
		y.innerHTML = "";
		x.innerHTML = countComments(id);
		dispContents[id] = 0;
	}
}

