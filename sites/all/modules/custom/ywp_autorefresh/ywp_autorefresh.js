(function () {

  "use strict";

  Drupal.Nodejs = Drupal.Nodejs ||  {
    'contentChannelNotificationCallbacks': {},
    'presenceCallbacks': {},
    'callbacks': {},
    'socket': false,
    'connectionSetupHandlers': {}
  };
  Drupal.Nodejs.callbacks = Drupal.Nodejs.callbacks || {};

})();
