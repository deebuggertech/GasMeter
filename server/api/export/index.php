<?php

require 'PHP_XLSXWriter/xlsxwriter.class.php';
require '../config.php';

$filename = "GasMeter-Data.xlsx";
header('Content-disposition: attachment; filename="'.XLSXWriter::sanitize_filename($filename).'"');
header("Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
header('Content-Transfer-Encoding: binary');
header('Cache-Control: must-revalidate');
header('Pragma: public');


$json_data = json_decode(file_get_contents('../data/days.json'), true);

$writer = new XLSXWriter();
$writer->setAuthor($device); 

$header = array(
	"Date"=>"string",
	"Consumption (".$counter_unit.")"=>"integer",
	"Consumption (".$target_unit.")"=>"integer");


$writer->writeSheetHeader('Consumption', $header, $col_options = ['widths'=>[14,20,20,10,24,10], 'font-style'=>'bold', 'halign'=>'center', 'fill' => '#D3D3D3'] );


$counter = 2;
foreach($json_data as $day => $value){
	$writer->writeSheetRow('Consumption', [$day, $value['consumption'], $value['consumption']*$target_unit_factor]);
	$counter++;
}


$writer->writeToStdOut();

exit(0);

?>
