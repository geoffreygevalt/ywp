/**
 * @file
 * Implement a JS-only statuses comment refresh.
 */

(function (Drupal, $) {

  "use strict";

  // Time in seconds.
  var authUpdateDelay = 20;
  // This value is half of 'cache_lifetime'.
  var anonUpdateDelay;

  var timer;
  var delay;
  // Increased delay when no updates.
  var slowDelay;
  var refreshIDs = ['.view-id-statuses_stream'];
  var loaded = {};
  // When 5 consecutive updates have no new content, increase delay.
  var timesNotUpdated = 0;


  function updateView(viewID, new_content) {

    function updateViewContent(index, value) {
      // New content
      var $this = $(this);
      // Existing content.
      var $el = $element.eq(index);

      var changed = $this.text() !== $el.text();
      // Only update the view if the number of rows is different (meaning a
      // comment was added/removed).
      if (changed) {
        Drupal.detachBehaviors($el);
        $el.replaceWith($this);
        Drupal.attachBehaviors($this);
        timesNotUpdated = 0;
      }
      else {
        timesNotUpdated++;
      }
    }

    if (loaded[viewID] !== true) {
      var $element = $(viewID);
      var $insert = new_content.find(viewID);
      // If a refreshID is found multiple times on the same page, replace each one sequentially.
      if ($insert.length && $element.length && $element.length >= $insert.length) {
        $insert.each(updateViewContent);
      }
      else if (!$element.length) {
        window.location.reload();
      }
      loaded[viewID] = true;
    }
  }

  function parsePage(data, textStatus) {
    // From load() in jQuery source. We already have the scripts we need.
    var new_data = data.replace(/<script(.|\s)*?\/script>/g, "");
    // Apparently Safari crashes with just $().
    var new_content = $('<div></div>').html(new_data);

    if (textStatus != 'error' && new_content) {
      for (var i = 0; i < refreshIDs.length; i++) {
        updateView(refreshIDs[i], new_content);
      }
    }
    $('.fbss-remove-me').remove();
  }

  // Refresh parts of the page.
  function refreshComments() {
    // Reset all seen views.
    loaded = {};
    // Refresh elements by re-loading the current page and replacing the old version with the updated version.
    var location = window.location.pathname + '?';
    // Build the relative URL with query parameters.
    var query = window.location.search.substring(1);
    if ($.trim(query) !== '') {
      location += query + '&';
    }
    // IE will cache the result unless we add an identifier (in this case, the time).
    $.get(location, parsePage);
  }

  function refresh() {
    var actualDelay = timesNotUpdated < 5 ? delay : slowDelay;
    if (timer) {
      window.clearTimeout(timer);
    }
    refreshComments();
    // console.log('refresh', (actualDelay/1000), timesNotUpdated);
    timer = window.setTimeout(refresh, actualDelay);
  }

  // Don't use behaviors since we want that bound only once!
  $(document).ready(function (context) {
    anonUpdateDelay = Math.max(60, Drupal.settings.ywp_autorefresh.anon) / 2;
    delay = $('body').hasClass('logged-in') ? authUpdateDelay : anonUpdateDelay;
    delay = delay * 1000;
    slowDelay = delay * 5;
    refresh();
  });

})(Drupal, jQuery);
