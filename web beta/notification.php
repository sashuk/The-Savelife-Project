<?php
include_once('config.php');
$numba = $_GET['numba'];
$session_id = $_POST['session'];
$link = mysql_connect($db_host, $db_user, $db_pass);
$db_selected = mysql_select_db($db_name, $link);
$query = 'SELECT * FROM '.$db_table_name;
$result = mysql_query($query);
$number_of_requests = mysql_num_rows($result);
if ($number_of_requests > $numba) {
	echo '<div class="notification" onclick="terminateInternals(\'notify_me\');return false;"><b>New calls ('.($number_of_requests - $numba).')</b></div>';
}
mysql_close($link);
?>