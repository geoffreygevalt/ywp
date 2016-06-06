jQuery(document).ready(function($) {	
	"use strict";			
	jQuery('html').addClass('without_border');				
	
	var data_width = 100/jQuery('.strip-menu.vertical').attr('data-count');
	jQuery('.strip-menu.vertical').attr('data-width', data_width);
	jQuery('.strip-menu.vertical .strip-item').css({'width': data_width + '%'});				
	
	if (jQuery(window).width() < 1025 && jQuery(window).width() > 760) {
		jQuery('.mobile-hover').click(function(){
			jQuery('.hovered').removeClass('hovered');
			jQuery(this).parent('.strip-item').addClass('hovered');
		});
	}
	if (jQuery(window).width() < 760 && jQuery('.strip-menu').hasClass('vertical')) {
		jQuery('.strip-menu').removeClass('vertical').addClass('was_vert');
	}
	strip_setup();
});	
jQuery(window).resize(function(){
	"use strict";
	strip_setup();
	setTimeout("strip_setup()",500);
	setTimeout("strip_setup()",1000);
});
function strip_setup() {
	"use strict";				
	if (jQuery('.strip-menu').hasClass('vertical')) {
		jQuery('.strip-menu').height(jQuery(window).height() - jQuery('.main_header').height());
		jQuery('.strip-menu').find('h1').each(function(){
			jQuery(this).width(jQuery('.strip-item').height());
			jQuery(this).css({'margin-top' : (jQuery('.strip-item').height() - jQuery(this).height())/2, 'margin-left' : -1*(jQuery(this).width() - jQuery('.strip-item').width())/2});
		});
	} else {
		jQuery('.strip-menu').height(jQuery(window).height() - jQuery('.main_header').height());
		jQuery('.strip-menu').find('.strip-text').each(function(){						
			jQuery(this).css('margin-top' , (jQuery('.strip-item').height() - jQuery(this).height()-13)/2);
		});					
	}
}