/**
 * @file
 * Disable Annotator annotation creation widget.
 */
(function (Drupal) {

  "use strict";

  if (typeof window.Annotator === 'object') {
    var instances = Annotator._instances;

    Drupal.behaviors.disableAnnotator = {
      /**
       * When people don't have permission to write annotation, make it so that
       * selecting text is always empty, for *all* Annotator objects.
       */
      attach: function () {
        for (var i = 0; i < instances.length; i++) {
          instances[i].ignoreMouseup = true;
        }
      }
    };
  }

})(Drupal);
