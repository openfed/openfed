<?php

/**
 * Views area text custom handler.
 *
 * @ingroup views_area_handlers
 */
class ofed_area_show_results_count extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function render($empty = FALSE) {
    // Initialize.
    $output = '';

    if(isset( $this->view->filter['type'])) {
      foreach($this->view->filter['type']->value as $key => $value) {
        // Get the current view.
        $view = views_get_current_view();
        
        // Set the total of results.
        $count_t = (isset($view->total_rows)) ? $view->total_rows : count($view->result);
        
        // Set the current position.
        if($count_t >= 1){
          $count_x = ($view->query->pager->current_page * $view->query->pager->options['items_per_page']) + 1;
          // Set the number of the displayed results.
          $count_y = $count_x + count($view->result) - 1;
          // Generate output.
          $output .= '<div class="view-show-result-count-container">';
          $output .= sprintf(t('Showing %x%-%y% of %t% result(s)', array(
            '%x%' => $count_x,
            '%y%' => $count_y,
            '%t%' => $count_t,
          )));
          $output .= '</div>';
        }
        else{
          $output .= '<div class="view-show-result-count-container">';
          $output .= '<span class=views-no-results>' . t('No results') . '</span>';
          $output .= '</div>';
        }
        
        
      }
    }
    
    // Return.
    return $output;
  }
}