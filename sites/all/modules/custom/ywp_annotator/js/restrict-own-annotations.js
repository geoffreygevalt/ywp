/**
 * @file
 * Disable the storage plugin.
 *
 * Avoid an ajax request on nodes where the user is not author.
 */
(function (Drupal) {

  "use strict";

  Drupal.behaviors.annotatorStore = {
    attach: function () {}
  };

})(Drupal);
