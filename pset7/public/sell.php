<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["stock"]))
        {
            apologize("You must provide a stock symbol.");
        }
        
        // query Yahoo for the stock's CSV file
        $stock = lookup($_POST["stock"]);
        
        // check if the stock doesn't exist
        if ($stock === false)
        {
            apologize("Entered stock symbol was invalid.");
        }
        
        else
        {                
            // query database for the user-stock key
            $rows = query("SELECT * FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], strtoupper($_POST["stock"]));
                 
            // if that user-stock key doesn't exist then run an error
            if ($rows === false)
            {
                apologize("You do not have any stocks in that company.");
            }
            
            // store the amount of shares
            $shares = $rows[0]["shares"];
            
            // calculate the worth of selling all the shares
            $worth = $stock["price"] * $shares;
                       
            // delete the user stocks from the stocks DB
            $sold = query("DELETE FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], strtoupper($_POST["stock"]));
             
            if ($sold === false)
            {
                apologize("Error: share selling.");
            }
             
            // COME BACK TO!!!!
            $update = query("UPDATE users SET cash = cash + ? WHERE id = ?", $_SESSION["id"], $worth);
             
            if ($update === false)
            {
                apologize("Error: share selling.");
            }           
                
            // log the history
            $history = query("INSERT INTO history (id, type, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?, Now())", $_SESSION["id"], "sold", strtoupper($stock["symbol"]), $shares, $stock["price"]);
 
            //$history = query("INSERT INTO history3 (id, type, symbol) VALUES (?, ?, ?)", $_SESSION["id"], "sold", strtoupper($stock["symbol"]));
                                   
            if ($history === false)
            {
                //apologize("history logging error");
            }


            //redirect to the homepage
            redirect("/");
    
        }
    }    
    
    // if the form wasn't submitted   
    else
    {
        // fill the array of user shares
        $rows = query("SELECT symbol FROM stocks WHERE id = ?", $_SESSION["id"]);
        render("sell_form.php", ["title" => "Buy", "symbols" => $rows]);
    }
?>

