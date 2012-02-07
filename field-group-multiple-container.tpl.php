<?php
/**
 *
 * - group
 * - items
 *  - delta + field_name + value render_array or null if empty
 */
?>
<div class="field-group-mutliple-container clearfix field-label-inline">

<div class="field-items field-group-multiple-items field-group-multiple-horizontal-items">
<?php foreach($items as $delta => $item): ?>

<div class="field-group-multiple-item <?= $delta % 2 == 1 ? "odd" : "even" ?>">
<?php foreach($item as $field_name => $field_value): ?>

<div class="field-item <?= $field_name ?>">
<?php if(!is_null($field_value)): ?>
   <?= render($field_value); ?>
<?php else: ?>
  <span class="field-is-empty"> </span>
<?php endif; ?>
</div>


<?php endforeach; ?>
</div>



<?php endforeach; ?>

</div>
</div>