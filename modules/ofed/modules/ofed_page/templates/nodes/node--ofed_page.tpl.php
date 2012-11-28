<div id="node-<?php print $node->nid; ?>" class="content <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php echo render($content['field_ofed_page_content']); ?>"
  <?php if(!empty($node->field_ofed_page_docs)) : ?>
    <?php echo render($content['field_ofed_page_docs']); ?>
  <?php endif; ?>
</div>
