dispContents = new Array();

function getComments(id)
{
	var toRet = "";
	for(var i = 0; i < comments.length; i++)
	{
		if (entry[i] == id)
		{
			toRet+= "<p>" + comments[i] + "</p>";
		}
	}
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
	return toRet;
}

function showHideComments(button, content, id)
{
	var x = document.getElementById(button);
	var y = document.getElementById(content);
	if (dispContents[id] == 0)
	{
		y.innerHTML = getComments(id);
		x.innerHTML = "[-] Comments";
		dispContents[id] = 1;
	}
	else
	{
		y.innerHTML = "";
		x.innerHTML = "[+] "+countComments(id)+" Comments";
		dispContents[id] = 0;
	}
}

