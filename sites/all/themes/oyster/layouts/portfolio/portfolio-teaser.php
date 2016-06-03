<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix blog_post_preview"<?php print $attributes; ?>>
  <div class="post_preview_wrapper has_pf">
	  <div class="pf_output_container"> 
	    <?php if (count(field_get_items('node', $node, 'field_image')) == 1 && !isset($content['field_media_embed'])): ?>                                                                 
	      <?php print render($content['field_image']); ?>
	    <?php endif; ?>
	    
	    <?php if (count(field_get_items('node', $node, 'field_image')) > 1 && !isset($content['field_media_embed'])): ?>     
	                                              	
	    <div class="slider-wrapper theme-default ">
	      <div class="nivoSlider">                                                
	        <?php print render($content['field_image']); ?>
	      </div>
	    </div>
	    <?php endif; ?>
	    
	    <?php if (render($content['field_media_embed'])): ?>
        <?php print render($content['field_media_embed']);?>
      <?php endif; ?>
	 	</div>   
	 	<div class="blog_content">
	 	
		  <div class="blogpreview_top <?php if ( theme_get_setting('portfolio_meta_date') != '1' ) { print "nodate"; } ?>">
		    
		    <?php if ( theme_get_setting('portfolio_meta_date') == '1' ) : ?>
        <div class="box_date">
          <span class="box_month"><?php print format_date($node->created, 'custom', 'M'); ?></span>
          <span class="box_day"><?php print format_date($node->created, 'custom', 'd'); ?></span>
        </div>  
        <?php endif ; ?>                                          
        
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
        </div>   
		  </div>  

      <?php print render($title_prefix); ?>
      <?php if ( theme_get_setting('portfolio_meta_title') == '1' ) : ?>
      <h3<?php print $title_attributes; ?> class="blogpost_title"><?php print $title; ?></h3>
      <?php endif ; ?> 
      <?php print render($title_suffix); ?>
    
      <article class="contentarea">
  
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
	   
	    <div class="preview_footer">
				<a href="<?php print $node_url; ?>" class="shortcode_button btn_small btn_type5 reamdore"><?php print t('Read More'); ?></a>
			</div>
  
	  </div>
  </div>
</div>