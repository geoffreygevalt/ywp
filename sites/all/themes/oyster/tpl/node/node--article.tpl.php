<?php 
  // Declare $base_url global.
  global $base_url;
  // Require article.inc helper file.
  require_once(drupal_get_path('theme', 'oyster').'/inc/article.inc'); 
	// Set $share_image variable for passing as argument to oyster_social_share.
	if (isset($content['field_image'])) {
		$share_image = file_create_url($node->field_image['und'][0]['uri']);
	} else{
		$share_image = NULL;
	}
?>
  
<?php if (!$teaser): ?>
<div class="prev_next_links">
  <?php if (oyster_node_pagination($node, 'p') != NULL) : ?>
    <div class="fleft"><a href="<?php print url('node/' . oyster_node_pagination($node, 'p'), array('absolute' => TRUE)); ?>"><?php print t('Previous Post'); ?></a></div>
  <?php endif; ?>
  <?php if (oyster_node_pagination($node, 'n') != NULL) : ?>
    <div class="fright"><a href="<?php print url('node/' . oyster_node_pagination($node, 'n'), array('absolute' => TRUE)); ?>"><?php print t('Next Post'); ?></a></div>
  <?php endif; ?>
</div>
<?php endif; ?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <div class="blog_post_page <?php if ($teaser) { print 'blog_teaser'; } ?>">
  
    <?php if (render($content['field_image']) && count(field_get_items('node', $node, 'field_image')) == 1 && !isset($content['field_media_embed'])): ?>                                                                 
      <?php print render($content['field_image']); ?>
    <?php endif; ?>
    
    <?php if (render($content['field_image']) && count(field_get_items('node', $node, 'field_image')) > 1 && !isset($content['field_media_embed'])): ?>     
                                              	
    <div class="slider-wrapper theme-default ">
      <div class="nivoSlider">                                                
        <?php print render($content['field_image']); ?>
      </div>
    </div>
    <?php endif; ?>
    
    <?php if (render($content['field_media_embed'])): ?>
      <div class="pf_output_container"><?php print render($content['field_media_embed']);?></div>
    <?php endif; ?>
    
    <div class="blogpreview_top <?php if ( theme_get_setting('article_meta_date') != '1' ) { print "nodate"; } ?>">
      <?php if ( theme_get_setting('article_meta_date') == '1' ) : ?>
      <div class="box_date">
        <span class="box_month"><?php print format_date($node->created, 'custom', 'M'); ?></span>
        <span class="box_day"><?php print format_date($node->created, 'custom', 'd'); ?></span>
      </div>   
      <?php endif; ?>                                         
      <div class="listing_meta">
        <?php if ($content['field_article_category']): ?>
          <span><?php print t('in'); ?> <?php print render($content['field_article_category']); ?></span>
        <?php endif; ?>  
        <?php if ( theme_get_setting('article_meta_comments') == '1' ) : ?>
        <span><a href="<?php print $node_url;?>/#comments"><?php print $comment_count; ?> <?php print t('Comment'); ?><?php if ($comment_count != "1" ) { echo "s"; } ?></a></span>
        <?php endif; ?>
        <?php if (render($content['field_tags'])): ?><span><?php print t('tags: '); print render($content['field_tags']); ?></span><?php endif;?>
      </div>   
      <?php if ($display_submitted): ?>                                     
        <div class="author_ava"><?php print $user_picture; ?></div>
      <?php endif; ?>
    </div>
    <?php print render($title_prefix); ?>
    <?php if ( theme_get_setting('article_meta_title') == '1' ) : ?>
    <h3<?php print $title_attributes; ?> class="blogpost_title"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h3>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
	
	  <article class="contentarea clearfix"<?php print $content_attributes; ?>>
	    <?php
	      // We hide the comments and links now so that we can render them later.
	      hide($content['comments']);
	      hide($content['links']);
	      hide($content['field_image']);
	      hide($content['field_like']);
	      print render($content);
	    ?>
	  </article>

		<div class="blog_post-footer">
		  
	    <?php if (!$teaser && module_exists('oyster_utilities') && theme_get_setting('article_meta_share') == '1') { print theme('oyster_social_share', array('title' => $title, 'link' => $base_url.'/node/'.$nid, 'image' => $share_image)); }?>
	    
	    <?php if ($teaser): ?>
	    <a href="<?php print $node_url; ?>" class="shortcode_button btn_small btn_type5 reamdore"><?php print t('Read More'); ?></a>
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
    </div>
  </div> 
  
  <?php if (!$teaser && theme_get_setting('article_meta_author') == '1'): ?>
  <div class="blogpost_user_meta">
		<div class="author-ava"><?php print $user_picture; ?></div>
		<div class="author-name"><h6><?php print t('About the Author:'); ?> <?php print $name; ?></h6></div>
		<?php if (isset(user_load($uid)->field_author_info)): ?>
		<div class="author-description"><?php print user_load($uid)->field_author_info['und'][0]['value']; ?></div>
		<?php endif; ?>
		<div class="clear"></div>
  </div> 
  <?php endif; ?>
  <hr class="single_hr">          

  <?php if (!$teaser) { print article_related_works($nid); } ?>
  
	<?php print render($content['comments']); ?>
 
</div>