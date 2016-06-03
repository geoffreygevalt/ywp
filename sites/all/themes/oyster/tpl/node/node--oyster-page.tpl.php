<?php if (isset($content['field_oyster_page_layouts']) && $content['field_oyster_page_layouts']['#items'][0]['value']
 == 'image'): ?>
  <div class="fullscreen_block fw_background bg_image bg1"></div>       
	<div class="content_bg"></div>
	
	<?php 
	  drupal_add_js(drupal_get_path('theme', 'oyster') .'/js/page/oyster_page_image.js');
	  
		if (render($content['field_oyster_page_image'])) {
		  drupal_add_css(
		    '.fw_background.bg_image {background: url('. file_create_url($node->field_oyster_page_image['und'][0]['uri']) .');}',
		    array(
		      'group' => CSS_THEME,
		      'type' => 'inline',
		      'media' => 'screen',
		      'preprocess' => FALSE,
		      'weight' => '9999',
		    )
		  );
		}
		?>

<?php endif; ?>

<?php if (isset($content['field_oyster_page_layouts']) && $content['field_oyster_page_layouts']['#items'][0]['value'] == 'video'): ?>
   
   <?php drupal_add_js(drupal_get_path('theme', 'oyster') .'/js/page/oyster_page_video.js'); ?>
   
   <?php if (render($content['field_oyster_page_video'])): ?>
   <div class="fullscreen_block fw_background bg_video">
     <?php print render($content['field_oyster_page_video']); ?> 	
   </div>
   <?php endif; ?>
  
<?php endif; ?>

<?php if (isset($content['field_oyster_page_layouts']) && $content['field_oyster_page_layouts']['#items'][0]['value'] == 'fullscreen'): ?>
  <div class="fw_content_wrapper">
    <div class="fw_content_padding">
      <div class="content_wrapper noTitle">
        <div class="container">
          <div class="row">
            <div class="posts-block ">                                                   
              <div class="contentarea">
                <div class="row">
                  <div class="span12 first-module module_number_1 module_cont pb0 module_text_area">
                    <div class="bg_title"><h2 class="headInModule"><?php print $title; ?></h2></div>
                      <div class="module_content">
                        <?php
										     	hide($content['comments']);
										      hide($content['links']);
										      hide($content['field_oyster_page_layouts']);
										      hide($content['field_oyster_page_image']);
										      hide($content['field_oyster_page_video']);
										      print render($content);
										    ?>
                      </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>  
  </div>
	<div class="fixed_bg"></div>
	
	<?php 
	  drupal_add_js(drupal_get_path('theme', 'oyster') .'/js/page/oyster_page_fullscreen.js');
		if (render($content['field_oyster_page_image'])) {
		  drupal_add_css(
		    '.fixed_bg {background: url('. file_create_url($node->field_oyster_page_image['und'][0]['uri']) .');}',
		    array(
		      'group' => CSS_THEME,
		      'type' => 'inline',
		      'media' => 'screen',
		      'preprocess' => FALSE,
		      'weight' => '9999',
		    )
		  );
		}
  ?>

<?php endif; ?>