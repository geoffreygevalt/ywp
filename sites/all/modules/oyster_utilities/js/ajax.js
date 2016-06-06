(function ($) {
  Drupal.behaviors.oyster = {
    attach: function (context, settings) {
       
      $('.oyster-like').click(function(event) {
        // Prevent the default link action
        event.preventDefault();

        // Get the request URL without the query string
        var ajaxUrl = $(this).attr('href').split('?');
         
        $.ajax({
          type: "POST",
          url: ajaxUrl[0],
          data: {
            // For server checking
            'from_js': true
          },
          dataType: "json",
          success: function (data) {
            // Display the time from successful response
            if (data.score) {
              $("span.vote-count-number-" + data.nid + "").remove();
              $(".vote-count-" + data.nid + "").append('<span class="vote-count-number-' + data.nid + ' vote-count-number">' + data.score + '</span>');
              
              var value;

							$(".vote-icon-" + data.nid + ".vote-icon-wrapper i").each(function() {
							    value = $(this).attr("class").replace("-o", "");
							    $(this).attr("class", value);
							});
            }
          },
          error: function (xmlhttp) {
            // Error alert for failure
            alert('An error occured: ' + xmlhttp.status);
          }
        });
      });
    }
  };
})(jQuery);