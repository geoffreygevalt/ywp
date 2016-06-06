<div class="blogpost_share">
  <span><?php print t('Share this:'); ?></span>
  <a href="http://www.facebook.com/share.php?u=<?php print $link; ?>" class="share_facebook" target="_blank"><i class="stand_icon icon-facebook-square"></i></a>
  <?php if ($image != NULL): ?>
  <a href="http://pinterest.com/pin/create/button/?url=<?php print $link; ?>&media=<?php print $image; ?>" class="share_pinterest" target="_blank"><i class="stand_icon icon-pinterest"></i></a> 
  <?php endif; ?>                                                           
  <a href="https://twitter.com/intent/tweet?text=<?php print $title; ?>&url=<?php print $link; ?>" class="share_tweet" target="_blank"><i class="stand_icon icon-twitter"></i></a>                                                       
  <a href="https://plus.google.com/share?url=<?php print $link; ?>" class="share_gplus" target="_blank"><i class="icon-google-plus-square"></i></a>
  <div class="clear"></div>
</div>