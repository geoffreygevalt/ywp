<?php
/*
 * Prefix your custom functions with oyster_sub. For example:
 * oyster_sub_form_alter(&$form, &$form_state, $form_id) { ... }
 */

/**
 * Modify theme_field()
 */
function oyster_sub_field($variables) {
  $output = '';
  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label"' . $variables['title_attributes'] . '>' . $variables['label'] . ':&nbsp;</div>';
  }
  switch ($variables['element']['#field_name']) {
	  case 'field_tags':
	    foreach ($variables['items'] as $delta => $item) {
	      $rendered_tags[] = drupal_render($item);
	    }
	    $output .= implode(', ', $rendered_tags);
	  break;
	  case 'field_portfolio_category':
	  case 'field_category':
	  case 'field_article_category':
	    foreach ($variables['items'] as $delta => $item) {
	      $rendered_tags[] = drupal_render($item);
	    }
	    $output .= implode(', ', $rendered_tags);
	  break;  
	  case 'field_portfolio_skills':	    
	    foreach ($variables['items'] as $delta => $item) {
	       $output .= '<span class="preview_skills">' . drupal_render($item) . '</span>';
	    }
	  break;
	  case 'field_image':
	    if ($variables['element']['#bundle'] =='article') {
		    foreach ($variables['items'] as $delta => $item) {
		       $output .= '<div class="item">' . drupal_render($item) . '</div>';
		    }
	    }
	  break;
	  case 'field_image':
	    if ($variables['element']['#bundle'] =='portfolio') {
		    foreach ($variables['items'] as $delta => $item) {
		       $output .=  drupal_render($item);
		    }
	    }
	  break;
	   case 'field_media_embed':
	   case 'field_oyster_page_video':
	     foreach ($variables['items'] as $delta => $item) {
		     $output .=  drupal_render($item);
	     }
	  break;
	  default:
	    // Render the items.
		  $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
		  foreach ($variables['items'] as $delta => $item) {
		    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
		    $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
		  }
		  $output .= '</div>';
		
		  // Render the top-level DIV.
		  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';
	  break;
  }
   
  return $output;
}


