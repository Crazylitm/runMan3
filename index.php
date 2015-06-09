<?php

//http://litianmin.com/litm/index.php?latitude=30.282325&longitude=120.021781&timestamp=1393496433.804634&id=a
// just for test 
// just just for test
// just for test i12345

>>>>>>> updae README.md & index.php
define('TMP_FILE', "/home/wwwroot/litm/log/tmp.log");
define('SECONDS', 200);//毫秒秒
define('DISTANCE', 50);//米

define('EARTH_RADIUS', 6378.137);//地球半径，假设地球是规则的球体 
define('PI', 3.1415926); 

$micCurTime = microtime();
$micTime    = substr($micCurTime,0,9)*1000;
$secTime    = substr($micCurTime,11,20);
$_GET['timestamp']  = $secTime.$micTime;
/*
echo  $micCurTime;
echo  '\n';
echo  $micTime;
echo  '\n';
echo  $secTime;
echo  '\n';
echo  $_GET['timestamp'];

*/
$brother = array();

if (save_file() ) {

    for ($i = 0 ;$i < 5; $i++) {
        $brother = array_merge($brother,find_pp_records());

        if (empty($brother)) {
            usleep(50000);
        } else {
            break;
        }
    }
}

if (!empty($brother)) {
    foreach ($brother as $b) {
        echo "found:" ."id=". $b['id'] . ":spriteX=".$b['spriteX'] . ":spriteY=" . $b['spriteY'] . ":\n";
    }
} else {
    echo "NULL";
}

function save_file() {
    $line = json_encode($_GET) . "\n";
    return file_put_contents (TMP_FILE,$line,FILE_APPEND | LOCK_EX);
}

function find_pp_records() {
    $content = file_get_contents(TMP_FILE);
    $lines = explode("\n",$content);
    $found = array();

    foreach ($lines as $line) {
        $info = json_decode($line,true);
        if (count($info) > 0) {
            if ($_GET['name'] != $info['name'] 
                && ($info['time_abs'] = abs($_GET['timestamp'] - $info['timestamp'])) <= SECONDS) 
            {
                $info['distance_abs'] = get_distance($_GET['latitude'],$_GET['longitude'],$info['latitude'],
                                        $info['longitude']);

                if ($info['distance_abs'] <= DISTANCE) {
                    $found[] = $info;
                    break;
                }
            }
        }
    }

    return $found;
}

function get_distance($lat1, $lng1, $lat2, $lng2, $len_type = 1, $decimal = 2) {
    $radLat1 = $lat1 * PI / 180.0; 
    $radLat2 = $lat2 * PI / 180.0; 
    $a = $radLat1 - $radLat2; 
    $b = ($lng1 * PI / 180.0) - ($lng2 * PI / 180.0); 
    $s = 2 * asin(sqrt(pow(sin($a/2),2) + cos($radLat1) * cos($radLat2) * pow(sin($b/2),2))); 
    $s = $s * EARTH_RADIUS; 
    $s = round($s * 1000); 
    if ($len_type > 1) { 
        $s /= 1000; 
    } 
    return round($s, $decimal); 
} 
