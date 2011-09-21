function href(url){
	location.href = url;
}

function loadNavigation(id){	
	var html = " <ul id=\"navigation\"> ";
	html += "<li onclick=\"href('pokerWeb.html')\"> Poker</li>";
	html += "<li onclick=\"href('ruleCreatorWeb.html')\"> RuleCreator</li>";
	html += "<li onclick=\"href('tutorialWeb.html')\"> Tutorial</li>";
	html += "<li onclick=\"href('featuresWeb.html')\"> Features</li>";
	html += "<li onclick=\"href('functionsWeb.html')\"> Functions</li>";
	html += "<li onclick=\"href('welcomeWindowWeb.html')\"> Welkomsvenster</li>";
	html += "</ul> ";
	
	document.getElementById(id).innerHTML = html;
}