jQuery(document).ready(function(){
	"use strict";
	if (jQuery(window).width() < 760) {
		jQuery('.is_masonry').removeClass('is_masonry').addClass('listing_gallery');
		jQuery('.gallery_type_selector').hide();
	}
	jQuery('.is_masonry').masonry();
	jQuery('.btn_gallery_masonry').click(function(){
		jQuery('.gallery_type_selector a').removeClass('active');
		jQuery('.listing_gallery').removeClass('listing_gallery');
		jQuery(this).addClass('active');
		jQuery('.content_gallery').addClass('is_masonry');
		setTimeout("jQuery('.is_masonry').masonry()",250);
		setTimeout("jQuery('.is_masonry').masonry()",500);
		setTimeout("jQuery('.is_masonry').masonry()",1000);				
	});
	jQuery('.btn_gallery_column').click(function(){
		jQuery('.gallery_type_selector a').removeClass('active');
		jQuery(this).addClass('active');
		jQuery('.content_gallery').removeClass('is_masonry');
		jQuery('.content_gallery').addClass('listing_gallery');
	});
	setTimeout("jQuery('.is_masonry').masonry()",3000);	
});

jQuery(window).load(function () {
  "use strict";
	jQuery('.is_masonry').masonry();
	setTimeout("jQuery('.is_masonry').masonry()",1000);
});
jQuery(window).resize(function () {
	"use strict";
	jQuery('.is_masonry').masonry();
	setTimeout("jQuery('.is_masonry').masonry()",500);
	setTimeout("jQuery('.is_masonry').masonry()",1000);
});