<?php

/**
 * @file
 * Easy breadcrumb template file.
 */

if ($segments_quantity > 0): ?>
  <div class="easy-breadcrumb">

    <?php
      $html = '';
      for ($i = 0, $s = $segments_quantity - 1; $i < $segments_quantity; ++$i) { 
        $it = $breadcrumb[$i];
        $content = decode_entities($it['content']);
        if (isset($it['url'])) {
          $html .= l($content, $it['url'], array('attributes' => array('class' => $it['class'])));
        } else {
          $class = implode(' ', $it['class']);
          $html .= '<span class="' . $class . '">'  . filter_xss($content) . '</span>';
        }
        if ($i < $s) {
          $html .= '<span class="easy-breadcrumb_segment-separator"> ' . $separator . ' </span>';
        }
      }

      print $html; 
    ?>
    
  </div>
<?php
endif; ?>
