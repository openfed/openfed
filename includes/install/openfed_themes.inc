<?php

$enable = array(
  'theme_default' => 'nerra',
  'admin_theme' => 'cms_theme',
);
theme_enable($enable);

foreach ($enable as $var => $theme) {
  if (!is_numeric($var)) {
    variable_set($var, $theme);
  }
}
// Disable the default Bartik theme
theme_disable(array('bartik'));

variable_set('node_admin_theme', '1');
variable_set('admin_theme_admin_theme_batch', '1');