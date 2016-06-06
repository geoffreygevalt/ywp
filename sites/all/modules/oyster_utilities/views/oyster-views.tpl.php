<?php switch ($view->style_options['oyster_views']['optionset']):
	case 'grid1': ?>
    <div class="fullscreen_block">
    <div class="fs_blog_module image-grids">
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div></div><div class="preloader"></div>
  <?php break; ?>
  <?php case 'grid2': ?>
    <div class="fullscreen_block fs_grid_block">
    <div class="fullscreen-gallery">
    <div class="fs_grid_gallery fs_grid_portfolio">
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div></div></div><div class="preloader"></div>
  <?php break; ?>
  <?php case 'masonry': ?>
    <div class="fullscreen_block">
    <div class="fs_blog_module image-grid">
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div></div><div class="preloader"></div>
  <?php break; ?>
  <?php case '1col': ?>
    <div class="portfolio_block image-grid columns1 portf_columns">
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div>
  <?php break; ?>
  <?php case '2col': ?>
    <div class="portfolio_block image-grid columns2 portf_columns">
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div>
  <?php break; ?>
  <?php case '3col': ?>
    <div class="portfolio_block image-grid columns3 portf_columns">
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div>
  <?php break; ?>
  <?php case '4col': ?>
    <div class="portfolio_block image-grid columns4 portf_columns">
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div>
  <?php break; ?>
  <?php case 'filter': ?>
    <ul class="optionset" data-option-key="filter">
    <li class="selected"><a href="#filter" data-option-value="*"><?php print t('All Works'); ?></a></li>
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </ul>
  <?php break; ?>
  <?php case 'blog-full'; ?>
    <div class="fullscreen_block">
    <div class="fs_blog_module is_masonry this_is_blog">
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div></div><div class="preloader"></div>';
  <?php break; ?>
  <?php case 'cloud': ?>
    <div class="widget_tag_cloud">
    <div class="tagcloud">
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div></div>
  <?php break; ?>
  <?php default:  ?>
    <div>
    <?php foreach ( $rows as $id => $row ): ?>
      <?php print $row; ?>
    <?php endforeach; ?>
    </div>
  <?php break; ?>
<?php endswitch; ?>