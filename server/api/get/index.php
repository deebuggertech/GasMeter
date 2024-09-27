<?php

require '../config.php';

$current_data = json_decode(file_get_contents('../data/current.json'), true);
$hours_data = json_decode(file_get_contents('../data/hours.json'), true);
$days_data = json_decode(file_get_contents('../data/days.json'), true);

$result = [];
$result["header"] = [];

$result["header"]["device"] = $device;
$result["header"]["counter_unit"] = $counter_unit;

$result["header"]["target_unit"] = $target_unit;
$result["header"]["target_unit_factor"] = $target_unit_factor;

$result["header"]["backend_version"] = $api_server_version;

$result["header"]["last_push"] = time() - $current_data['last_push'];

$result["hours"] = $hours_data;

$result["days"] = $days_data;

header('Content-Type: application/json; charset=utf-8');
header('Access-Control-Allow-Origin: *');
echo json_encode($result, JSON_PRETTY_PRINT);
die();

?> 
