<?php
// memento

/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function at_memento_form_system_theme_settings_alter(&$form, &$form_state)  {

  // Include a hidden form field with the current release information
  $form['at-release'] = array(
    '#type' => 'hidden',
    '#default_value' => '7.x-3.x',
  );

  // Tell the submit function its safe to run the color inc generator
  // if running on AT Core 7.x-3.x
  $form['at-color'] = array(
    '#type' => 'hidden',
    '#default_value' => TRUE,
  );

  // EXTENSIONS
  $enable_extensions = isset($form_state['values']['enable_extensions']);
  if (($enable_extensions && $form_state['values']['enable_extensions'] == 1) || (!$enable_extensions && $form['at-settings']['extend']['enable_extensions']['#default_value'] == 1)) {

    // Remove options not usable or applicable to this design.
    $form['at']['modify-output']['design']['global_gutter_width'] = array(
      '#access' => FALSE,
    );
    // Remove option to use full width wrappers
    $form['at']['modify-output']['design']['page_full_width_wrappers'] = array(
      '#access' => FALSE,
      '#default_value' => 0,
    );

    // Content displays
    $form['at']['content_display'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content Displays'),
      '#description' => t('<h3>Content Displays</h3><p>Display the front page or taxonomy term pages as a grid. The grid is responsive and items will wrap as the screen size degreases. These settings use the normal node teasers and format them as a grid. Article links (such as the <em>Read More</em> link) are hidden when displayed in the grid. These settings will work well with the responsive design, unlike a Views table grid which does not.</p>'),
    );
    $form['at']['content_display']['content_display_grids']['frontpage'] = array(
      '#type' => 'fieldset',
      '#title' => t('Frontpage'),
      '#description' => t('<h3>Frontpage</h3>'),
    );
    $form['at']['content_display']['content_display_grids']['frontpage']['content_display_grids_frontpage'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display front page teasers as a grid'),
      '#default_value' => theme_get_setting('content_display_grids_frontpage'),
    );
    $form['at']['content_display']['content_display_grids']['frontpage']['content_display_grids_frontpage_colcount'] = array(
      '#type' => 'select',
      '#title' => t('Enter the max number of grid columns'),
      '#default_value' => theme_get_setting('content_display_grids_frontpage_colcount'),
      '#options' => array(
        'fpcc-2' => t('2'),
        'fpcc-3' => t('3'),
        'fpcc-4' => t('4'),
        'fpcc-5' => t('5'),
        'fpcc-6' => t('6'),
        'fpcc-7' => t('7'),
        'fpcc-8' => t('8'),
      ),
      '#states' => array (
        'visible' => array (
          'input[name="content_display_grids_frontpage"]' => array ('checked' => TRUE)
        )
      )
    );
    $form['at']['content_display']['content_display_grids']['taxonomy'] = array(
      '#type' => 'fieldset',
      '#title' => t('Taxonomy'),
      '#description' => t('<h3>Taxonomy Pages</h3>'),
    );
    $form['at']['content_display']['content_display_grids']['taxonomy']['content_display_grids_taxonomy_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display taxonomy page teasers as a grid'),
      '#default_value' => theme_get_setting('content_display_grids_taxonomy_pages'),
    );
    $form['at']['content_display']['content_display_grids']['taxonomy']['content_display_grids_taxonomy_pages_colcount'] = array(
      '#type' => 'select',
      '#title' => t('Enter the max number of grid columns'),
      '#default_value' => theme_get_setting('content_display_grids_taxonomy_pages_colcount'),
      '#options' => array(
        'tpcc-2' => t('2'),
        'tpcc-3' => t('3'),
        'tpcc-4' => t('4'),
        'tpcc-5' => t('5'),
        'tpcc-6' => t('6'),
        'tpcc-7' => t('7'),
        'tpcc-8' => t('8'),
      ),
      '#states' => array (
        'visible' => array (
          'input[name="content_display_grids_taxonomy_pages"]' => array ('checked' => TRUE)
        )
      )
    );


    // Header layout
    $form['at']['header'] = array(
      '#type' => 'fieldset',
      '#title' => t('Header layout'),
      '#description' => t('<h3>Header layout</h3><p>Change the position of the logo, site name and slogan. Note that his will automatically alter the header region layout also. If the branding elements are centered the header region will center below them, otherwise the header region will float in the opposite direction.</p>'),
    );
    $form['at']['header']['header_layout'] = array(
      '#type' => 'radios',
      '#title' => t('Branding position'),
      '#default_value' => theme_get_setting('header_layout'),
      '#options' => array(
        'hl-l'  => t('Left'),
        'hl-r'  => t('Right'),
        'hl-c' => t('Centered'),
      ),
    );

    // Corners
    $form['at']['corners'] = array(
      '#type' => 'fieldset',
      '#title' => t('Rounded corners'),
      '#description' => t('<h3>Rounded Corners</h3><p>Rounded corners are implimented using CSS and only work in modern compliant browsers.</p>'),
    );
    $form['at']['corners']['forms'] = array(
      '#type' => 'fieldset',
      '#title' => t('Rounded corners for form elements'),
      '#description' => t('Rounded corners for form elements'),
    );
    $form['at']['corners']['forms']['corner_radius_form_input_text'] = array(
      '#type' => 'select',
      '#title' => t('Form text fields'),
      '#default_value' => theme_get_setting('corner_radius_form_input_text'),
      '#description' => t('Change the corner radius for text fields.'),
      '#options' => array(
        'itrc-0' => t('none'),
        'itrc-2' => t('2px'),
        'itrc-3' => t('3px'),
        'itrc-4' => t('4px'),
        'itrc-6' => t('6px'),
        'itrc-8' => t('8px'),
        'itrc-10' => t('10px'),
        'itrc-12' => t('12px'),
      ),
    );
    $form['at']['corners']['forms']['corner_radius_form_input_submit'] = array(
      '#type' => 'select',
      '#title' => t('Submit buttons'),
      '#default_value' => theme_get_setting('corner_radius_form_input_submit'),
      '#description' => t('Change the corner radius for submit buttons.'),
      '#options' => array(
        'isrc-0' => t('none'),
        'isrc-2' => t('2px'),
        'isrc-3' => t('3px'),
        'isrc-4' => t('4px'),
        'isrc-6' => t('6px'),
        'isrc-8' => t('8px'),
        'isrc-10' => t('10px'),
        'isrc-12' => t('12px'),
      ),
    );
    $form['at']['corners']['htc'] = array(
      '#type' => 'fieldset',
      '#title' => t('IE corners'),
    );
    $form['at']['corners']['htc']['ie_corners'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable rounded corners for Internet Explorer 6, 7 and 8'),
      '#default_value' => theme_get_setting('ie_corners'),
      '#description' => t('<p>NOTE: For this to work you must download install the <a href="!link">CSS3PIE</a> library to <code>sites/all/libraries/PIE</code>.</p><p>The path should be like this: <code>sites/all/libraries/PIE/PIE.htc</code></p><p>Then you MUST change the path in <strong>ie-htc.css</strong> to be absolute and match this path, e.g. <code>http://examplesite.com/sites/all/libraries/PIE/PIE.htc</code> - look in the <code>/css</code> folder to find this file.<p>Usage is at your own risk. Elements such as text inside other JS items such as drop menus or slideshows may be degraded in Internet Explorer.</p>', array('!link' => 'http://css3pie.com/')),
    );


    // Page
    $form['at']['pagestyles'] = array(
      '#type' => 'fieldset',
      '#title' => t('Textures'),
      '#description' => t('<h3>Textures</h3><p>Textures are small, semi-transparent images that tile to fill the entire background.</p>'),
    );
    $form['at']['pagestyles']['textures']['bgo'] = array(
      '#type' => 'fieldset',
      '#title' => t('Main Background'),
      '#description' => t('<h3>Main Background Overlay</h3><p>Change the overlay texture for the entire background, or choose none.</p>'),
    );
    $form['at']['pagestyles']['textures']['bgo']['main_background_overlay'] = array(
      '#type' => 'select',
      '#title' => t('Select texture'),
      '#default_value' => theme_get_setting('main_background_overlay'),
      '#options' => array(
        'bgo-n'   => t('None'),
        'bgo-h1'  => t('Hatch #1'),
        'bgo-h2'  => t('Hatch #2'),
        'bgo-h3'  => t('Hatch #3'),
        'bgo-h4'  => t('Hatch #4'),
        'bgo-dg'  => t('Diagonals'),
        'bgo-ds'  => t('Dots'),
      ),
    );
    $form['at']['pagestyles']['textures']['fpo'] = array(
      '#type' => 'fieldset',
      '#title' => t('Feature Panel'),
      '#description' => t('<h3>Feature Panel Overlay</h3><p>Change the overlay texture for the Features Panel, or choose none.</p>'),
    );
    $form['at']['pagestyles']['textures']['fpo']['features_overlay'] = array(
      '#type' => 'select',
      '#title' => t('Select texture'),
      '#default_value' => theme_get_setting('features_overlay'),
      '#options' => array(
        'fpo-n'   => t('None'),
        'fpo-h1'  => t('Hatch #1'),
        'fpo-h2'  => t('Hatch #2'),
        'fpo-h3'  => t('Hatch #3'),
        'fpo-h4'  => t('Hatch #4'),
        'fpo-dg'  => t('Diagonals'),
        'fpo-ds'  => t('Dots'),
      ),
    );
    $form['at']['pagestyles']['textures']['pfo'] = array(
      '#type' => 'fieldset',
      '#title' => t('Footer'),
      '#description' => t('<h3>Footer Overlay</h3><p>Change the overlay texture for the Footer area, or choose none.</p>'),
    );
    $form['at']['pagestyles']['textures']['pfo']['footer_overlay'] = array(
      '#type' => 'select',
      '#title' => t('Select texture'),
      '#default_value' => theme_get_setting('footer_overlay'),
      '#options' => array(
        'pfo-n'   => t('None'),
        'pfo-h1'  => t('Hatch #1'),
        'pfo-h2'  => t('Hatch #2'),
        'pfo-h3'  => t('Hatch #3'),
        'pfo-h3'  => t('Hatch #4'),
        'pfo-dg'  => t('Diagonals'),
        'pfo-ds'  => t('Dots'),
      ),
    );


    // Menus
    $form['at']['menu_styles'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu Styles'),
    );
    $form['at']['menu_styles']['bullets'] = array(
      '#type' => 'fieldset',
      '#title' => t('Menu Bullets'),
      '#description' => t('<h3>Menu Bullets</h3><p>This setting allows you to customize the bullet images used on menus items. Bullet images only show on normal vertical block menus.</p>'),
    );
    $form['at']['menu_styles']['bullets']['menu_bullets'] = array(
      '#type' => 'select',
      '#title' => t('Menu Bullets'),
      '#default_value' => theme_get_setting('menu_bullets'),
      '#options' => array(
        'mb-n' => t('None'),
        'mb-dd'  => t('Drupal default'),
        'mb-ah'  => t('Arrow head'),
        'mb-ahl' => t('Arrow head light'),
        'mb-ad'  => t('Double arrow head'),
        'mb-ca'  => t('Circle arrow'),
        'mb-fa'  => t('Fat arrow'),
        'mb-sa'  => t('Skinny arrow'),
      ),
    );
  }
}
