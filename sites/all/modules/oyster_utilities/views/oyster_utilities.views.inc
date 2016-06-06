<?php

/**
 * Implements hook_views_data_alter()
 */
function oyster_utilities_views_data_alter(&$data) {
  
  $data['node']['term_node_tid'] = array(
    'title' => t('Taxonomy terms on node'),
    'help' => t('Relate nodes to taxonomy terms, specifying which vocabulary or vocabularies to use. This relationship will cause duplicated records if there are multiple terms.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship_node_term_data',
      'label' => t('term'),
      'base' => 'taxonomy_term_data',
    ),
	  'field' => array(
      'title' => t('All taxonomy terms'),
      'help' => t('Display all taxonomy terms associated with a node from specified vocabularies.'),
      'handler' => 'oyster_utilities_handler_field_term_node_tid',
      'no group by' => TRUE,
    ),
  );
}

/**
 * Implements template_preprocess_views_view().
 */
function oyster_utilities_preprocess_views_view(&$vars) {
  $view = $vars['view'];
 
  if ($view->style_plugin->plugin_name == 'oyster_views') {
    // Assign views plugin layout option to $vars['layout']
	  $vars['layout'] = $view->style_plugin->options['oyster_views']['optionset'];	 	  
	  // Add css/js for layouts that need it.
	  switch ($view->style_plugin->options['oyster_views']['optionset']) {
		  case 'grid1':
			  drupal_add_css(drupal_get_path('module', 'oyster_utilities') . '/oyster_utilities.css');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities')  . '/js/jquery.isotope.js');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities') . '/js/portfolio_grid1.js');
		  break;
		  case 'grid2':
			  drupal_add_css(drupal_get_path('module', 'oyster_utilities') . '/oyster_utilities.css');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities') . '/js/portfolio_grid2.js');
		  break;
		  case 'masonry':
			  drupal_add_css(drupal_get_path('module', 'oyster_utilities') . '/oyster_utilities.css');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities')  . '/js/jquery.isotope.js');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities') . '/js/portfolio_masonry.js');
		  break;
		  case '1col':
			  drupal_add_css(drupal_get_path('module', 'oyster_utilities') . '/oyster_utilities.css');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities')  . '/js/jquery.isotope.js');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities') . '/js/portfolio_col1.js');
		  break;
		  case '2col':
			  drupal_add_css(drupal_get_path('module', 'oyster_utilities') . '/oyster_utilities.css');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities')  . '/js/jquery.isotope.js');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities') . '/js/portfolio_col2.js');
		  break;
		  case '3col':
			  drupal_add_css(drupal_get_path('module', 'oyster_utilities') . '/oyster_utilities.css');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities')  . '/js/jquery.isotope.js');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities') . '/js/portfolio_col3.js');
		  break;
      case '4col':
			  drupal_add_css(drupal_get_path('module', 'oyster_utilities') . '/oyster_utilities.css');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities')  . '/js/jquery.isotope.js');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities') . '/js/portfolio_col4.js');
		  break;
		  case 'blog-full':
			  drupal_add_css(drupal_get_path('module', 'oyster_utilities') . '/oyster_utilities.css');
			  drupal_add_js(drupal_get_path('module', 'oyster_utilities') . '/js/blog_masonry.js');
		  break;



	  }
  }  

}