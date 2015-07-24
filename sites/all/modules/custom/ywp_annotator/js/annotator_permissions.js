/**
 * @file
 * Overrides the annotator module js file of the same name.
 *
 * This one fixes the permissions to show update link on annotations by changing
 * the userAuthorize callback. other than that it's a copy paste of the module
 * file.
 */

(function ($) {

  "use strict";

  Drupal.behaviors.annotatorPermissions = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Permissions', {
        user: settings.annotator_permissions.user,
        permissions: settings.annotator_permissions.permissions,
        showViewPermissionsCheckbox: settings.annotator_permissions.showViewPermissionsCheckbox === 1,
        showEditPermissionsCheckbox: settings.annotator_permissions.showEditPermissionsCheckbox === 1,
        userId: function (user) {
          if (user && user.uid) {
            return user.uid;
          }
          return user;
        },
        userString: function (user) {
          if (user && user.name) {
            return user.name;
          }
          return user;
        },
        /**
         * Check whether the user can edit annotations so that the right button
         * is displayed on the page.
         */
        userAuthorize: function (action, annotation, user) {
          if (!user || !annotation) {
            return false;
          }

          var permissions = Drupal.settings.annotator_permissions.permissions[action];

          // Edit own annotations
          if ((user.uid == annotation.user.uid) &&
             (jQuery.inArray(user.uid, permissions.user) !== -1)) {
            return true;
          }

          // Check if user has appropriate role
          for (var i = 0; i < user.roles.length; i++) {
            if (jQuery.inArray(user.roles[i], permissions.roles) !== -1) {
              return true;
            }
          }

          // Deny access
          return false;
        }
      });
    }
  };
})(jQuery);
