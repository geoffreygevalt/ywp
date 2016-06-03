jQuery(document).ready(function($){
	"use strict";
	jQuery('html').addClass('fullscreen_page sticky_menu');
	$('.main_wrapper').addClass('fullwidth');
	
	if (jQuery('.fl-container').size() > 0) {
		jQuery('.fw_post_info').click(function(){
			jQuery('html, body').stop().animate({
				0: jQuery(jQuery('.content_wrapper')).offset().top-10
			}, 500);					
		});
	} else {
		jQuery('.fw_post_info').hide();
	}
			
	video_setup();
});	
jQuery(window).resize(function($){
	"use strict";
	video_setup();
});	
jQuery(window).load(function($){
	"use strict";
	video_setup();
});	

function video_setup() {
	"use strict";
	var setHeight2 = jQuery(window).height() - jQuery('.main_header').height() - jQuery('.slider_info').height();
	jQuery('.fs_grid_gallery').height(jQuery(window).height() - jQuery('.main_header').height()-1);
	jQuery('.ribbon_wrapper').height(setHeight2);
	jQuery('.fw_video_block').height(setHeight2-20);
	jQuery('.fw_video_block').width(((setHeight2-20)/9)*16);
}
