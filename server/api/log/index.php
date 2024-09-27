<?php

if($_GET['token'] == '929ca1f2-efb9-4ed1-9656-1a15ea731ee6') {

	$post_data = json_decode(file_get_contents('php://input'), true);
	file_put_contents("../data/log.txt", $post_data['esp_time'].'  -->  '.$post_data['message'].PHP_EOL, FILE_APPEND);

	http_response_code(200);
	die();	
	
} else{

	header("Content-Type: text/plain; charset=utf-8");
	echo file_get_contents('../data/log.txt');
	die();
	
}


?> 
