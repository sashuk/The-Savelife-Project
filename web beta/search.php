<?php
$search_id = $_GET['search_id'];
$search_date = $_GET['search_date'];

include_once('config.php');
$s_link = mysql_connect($db_host, $db_user, $db_pass);
$s_db_selected = mysql_select_db($db_name, $s_link);
if (($search_id != '') and ($search_date != '')) {
	$s_sql = 'SELECT * FROM '.$db_table_name.' WHERE `id_device`="'.$search_id.'%" and ((`date` < "'.$search_date.' 23:59:59") AND (`date` > "'.$search_date.' 00:00:00"))';
} elseif (($search_id != '') and ($search_date == '')) {
	$s_sql = 'SELECT * FROM '.$db_table_name.' WHERE `id_device` like "'.$search_id.'%"';
} elseif (($search_id == '') and ($search_date != '')) {
	$s_sql = 'SELECT * FROM '.$db_table_name.' WHERE ((`date` < "'.$search_date.' 23:59:59") AND (date > "'.$search_date.' 00:00:00"))';
} else {
	$s_sql = 'SELECT * FROM '.$db_table_name.'';
}
$s_result = mysql_query($s_sql);
$s_row = array();
$i = 0;
?>
<div id="search_res">
<table border="0" width="900">
<tr><td colspan="6"><hr></td></tr>
<tr class="table_headers">
<td>Device ID</td>
<td>Latitude</td>
<td>Longitude</td>
<td>Signal type</td>
<td>Time and date</td>
<td>Map</td>
</tr>
<?php
if ($s_result) {
	while($s_res = mysql_fetch_array($s_result, MYSQL_BOTH)) { 
		if(!isset($s_res['id_device'])) continue;
			echo '<tr>'; 
			$s_row[$i]['id_device'] = $s_res['id_device'];
				echo '<td>'.$s_row[$i]['id_device'].'</td>';
			$s_row[$i]['x'] = $s_res['x']; 
				echo '<td>'.$s_row[$i]['x'].'</td>';
			$s_row[$i]['y'] = $s_res['y']; 
				echo '<td>'.$s_row[$i]['y'].'</td>';
			$s_row[$i]['type'] = $s_res['type'];
				echo '<td>'.$s_row[$i]['type'].'</td>';		
			$s_row[$i]['date'] = $s_res['date']; 
				echo '<td>'.Base::dateTransform($s_row[$i]['date']).'</td>';
			echo '<td><a target="_blank" href="map.php?lat='.$s_row[$i]['x'].'&lgt='.$s_row[$i]['y'].'&action=show&date='.$s_row[$i]['date'].'&device_id='.$row[$i]['id_device'].'">Show Map</a></td>';	
			echo '</tr>';
			$i++;
	}
}
mysql_close($s_link);
echo '<tr><td colspan="6"><hr></td></tr></table><div class="table_headers"><div class="table_headers">Total: <span id="num_of_rows">'.$i.'</span> results</div></div>';
?>
