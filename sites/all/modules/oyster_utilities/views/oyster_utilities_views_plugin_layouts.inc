<?php

/**
 * @file
 */

/**
 * Style plugin.
 */
class oyster_utilities_views_plugin_layouts extends views_plugin_style {

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['oyster_views'] = array('default' => ''); // Declare style settings so they can be exported properly.
    return $options;
  }

  /**
   * Render the given style.
   */
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['oyster_views'] = array(
    	'#type' => 'fieldset',
    	'#title' => t('Oyster'),
    );
    $form['oyster_views']['optionset'] = array(
  		'#title' => t('Template'),
  		'#description' => t('Select a template for this view.'),
  		'#type' => 'radios',
  		'#options' => array(
  			'grid1' => t('Portfolio - Grid 1'),
  			'grid2' => t('Portfolio - Grid 2'),
  			'masonry' => t('Portfolio - Masonry'),
  			'1col' => t('Portfolio - 1 Column'),
  			'2col' => t('Portfolio - 2 Columns'),
  			'3col' => t('Portfolio - 3 Columns'),
  			'4col' => t('Portfolio - 4 Columns'),
  			'blog-full' => t('Blog - Masonry'),
  			'blog-standard' => t('Blog - Standard'),
  			'horizontal-striped' => t('Horizontal Striped'),
  			'vertical-striped' => t('Vertical Striped'),
  			'filter' => t('Isotope Filter Block'),
  			'cloud' => t('Tag Cloud')
  		),
  		'#default_value' => $this->options['oyster_views']['optionset'],
    );

  }
}
