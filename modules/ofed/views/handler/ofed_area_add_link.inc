<?php

/**
 * Views area text custom handler.
 *
 * @ingroup views_area_handlers
 */
class ofed_area_add_link extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function render($empty = FALSE) {
    $output = '';

    if ( isset( $this->view->filter['type'] ) ) {
      foreach ($this->view->filter['type']->value as $key => $value) {
        if (user_access('create ' . $key . ' content')) {
          $output .= '<div class="lk-add-container">';
            $content_type = node_type_load($key);
            $output .= l( 
                    t("Add !name", array('!name' => $content_type->title_label)), 
                      'node/add/' . str_replace('_', '-', $key), 
                      array(
                        'attributes' => array( 'class' => 'lk-add')
                      ) 
                    );
          $output .= '</div>';
        }
      }
    }
    
    return $output;
  }
}