jQuery(document).ready(function($){
	"use strict";
	jQuery('html').addClass('fullscreen_page');
  jQuery('#ribbon_swipe').on("swipeleft",function(e){
		next_slide();
	});
	jQuery('#ribbon_swipe').on("swiperight",function(e){
		prev_slide();
	});			
	jQuery('.ltl_prev').click(function(){
		prev_slide();
	});
	jQuery('.ltl_next').click(function(){
		next_slide();
	});
	jQuery('.btn_prev').click(function(){
		prev_slide();
	});
	jQuery('.btn_next').click(function(){
		next_slide();
	});

	jQuery('.slide1').addClass('currentStep');
	jQuery('.slider_caption').text(jQuery('.currentStep').attr('data-title'));
	
	ribbon_setup();
});	
jQuery(window).resize(function($){
	"use strict";
	ribbon_setup();
	setTimeout("ribbon_setup()",500);
	setTimeout("ribbon_setup()",1000);			
});	
jQuery(window).load(function($){
	"use strict";
	ribbon_setup();
	setTimeout("ribbon_setup()",700);
});	

function ribbon_setup() {
	"use strict";
	var setHeight = jQuery(window).height() - jQuery('.main_header').height() - 20;
	var setHeight2 = jQuery(window).height() - jQuery('.main_header').height() - jQuery('.slider_info').height() - 20;
	jQuery('.fs_grid_gallery').height(jQuery(window).height() - jQuery('.main_header').height()-1);
	jQuery('.currentStep').removeClass('currentStep');
	jQuery('.slide1').addClass('currentStep');
	jQuery('.slider_caption').text(jQuery('.currentStep').attr('data-title'));
	jQuery('.num_current').text('1');
	
	jQuery('.num_all').text(jQuery('.ribbon_list li').size());			
	jQuery('.ribbon_wrapper').height(setHeight2);
	jQuery('.ribbon_list .slide_wrapper').height(setHeight2);
	jQuery('.ribbon_list').height(setHeight2).width(20).css('left', 0);
	jQuery('.fs_grid_gallery').width(jQuery(window).width());
	jQuery('.ribbon_list').find('li').each(function(){
		jQuery('.ribbon_list').width(jQuery('.ribbon_list').width()+jQuery(this).width());
		jQuery(this).attr('data-offset',jQuery(this).offset().left);
		jQuery(this).width(jQuery(this).find('img').width()+parseInt(jQuery(this).find('.slide_wrapper').css('margin-left')));
	});
	var max_step = -1*(jQuery('.ribbon_list').width()-jQuery(window).width());
}
function prev_slide() {
	"use strict";
	var max_step = -1*(jQuery('.ribbon_list').width()-jQuery(window).width());
	var current_slide = parseInt(jQuery('.currentStep').attr('data-count'));
	current_slide--;
	if (current_slide < 1) {
		current_slide = jQuery('.ribbon_list').find('li').size();
	}
	jQuery('.currentStep').removeClass('currentStep');
	jQuery('.num_current').text(current_slide);
	jQuery('.slide'+current_slide).addClass('currentStep');
	jQuery('.slider_caption').text(jQuery('.currentStep').attr('data-title'));
	if (-1*jQuery('.slide'+current_slide).attr('data-offset') > max_step) {
		jQuery('.ribbon_list').css('left', -1*jQuery('.slide'+current_slide).attr('data-offset'));
	} else {
		jQuery('.ribbon_list').css('left', max_step);
	}
}
function next_slide() {
	"use strict";
	var max_step = -1*(jQuery('.ribbon_list').width()-jQuery(window).width());
	var current_slide = parseInt(jQuery('.currentStep').attr('data-count'));
	current_slide++;
	if (current_slide > jQuery('.ribbon_list').find('li').size()) {
		current_slide = 1
	}
	jQuery('.currentStep').removeClass('currentStep');
	jQuery('.num_current').text(current_slide);
	jQuery('.slide'+current_slide).addClass('currentStep');
	jQuery('.slider_caption').text(jQuery('.currentStep').attr('data-title'));
	if (-1*jQuery('.slide'+current_slide).attr('data-offset') > max_step) {
		jQuery('.ribbon_list').css('left', -1*jQuery('.slide'+current_slide).attr('data-offset'));
	} else {
		jQuery('.ribbon_list').css('left', max_step);
	}
}