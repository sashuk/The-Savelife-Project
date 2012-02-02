<?php
$search_id = $_GET['search_id'];
$search_date = $_GET['search_date'];
$search_telephone = $_GET['search_telephone'];
include_once('config.php');
$s_link = mysql_connect($db_host, $db_user, $db_pass);
$s_db_selected = mysql_select_db($db_name, $s_link);

//Overallnumber of rows
$overall_sql = 'SELECT * FROM '.$db_table_name.'';
$overall_s_result = mysql_query($overall_sql);
$overall_num_of_rows = mysql_num_rows($overall_s_result);
echo '<div id="num_of_rows" style="visibility:hidden;">'.$overall_num_of_rows.'</div>';

$control_num = 0;
$id_add_query = '';
$date_add_query = '';
$telephone_add_query = '';

if ($search_id != '') {
	$id_add_query = '(id_device like "'.$search_id.'%")';
	$control_num = $control_num + 1;
}
if ($search_date != '') {
	$date_add_query = '(date BETWEEN "'.$search_date.' 00:00:00" AND "'.$search_date.' 23:59:59")';
	$control_num = $control_num + 2;
}
if ($search_telephone != '') {
	$telephone_add_query = '(telephone like "'.$search_telephone.'%")';
	$control_num = $control_num + 4;
}
if (($control_num == 1) OR ($control_num == 2) OR ($control_num == 4)) {
	$main_query = 'SELECT * FROM '.$db_table_name.' WHERE '.$id_add_query.$date_add_query.$telephone_add_query.' ORDER BY date DESC';
}

if 	($control_num > 0) {
	switch ($control_num) {
		case 3:
			$main_query = 'SELECT * FROM '.$db_table_name.' WHERE ('.$id_add_query.' AND '.$date_add_query.') ORDER BY date DESC';
			break;
		case 6:
			$main_query = 'SELECT * FROM '.$db_table_name.' WHERE ('.$telephone_add_query.' AND '.$date_add_query.') ORDER BY date DESC';
			break;
		case 5:
			$main_query = 'SELECT * FROM '.$db_table_name.' WHERE ('.$id_add_query.' AND '.$telephone_add_query.') ORDER BY date DESC';
			break;
		case 7:
			$main_query = 'SELECT * FROM '.$db_table_name.' WHERE ('.$id_add_query.' AND '.$date_add_query.' AND '.$telephone_add_query.') ORDER BY date DESC';
			break;
	}
} else {
	$main_query = 'SELECT * FROM '.$db_table_name.' ORDER BY date DESC';
}

/*
if (($search_id != '') and ($search_date != '')) {
	$s_sql = 'SELECT * FROM `'.$db_table_name.'` WHERE ((`id_device` like "'.$search_id.'%") AND (date BETWEEN "'.$search_date.' 00:00:00" AND "'.$search_date.' 23:59:59")) ORDER BY date DESC';
} elseif (($search_id != '') and ($search_date == '')) {
	$s_sql = 'SELECT * FROM `'.$db_table_name.'` WHERE `id_device` like "'.$search_id.'%" ORDER BY date DESC';
} elseif (($search_id == '') and ($search_date != '')) {
	echo '<h1>GOTHERE</h1>';
	$s_sql = 'SELECT * FROM `'.$db_table_name.'` WHERE date BETWEEN "'.$search_date.' 00:00:00" AND "'.$search_date.' 23:59:59" ORDER BY date DESC';
} else {
	$s_sql = 'SELECT * FROM '.$db_table_name.' ORDER BY date DESC';
}
*/

$s_result = mysql_query($main_query);
$s_row = array();
$i = 0;
?>
<div id="search_res">
<table border="0" width="900">
<tr><td colspan="7s"><hr></td></tr>
<tr class="table_headers">
<td>Device ID</td>
<td>Latitude</td>
<td>Longitude</td>
<td>Signal type</td>
<td>Telephone</td>
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
			$s_row[$i]['telephone'] = $s_res['telephone'];
				echo '<td>'.$s_row[$i]['telephone'].'</td>';	
			$s_row[$i]['date'] = $s_res['date']; 
				echo '<td>'.Base::dateTransform($s_row[$i]['date']).'</td>';
			echo '<td><a target="_blank" href="map.php?lat='.$s_row[$i]['x'].'&lgt='.$s_row[$i]['y'].'&action=show&date='.$s_row[$i]['date'].'&device_id='.$s_row[$i]['id_device'].'">Show Map</a></td>';	
			echo '</tr>';
			$i++;
	}
}
mysql_close($s_link);
echo '<tr><td colspan="7"><hr></td></tr></table><div class="table_headers"><div class="table_headers">Total: '.$i.' results</div></div>';
?>
