<table class="table table-striped table-hover">
<thead>
  <tr>
    <th>Date</th>
    <th>Symbol</th>
    <th>Price</th>
    <th>No. of Shares</th>
    <th>Action</th>
  </tr>
</thead>

<tbody>
    <?php foreach($symbols as $symbol): ?>
        <tr>
            <td><?= $symbol['date'] ?></td>
            <td><?= $symbol['symbol'] ?></td>
            <td><?= $symbol['price'] ?></td>
            <td><?= $symbol['shares'] ?></td>
            <td><?= $symbol['type'] ?></td>
        </tr>
    <? endforeach ?>
</tbody>

</table>
