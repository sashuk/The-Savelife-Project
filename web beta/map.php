<!DOCTYPE html>
<html>
<head>
<title>Show map</title>
<link rel="stylesheet" type="text/css" href="sitefiles/style.css" >
<script src="sitefiles/mod_ajax.js"></script>
</head>
<body>
<div align="center" class="printing">
<?php
$lat=$_GET['lat'];
$lgt=$_GET['lgt'];
$action=$_POST['action'];
echo 'Latitude: '.$lat.'  ,  Longitude: '.$lgt.'     <br/><form><input type="button" value=" Print this page " onclick="window.print();return false;" /></form><br/>'; 
echo '<img src="http://maps.googleapis.com/maps/api/staticmap?center='.$lat.','.$lgt.'&zoom=11&size=500x500&sensor=true"><br/>';
?>
</div>
</body>
</html>