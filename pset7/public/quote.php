<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["stock"]))
        {
            apologize("Please enter a stock symbol.");
        }
        
        // query Yahoo for CSV
        $stock = lookup($_POST["symbol"]);
        
        // check if the lookup was successful
        if ($stock === false)
        {
            apologize("That stock symbol is invalid.");
        }   
        
        else
        {
            // display the stock  on a new page
            render("quote_display.php", ["title" => "Quote", "symbol" => $stock]);
        }
    }
    
    // re-render the quote form
    else
    {
        render("quote_form.php", ["title" => "Quote"]);
    } 
?>



