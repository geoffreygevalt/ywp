<?php drupal_add_js(drupal_get_path('theme', 'oyster') .'/js/portfolio/portfolio_with_info.js'); ?>

<div class="fullscreen-gallery">
  <div class="fs_grid_gallery">	
    
    <div class="ribbon_wrapper">
        <?php if (isset($content['field_image'])): ?>
        <div id="ribbon_swipe"></div>
        <div class="ribbon_list_wrapper">
          <ul class="fw_gallery_list">
            <?php 
              $count = '1';
              foreach ($node->field_image['und'] as $image) {
                print '<li data-count="'.$count.'" class="slide'.$count.'"><img src="'.file_create_url($image['uri']).'" alt="image'.$count.'"/></li>';
                $count++;
              }
            ?>
	          
      	  </ul>
        </div>
        <?php endif; ?>
    </div>
    
    <?php if (isset($content['field_media_embed'])) { print render($content['field_media_embed']); } ?>
    
    <div class="slider_info fw_slider_info">
    
      <?php if (isset($content['field_image'])): ?>
      <div class="slider_data">
        <a href="javascript:void(0)" class="ltl_prev"><i class="icon-angle-left"></i></a><span class="num_current">1</span> <?php print t('of'); ?> <span class="num_all"></span><a href="javascript:void(0)" class="ltl_next"><i class="icon-angle-right"></i></a>
        <?php print render($title_prefix); ?>
        <?php if ( theme_get_setting('portfolio_meta_title') == '1' ) : ?>
        <h6 class="post_title"><?php print $title; ?></h6>
        <?php endif; ?>
        <?php print render($title_suffix); ?>
      </div>
      <?php endif; ?>
      
      <?php if (!$teaser && module_exists('oyster_utilities') && theme_get_setting('portfolio_meta_share') == '1'): ?>
      <div class="slider_share">
        <?php print theme('oyster_social_share', array('title' => $title, 'link' => $base_url.'/node/'.$nid, 'image' => $share_image)); ?>
      </div>
      <?php endif; ?>
      
      <?php if (render($content['field_like']) || module_exists('statistics')): ?> 
	    <div class="block_likes">
	      <?php if (module_exists('statistics') && user_access("view post access counter")): ?>
	      <div class="post-views"><i class="stand_icon icon-eye"></i> <span><?php $var = statistics_get($nid); print ($var['totalcount']) +1; ?></span></div>
	      <?php endif; ?>
	      <?php if (render($content['field_like'])): ?><?php print render($content['field_like']); ?><?php endif; ?>	   
	    </div> 
	    <?php endif; ?>
      <div class="clear"></div>
      <div class="post_meta_data">
        <div class="listing_meta">
          <?php if ( theme_get_setting('portfolio_meta_author') == '1' ) : ?> 
          <span><?php print t('by '); print $name; ?></span>
          <?php endif; ?>
          <?php if (render($content['field_portfolio_category'])): ?>
            <span><?php print t('in'); ?> <?php print render($content['field_portfolio_category']); ?></span>
          <?php endif; ?>
          <?php if ( theme_get_setting('portfolio_meta_comments') == '1' ) : ?>
          <span><a href="<?php print $node_url;?>/#comments"><?php print $comment_count; ?> <?php print t('Comment'); ?><?php if ($comment_count != "1" ) { echo "s"; } ?></a></span>
          <?php endif; ?>
          <?php if (render($content['field_portfolio_skills'])) { print render($content['field_portfolio_skills']); } ?>                                                   
        </div>
        <div class="post_controls">
          <?php if (oyster_node_pagination($node, 'p') != NULL) : ?>
        	  <div class="fleft"><a href="<?php print url('node/' . oyster_node_pagination($node, 'p'), array('absolute' => TRUE)); ?>" rel="prev"></a></div>
          <?php endif; ?>
          <?php if (oyster_node_pagination($node, 'n') != NULL) : ?>
            <div class="fright"><a href="<?php print url('node/' . oyster_node_pagination($node, 'n'), array('absolute' => TRUE)); ?>" rel="next"></a></div> 
          <?php endif; ?>
            <a href="javascript:history.back()" class="fw_post_close"></a>
        </div>
      </div>                           
    </div>
  </div>
</div>   

<div class="content_wrapper">
  <div class="container simple-post-container fw-post-container">
    <div class="content_block no-sidebar row">
      <div class="fl-container">
        <div class="row">						
          <div class="posts-block simple-post">
            <article class="contentarea sp_contentarea">
    
					    <?php if (isset($content['field_portfolio_introduction'])) { print render($content['field_portfolio_introduction']); } ?>
					    
				      <?php if (isset($content['field_portfolio_gallery'])) { print portfolio_gallery($node); } ?>
					
					    <?php
					      // Hide all other fields and render $content.
					      hide($content['field_image']);
					      hide($content['field_tags']);
					      hide($content['field_portfolio_skills']);
					      hide($content['field_portfolio_gallery']);
					      hide($content['field_media_embed']);
					      hide($content['field_portfolio_introduction']);
					      hide($content['field_portfolio_category']);
					      hide($content['field_portfolio_layout']);
					      hide($content['field_like']);
					      hide($content['comments']);
					      hide($content['links']);
					      print render($content);
					    ?>
					                 
				    </article>
					   
					  <div class="blog_post-footer sp-blog_post-footer ">
						  <?php if (!$teaser && module_exists('oyster_utilities') && theme_get_setting('portfolio_meta_share') == '1') { print theme('oyster_social_share', array('title' => $title, 'link' => $base_url.'/node/'.$nid, 'image' => $share_image)); }?>
				  
						  <?php if (render($content['field_like']) || module_exists('statistics')): ?> 
					    <div class="block_likes">
					      <?php if (module_exists('statistics')): ?>
					      <div class="post-views"><i class="stand_icon icon-eye"></i> <span><?php $var = statistics_get($nid); print ($var['totalcount']) +1; ?></span></div>
					      <?php endif; ?>
					      <?php if (render($content['field_like'])): ?><?php print render($content['field_like']); ?><?php endif; ?>	   
					    </div> 
					    <?php endif; ?>
						  
						  <div class="clear"></div>
						</div> 

				    <hr class="single_hr">          
				  
				    <?php print portfolio_related_works($nid); ?>
				
				  <?php
				    // Remove the "Add new comment" link on the teaser page or if the comment
				    // form is being displayed on the same page.
				    if ($teaser || !empty($content['comments']['comment_form'])) {
				      unset($content['links']['comment']['#links']['comment-add']);
				    }
				    // Only display the wrapper div if there are links.
				    $links = render($content['links']);
				    if ($links):
				  ?>
				    <div class="link-wrapper">
				      <?php print $links; ?>
				    </div>
				  <?php endif; ?>
				
				  <?php print render($content['comments']); ?>
				
				  </div>

          </div>
        </div>
      </div>    
    </div>
  </div>
</div>