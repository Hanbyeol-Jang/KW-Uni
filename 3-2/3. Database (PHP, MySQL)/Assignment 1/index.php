<?php
 require_once("dbconfig.php");
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" >
        <title>자유게시판</title>
        <link rel="stylesheet" href="./css/normalize.css" />
        <link rel="stylesheet" href="./css/board.css" />    
    </head>
    <body>
        <article class="boardArticle">
            <h3>자유게시판</h3>
            <div id = "boardList">
                <table>
                    <caption class = "readHide">자유게시판</caption>
                    <thead>
                        <tr>
                            <th scope = "col" class = "no">번호</th>
                            <th scope = "col" class = "title">제목</th>
                            <th scope = "col" class = "author">작성자</th>
                            <th scope = "col" class = "date">작성일</th>
                            <th scope = "col" class = "hit">조회</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php
                            $sql = "select * from board_free order by b_no desc";
                            $result = $db->query($sql);
                            while($row = $result->fetch_assoc())
                            {
                                $datetime = explode(' ', $row['b_date']);
                                $date = $datetime[0];
                                $time = $datetime[1];
                                if($date == Date('Y-m-d'))
                                    $row['b_date'] = $time;
                                else
                                    $row['b_date'] = $date;
                        ?>
                        <tr>
                            <td class = "no"><?php echo $row['b_no']?></td>
                            <td class = "title">
                                <a href= "./view.php?bno=<?php echo $row['b_no']?>"><?php echo $row['b_title']?></a>
                            </td>
                            <td class = "author"><?php echo $row['b_id']?></td>
                            <td class = "date"><?php echo $row['b_date']?></td>
                            <td class = "hit"><?php echo $row['b_hit']?></td>
                        </tr>
                            <?php
                            }
                            ?>
                    </tbody>
                </table>
                <div class="btnSet">
                    <a href="./write.php" class="btnWrite btn">글쓰기</a>
                </div>
            </div>
        </article>
    </body>
</html>