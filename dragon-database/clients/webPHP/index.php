<!DOCTYPE html>
<html>
<head>
    <title>Dragon DB</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="css/app.css">
</head>
<body>    
    <div class="menu">
        <?php include 'views/view.menu.html'; ?>
    </div>
   
    <div class="contentPage">               
        <?php
        if (isset($_GET['page'])) {
                switch ($_GET['page']) {
                    case 'home':
                    {
                        include 'views/view.home.html';
                        break;
                    }
                }
            } else {
                //home
                include 'views/view.home.html';
            }
        ?>
    </div>
    
</body>
</html>
