"use strict";	
 var   preloader_block = jQuery('.preloader');
 
jQuery(document).ready(function($){  
  if (jQuery('.preloader').size() > 0) {
    setTimeout("preloader_block.addClass('la-animate');", 500);
    setTimeout("preloader_block.addClass('load_done')", 2500);
    setTimeout("preloader_block.remove()", 2950);
  }
});