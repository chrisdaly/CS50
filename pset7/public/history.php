<?php

    // configuration
    require("../includes/config.php"); 

    // fill the array of user shares
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    render("history_form.php", ["title" => "History", "symbols" => $rows]);



?>
