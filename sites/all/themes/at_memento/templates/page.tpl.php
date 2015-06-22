<?php // AT Memento ?>
<div id="page-wrapper">
  <div id="page" class="<?php print $classes; ?>">

    <div id="menu-top-wrapper">
      <div class="container clearfix">
        <?php if ($menu_bar_top = render($page['menu_bar_top'])): ?>
          <?php print $menu_bar_top; ?>
        <?php endif; ?>
      </div>
    </div>

    <div id="header-wrapper" class="<?php print $page['header'] ? 'with-header-region' : 'no-header-region'; ?>">
      <div class="container clearfix">

        <header<?php print $header_attributes; ?>>

          <?php if ($site_logo || $site_name || $site_slogan): ?>
            <!-- !Branding -->
            <div<?php print $branding_attributes; ?>>

              <?php if ($site_logo): ?>
                <div id="logo">
                  <?php print $site_logo; ?>
                </div>
              <?php endif; ?>

              <?php if ($site_name || $site_slogan): ?>
                <!-- !Site name and Slogan -->
                <div<?php print $hgroup_attributes; ?>>

                  <?php if ($site_name): ?>
                    <h1<?php print $site_name_attributes; ?>><?php print $site_name; ?></h1>
                  <?php endif; ?>

                  <?php if ($site_slogan): ?>
                    <h2<?php print $site_slogan_attributes; ?>><?php print $site_slogan; ?></h2>
                  <?php endif; ?>

                </div>
              <?php endif; ?>

            </div>
          <?php endif; ?>

          <?php if ($menu_bar = render($page['menu_bar'])): ?>
            <div id="menu-wrapper">
              <?php print $menu_bar; ?>
            </div>
          <?php endif; ?>

          <?php if ($header = render($page['header'])): ?>
            <div id="region-header-wrapper" class="clearfix">
              <?php print $header; ?>
            </div>
          <?php endif; ?>

        </header>
      </div>
    </div>

    <?php if ($messages || $page['help']): ?>
      <div id="messages-help-wrapper" class="clearfix">
        <div class="container clearfix">
          <?php print $messages; ?>
          <?php print render($page['help']) ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($secondary_content = render($page['secondary_content'])): ?>
      <div id="secondary-content-wrapper">
        <div class="container clearfix">
          <?php print $secondary_content; ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($tertiary_content = render($page['tertiary_content'])): ?>
      <div id="tertiary-content-wrapper">
        <div class="container clearfix">
          <?php print $tertiary_content; ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if (
      $page['three_33_top'] ||
      $page['three_33_first'] ||
      $page['three_33_second'] ||
      $page['three_33_third'] ||
      $page['three_33_bottom']
      ): ?>
      <div id="sub-panels-wrapper">
        <div class="container clearfix">
          <!-- Three column 3x33 Gpanel -->
          <div class="at-panel gpanel panel-display three-3x33 clearfix">
            <?php print render($page['three_33_top']); ?>
            <?php print render($page['three_33_first']); ?>
            <?php print render($page['three_33_second']); ?>
            <?php print render($page['three_33_third']); ?>
            <?php print render($page['three_33_bottom']); ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <div id="content-wrapper">
      <div class="container">

        <?php if ($breadcrumb): ?>
          <section id="breadcrumb" class="clearfix">
            <?php print $breadcrumb; ?>
          </section>
        <?php endif; ?>

        <div id="columns">
          <div class="columns-inner clearfix">
            <div id="content-column">
              <div class="content-inner">

                <?php print render($page['highlighted']); ?>

                <<?php print $tag; ?> id="main-content">

                  <?php print render($title_prefix); ?>
                  <?php if ($title && !isset($node)): ?>
                    <header>
                      <h1 id="page-title"><?php print $title; ?></h1>
                    </header>
                  <?php endif; ?>
                  <?php print render($title_suffix); ?>

                  <?php if ($primary_local_tasks || $secondary_local_tasks || $action_links): ?>
                    <div id="tasks" class="clearfix">
                      <?php if ($primary_local_tasks): ?>
                        <ul class="tabs primary clearfix"><?php print render($primary_local_tasks); ?></ul>
                      <?php endif; ?>
                      <?php if ($secondary_local_tasks): ?>
                        <ul class="tabs secondary clearfix"><?php print render($secondary_local_tasks); ?></ul>
                      <?php endif; ?>
                      <?php if ($action_links = render($action_links)): ?>
                        <ul class="action-links clearfix"><?php print $action_links; ?></ul>
                      <?php endif; ?>
                    </div>
                  <?php endif; ?>

                  <div id="content" class="clearfix"><?php print render($page['content']); ?></div>

                </<?php print $tag; ?>>

                <?php print render($page['content_aside']); ?>

              </div>
            </div>

            <?php print render($page['sidebar_first']); ?>
            <?php print render($page['sidebar_second']); ?>

          </div>
        </div>
      </div>
    </div>

    <?php if (
      $page['two_50_top'] ||
      $page['two_50_first'] ||
      $page['two_50_second'] ||
      $page['two_50_bottom']
      ): ?>
      <div id="bi-panels-wrapper">
        <div class="container clearfix">
          <!-- Two column 2x50 Gpanel -->
          <div class="at-panel gpanel panel-display two-50 clearfix">
            <?php print render($page['two_50_top']); ?>
            <?php print render($page['two_50_first']); ?>
            <?php print render($page['two_50_second']); ?>
            <?php print render($page['two_50_bottom']); ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if (
      $page['five_first'] ||
      $page['five_second'] ||
      $page['five_third'] ||
      $page['five_fourth'] ||
      $page['five_fifth']
      ): ?>
      <div id="quint-panels-wrapper">
        <div class="container clearfix">
          <!-- Five column Gpanel -->
          <div class="at-panel gpanel panel-display five-5x20 clearfix">
            <div class="panel-row row-1 clearfix">
              <?php print render($page['five_first']); ?>
              <?php print render($page['five_second']); ?>
            </div>
            <div class="panel-row row-2 clearfix">
              <?php print render($page['five_third']); ?>
              <?php print render($page['five_fourth']); ?>
              <?php print render($page['five_fifth']); ?>
            </div>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <div id="page-footer">
      <div class="texture-overlay">

        <?php if (
          $page['four_first'] ||
          $page['four_second'] ||
          $page['four_third'] ||
          $page['four_fourth']
          ): ?>
          <div id="footer-panels-wrapper">
            <div class="container clearfix">
              <!-- Four column Gpanel -->
              <div class="at-panel gpanel panel-display four-4x25 clearfix">
                <div class="panel-row row-1 clearfix">
                  <?php print render($page['four_first']); ?>
                  <?php print render($page['four_second']); ?>
                </div>
                <div class="panel-row row-2 clearfix">
                  <?php print render($page['four_third']); ?>
                  <?php print render($page['four_fourth']); ?>
                </div>
              </div>
            </div>
          </div>
        <?php endif; ?>

        <?php if ($footer = render($page['footer'])): ?>
          <div id="footer-wrapper">
            <div class="container clearfix">
              <footer class="clearfix">
                <?php print $footer; ?>
              </footer>
             </div>
           </div>
        <?php endif; ?>

      </div>
    </div>

    <?php if ($collapsible = render($page['collapsible'])): ?>
      <section id="section-collapsible" class="section-collapsible clearfix">
        <h2 class="collapsible-toggle">
          <a href="#"><?php print t('Toggle collapsible region'); ?></a>
        </h2>
        <?php print $collapsible; ?>
      </section>
    <?php endif; ?>

  </div>
</div>
