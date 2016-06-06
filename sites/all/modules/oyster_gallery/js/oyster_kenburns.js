jQuery(document).ready(function(){
	
	jQuery('html').addClass('without_border');
	jQuery('#kenburns').attr('width', jQuery(window).width());
	jQuery('#kenburns').attr('height', jQuery(window).height()-jQuery('.main_header').height());
	jQuery('#kenburns').kenburns({
		images: gallery_set,
		frames_per_second: 30,
		display_time: 5000,
		fade_time: 1000,
		zoom: 1.2,
		background_color:'#000000'
	});
	jQuery('#kenburns').css('top', jQuery('.main_header').height()+'px');
});

function kenburns_resize() {
	
	jQuery('.gallery_kenburns').append('<canvas id=\"kenburns\"><p>Your browser does not support canvas!</p></canvas>');
	jQuery('#kenburns').attr('width', jQuery(window).width());
	jQuery('#kenburns').attr('height', jQuery(window).height()-jQuery('.main_header').height());
		jQuery('#kenburns').kenburns({
			images: gallery_set,
			frames_per_second: 30,
			display_time: 5000,
			fade_time: 1000,
			zoom: 1.2,
			background_color:'#000000'
		});				
		jQuery('#kenburns').css('top', jQuery('.main_header').height()+'px');
}
jQuery(window).resize(function(){ 
	
	jQuery('#kenburns').remove();
	setTimeout('kenburns_resize()',300);
});		
