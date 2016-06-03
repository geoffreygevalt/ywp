jQuery(document).ready(function($){
	"use strict";
	$('.main_wrapper').addClass('fullwidth');
	jQuery('.fw_background').height(jQuery(window).height());			
	jQuery('.main_header').removeClass('hided');
	jQuery('.fullscreen_block').addClass('loaded');
	if (jQuery(window).width() > 1024) {
		if (jQuery('.bg_video').size() > 0) {
			if (((jQuery(window).height()+150)/9)*16 > jQuery(window).width()) {				
				jQuery('iframe').height(jQuery(window).height()+150).width(((jQuery(window).height()+150)/9)*16);
				jQuery('iframe').css({'margin-left' : (-1*jQuery('iframe').width()/2)+'px', 'top' : "-75px", 'margin-top' : '0px'});
			} else {
				jQuery('iframe').width(jQuery(window).width()).height(((jQuery(window).width())/16)*9);
				jQuery('iframe').css({'margin-left' : (-1*jQuery('iframe').width()/2)+'px', 'margin-top' : (-1*jQuery('iframe').height()/2)+'px', 'top' : '50%'});
			}
		}
	} else if (jQuery(window).width() < 760) {
		jQuery('.bg_video').height(jQuery(window).height()-jQuery('.main_header').height());
		jQuery('iframe').height(jQuery(window).height()-jQuery('.main_header').height());
	} else {
		jQuery('.bg_video').height(jQuery(window).height() - jQuery('.main_header').height());
		jQuery('.bg_video').css({'margin-top': jQuery('.main_header').height()+'px'});
		jQuery('iframe').height(jQuery(window).height() - jQuery('.main_header').height());				
	}
	jQuery('html').addClass('without_border');
});
jQuery(window).resize(function() {
	"use strict";
	jQuery('.fw_background').height(jQuery(window).height());
	if (jQuery(window).width() > 1024	) {
		if (jQuery('.bg_video').size() > 0) {
			if (((jQuery(window).height()+150)/9)*16 > jQuery(window).width()) {
				jQuery('iframe').height(jQuery(window).height()+150).width(((jQuery(window).height()+150)/9)*16);
				jQuery('iframe').css({'margin-left' : (-1*jQuery('iframe').width()/2)+'px', 'top' : "-75px", 'margin-top' : '0px'});
			} else {
				jQuery('iframe').width(jQuery(window).width()).height(((jQuery(window).width())/16)*9);
				jQuery('iframe').css({'margin-left' : (-1*jQuery('iframe').width()/2)+'px', 'margin-top' : (-1*jQuery('iframe').height()/2)+'px', 'top' : '50%'});
			}
		}
	} else if (jQuery(window).width() < 760) {
		jQuery('.bg_video').height(jQuery(window).height()-jQuery('.main_header').height());
		jQuery('iframe').height(jQuery(window).height()-jQuery('.main_header').height());
	} else {
		jQuery('.bg_video').height(jQuery(window).height() - jQuery('.main_header').height());
		jQuery('.bg_video').css({'margin-top': jQuery('.main_header').height()+'px'});
		jQuery('iframe').height(jQuery(window).height() - jQuery('.main_header').height());				
	}
});		