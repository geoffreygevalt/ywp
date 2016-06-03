<header class="main_header">
  <div class="header_wrapper">
  
    <?php if ($page['header_branding']) { print render($page['header_branding']); } ?>
    
    <?php if ($logo || $site_name || $site_slogan): ?>
  	<div class="logo_sect">
  	  <?php if ($logo): ?> 
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="logo_def"></a>
      <?php endif; ?> 
            
      <?php if ($site_name || $site_slogan): ?>
      <div id="name-and-slogan" <?php if ($disable_site_name && $disable_site_slogan) { print ' class="hidden"'; } ?>>

        <?php if ($site_name): ?>
          <?php if ($title): ?>
            <div id="site-name" <?php if ($disable_site_name) { print ' class="hidden"'; } ?>>
	            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
	          </div>
          <?php else: /* Use h1 when the content title is empty */ ?>
	          <h1 id="site-name" <?php if ($disable_site_name) { print ' class="hidden"'; } ?>>
	            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
	          </h1>
          <?php endif; ?>
        <?php endif; ?>

        <?php if ($site_slogan): ?>
          <div id="site-slogan" <?php if ( ($disable_site_slogan ) ) { print 'class="hidden"'; } if ( (!$disable_site_slogan ) AND ($disable_site_name) ) { print 'class="slogan no-name"'; } else { print 'class="slogan"'; } ?>>
            <?php print $site_slogan; ?>
          </div>
        <?php endif; ?>

      </div> <!-- /#name-and-slogan -->
	    <?php endif; ?>  
       
    </div>  
    <?php endif; ?>  
                       
    <div class="header_rp">
      <nav>
        <?php if (isset($page['header_menu'])): ?> 
        <div class="menu-main-menu-container">
          <?php print render($page['header_menu']); ?>    	
        </div>
        <?php endif; ?>
        
        <?php if (theme_get_setting('header_search') == '1'): ?>
        <div class="search_fadder"></div>
        <div class="header_search">
          <?php $block = module_invoke('search', 'block_view', 'search'); print render($block); ?>
	      </div>  
	      <?php endif; ?>              
      </nav>     
      <?php if (theme_get_setting('header_search') == '1'): ?>       
      <a class="search_toggler" href="#"></a>
      <?php endif; ?>
    </div>
    <div class="clear"></div>
  
  </div>
</header>
<?php print render($page['fullscreen']); ?>

<div class="main_wrapper <?php if (render($page['fullscreen'])){ print "hidden"; } ?>">
  <?php if ($page['left_sidebar'] || $page['right_sidebar']): ?><div class="bg_sidebar <?php if ($page['left_sidebar']) { print "is_left-sidebar"; }?> <?php if ($page['right_sidebar']) { print "is_right-sidebar";} ?>"></div><?php endif; ?>  
  <div class="content_wrapper">
    <div class="container main-container">
      <div class="content_block row <?php if (!$page['left_sidebar'] && $page['right_sidebar']) { print "right-sidebar"; } if ($page['left_sidebar'] && !$page['right_sidebar']) { print "left-sidebar"; } if (!$page['left_sidebar'] && !$page['right_sidebar']) { print "no-sidebar"; } ?>">
        <div class="fl-container <?php if ($page['right_sidebar']) { print "hasRS"; } ?>">
          <div class="row">
            
            <?php if ($messages): ?>
					    <div id="messages"><div class="section clearfix">
					      <?php print $messages; ?>
					    </div></div> <!-- /.section, /#messages -->
					  <?php endif; ?>
            
            <?php if ($tabs): ?>
			        <div class="tabs">
			          <?php print render($tabs); ?>
			        </div>
			      <?php endif; ?>
			      <?php print render($page['help']); ?>
			      <?php if ($action_links): ?>
			        <ul class="action-links">
			          <?php print render($action_links); ?>
			        </ul>
			      <?php endif; ?>
			      <div id="content" class="posts-block <?php if ($page['left_sidebar']) { print "hasLS"; } ?>">
              <?php print render($page['content']); ?>
			      </div>
              
          
		        <?php if ($page['left_sidebar']): ?>
		        <div class="left-sidebar-block">
		          <?php print render($page['left_sidebar']); ?> 
		        </div>
		        <?php endif; ?>
		        
		      </div>
        </div><!-- .fl-container -->     
        
        <?php if ($page['right_sidebar']): ?>
        <div class="right-sidebar-block">
          <?php print render($page['right_sidebar']); ?> 
        </div>
        <?php endif; ?>
        
      </div>
    </div>
  </div>
</div>  
<?php print render($page['after_content']); ?>  

<?php if (render($page['footer_bottom_left']) || render($page['footer_bottom_right']) || render($page['footer_1']) || render($page['footer_2']) || render($page['footer_3']) || render($page['footer_4'])): ?>          
<footer><!-- .main-wrapper -->
  <div class="footer_wrapper container">
    
    <?php if (render($page['footer_1']) || render($page['footer_2']) || render($page['footer_3']) || render($page['footer_4'])): ?>   
    <div class="row">
      <?php if (render($page['footer_1'])): ?>
      <div class="span3">
        <?php print render($page['footer_1']); ?> 
      </div>
      <?php endif; ?>
      <?php if (render($page['footer_2'])): ?>
      <div class="span3">
        <?php print render($page['footer_2']); ?> 
      </div>
      <?php endif; ?>
      <?php if (render($page['footer_3'])): ?>
      <div class="span3">
        <?php print render($page['footer_3']); ?> 
      </div>
      <?php endif; ?>
      <?php if (render($page['footer_4'])): ?>
      <div class="span3">
        <?php print render($page['footer_4']); ?> 
      </div>
      <?php endif; ?>
    </div>
    <?php endif; ?>
    
    <?php if (render($page['footer_bottom_left']) || render($page['footer_bottom_right'])): ?>   
    <div class="row">
      <?php if (render($page['footer_bottom_left'])): ?>
      <div class="span6">
        <?php print render($page['footer_bottom_left']); ?> 
      </div>
      <?php endif; ?>
      <?php if (render($page['footer_bottom_right'])): ?>
      <div class="span6">
        <?php print render($page['footer_bottom_right']); ?> 
      </div>
      <?php endif; ?>
    </div>
    <?php endif; ?>
  </div>
</footer>    
<?php endif; ?>