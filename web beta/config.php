<?php
//DB config
$db_host = 'localhost';
$db_pass = '';
$db_user = 'root';
$db_name = 'project';
$db_table_name = 'mobi';
//Site variables
$GLOB_mainpage = $_SERVER['SERVER_NAME'];
$GLOB_telephone = '89001234567';

//User class
Class Base {
	function killFZero($in_str) {
		if (substr($in_str, 0, 1) == '0') {
			return (substr($in_str, 1, (strlen($in_str) - 1)));
		} else {
			return $in_str;
		}
	}
	function dateTransform($in_date) {
		if (strlen($in_date) != 19) {
			echo $in_date;
		} else {
			$arr_month['01'] = 'January';
			$arr_month['02'] = 'February';
			$arr_month['03'] = 'March';
			$arr_month['04'] = 'April';
			$arr_month['05'] = 'May';
			$arr_month['06'] = 'June';
			$arr_month['07'] = 'July';
			$arr_month['08'] = 'August';
			$arr_month['09'] = 'September';
			$arr_month['10'] = 'October';
			$arr_month['11'] = 'November';
			$arr_month['12'] = 'December';

			$year = substr($in_date, 0, 4);
			$month = substr($in_date, 5, 2);
			$day = substr($in_date, 8, 2);
			
			$hours = substr($in_date, 11, 2);
			$minutes = substr($in_date, 14 ,2);
			$seconds = substr($in_date, 17, 2);
			
			return $hours.':'.$minutes.', '.Base::killFZero("$day").' '.$arr_month["$month"].' '.$year; 
		}
	}
}
?>