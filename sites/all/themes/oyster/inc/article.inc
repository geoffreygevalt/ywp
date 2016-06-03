<?php

function article_related_works($nid){
  $count = '1';
  global $base_url;
  $query = new EntityFieldQuery();
	$query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('status', 1)
    ->entityCondition('bundle', 'article');
  $results = $query->execute();

  $output = '';
  $output .= '<div class="row"><div class="span12 single_feature">';
  $output .= ' <div class="featured_items"><div class="items3 featured_portfolio"><ul class="item_list">';
  foreach ($results['node'] as $result) {
    if ($count == 4) {
	    break;
    }
    if ($result->nid != $nid) {
      // Load those nodes.
      $item = node_load($result->nid);
      
      // If image file does not exist in image style folder, create it.
			if (isset($item->field_image['und']) && !file_exists(image_style_path('oyster_related_works', $item->field_image['und'][0]['uri']))){ 
			  image_style_create_derivative(image_style_load('oyster_related_works'), $item->field_image['und'][0]['uri'], image_style_path('oyster_related_works', $item->field_image['und'][0]['uri']));
			}
			// Assign image to $image if available.
      isset($item->field_image['und']) ? $image = '<img src="'.file_create_url(image_style_path('oyster_related_works', $item->field_image['und'][0]['uri'])).'">' : $image = '';
      
      if (isset($item->body['und'])) {
	      $body = substr($item->body['und'][0]['value'], 0, 75) .'<a class="morelink" href="'.$base_url.'/node/'.$item->vid.'">'.t(' Read more').'</a>';
      }
      else {
	      $body = '';
      }
      
      // Set the $like variable.
      $like = '';
      if (isset($item->field_like['und'])) {
        $like = field_view_field('node', $item, 'field_like');
        $like = drupal_render($like);
      }
      
      // Set the comment text.
      $item->comment_count == '1' ? $comment = t('comment') : $comment = t('comments');
      
      // Get the portfolio item taxonomy terms.
      $taxonomy = array();
      foreach ($item->field_article_category['und'] as $term) {
	      $taxonomy[] = taxonomy_term_load($term['tid'])->name;
      }
      $terms = implode(', ', $taxonomy);
	    
			// Start markup output.
	    $output .= '
	    <li>
	      <div class="item">
	        <div class="item_wrapper">
						<div class="img_block wrapped_img">
							<a class="featured_ico_link" href="'.$base_url.'/node/'.$item->vid.'">
								'.$image.'
								<div class="featured_item_fadder"></div>
								<span class="gallery_ico"><i class="stand_icon icon-eye"></i></span>
							</a>
						</div>
						
						<div class="featured_items_body">
							<div class="featured_items_title">
								<h6><a href="'.$base_url.'/node/'.$item->vid.'">'.$item->title.'</a></h6>
							</div>
							<div class="featured_item_content">
								'.$body.'
								
								<div class="featured_items_meta">
									<div class="preview_categ">
									  <span class="preview_meta_data">'.t('in').' '.$terms.'</span>
									  <span class="preview_meta_comments"><a href="'.$base_url.'/node/'.$item->vid.'/#comments"> '.$item->comment_count.' '.$comment.'</a> </span>
									</div>
									<div class="gallery_likes gallery_likes_add ">
										'.$like.'
									</div>											
								</div>
							</div>	
					  </div>
				  </div>
			  </div>
			</li>			
			';
		$count ++;	
	  }
	  
  }
  $output .= '</ul></div></div></div></div><hr class="single_hr">';
  return $output;
}