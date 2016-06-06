jQuery(window).resize(function () {
	"use strict";
	jQuery('.is_masonry').masonry();
    });
jQuery(document).ready(function($){
	"use strict";
	jQuery('.is_masonry').masonry();
	setTimeout("jQuery('.is_masonry').masonry();",1000);
	setTimeout("jQuery('.is_masonry').masonry();",2000);			
	jQuery('.pf_output_container').each(function(){
		if (jQuery(this).html() == '') {
			jQuery(this).parents('.fw_preview_wrapper').addClass('no_pf');
		} else {
			jQuery(this).parents('.fw_preview_wrapper').addClass('has_pf');
		}
	});						
});

jQuery(document).ready(function($){
  "use strict";	

	$('.main_wrapper').addClass('fullwidth');
	$('footer').addClass('fullwidth');
	
	

});