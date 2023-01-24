<?php

if($_POST != null){
    if($_POST["state"] == "on"){
        writeOne();
    }else{
        writeZero();
    }
}

//writeOne function

function writeOne(){
    $file = fopen("bool.txt", "w");
    fwrite($file, '1');
    fclose($file);
}

//writeZero function
function writeZero(){
    $file = fopen("bool.txt", "w");
    fwrite($file, '0');
    fclose($file);
}