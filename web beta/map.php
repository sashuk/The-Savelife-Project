<!DOCTYPE html>
<html>
<head>
<title>Show map</title>
<link rel="stylesheet" type="text/css" href="sitefiles/style.css" >
<script src="sitefiles/mod_ajax.js"></script>
<script>
var zoom_value = 15;
function zoomin() {
	zoom_value = zoom_value + 1;
	zoom_x = document.getElementById('coorx').innerHTML;
	zoom_y = document.getElementById('coory').innerHTML;
	document.getElementById('des_image').src = 'http://maps.googleapis.com/maps/api/staticmap?center=' + zoom_x + ',' + zoom_y + '&zoom=' + zoom_value + '&size=500x500&sensor=true';
}

function zoomout() {
	zoom_value = zoom_value - 1;
	zoom_x = document.getElementById('coorx').innerHTML;
	zoom_y = document.getElementById('coory').innerHTML;
	document.getElementById('des_image').src = 'http://maps.googleapis.com/maps/api/staticmap?center=' + zoom_x + ',' + zoom_y + '&zoom=' + zoom_value + '&size=500x500&sensor=true';
}
</script>
</head>
<body align="center">
<?php
include_once('config.php');
$lat = $_GET['lat'];
$lgt = $_GET['lgt'];
$date = $_GET['date'];
$device_id = $_GET['device_id'];
if (($lat == '') or ($lgt == '')) echo '<h2>Sorry, there are some troubles with handling request.</h2><br/><br/>';
$action=$_POST['action'];
?>
<table border="0" width="810"><tr>
	<td class="map_td" width="510px">
	<div style="position:relative; height: 500px; width:500px;">
		<img id="des_image" class="shadowbox" src="http://maps.googleapis.com/maps/api/staticmap?center=<?php echo $lat.','.$lgt; ?>&zoom=15&size=500x500&sensor=true"><br/>
		<embed src="circle.svg" type="image/svg+xml" width="10" height="10" style="position:absolute; left: 255px; top: 255px">
	</div>
	</td>
	<td class="map_td" width="300" align="left">
		<div class="info_div" height="500">
			<p>ID of the device (IMEI): <b><?php echo $device_id; ?></b></p>
			<p>Call was accepted: <b><?php echo Base::dateTransform($date); ?></b></p>
			<p>Latitude: <b><span id="coorx"><?php echo $lat; ?></span></b><br/> Longitude: <b><span id="coory"><?php echo $lgt; ?></span></b></p>
			<?php
			$url = "http://maps.googleapis.com/maps/api/geocode/json?latlng=$lat,$lgt&sensor=false";
			$curl = curl_init();
			curl_setopt($curl, CURLOPT_URL, $url);
			curl_setopt($curl, CURLOPT_HEADER, false);
			curl_setopt($curl, CURLOPT_FOLLOWLOCATION, true);
			curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
			curl_setopt($curl, CURLOPT_ENCODING, "");
			$curlData = curl_exec($curl);
			curl_close($curl);
			$address = json_decode($curlData, true);
				echo '<p>';
				$show_var = true;
				if ($address["results"]["0"]["address_components"]["0"]["long_name"] != '') {
					echo $address["results"]["0"]["address_components"]["0"]["long_name"].'<br/>';
					echo $address["results"]["0"]["address_components"]["1"]["long_name"].'<br/>';
					echo $address["results"]["0"]["address_components"]["2"]["long_name"].'<br/>';
					echo $address["results"]["0"]["address_components"]["4"]["long_name"].'<br/>';
					echo $address["results"]["0"]["address_components"]["5"]["long_name"].'<br/>';
				} else {
					echo 'Sorry, the wrong data was transmitted to the services';
					$show_var = false;
				}
				echo '</p>';
			if ($show_var) {
				echo '<a href="#" onclick="zoomin();return false;">Zoom in</a>&nbsp;&nbsp;&nbsp;&nbsp;<a href="#" onclick="zoomout();return false;">Zoom out</a><br/><br/><a href="#" onclick="window.print();return false;">Print the page</a><br/><br/>';
			}
			?>
			<a href="<?php echo $GLOB_mainpage; ?>">Back to the main page</a>
			<br/><br/>
		</div>
	</td>
</tr></table>
	


	
</body>
</html>