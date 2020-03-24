<?php
    $db = new mysqli('localhost', 'root', '55f24811', 'tutorial');

    if($db->connect_error){
        die('오류');
    }

    $db->set_charset('utf-8');
    date_default_timezone_set('Asia/Seoul');
?>