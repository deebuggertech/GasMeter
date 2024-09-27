<?php

if($_GET['token'] == '4QHWYyM') {

	$post_data = json_decode(file_get_contents('php://input'), true);

	$current_data = json_decode(file_get_contents('../data/current.json'), true);
	$hours_data = json_decode(file_get_contents('../data/hours.json'), true);
	$days_data = json_decode(file_get_contents('../data/days.json'), true);

	if($post_data['current']['day'] == $current_data['day']){

		file_put_contents('../data/hours.json', json_encode($post_data['data']));
		$current_data['hour'] = $post_data['current']['hour'];
		$current_data['last_push'] = time();
		file_put_contents('../data/current.json', json_encode($current_data));

	}else{

		if(count($hours_data) != 0){

			$day_consumption = 0;

			foreach ($hours_data as $hour_entry) {
				$day_consumption += $hour_entry['consumption'];
			}

			$days_data[$current_data['day']]['consumption'] = $day_consumption;

			file_put_contents('../data/days.json', json_encode($days_data));

		}

		file_put_contents('../data/hours.json', json_encode($post_data['data']));

		$current_data['day'] = $post_data['current']['day'];
		$current_data['hour'] = $post_data['current']['hour'];
		$current_data['last_push'] = time();
		file_put_contents('../data/current.json', json_encode($current_data));

	}

	http_response_code(200);
	die();
	
}else{
	
	http_response_code(401);
	die();
	
}
?> 
