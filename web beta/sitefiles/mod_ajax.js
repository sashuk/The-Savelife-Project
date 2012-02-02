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

//Updating the search
function searchCall(inc_string) {
	if (inc_string == 'regular') {
		search_id = '';
		search_date = '';
		search_telephone = '';
	} else {
		search_id = encodeURI(document.getElementById('search_id_device').value);
		search_date = encodeURI(document.getElementById('search_date').value);
		search_telephone = encodeURI(document.getElementById('search_telephone').value);
	}
	http.open('get', 'search.php?search_id=' + search_id + '&search_date=' + search_date + '&search_telephone=' + search_telephone);
	http.onreadystatechange =  searchNameqReply;
	http.send(null);
}

function searchNameqReply() {
	if(http.readyState == 4){
	var response = http.responseText;
	document.getElementById('search_res').innerHTML = response;
}
}

//Updating nofifications
function showNotification() {
	http.open('get', 'notification.php?numba=' + numba + '');
	http.onreadystatechange =  findNewEvent;
	http.send(null);
}

function findNewEvent() {
	if(http.readyState == 4){
	var response = http.responseText;
	document.getElementById('notify_me').innerHTML = response;
	searchCall();
}
}