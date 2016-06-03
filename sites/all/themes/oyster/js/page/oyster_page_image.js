jQuery(document).ready(function($){
  "use strict";	
 	$('.main_wrapper').addClass('fullwidth');
 	
 	jQuery('.fw_background').height(jQuery(window).height());
	jQuery('.main_header').removeClass('hided');
	jQuery('.fullscreen_block').addClass('loaded');
	jQuery('html').addClass('without_border');
});
jQuery(window).resize(function() {
	"use strict";
	jQuery('.fw_background').height(jQuery(window).height());		
});
