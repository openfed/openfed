<div class="newsletter">
	<?php print render($title_prefix); ?>
	<?php if ($block->subject): ?>
	<h2 class="big-title"<?php print $title_attributes; ?>><?php print $block->subject ?></h2>
	<?php endif;?>
	<?php print render($title_suffix); ?>
	
	<?php print $content ?>
</div>