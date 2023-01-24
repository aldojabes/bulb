<?php


if(isOn()){
    print "on";
}else{
    print "off";
}

function isOn(){
    $string = file_get_contents("bool.txt");
    if($string == "1"){
        return true;
    }
    return false;
}