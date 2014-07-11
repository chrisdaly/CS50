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
        
        if (empty($_POST["amount"]))
        {
            apologize("You must provide an amount.");
        }     
        
        // check that the user inputed a whole number for shares
        $check = preg_match("/^\d+$/", $_POST["amount"]);
        
        if ($check == false)
        {
            apologize("You must enter a whole number");
        }
        
        // query Yahoo for the stock's CSV file
        $stock = lookup($_POST["stock"]);
        
        // check if the stock doesn't exist
        if ($stock === false)
        {
            apologize("Entered stock symbol was invalid.");
        }
        
        // calculate the cost of buying that amount of stocks
        $total = $stock["price"] * $_POST["amount"];
        
        // check how much cash the user has in his account
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $bank = $rows[0]["cash"];

        // check if the user can afford that amount of stocks
        if ($bank < $total)
        {
            apologize("You do not have sufficient funds for that transaction.");
        }
        
        else
        {    
            // add the shares to the user's stock portfolio - accounting for creating a new row or updating one
            $update_stocks = query("INSERT INTO stocks (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $stock["symbol"], ($_POST["amount"]));
            
            if ($update_stocks === false)
            {
                    apologize("Error while updating stocks.");
            }
            
            // store the amount of shares
            $shares = $_POST["amount"];
            
            // subtract the cost from the user's bank
            $update_cash = query("UPDATE users SET cash = cash - ? WHERE id = ?", $total,  $_SESSION["id"]);

            if ($update_cash === false)
            {
                    apologize("Error while updating your funds.");
            }

            // Log the history
            $history = query("INSERT INTO history(id, type, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?, Now())", $_SESSION["id"], "bought", strtoupper($stock["symbol"]), $_POST["amount"], $stock["price"]);
            
            if ($history === false)
            {
                apologize("history logging error");
            } 
            
            // redirect to the homepage
            redirect("/");
    
        }
    }    
    
    // if the form wasn't submitted   
    else
    {
        // fill the array of user shares
        $rows = query("SELECT symbol FROM stocks WHERE id = ?", $_SESSION["id"]);
        render("buy_form.php", ["title" => "Buy"]);
    }



?>

