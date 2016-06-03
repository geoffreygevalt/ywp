<?php


/**
 * Implements hook_form_system_theme_settings_alter()
 */
function oyster_form_system_theme_settings_alter(&$form, &$form_state) {

  // Default path for alt logo
  $mobile_logo_path = theme_get_setting('mobile_logo_path');
  if (file_uri_scheme($mobile_logo_path) == 'public') {
    $mobile_logo_path = file_uri_target($mobile_logo_path);
  }
  
  // Main settings wrapper
  $form['options'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'defaults',
    '#weight' => '-10',
  );
  
  // Default Drupal Settings    
  $form['options']['drupal_default_settings'] = array(
		'#type' => 'fieldset',
		'#title' => t('Drupal Core Settings'),
	);
	
	  // "Toggle Display" 
		$form['options']['drupal_default_settings']['theme_settings'] = $form['theme_settings'];
		
		// "Unset default Toggle Display settings" 
		unset($form['theme_settings']);
		
		// "Logo Image Settings" 
		$form['options']['drupal_default_settings']['logo'] = $form['logo'];
		
		// "Unset default Logo Image Settings" 
		unset($form['logo']);
		
		// "Shortcut Icon Settings" 
		$form['options']['drupal_default_settings']['favicon'] = $form['favicon'];   
		
		// "Unset default Shortcut Icon Settings" 
		unset($form['favicon']);
  
  // General
  $form['options']['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
  );
  
    // Sticky Header
    $form['options']['general']['sticky_header'] = array(
      '#type' => 'checkbox',
      '#title' => t('Sticky Header'),
      '#default_value' => theme_get_setting('sticky_header'),
    );
    
    // Header Search
    $form['options']['general']['header_search'] = array(
      '#type' => 'checkbox',
      '#title' => t('Header Search'),
      '#default_value' => theme_get_setting('header_search'),
    );
                          
  // Post Meta
  $form['options']['meta'] = array(
    '#type' => 'fieldset',
    '#title' => t('Post Meta'),
  );
  
    // General
	  $form['options']['meta']['portfolio'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Portfolio'),
	  );
              
      // Meta Date
	    $form['options']['meta']['portfolio']['portfolio_meta_author'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Author'),
	      '#default_value' => theme_get_setting('portfolio_meta_author'),
	    );
               
	    // Meta Date
	    $form['options']['meta']['portfolio']['portfolio_meta_date'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Date'),
	      '#default_value' => theme_get_setting('portfolio_meta_date'),
	    );
	    	    
	    // Meta Comments
	    $form['options']['meta']['portfolio']['portfolio_meta_comments'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Comments'),
	      '#default_value' => theme_get_setting('portfolio_meta_comments'),
	    );
	    
	    // Meta Title
	    $form['options']['meta']['portfolio']['portfolio_meta_title'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Title'),
	      '#default_value' => theme_get_setting('portfolio_meta_title'),
	    );
	            
	    // Meta Share
	    $form['options']['meta']['portfolio']['portfolio_meta_share'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Share'),
	      '#default_value' => theme_get_setting('portfolio_meta_share'),
	    );
	    
	  // General
	  $form['options']['meta']['article'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Article'),
	  );
           
      // Meta Author
	    $form['options']['meta']['article']['article_meta_author'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Author'),
	      '#default_value' => theme_get_setting('article_meta_author'),
	    );     
               
	    // Meta Date
	    $form['options']['meta']['article']['article_meta_date'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Date'),
	      '#default_value' => theme_get_setting('article_meta_date'),
	    );
	    
	    // Meta Comments
	    $form['options']['meta']['article']['article_meta_comments'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Comments'),
	      '#default_value' => theme_get_setting('article_meta_comments'),
	    );
	    
	  	// Meta Title
	    $form['options']['meta']['article']['article_meta_title'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Title'),
	      '#default_value' => theme_get_setting('article_meta_title'),
	    );
	            
	    // Meta Share
	    $form['options']['meta']['article']['article_meta_share'] = array(
	      '#type' => 'checkbox',
	      '#title' => t('Meta Share'),
	      '#default_value' => theme_get_setting('article_meta_share'),
	    );
        
  // CSS
  $form['options']['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS'),
  );
  
    // User CSS
      $form['options']['css']['user_css'] = array(
        '#type' => 'textarea',
        '#title' => t('Add your own CSS'),
        '#default_value' => theme_get_setting('user_css'),
      );     
      
}

?>