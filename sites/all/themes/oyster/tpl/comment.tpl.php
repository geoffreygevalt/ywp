<?php
/**
 * @file comment.tpl.php
 * Oyster's comment template.
 */
 
global $parent_root;
?>

<ol class="commentlist">
  <li>
    <div class="stand_comment">
		  <div class="commentava wrapped_img">
		    <?php 
		      if (!$picture) {
		        echo '<img src="'.$parent_root.'/img/anon.png" alt="anon">'; 
		      }
		      else { 
		        print $picture;   
		      }
		    ?>
		  </div>
		  <div class="thiscommentbody">
        <div class="comment_info">
            <h6 class="author_name"><?php print $author; ?> </h6>
            <h6 class="date"><?php print format_date($comment->created, 'custom', 'M d, Y'); ?></h6>
            
        </div>
        <div class="comment-content"<?php print $content_attributes; ?>>
		      <div class="row">
		      <p>
		      <?php hide($content['links']); print render($content); ?>
		      </p>
		      </div>
		      <?php if ($signature): ?>
		       <div class="user-signature clearfix">
		         <?php print $signature ?>
		      </div>
		     <?php endif; ?>
		    </div>
<?php if (!empty($content['links'])) { print render($content['links']); } ?>
      </div>
      <div class="clear"></div>
    </div>  
  </li>
</ol>