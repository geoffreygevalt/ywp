<?php 
  if (!isset($content['field_media_embed'])) { drupal_add_js(drupal_get_path('theme', 'oyster') .'/js/portfolio/portfolio_without_info_image.js'); } if (isset($content['field_media_embed'])) { drupal_add_js(drupal_get_path('theme', 'oyster') .'/js/portfolio/portfolio_without_info_video.js'); 
	}
?>   

<div class="fullscreen-gallery">
  <div class="fs_grid_gallery">	
    
    <div class="ribbon_wrapper">
        <?php if (isset($content['field_image']) && !isset($content['field_media_embed'])): ?>
        <div id="ribbon_swipe"></div>
        <div class="ribbon_list_wrapper">
          <ul class="fw_gallery_list">
            <?php 
              $count = '1';
              foreach ($node->field_image['und'] as $image) {
                print '<li data-count="'.$count.'" class="slide'.$count.'"><img src="'.file_create_url($image['uri']).'" alt="image'.$count.'"/>/li>';
                $count++;
              }
            ?>
	          
      	  </ul>
        </div>
        <?php endif; ?>
        <?php if (isset($content['field_media_embed'])): ?>
        
        <div class="ribbon_list_wrapper">
          <div class="fw_video_block">
            <?php print render($content['field_media_embed']); ?>
          </div>   
        </div>
        <?php endif; ?>
    </div>
    
    <div class="slider_info fw_slider_info">
      
      <div class="slider_data">
        <?php if (isset($content['field_image']) && !isset($content['field_media_embed'])): ?>
        <a href="javascript:void(0)" class="ltl_prev"><i class="icon-angle-left"></i></a><span class="num_current">1</span> <?php print t('of'); ?> <span class="num_all"></span><a href="javascript:void(0)" class="ltl_next"><i class="icon-angle-right"></i></a>
        <?php endif; ?>
        <?php print render($title_prefix); ?>
        <?php if ( theme_get_setting('portfolio_meta_title') == '1' ) : ?>
        <h6 class="post_title"><?php print $title; ?></h6>
        <?php endif; ?>
        <?php print render($title_suffix); ?>
      </div>
      
      
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