<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["email"]))
        {
            apologize("You must provide your email.");
        }
        
        // check that the user inputed a valid email address
        $check = preg_match("/^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4})$/", $_POST["email"]);
        
        if ($check == false)
        {
            apologize("You must enter a valid email");
        }
        
        // query the user DB for that email
        $rows = query("SELECT * FROM users WHERE email = ?", $_POST["email"]);
        
        // check that the email is in the DB
        if ($rows == false)
        {
            apologize("There is no user with that email on record");
        }

        // get the encrypted password
        $old_pw = $rows[0]["email"];
        
        // create a new password by generating a random number, encrypting it, then splicing the first 9 characters
        $new_pw = substr(crypt(rand(99,99999)), 0, 8);
        
        // update the user password in the DB
        $change = query("UPDATE users SET hash = ? WHERE email = ?", crypt($new_pw), $_POST["email"]);
        
        // email the user their new pw - mail("to", "subject", "body", "headers")
        mail($_POST["email"], "Requested password change", "Your password has been changed to .$new_pw", "From: admin@CS50finance.com");        

        // redirect to portfolio
        redirect("/");     
    }   
    
    else
    {           
        // else render form
        render("forgot_form.php", ["title" => "Forgot Password"]);
    }
    
    
?>
