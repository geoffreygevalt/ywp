<?php
/**
 * Implements hook_block_info.
 */
function oyster_striped_block_info() {
  $blocks = array();
  $galleries = entity_load('oyster_striped');
  
  if (is_array($galleries)) {
	  foreach ($galleries as $striped) {
		  $blocks[$striped->id]['info'] = t('Oyster Striped: '. $striped->name.'' );
	  }
  }
  
  return $blocks;
}

/**
 * Implements hook_block_view.
 */
function oyster_striped_block_view($delta = '') {
  $striped = entity_load('oyster_striped', array($delta));
  // Exit function if $striped is empty.
  if ($striped == NULL) { 
    return;
  }
  // Call striped markup function based on "display" field setting. 
  switch ($striped[$delta]->striped_display['und'][0]['display']) {
	  case 'horizontal':
	    $block['content'] = array(
		    '#markup' => oyster_striped_horizontal($delta),
		    '#attached' => array(
		      'js' => array(
		        drupal_get_path('module', 'oyster_striped') .'/js/striped_horizontal.js'
		      ),
		    ),
		  );
	  break;
	  case 'vertical':
	    $block['content'] = array(
		    '#markup' => oyster_striped_vertical($delta),
		    '#attached' => array(
		      'js' => array(
		        drupal_get_path('module', 'oyster_striped') .'/js/striped_vertical.js'
		      ),
		    ),
		  );
		break;  
  }

  return $block;
}
 
function oyster_striped_horizontal($id) {
  $count = 1;
  $galleries = entity_load('oyster_striped', array($id));
  $output = '';
  $output .= '<div class="strip_template"><figure class="strip-menu horizontal" data-count="'.count($galleries[$id]->striped_content['und']).'">
   
  ';
   foreach ($galleries[$id]->striped_content['und'] as $striped) {
    $output .= '<div class="strip-item strip_hor_'.$id.'_'.$count.'" data-href="'.$striped['url'].'">';
    $output .= '<div class="mobile-hover"></div><div class="strip-fadder"></div>';
    
    $output .= '<div class="strip-text">';
    $output .= '<h1 class="strip-title">'.$striped['title'].'</h1>';
    $output .= '<h3 class="strip-caption">'.$striped['caption'].'</h3>';
    $output .= '</div>';
    $output .= '<a href="'.$striped['url'].'"></a>';
	  $output .= '</div>';
	  $output .= '
	    <style>
	      .strip_hor_'.$id.'_'.$count.'{ background-image:url('.file_create_url(file_load($striped['image'])->uri).');}
	    </style>
	  ';
	  $count++;
  }

  $output .= '</figure></div>';
  $output .= '<div class="preloader"></div><div class="content_bg"></div>'; 
  return $output;
}

function oyster_striped_vertical($id) {
  $count = 1;
  $galleries = entity_load('oyster_striped', array($id));
  $output = '';
  $output .= '<div class="strip_template"><figure class="strip-menu vertical" data-count="'.count($galleries[$id]->striped_content['und']).'">
   
  ';
   foreach ($galleries[$id]->striped_content['und'] as $striped) {
    $output .= '<div class="strip-item strip_vert_'.$id.'_'.$count.'" data-href="'.$striped['url'].'">';
    $output .= '<div class="mobile-hover"></div><div class="strip-fadder"></div>';
    
    $output .= '<div class="strip-text">';
    $output .= '<h1 class="strip-title">'.$striped['title'].'</h1>';
    $output .= '</div>';
    $output .= '<a href="'.$striped['url'].'"></a>';
	  $output .= '</div>';
	  $output .= '
	    <style>
	      .strip_vert_'.$id.'_'.$count.'{ background-image:url('.file_create_url(file_load($striped['image'])->uri).');}
	    </style>
	  ';
	  $count++;
  }

  $output .= '</figure></div>';
  $output .= '<div class="preloader"></div><div class="content_bg"></div>'; 
  return $output;
}