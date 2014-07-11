<?php

    // configuration
    require("../includes/config.php"); 

    // query database for user's info
    $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    
    // store user data to pass to template
    $username = $rows[0]["username"];
    $cash = $rows[0]["cash"];

    // query database for user's stocks
    $rows = query("SELECT * FROM stocks WHERE id = ?", $_SESSION["id"]);

    // initialize a stock array
    $shares = [];

    foreach($rows as $row)
    {
        // query Yahoo for the stock's CSV file
        $stock = lookup($row["symbol"]);
        
        if ($stock !== false)
        {
            $shares[] = [
                "symbol"        => $row["symbol"],
                "name"          => $stock["name"],
                "shares"        => $row["shares"],
                "price_cur"     => $stock["price"]
            ];
        }
    }

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "username" => $username, "cash" => $cash, "shares" => $shares]);

?>
