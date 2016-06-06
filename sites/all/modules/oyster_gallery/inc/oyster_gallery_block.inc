<?php
/**
 * Implements hook_block_info.
 */
function oyster_gallery_block_info() {
  $blocks = array();
  $galleries = entity_load('oyster_gallery');
  
  if (is_array($galleries)) {
	  foreach ($galleries as $gallery) {
		  $blocks[$gallery->id]['info'] = t('Oyster Gallery: '. $gallery->name.'' );
	  }
  }
  
  return $blocks;
}

/**
 * Implements hook_block_view.
 */
function oyster_gallery_block_view($delta = '') {
  $gallery = entity_load('oyster_gallery', array($delta));
   // Exit function if $gallery is empty.
  if ($gallery == NULL) { 
    return;
  }
  // Call gallery markup function based on "display" field setting. 
  switch ($gallery[$delta]->gallery_display['und'][0]['display']) {
    case 'kenburns':
      $block['content'] = array(
		    '#markup' => oyster_gallery_kenburns($delta),
		    '#attached' => array(
		      'js' => array(
		        drupal_get_path('module', 'oyster_gallery') .'/js/kenburns.js',
		        drupal_get_path('module', 'oyster_gallery') .'/js/oyster_kenburns.js'
		      ),
		    ),
		  );
	  break;
	  case 'flow':
      $block['content'] = array(
		    '#markup' => oyster_gallery_flow($delta),
		  );
	  break;
	  case 'ribbon':
      $block['content'] = array(
		    '#markup' => oyster_gallery_ribbon($delta),
		    '#attached' => array(
		      'js' => array(
		        drupal_get_path('module', 'oyster_gallery') .'/js/oyster_ribbon.js'
		      ),
		    ),
		  );
	  break;
	  case 'listing':
      $block['content'] = array(
		    '#markup' => oyster_gallery_listing($delta),
		    '#attached' => array(
		      'js' => array(
		        drupal_get_path('module', 'oyster_gallery') .'/js/oyster_listing.js'
		      ),
		    ),
		  );
	  break;
	  case 'grid':
      $block['content'] = array(
		    '#markup' => oyster_gallery_grid($delta),
		    '#attached' => array(
		      'js' => array(
		        drupal_get_path('module', 'oyster_gallery') .'/js/oyster_grid.js'
		      ),
		    ),
		  );
	  break;
	  case 'grid2':
      $block['content'] = array(
		    '#markup' => oyster_gallery_grid_alt($delta),
		    '#attached' => array(
		      'js' => array(
		        drupal_get_path('module', 'oyster_gallery') .'/js/oyster_grid.js'
		      ),
		    ),
		  );
	  break;
	  case 'masonry':
      $block['content'] = array(
		    '#markup' => oyster_gallery_masonry($delta),
		  );
	  break;
	  case 'masonry2':
      $block['content'] = array(
		    '#markup' => oyster_gallery_masonry_alt($delta),
		  );
	  break;
  }
  
  return $block;
}
 
function oyster_gallery_kenburns($id) {
  $galleries = entity_load('oyster_gallery', array($id));
  $output = '';
  $output .= '
    <div class="gallery_kenburns">
      <canvas id="kenburns">
        <p>Your browser does not support canvas!</p>
      </canvas>
    </div>    
	  <div class="content_bg"></div>
  ';
  $output .= '<script type="text/javascript">';
  $output .= 'gallery_set = [';
  foreach ($galleries[$id]->gallery_content['und'] as $gallery) {
	  $output .= "'".file_create_url(file_load($gallery['image'])->uri)."',";
  }
  $output .= ']';
  $output .= '</script>';
      
  return $output;
}

function oyster_gallery_flow($id) {
  global $base_url;
  $url = ''.$base_url.'/'.$_GET['q'].'';
  $galleries = entity_load('oyster_gallery', array($id));
  
  // Set $share_url variable for oyster_social_share.
  if (isset($galleries[$id]->gallery_content['und']['1'])) {
		$share_image = file_create_url(file_load($galleries[$id]->gallery_content['und'][0]['image'])->uri);
	} else{
		$share_image = NULL;
	}
  // Set $share variable.
  $share = theme('oyster_social_share', array('title' => drupal_get_title(), 'link' => $url, 'image' => $share_image));
 
  $output = '';
  
  $output .= '
    <div class="whaterWheel_content">
    <div id="whaterwheel">
    <div id="ww_finger"></div>
  ';
  
  $count = '1';
  foreach ($galleries[$id]->gallery_content['und'] as $gallery) {
  
    // If image file does not exist in image style folder, create it.
		if (isset($gallery['image']) && !file_exists(image_style_path('oyster_gallery_flow', file_load($gallery['image'])->uri))){ 
		  image_style_create_derivative(image_style_load('oyster_gallery_flow'), file_load($gallery['image'])->uri, image_style_path('oyster_gallery_flow', file_load($gallery['image'])->uri));
		}
        
    $output .= '<div class="ww_block" id="ww_block'.$count.'" data-count="'.$count.'" data-title=" : '.$gallery['title'].'">';
	  $output .= '<div class="ww_wrapper"><a href="javascript:void(0)" class="ww_link" data-count="'.$count.'"><img width="740" alt="Flow : '.$gallery['title'].'" height="550" src="'.file_create_url(image_style_path('oyster_gallery_flow', file_load($gallery['image'])->uri)).'" /></a></div>';
	  $output .= '</div>';
	  $count ++;
  }
  
  $output .= '</div>';
  $output .= '
    <div class="ww_footer">
		  <div class="ww_footer_left">
		  	<h6 class="title">Flow</h6>
		      <h6 class="img_title"></h6>
		  </div>
		  <div class="ww_footer_right">
		    <div class="slider_share"> 
		      '.$share.'
		    </div>             
		  </div>
		</div>
  ';
  $output .= '</div>';
  $output .= '<div class="preloader"></div>';
  $output .= '<div class="content_bg"></div>';  
  return $output;
}

function oyster_gallery_ribbon($id) {
  global $base_url;
  $url = ''.$base_url.'/'.$_GET['q'].'';
  $galleries = entity_load('oyster_gallery', array($id));
 
  $output = '';
  
  $output .= '
    <div class="fullscreen-gallery hided">
    <div class="fs_grid_gallery">
    <div class="ribbon_wrapper">
    <a href="javascript:void(0)" class="btn_prev"></a>
    <a href="javascript:void(0)" class="btn_next"></a>
    <div id="ribbon_swipe"></div>
    <div class="ribbon_list_wrapper">
    <ul class="ribbon_list">
  ';

  // Set $share_url variable for oyster_social_share.
  if (isset($galleries[$id]->gallery_content['und']['1'])) {
		$share_image = file_create_url(file_load($galleries[$id]->gallery_content['und'][0]['image'])->uri);
	} else{
		$share_image = NULL;
	}
  // Set $share variable.
  $share = theme('oyster_social_share', array('title' => drupal_get_title(), 'link' => $url, 'image' => $share_image));
  
  $count = '1';
  foreach ($galleries[$id]->gallery_content['und'] as $gallery) {
	  $output .= ' <li data-count="'.$count.'" data-title=" : '.$gallery['title'].'" class="slide'.$count.'"><div class="slide_wrapper"><img src="'.file_create_url(file_load($gallery['image'])->uri).'" alt="image'.$count.'"/></div></li>';
	  $count ++;
  }
  $output .= '</ul></div></div>';

  $output .= '
    <div class="slider_info">
	  	<div class="slider_data">
	    	<a href="javascript:void(0)" class="ltl_prev"><i class="icon-angle-left"></i></a><span class="num_current">1</span> of <span class="num_all"></span><a href="javascript:void(0)" class="ltl_next"><i class="icon-angle-right"></i></a>
	      <h6 class="slider_title">Ribbon</h6><h6 class="slider_caption"></h6>
	    </div>
	    <div class="slider_share">
	        '.$share.'
	    </div>
	                 
	  </div>
  ';
  $output .= '</div></div>';
  $output .= '<div class="preloader"></div>';
  $output .= '<div class="content_bg"></div>';

  
  return $output;
}

function oyster_gallery_listing($id) {
  $galleries = entity_load('oyster_gallery', array($id));
 
  $output = '';
  
  $output .= '
    <div class="gallery_toolbar">
    <a href="javascript:history.back()" class="btn_back">Back</a>
    <div class="gallery_type_selector">                            	
    <a href="javascript:void(0)" class="btn_gallery_masonry "></a>
    <a href="javascript:void(0)" class="btn_gallery_column active"></a>
    </div>
    </div>
    <div class="contentarea">
    <div class="content_gallery listing_gallery">
  ';
  
  
  foreach ($galleries[$id]->gallery_content['und'] as $gallery) {
    $output .= '
      <div class="cont_gallery_item">
        <div class="cont_gallery_wrapper">
          <div class="grid-gallery-item">
              <img src="'.file_create_url(file_load($gallery['image'])->uri).'" alt="image-listing">
              <div class="gallery_fadder"></div>
              <span class="gallery_ico"><i class="stand_icon icon-eye"></i></span>
              <a href="'.file_create_url(file_load($gallery['image'])->uri).'" class="prettyPhoto gallery_list_zoom" data-rel="prettyPhoto[gallery'.$id.']"></a>
          </div>
        </div>
      </div>
    ';
  }
  
  $output .= '</div></div>';
  $output .= '<div class="content_bg"></div>';
  return $output;
}

function oyster_gallery_grid($id) {
  $galleries = entity_load('oyster_gallery', array($id));
 
  $output = '';
  
  $output .= '
    <div class="fullscreen-gallery hided">
	  <div class="fs_grid_gallery pb0 pl0">
  ';
  
  
  foreach ($galleries[$id]->gallery_content['und'] as $gallery) {
    // If image file does not exist in image style folder, create it.
		if (isset($gallery['image']) && !file_exists(image_style_path('oyster_gallery_grid', file_load($gallery['image'])->uri))){ 
		  image_style_create_derivative(image_style_load('oyster_gallery_grid'), file_load($gallery['image'])->uri, image_style_path('oyster_gallery_grid', file_load($gallery['image'])->uri));
		}
    
    $output .= '
      <div class="grid-gallery-item loading anim_el pr0 pt0">
        <a href="'.file_create_url(file_load($gallery['image'])->uri).'" class="prettyPhoto" data-rel="prettyPhoto[gallery'.$id.']" title="">
          <img src="'.file_create_url(image_style_path('oyster_gallery_grid', file_load($gallery['image'])->uri)).'" alt="" class="fw_featured_image" width="540">
          <span class="gallery_fadder"></span>
          <span class="gallery_ico"><i class="stand_icon icon-eye"></i></span>
        </a>
      </div>
    ';
  }
  
  $output .= '</div></div>';
  $output .= '<div class="preloader"></div>';
  $output .= '<div class="content_bg"></div>';  
  return $output;
}

function oyster_gallery_grid_alt($id) {
  $galleries = entity_load('oyster_gallery', array($id));
 
  $output = '';
  $output .= '
    <div class="fullscreen-gallery hided">
	  <div class="fs_grid_gallery pb5 pl5">
  ';
  
  foreach ($galleries[$id]->gallery_content['und'] as $gallery) {
  
    // If image file does not exist in image style folder, create it.
		if (isset($gallery['image']) && !file_exists(image_style_path('oyster_gallery_grid', file_load($gallery['image'])->uri))){ 
		  image_style_create_derivative(image_style_load('oyster_gallery_grid'), file_load($gallery['image'])->uri, image_style_path('oyster_gallery_grid', file_load($gallery['image'])->uri));
		}
    
    $output .= '
      <div class="grid-gallery-item loading anim_el pr5 pt5">
        <a href="'.file_create_url(file_load($gallery['image'])->uri).'" class="prettyPhoto" data-rel="prettyPhoto[gallery99]" title="">
          <img src="'.file_create_url(image_style_path('oyster_gallery_grid', file_load($gallery['image'])->uri)).'" alt="" class="fw_featured_image" width="540" height="375">
          <span class="gallery_fadder"></span>
          <span class="gallery_ico"><i class="stand_icon icon-eye"></i></span>
        </a>
      </div>
    ';
  }
  
  $output .= '</div></div>';
  $output .= '<div class="preloader"></div>';
  $output .= '<div class="content_bg"></div>';  
  return $output;
}

function oyster_gallery_masonry($id) {
  $galleries = entity_load('oyster_gallery', array($id));
 
  $output = '';
  
  $output .= '
    <div class="fullscreen-gallery hided pb0 pl0">
	  <div class="fs_grid_gallery is_masonry">	
  ';

  foreach ($galleries[$id]->gallery_content['und'] as $gallery) {
    $output .= '
      <div class="grid-gallery-item pr0 pt0">
        <a href="'.file_create_url(file_load($gallery['image'])->uri).'" class="prettyPhoto" data-rel="prettyPhoto[gallery99]" title="">
          <img src="'.file_create_url(file_load($gallery['image'])->uri).'" alt="" class="fw_featured_image" width="540">
          <span class="gallery_fadder"></span>
          <span class="gallery_ico"><i class="stand_icon icon-eye"></i></span>
        </a>
      </div>
    ';
  }
  
  $output .= '</div></div>';
  $output .= '<div class="content_bg"></div>';
  $output .= '<div class="preloader"></div>';
  $output .= '<script type="text/javascript">';
  $output .= "
    jQuery(document).ready(function(){
			\"use strict\";
			jQuery('.is_masonry').masonry();
			jQuery('html').addClass('without_border');
			jQuery('.is_masonry').masonry();
			setTimeout(\"jQuery('.is_masonry').masonry()\",500);
			setTimeout(\"jQuery('.is_masonry').masonry()\",1000);
		});
		jQuery(window).load(function () {
			\"use strict\";
			setTimeout(\"jQuery('.is_masonry').masonry()\",500);
			setTimeout(\"jQuery('.is_masonry').masonry()\",1000);
		});
		jQuery(window).resize(function () {
			\"use strict\";
			setTimeout(\"jQuery('.is_masonry').masonry()\",500);
			setTimeout(\"jQuery('.is_masonry').masonry()\",1000);
		});						
  ";
  $output .= '</script>';
  
  return $output;
}

function oyster_gallery_masonry_alt($id) {
  $galleries = entity_load('oyster_gallery', array($id));
 
  $output = '';
  
  $output .= '
    <div class="fullscreen-gallery hided pb10 pl10">
	  <div class="fs_grid_gallery is_masonry">
  ';
  
  
  foreach ($galleries[$id]->gallery_content['und'] as $gallery) {
    $output .= '
      <div class="grid-gallery-item pr10 pt10">
        <a href="'.file_create_url(file_load($gallery['image'])->uri).'" class="prettyPhoto" data-rel="prettyPhoto[gallery99]" title="">
          <img src="'.file_create_url(file_load($gallery['image'])->uri).'" alt="" class="fw_featured_image" width="540" height="375">
          <span class="gallery_fadder"></span>
          <span class="gallery_ico"><i class="stand_icon icon-eye"></i></span>
        </a>
      </div>
    ';
  }
  
  $output .= '</div></div>';
  $output .= '<div class="content_bg"></div>';
  $output .= '<div class="preloader"></div>';
  $output .= '<script type="text/javascript">';
  $output .= "
    jQuery(document).ready(function(){
			\"use strict\";
			jQuery('.is_masonry').masonry();
			jQuery('html').addClass('without_border');
			jQuery('.is_masonry').masonry();
			setTimeout(\"jQuery('.is_masonry').masonry()\",500);
			setTimeout(\"jQuery('.is_masonry').masonry()\",1000);
		});
		jQuery(window).load(function () {
			\"use strict\";
			setTimeout(\"jQuery('.is_masonry').masonry()\",500);
			setTimeout(\"jQuery('.is_masonry').masonry()\",1000);
		});
		jQuery(window).resize(function () {
			\"use strict\";
			setTimeout(\"jQuery('.is_masonry').masonry()\",500);
			setTimeout(\"jQuery('.is_masonry').masonry()\",1000);
		});						
  ";
  $output .= '</script>';
  
  return $output;
}