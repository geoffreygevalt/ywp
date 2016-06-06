jQuery(document).ready(function($){
  "use strict";	
 
  
	$('.main_wrapper').addClass('fullwidth');
	$('footer').addClass('fullwidth');

  jQuery('html').addClass('without_border');
			setupGrid();
		});
		jQuery(window).resize(function(){
			"use strict";
			setupGrid();
		});
		jQuery(window).load(function(){
			"use strict";
			setupGrid();
		});
		
		function setupGrid() {
			"use strict";
			jQuery('.fs-port-cont').each(function(){
				jQuery(this).css('margin-top', jQuery(this).parents('.grid-portfolio-item').find('img').height());
				jQuery(this).parents('.grid-item-trigger').find('a.grid-img-link').height(jQuery(this).parents('.grid-portfolio-item').find('img').height());
				jQuery(this).parents('.grid-item-trigger').css('height', jQuery(this).parents('.grid-portfolio-item').find('img').height());		
			});
			jQuery('.grid-portfolio-item').bind({
				mouseover: function() {
					jQuery(this).removeClass('unhovered');
					jQuery(this).find('.grid-item-trigger').css('height', jQuery(this).find('img').height()+jQuery(this).find('.fs-port-cont').height());
				},
				mouseout: function() {
					jQuery(this).addClass('unhovered');
					jQuery(this).find('.grid-item-trigger').css('height', jQuery(this).find('img').height());
				}				
			});			
		}