<?php 
  
  // Declare $base_url global.
  global $base_url;
  
	// Set $share_image variable for passing as argument to oyster_social_share.
	if (isset($content['field_image'])) {
		$share_image = file_create_url($node->field_image['und'][0]['uri']);
	} else{
		$share_image = NULL;
	}
  require_once(drupal_get_path('theme', 'oyster').'/inc/portfolio.inc');
 
  if (!$teaser && isset($node->field_portfolio_layout['und'])) {
    switch ($node->field_portfolio_layout['und'][0]['value']) {
      case 'simple':
        include_once(drupal_get_path('theme', 'oyster').'/layouts/portfolio/portfolio-simple.php');
      break;  
      case 'ribbon':
        include_once(drupal_get_path('theme', 'oyster').'/layouts/portfolio/portfolio-ribbon.php');
      break; 
      case 'full_no_info':
        include_once(drupal_get_path('theme', 'oyster').'/layouts/portfolio/portfolio-without-info.php');
      break;
      case 'full_with_info':
        include_once(drupal_get_path('theme', 'oyster').'/layouts/portfolio/portfolio-with-info.php');
      break;
      default:
        include_once(drupal_get_path('theme', 'oyster').'/layouts/portfolio/portfolio-simple.php');
      break;
    }
  }
  
  else if ($teaser) {
	  include(drupal_get_path('theme', 'oyster').'/layouts/portfolio/portfolio-teaser.php');
  }
  
  else {
	  include_once(drupal_get_path('theme', 'oyster').'/layouts/portfolio/portfolio-simple.php');
  }
?>