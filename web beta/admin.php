<?php
session_start();
?>
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
$login = $_POST['login'];
$password = $_POST['password'];
$login = strip_tags($login);
$password = strip_tags($password);
$verif = false;
if (($login == 'admin') and ($password == 'admin')) {
		$verif = true;
} else {
	echo "Wrong data, go back";
}
if ($verif == true) {
echo '<div><form action="sql.php" method="post">Execute SQL sentence<input type="text" name="sql_sentence"><input type="submit" value="Execute"><input type="hidden" name="session" value="'.SID.'"></form></div>';
}
?>



<div id="sql_execute">




</body>
</html>