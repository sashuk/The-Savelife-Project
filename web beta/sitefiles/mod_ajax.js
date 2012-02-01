/*Supportive files for JS handling*/

function createObject() {
var request_type;
var browser = navigator.appName;
if(browser == "Microsoft Internet Explorer"){
request_type = new ActiveXObject("Microsoft.XMLHTTP");
} else {
request_type = new XMLHttpRequest();
}
return request_type;
}

var http = createObject();
function searchCall() {
	search_id = encodeURI(document.getElementById('search_id_device').value);
	search_date = encodeURI(document.getElementById('search_date').value);
	http.open('get', 'search.php?search_id=' + search_id + '&search_date=' + search_date);
	http.onreadystatechange =  searchNameqReply;
	http.send(null);
}

function searchNameqReply() {
	if(http.readyState == 4){
	var response = http.responseText;
	document.getElementById('search_res').innerHTML = response;
}
}