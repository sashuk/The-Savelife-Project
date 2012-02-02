<!DOCTYPE html>
<?php
include_once('config.php');
?>
<html>
<head>
<title>Alarm Lister</title>
<link rel="stylesheet" type="text/css" href="sitefiles/style.css" >
<script src="sitefiles/mod_ajax.js"></script>
<script src="sitefiles/jquery171.js"></script>
<script>
function showtab1() {
	$('#searchpanel').toggle('slow');
}
function showtab2() {
	$('#login_form').toggle('slow');
}
function showresults() {
	searchCall();
}
function terminateInternals(ord_string) {
	var temp_str = '#' + ord_string;
	$(temp_str).hide('slow');
}

searchCall('regular');

function showShortInfo(inf_string) {
}
</script>
</head>
<body>
<table border="0" cellspacing="0" cellpadding="0" width="900" align="center"><tr><td>
<div align="left"><h2>Emergency Signal Trapper</h2></div>
	<a class="false_link" id="searchpaneltrigger" onclick="showtab1();">Show search parameters</a>
	<div id="searchpanel" style="display:none">
	<form id="search_form" class="form_block">
		<table align="center">
			<tr><td>Device id</td><td><input type="text" id="search_id_device" onKeyUp="showresults();" value=""></td><td><h5></h5></td></tr>
			<tr><td>Date</td><td><input type="text" id="search_date" value="" onKeyUp="showresults();"></td><td class="like_h5">*<?php echo date('Y-d-m');?></td></tr>
			<tr><td>Telephone</td><td><input type="text" id="search_telephone" value="" onKeyUp="showresults();"></td><td class="like_h5">*<?php echo $GLOB_telephone;?></td></tr>
			<tr><td colspan="3" align="center"><h5>*search will be performed automatically</h5></td></tr>
		</table>
	</form>
	</div>
	<?php
	$link = mysql_connect($db_host, $db_user, $db_pass);
	$db_selected = mysql_select_db($db_name, $link);
	$sql = 'SELECT * FROM '.$db_table_name; 
	$result = mysql_query($sql);
	$row = array();
	$i = 0;
	?>
	<div id="search_res">

	</div>
	<a class="false_link" id="show_login_form" onclick="showtab2();">Login form</a>
	<div id="login_form" style="display:none;">
		<form method="POST" action="admin.php">
			<table class="form_block">
			<tr><td>Login </td><td><input type="text" name="login"></td></tr>
			<tr><td>Password </td><td><input type="text" name="password"></td></tr>
			</table>
		<input type="submit" value="Log in">
		</form>
	</div>
</td></tr></table>

	<div id="notify_me" style="position:fixed; top:0; right:0; z-index:9999;">
	</div>
	
</body>
<script>
var numba;
function checkUpdate() {
	numba = document.getElementById('num_of_rows').innerHTML;
	showNotification("' + numba + '");
}

setInterval('checkUpdate()', 4000);
</script>
</html>