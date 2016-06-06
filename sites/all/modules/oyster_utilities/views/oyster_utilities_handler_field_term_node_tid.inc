<?php

/**
 * @file
 * Definition of views_handler_field_term_node_tid.
 */

/**
 * Field handler to display all taxonomy terms of a node.
 *
 * @ingroup views_field_handlers
 */
class oyster_utilities_handler_field_term_node_tid extends views_handler_field_term_node_tid {
  
  function option_definition() {
    $options = parent::option_definition();
    $options['convert_spaces'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  /**
   * Option to replace spaces with hyphens.
   */
  function options_form(&$form, &$form_state) {
  
    $form['convert_spaces'] = array(
      '#title' => t('Convert spaces in term names to hyphens'),
      '#description' => t('This allows terms to be used as Isotope filter classes.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['convert_spaces']),
    );
    
    parent::options_form($form, $form_state);
    
  }

  function render_item($count, $item) {
    if ($this->options['convert_spaces'] == 1) {
	    return str_replace(' ', '-', $item['name']);
    }
    else {
      return $item['name'];
    }
  }

}