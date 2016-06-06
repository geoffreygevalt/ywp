var whaterWheel = jQuery("#whaterwheel"),
	allSize = jQuery('.ww_block').size();
jQuery(document).ready(function ($) {
	"use strict";
	setupWW();
	jQuery('.ww_link').click(function(){
		setSlide(parseInt(jQuery(this).attr('data-count')))
	});

	jQuery(document.documentElement).keyup(function (event) {
		if ((event.keyCode == 37) || (event.keyCode == 40)) {
			prev_ww();
		// Right Arrow or Up Arrow
		} else if ((event.keyCode == 39) || (event.keyCode == 38)) {
			next_ww();
		}	
	});

	jQuery('#ww_finger').on("swipeleft",function(){
		next_ww();
	});
	jQuery('#ww_finger').on("swiperight",function(){
		prev_ww();
	});		
        
});
function next_ww() {
	"use strict";
	cur_slide = parseInt(jQuery('.current').attr('data-count'));
	cur_slide++;
	if (cur_slide > allSize) cur_slide = 1;
	if (cur_slide < 1) cur_slide = allSize;
	setSlide(cur_slide);
}
function prev_ww() {
	"use strict";
	cur_slide = parseInt(jQuery('.current').attr('data-count'));
	cur_slide--;
	if (cur_slide > allSize) cur_slide = 1;
	if (cur_slide < 1) cur_slide = allSize;
	setSlide(cur_slide);
}

jQuery(window).load(function (){
	"use strict";
	setupWW();		
	setTimeout("setupWW()",500);
	setTimeout("setupWW()",1000);
});
jQuery(window).resize(function (){
	"use strict";
	setupWW();
	setTimeout("setupWW()",500);
	setTimeout("setupWW()",1000);
});

var atr056 = 0,
	atr078 = 0,
	atr_main = 1;
function setSlide(cur) {
	"use strict";
	if (jQuery(window).width() > 1025) {
		whaterWheel.find('img').unreflect();
	}
	if (jQuery(window).width() > 960) {
		atr056 = 0.56;
		atr078 = 0.78;
		atr_main = 1;
	} else if (jQuery(window).width() > 760 && jQuery(window).width() < 960){
		atr056 = 0.37;
		atr078 = 0.56;
		atr_main = 0.75;
	} else if (jQuery(window).width() < 760){
		atr056 = 0.3;
		atr078 = 0.5;
		atr_main = 0.75;
	}
	jQuery('.prev2').removeClass('prev2');
	jQuery('.prev').removeClass('prev');
	jQuery('.current').removeClass('current');				
	jQuery('.next').removeClass('next');
	jQuery('.next2').removeClass('next2');
	jQuery('#ww_block'+cur).addClass('current');
	if (whaterWheel.hasClass('type5')) {
		if((cur+1) > allSize) {
			jQuery('#ww_block1').addClass('next');
			jQuery('#ww_block2').addClass('next2');
		} else if ((cur+1) == allSize){
			jQuery('#ww_block'+allSize).addClass('next');
			jQuery('#ww_block1').addClass('next2');					
		} else {
			jQuery('#ww_block'+(cur+1)).addClass('next');
			jQuery('#ww_block'+(cur+2)).addClass('next2');				
		}
		if((cur-1) < 1) {
			jQuery('#ww_block'+allSize).addClass('prev');
			jQuery('#ww_block'+(allSize-1)).addClass('prev2');
		} else if ((cur-1) == 1){					
			jQuery('#ww_block1').addClass('prev');
			jQuery('#ww_block'+allSize).addClass('prev2');
		} else {
			jQuery('#ww_block'+(cur-1)).addClass('prev');
			jQuery('#ww_block'+(cur-2)).addClass('prev2');
		}
	}

	jQuery('.prev2').css('margin-left', -1*(jQuery('.current').width()/2)-jQuery('.current').width()*0.78/1.333-jQuery('.current').width()*0.56/1.333);
	jQuery('.prev').css('margin-left', -1*(jQuery('.current').width()/2)-jQuery('.current').width()*0.78/1.333);
	jQuery('.current').css('margin-left', -1*(jQuery('.current').width()/2));
	jQuery('.next').css('margin-left' , -1*(jQuery('.current').width()/2)+jQuery('.current').width()*0.78/1.333);
	jQuery('.next2').css('margin-left' , -1*(jQuery('.current').width()/2)+jQuery('.current').width()*0.78/1.333+jQuery('.current').width()*0.56/1.333);
	jQuery('.img_title').text(jQuery('.current').attr('data-title'));
	if (jQuery(window).width() > 1025) {
		whaterWheel.find('img').reflect({height:0.24,opacity:0.25});
		whaterWheel.find('canvas').each(function(){
			jQuery(this).width(jQuery(this).prev('img').width());
		});
	}
}
function setupWW() {
	"use strict";
	if (jQuery(window).width() > 1025) {
		whaterWheel.find('img').unreflect();
	}
	if (jQuery(window).width() > 960) {
		atr056 = 0.56;
		atr078 = 0.78;
		atr_main = 1;
	} else if (jQuery(window).width() > 760 && jQuery(window).width() < 960){
		atr056 = 0.37;
		atr078 = 0.56;
		atr_main = 0.75;
	} else if (jQuery(window).width() < 760){
		atr056 = 0.3;
		atr078 = 0.5;
		atr_main = 0.75;
	}
	var setHeight = (jQuery(window).height()-jQuery('.main_header').height()-jQuery('.ww_footer').height()-1)*atr_main;
	var setWidth = jQuery(window).width() - parseInt(whaterWheel.css('padding-left')) - parseInt(whaterWheel.css('padding-right'));			
	whaterWheel.height(setHeight*0.7).width(setWidth).css({'margin-top' : setHeight*0.15, 'margin-bottom' : setHeight*0.15});
	whaterWheel.width();
	whaterWheel.height((jQuery(window).height()-jQuery('.main_header').height()-jQuery('.ww_footer').height())*0.7);
	if (jQuery('.current').size() < 1) {
		if (whaterWheel.find('.ww_block').size() > 4) {
			whaterWheel.addClass('type5');
			jQuery('#ww_block1').addClass('prev2');
			jQuery('#ww_block2').addClass('prev');
			jQuery('#ww_block3').addClass('current');
			jQuery('#ww_block4').addClass('next');
			jQuery('#ww_block5').addClass('next2');				
		} else if (whaterWheel.find('.ww_block').size() > 2) {
			whaterWheel.addClass('type3');
			jQuery('#ww_block1').addClass('prev');
			jQuery('#ww_block2').addClass('current');
			jQuery('#ww_block3').addClass('next');				
		} else if (whaterWheel.find('.ww_block').size() == 2) {
			whaterWheel.addClass('type2');
			jQuery('#ww_block1').addClass('current');
			jQuery('#ww_block2').addClass('next');
		} else if (whaterWheel.find('.ww_block').size() == 1) {
			whaterWheel.addClass('type1');
			jQuery('#ww_block1').addClass('current');
		}
	}
	jQuery('.prev2').css('margin-left', -1*(jQuery('.current').width()/2)-jQuery('.current').width()*atr078/1.333-jQuery('.current').width()*atr056/1.333);
	jQuery('.prev').css('margin-left', -1*(jQuery('.current').width()/2)-jQuery('.current').width()*atr078/1.333);
	jQuery('.current').css('margin-left', -1*(jQuery('.current').width()/2));
	jQuery('.next').css('margin-left' , -1*(jQuery('.current').width()/2)+jQuery('.current').width()*atr078/1.333);
	jQuery('.next2').css('margin-left' , -1*(jQuery('.current').width()/2)+jQuery('.current').width()*atr078/1.333+jQuery('.current').width()*atr056/1.333);
	jQuery('.img_title').text(jQuery('.current').attr('data-title'));
	if (jQuery(window).width() > 1025) {
		whaterWheel.find('img').reflect({height:0.24,opacity:0.25});
		whaterWheel.find('canvas').each(function(){
			jQuery(this).width(jQuery(this).prev('img').width());
		});
	}
}