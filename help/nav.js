function href(url){
	location.href = url;
}

function loadNavigation(id){	
	var html = " <ul id=\"navigation\"> ";
	html += "<li id=\"poker\" onclick=\"href('pokerWeb.html')\"> Poker</li>";
	html += "<li id=\"ruleCreator\" onclick=\"href('ruleCreatorWeb.html')\"> RuleCreator</li>";
	html += "<li id=\"tutorial\" onclick=\"href('tutorialWeb.html')\"> Tutorial</li>";
	html += "<li id=\"features\" onclick=\"href('featuresWeb.html')\"> Features</li>";
	html += "<li id=\"functions\" onclick=\"href('functionsWeb.html')\"> Functions</li>";
	html += "<li id=\"welcomeWindow\" onclick=\"href('welcomeWindowWeb.html')\"> Welkomsvenster</li>";
	html += "</ul> ";
	
	document.getElementById(id).innerHTML = html;
}

function highlight(id){
	document.getElementById(id).style.background = "#6e0600";
	document.getElementById(id).style.color = "white";
}