<!DOCTYPE html>
<html>
<head>
<title>Alarm Lister - Admin page</title>
<link rel="stylesheet" type="text/css" href="sitefiles/style.css" >
<script src="sitefiles/mod_ajax.js"></script>
<script src="sitefiles/jquery171.js"></script>
</head>
<body>
<?php
include_once('config.php');
$session_id = $_POST['session'];
$query = $_POST['sql_sentence'];
if ($session_id = SID) {
	$link = mysql_connect($db_host, $db_user, $db_pass);
	$db_selected = mysql_select_db($db_name, $link);
	$result = mysql_query(trim($query));
	if ($result) echo 'Press Back in browser, query was successfully executed';
}
?>
</body>
</html>