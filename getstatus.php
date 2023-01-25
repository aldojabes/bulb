<?php

$status = null;

if($_POST != null){
    $status = $_POST["status"];
}

if($status == "on"){
    writeOne();
}elseif($status == "off") {
    writeZero();
}

//writeOne function

function writeOne(){
    $file = fopen("status.txt", "w");
    fwrite($file, '1');
    fclose($file);
}

//writeZero function
function writeZero(){
    $file = fopen("status.txt", "w");
    fwrite($file, '0');
    fclose($file);
}