<?php

if ($argc == 4) {
	$amount = $argv[1];
	$min = $argv[2];
	$max = $argv[3];
}
else if ($argc == 2) {
	$amount = $argv[1];
	$min = -2147483648;
	$max = 2147483647;
}
else {
	echo "wrong amount of arguments\n";
	return ;
}

// echo rand($min, $max);
$arr = array();
while (count($arr) < $amount) {
	$tmp = mt_rand($min, $max);
	if (!in_array($tmp, $arr)) {
		$arr[] = $tmp;
	}
}
shuffle($arr);

foreach ($arr as $value) {
	echo "$value ";
}

