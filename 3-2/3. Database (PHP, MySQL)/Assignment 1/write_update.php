<?php
    require_once("dbconfig.php");

    if(isset($_POST['bno'])) {
		$bNo = $_POST['bno'];
	}

	if(empty($bNo)) {
		$bID = $_POST['bID'];
		$date = date('Y-m-d H:i:s');
	}

    $bID = $_POST['bID'];
    $bPassword = $_POST['bPassword'];
    $bTitle = $_POST['bTitle'];
    $bContent = $_POST['bContent'];

    $date = date('Y-m-d H:i:s');

    //글 수정
    if(isset($bNo)) {
        //수정 할 글의 비밀번호가 입력된 비밀번호와 맞는지 체크
        $sql = "select count(b_password) as cnt from board_free where b_password='$bPassword' and b_no = '$bNo'";
        $result = $db->query($sql);
        $row = $result->fetch_assoc();
        
        //비밀번호가 맞다면 업데이트 쿼리 작성
        if($row['cnt']) {
            $sql = "update board_free set b_title='$bTitle', b_content='$bContent' where b_no = '$bNo'";
            $msgState = '수정';
        //틀리다면 메시지 출력 후 이전화면으로
        } else {
            $msg = '비밀번호가 맞지 않습니다.';
        ?>
            <script>
                alert("<?php echo $msg?>");
                history.back();
            </script>
        <?php
            exit;
        }
        
    //글 등록
    } else {
	    $upload_image = basename($_FILES['bImage']['name']); // 파일명
	    move_uploaded_file($_FILES['bImage']['tmp_name'], $upload_image);

        $sql = "insert into board_free (b_no, b_title, b_content, b_date, b_hit, b_id, b_password, b_image) 
                values(null, '$bTitle', '$bContent', '$date', 0, '$bID', '$bPassword','$upload_image')";
        $msgState = '등록';
    }

    //메시지가 없다면 (오류가 없다면)
    if(empty($msg)) {
        $result = $db->query($sql);
        
        //쿼리가 정상 실행 됐다면,
        if($result) {
            $msg = '정상적으로 글이 ' . $msgState . '되었습니다.';
            if(empty($bNo)) {
                $bNo = $db->insert_id;
            }
            $replaceURL = './view.php?bno=' . $bNo;
        } else {
            $msg = '글을 ' . $msgState . '하지 못했습니다.';
    ?>
            <script>
                alert("<?php echo $msg?>");
                history.back();
            </script>
    <?php
            exit;
        }
    }
    ?>
<script>
	alert("<?php echo $msg?>");
	location.replace("<?php echo $replaceURL?>");
</script>