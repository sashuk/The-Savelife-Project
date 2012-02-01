<!DOCTYPE html>
<html>
<head>
<title>Show map</title>
<link rel="stylesheet" type="text/css" href="sitefiles/style.css" >
<script src="sitefiles/mod_ajax.js"></script>
</head>
<body>
<div align="left" class="printing">
<?php
$lat=$_GET['lat'];
$lgt=$_GET['lgt'];
$action=$_POST['action'];
?>
<p>Latitude: <?php echo $lat; ?>; Longitude: <?php echo $lgt; ?></p>
<a href="#" onclick="window.print();return false;">Print the page</a><br/><br/>
<div style="position: relative; left: 0; top: 0; height: 400px">
	<img src="http://maps.googleapis.com/maps/api/staticmap?center=<?php echo $lat.','.$lgt; ?>&zoom=11&size=500x500&sensor=true"><br/>
	<embed src="circle.svg" type="image/svg+xml" width="20" height="20" style="position: absolute; left: 200px; top: 200px">
</div>
</body>
</html>