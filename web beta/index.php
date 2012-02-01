<!DOCTYPE html>
<!--
####################GOT TO DO###############################
Animated junk - animate any row in the search table
Parse the geospatial data coorrectly
Sort query results by INC, DECR
Make developers page
-->

<html>
<head>
<title>Alarm Lister</title>
<link rel="stylesheet" type="text/css" href="sitefiles/style.css" >
<script src="sitefiles/mod_ajax.js"></script>
<script src="sitefiles/jquery171.js"></script>
<script>
function showtab() {
	$('#searchpanel').show('slow');
}
function showresults() {
	searchCall();
}

</script>
</head>
<body>
<span id="searchpaneltrigger" onclick="showtab();">Show search parameters</span>
<div id="searchpanel" style="display:none">
<form id="search_form" onKeyUp="showresults();">
Device id<input type="text" id="search_id_device" value=""><br/>
Date<input type="text" id="search_date" value=""><br/>
</form>
</div><br/>
<?php
include_once('config.php');
$link = mysql_connect($db_host, $db_user, $db_pass);
$db_selected = mysql_select_db($db_name, $link);
$sql = 'SELECT * FROM '.$db_table_name; 
$result = mysql_query($sql);
$row = array();
$i = 0;
?>
<div id="search_res">
<table border="0">
<tr class="table_headers">
<td>Device ID</td>
<td>Latitude</td>
<td>Longitude</td>
<td>Signal type</td>
<td>Time and date</td>
<td>Map</td>
</tr>
<?php
while($res = mysql_fetch_array($result, MYSQL_BOTH)) { 
    if(!isset($res['id_device'])) continue;
		echo '<tr>'; 
        $row[$i]['id_device'] = $res['id_device'];
			echo '<td>'.$row[$i]['id_device'].'</td>';
        $row[$i]['x'] = $res['x']; 
			echo '<td>'.$row[$i]['x'].'</td>';
        $row[$i]['y'] = $res['y']; 
			echo '<td>'.$row[$i]['y'].'</td>';
        $row[$i]['type'] = $res['type'];
			echo '<td>'.$row[$i]['type'].'</td>';		
 		$row[$i]['date'] = $res['date']; 
       		echo '<td>'.$row[$i]['date'].'</td>';
		echo '<td><a href="map.php?lat='.$row[$i]['x'].'&lgt='.$row[$i]['y'].'&action=show">Show Map</a></td>';	
		echo '</tr>';
        $i++;
} 
mysql_close($link);
echo '</table>Total: '.$i.' results';
?>
</div>
<hr>
</body>
</html>