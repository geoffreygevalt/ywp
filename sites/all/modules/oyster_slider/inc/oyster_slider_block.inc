<?php

/**
 * Implements hook_block_info.
 */
function oyster_slider_block_info() {
  $blocks = array();
  $sliders = entity_load('oyster_slider');
  
  if (is_array($sliders)) {
	  foreach ($sliders as $slider) {
		  $blocks[$slider->id]['info'] = t('Oyster Slider: '. $slider->name.'' );
	  }
  }
  return $blocks;
}

/**
 * Implements hook_block_view.
 */
function oyster_slider_block_view($delta = '') {
  $block['content'] = array(
    '#markup' => oyster_slider_block_content($delta),
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'oyster_slider') .'/js/gallery.js',
      ),
    ),
  );

  return $block;
}
 
/**
 * Callback function for oyster_slider_block_view() content.
 */
function oyster_slider_block_content($id) {
  $slider = entity_load('oyster_slider', array($id));
	$output = '';
	
	if ($slider[$id]->slider_settings['und'][0]['icons'] == 1) {
		// Social icons markup.
		$output .= '<div class="fs_fadder hided"></div><div class="fs_sharing_wrapper hided"><div class="fs_sharing">';
	  foreach ($slider[$id]->slider_icons['und'] as $icon) {
		  $output .= '<a href="'.$icon['url'].'" target="_blank"><i class="fa '.$icon['icon'].'"></i></a>';
	  }
	  $output .= '<a class="fs_share_close hided" href="javascript:void(0)"></a>';
	  $output .='</div></div>';
	  drupal_add_css('.fs_controls a.fs_share {display: inline-block;}', array('group' => CSS_THEME, 'type' => 'inline'));
  }
  
  if ($slider[$id]->slider_settings['und'][0]['icons'] == 0) {
    drupal_add_css('.fs_controls a.fs_share {display: none;}', array('group' => CSS_THEME, 'type' => 'inline'));
  }
  
  // Slides markup.
  $output .='<script>';
  $output .='gallery_set = [';
  
  foreach ($slider[$id]->slider_content['und'] as $slide) {
    $file = file_load($slide['image']);
    $slide['title'] = htmlspecialchars($slide['title']);
	  $output .= '{image: "'.image_style_url('oyster_slider_image', $file->uri).'", thmb: "'.image_style_url('oyster_slider_thumbnail', $file->uri).'", alt: "'.$slide['title'].'", title: "'.$slide['title'].'", description: "'.$slide['caption'].'", titleColor: "#ffffff", descriptionColor: "#ffffff"},';
  }
  
  $output .=']';
  
  $output .= "
	  jQuery(document).ready(function ($) {
		
			jQuery('html').addClass('hasPag');
			
			jQuery('body').fs_gallery({
				fx: '".$slider[$id]->slider_settings['und'][0]['effect']."', 
				fit: 'no_fit',
				slide_time: ".$slider[$id]->slider_settings['und'][0]['time'].", /*This time must be < then time in css*/
				autoplay: ".$slider[$id]->slider_settings['und'][0]['autoplay'].",
				show_controls: ".$slider[$id]->slider_settings['und'][0]['controls'].",
				slides: gallery_set
			});
			
		});
  ";
	if ($slider[$id]->slider_settings['und'][0]['icons'] == 1) {
		$output .= "	
		  jQuery(document).ready(function ($) {	
				jQuery('.fs_share').click(function(){
					jQuery('.fs_fadder').removeClass('hided');
					jQuery('.fs_sharing_wrapper').removeClass('hided');
					jQuery('.fs_share_close').removeClass('hided');
				});
				jQuery('.fs_share_close').click(function(){
					jQuery('.fs_fadder').addClass('hided');
					jQuery('.fs_sharing_wrapper').addClass('hided');
					jQuery('.fs_share_close').addClass('hided');
				});
				jQuery('.fs_fadder').click(function(){
					jQuery('.fs_fadder').addClass('hided');
					jQuery('.fs_sharing_wrapper').addClass('hided');
					jQuery('.fs_share_close').addClass('hided');
				});
			});	
	  ";	
  }
  
	  $output .= "		
    jQuery(document).ready(function ($) {	
			jQuery('.close_controls').click(function(){
				if (jQuery(this).hasClass('open_controls')) {
					jQuery('.fs_controls').removeClass('hide_me');
					jQuery('.fs_title_wrapper ').removeClass('hide_me');
					jQuery('.fs_thmb_viewport').removeClass('hide_me');
					jQuery('header.main_header').removeClass('hide_me');
					jQuery(this).removeClass('open_controls');
				} else {		
					jQuery('header.main_header').addClass('hide_me');
					jQuery('.fs_controls').addClass('hide_me');
					jQuery('.fs_title_wrapper ').addClass('hide_me');
					jQuery('.fs_thmb_viewport').addClass('hide_me');
					jQuery(this).addClass('open_controls');
				}
			});
		});
	";

		  
  $output .='</script>';
  
  // Return slider output.
  return $output;
} 

/**
 * Implements hook_contextual_links_view_alter.
 */
function oyster_slider_contextual_links_view_alter(&$element, &$items) {
  if (isset($element['#element']['#block']) && $element['#element']['#block']->module == "oyster_slider") {
    $delta = $element['#element']['#block']->delta;
	  $element['#links']['edit_oyster_sliderl'] = array(
	    'title' => 'Configure Slider',
	    'href' => url("admin/structure/oyster-slider/manage/$delta", array('absolute' => TRUE)),
	  );
  }
}