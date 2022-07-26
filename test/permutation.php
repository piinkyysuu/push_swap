<?php

function permute($str, $l, $r, $len)
{
	if ($l == $r)
	{
		echo "\$PATH/push_swap ";
		for ($index = 0; $index < $len; $index++)
			echo $str[$index]." ";
		echo "\n";
	}
	else {
		for ($i = $l; $i <= $r; $i++) {
			$str = swap($str, $l, $i);
			permute($str, $l + 1, $r, $len);
			$str = swap($str, $l, $i);
		}
	}
}

/** 
 * Swap Characters at position 
 * @param a string value 
 * @param i position 1 
 * @param j position 2 
 * @return swapped string 
 */
function swap($a, $i, $j)
{
	// $temp;
	$charArray = str_split($a);
	$temp = $charArray[$i];
	$charArray[$i] = $charArray[$j];
	$charArray[$j] = $temp;
	return implode($charArray);
}

// Driver Code 
$str = "123";
$n = strlen($str);
permute($str, 0, $n - 1, $n);
