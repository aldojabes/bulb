<?php

$string = file_get_contents("status.txt");

if($string == "1"){
    print "on";
}else{
    print "off";
}