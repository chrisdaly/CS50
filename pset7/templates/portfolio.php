<p>
    Welcome back, <strong><?= $username ?>!</strong> Your current deposit is <strong>$<?= number_format($cash, 2) ?></strong>
</p>

<ul class="nav nav-tabs">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>


<table class="table table-striped table-hover">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price Current</th>
        </tr>
    </thead>
    
    <tbody>
        <?php foreach($shares as $share): ?>
            <tr>
                <td><?= $share["symbol"] ?></td>
                <td><?= $share["name"] ?></td>
                <td><?= $share["shares"] ?></td>
                <td><?= number_format($share["price_cur"], 2) ?></td>
            </tr>
        <? endforeach ?>
    </tbody>

    
</table>
