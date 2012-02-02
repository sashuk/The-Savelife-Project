<!DOCTYPE html>
<?php
include_once('config.php');
$lat = $_GET['lat'];
$lgt = $_GET['lgt'];
$date = $_GET['date'];
$device_id = $_GET['device_id'];
if (($lat == '') or ($lgt == '')) echo '<h2>Sorry, there are some troubles with handling request.</h2><br/><br/>';
$action=$_POST['action'];
?>



<html>
<head>
<title>Show map</title>
<link rel="stylesheet" type="text/css" href="sitefiles/style.css" >
<script src="sitefiles/mod_ajax.js"></script>
<script src="http://maps.google.com/maps?file=api&amp;v=2&amp;sensor=false&amp;key=ABQIAAAAKWSsSEKm0Rp1BuDpGiBzZxSEd2Kr5ZAXoOcww5bPIl_SSsedURSo5TW0DzY0Lxwhp66Yqk3hz9xNFQ"></script>
 <script type="text/javascript">
var markers = [
 {'x' : <?php echo $lat; ?>, 'y' : <?php echo $lgt; ?>, 'comment' : 'Recorded placement of call'},
];

function GMapInit() {
 var map = new GMap2(document.getElementById("GMapContainer"));
        map.addControl(new GSmallMapControl());
        map.addControl(new GMapTypeControl());

map.setCenter(new GLatLng(<?php echo $lat; ?>, <?php echo $lgt; ?>), 13); 
for(i in markers) {
     map.addOverlay(createMarker(markers[i]['x'],markers[i]['y'],markers[i]['comment']));
    }
}

function createMarker(x, y, comment) {
 var point = new GLatLng(x, y);
 var marker = new GMarker(point);
 GEvent.addListener(marker, "click", function() {
 marker.openInfoWindowHtml(comment);
 });
 return marker;
}
</script>
</head>
<body align="center" onload="GMapInit()" onunload="GUnload()">
<table border="0" cellspacing="0" cellpadding="0" width="900" align="center"><tr><td>
<table border="0" width="810"><tr>
	<td class="map_td" width="510px">
		<div class="shadowbox" style="width: 500px; height: 500px" id="GMapContainer"></div>
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
				echo '<br/><br/><a href="#" onclick="window.print();return false;">Print the page</a><br/><br/>';
			}
			?>
			<a href="<?php echo $GLOB_mainpage; ?>">Back to the main page</a>
			<br/><br/>
		</div>
	</td>
</tr></table>
</td></tr></table>


	
</body>
</html>