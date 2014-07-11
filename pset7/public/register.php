<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        
        if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        
        if (empty($_POST["confirmation"]))
        {
            apologize("You must verify your password.");
        }

        if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your passwords must match.");
        }
        
        if (empty($_POST["email"]))
        {
            apologize("Your must provide an email.");
        }
        
        // check that the user inputed a valid email address
        $check = preg_match("/^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4})$/", $_POST["email"]);
        
        if ($check == false)
        {
            apologize("You must enter a valid email");
        }
        
        // check if that email is already associated with a user
        $check_email = query("SELECT * FROM users WHERE email = ?", $_POST["email"]);
        
        //         
        if ($check_email)
        {
            apologize("That email is already registered to a user");
        }
        
        // insert the new user into the user database
        $newuser = query("INSERT INTO users (username, hash, cash, email) VALUES(?, ?, 10000.00, ?)", $_POST["username"], crypt($_POST["password"]), $_POST["email"]);

        // if the transaction was not completed then that user name already exists
        if ($newuser === false)
        {
            apologize("That user already exists");
        }
        
        // otherwise, get the entry's id
        else
        {
            $user_id = query("SELECT LAST_INSERT_ID() AS id");
            $id = $user_id[0]["id"];
        }
        
        // log the user in and store the user's ID in session
        $_SESSION["id"] = $id;

        // redirect to portfolio
        redirect("/");     
    }
        
    else
    {           
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>  
