/**
 * @file
 * Implement a JS-only statuses comment refresh.
 */

(function (Drupal, $) {

  "use strict";

  var activeTime;
  // Time in seconds before refreshing comments.
  var authDelay;
  // This value is half of 'cache_lifetime'.
  var anonDelay;
  // Increased delay when no updates.
  var waitingDelay;

  var timer;
  var refreshIDs = ['.view-id-statuses_stream'];
  var loaded = {};
  // if no content within 1 minute, use the 'waiting' delay.
  var lastContentUpdate = new Date();

  function updateView(viewID, new_content) {

    function updateViewContent(index, value) {
      // New content
      var $this = $(this);
      // Existing content.
      var $el = $element.eq(index);

      // Only look at the actual content of the comments, no metadata.
      var changed = $this.find('.statuses-content').text() !== $el.find('.statuses-content').text();
      // Only update the view if the number of rows is different (meaning a
      // comment was added/removed).
      if (changed) {
        Drupal.detachBehaviors($el);
        $el.replaceWith($this);
        Drupal.attachBehaviors($this);
        lastContentUpdate = new Date();
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
    var location = window.location.pathname;
    // Build the relative URL with query parameters.
    var query = window.location.search.substring(1);
    if ($.trim(query) !== '') {
      location += '?' + query + '&';
    }
    // IE will cache the result unless we add an identifier (in this case, the time).
    $.get(location, parsePage);
  }

  function getDelay() {
    var delay;
    var isAuth = $('body').hasClass('logged-in');
    var timeOffset = new Date() - lastContentUpdate;

    if (timeOffset < activeTime * 1000) {
      delay = isAuth ? authDelay : anonDelay;
    }
    else {
      delay = waitingDelay;
    }
    return delay * 1000;
  }

  function refresh() {
    if (timer) {
      window.clearTimeout(timer);
    }
    refreshComments();
    timer = window.setTimeout(refresh, getDelay());
  }

  // Don't use behaviors since we want that bound only once!
  $(document).ready(function (context) {
    var settings = Drupal.settings.ywp_autorefresh;
    activeTime = Math.max(60, +settings.activeTime);
    authDelay = Math.max(5, +settings.auth);
    anonDelay = Math.max(20, +settings.anon);
    waitingDelay = Math.max(anonDelay, +settings.waiting);

    // If we click on 'Share', reset the active counter.
    var $element = $('input.statuses-submit');
    if (Drupal.settings.ajax && Drupal.settings.ajax[$element[0].id]) {
      $element.bind(Drupal.settings.ajax[$element[0].id].event, function () {
        lastContentUpdate = new Date();
        // Don't refresh just now, the ajax stuff already updated the page,
        // wait for next tick.
        if (timer) {
          window.clearTimeout(timer);
        }
        timer = window.setTimeout(refresh, getDelay());
      });
    }

    timer = window.setTimeout(refresh, getDelay());
  });

})(Drupal, jQuery);
