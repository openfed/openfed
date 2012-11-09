<?php

/**
 * @file
 * Customize the display of a complete webform.
 *
 * This file may be renamed "webform-form-[nid].tpl.php" to target a specific
 * webform on your site. Or you can leave it "webform-form.tpl.php" to affect
 * all webforms on your site.
 *
 * Available variables:
 * - $form: The complete form array.
 * - $nid: The node ID of the Webform.
 *
 * The $form array contains two main pieces:
 * - $form['submitted']: The main content of the user-created form.
 * - $form['details']: Internal information stored by Webform.
 */
?>
<?php
  // If editing or viewing submissions, display the navigation at the top.
  if (isset($form['submission_info']) || isset($form['navigation'])) {
    print drupal_render($form['navigation']);
    print drupal_render($form['submission_info']);
  }
?>    
    <div class="span-4"><?php echo drupal_render( $form['submitted']['name'] ); ?></div>
    <div class="span-4 last"><?php echo drupal_render( $form['submitted']['firstname'] ); ?></div>
    <div class="span-4"><?php echo drupal_render( $form['submitted']['email'] ); ?></div>
    <div class="span-4 last"><?php echo drupal_render( $form['submitted']['society'] ); ?></div>
    <div class="clear clearfix"><?php echo drupal_render( $form['submitted']['message'] );?></div>
    
    <div class="clear clearfix">
<!--    <button type="submit" value="envoyer" class="contact-submit"/>Envoyer</button>-->
    </div>

<?php
  

  // Print out the main part of the form.
  // Feel free to break this up and move the pieces within the array.
  print drupal_render($form['submitted']);

  // Always print out the entire $form. This renders the remaining pieces of the
  // form that haven't yet been rendered above.
  print drupal_render_children($form);

  // Print out the navigation again at the bottom.
  if (isset($form['submission_info']) || isset($form['navigation'])) {
    unset($form['navigation']['#printed']);
    print drupal_render($form['navigation']);
  }
