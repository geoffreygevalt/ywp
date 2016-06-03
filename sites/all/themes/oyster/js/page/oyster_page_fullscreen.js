jQuery(document).ready(function($){
	"use strict";
	$('.main_wrapper').addClass('fullwidth oyster_fullwidth');			
	centerWindow();
	if (jQuery(window).width() > 760) {
		jQuery('html').addClass('without_border');
	}
});
jQuery(window).load(function(){
	"use strict";
	centerWindow();
});
jQuery(window).resize(function(){
	"use strict";
	centerWindow();
	setTimeout('centerWindow()',500);
	setTimeout('centerWindow()',1000);
});
var setTop = 0;
function centerWindow() {
	"use strict";
	setTop = (jQuery(window).height() - jQuery('.fw_content_wrapper').height() - jQuery('.main_header').height())/2+jQuery('.main_header').height();
	if (setTop < jQuery('.main_header').height()+50) {
		jQuery('.fw_content_wrapper').addClass('fixed');
		jQuery('body').addClass('addPadding');
		jQuery('.fw_content_wrapper').css('top', jQuery('.main_header').height()+50+'px');
	} else {
		jQuery('.fw_content_wrapper').css('top', setTop +'px');
		jQuery('.fw_content_wrapper').removeClass('fixed');
		jQuery('body').removeClass('addPadding');
	}
}