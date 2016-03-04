# Node.js integration for Drupal

Server app for the Node.js Integration Drupal module https://www.drupal.org/project/nodejs

See [nodejs.config.js.example](https://github.com/beejeebus/drupal-nodejs/blob/master/nodejs.config.js.example) for a details of the configuration values.

A minimal nodejs.config.js configuration file looks like this:

```javascript
settings = {
  // Make sure this matches with Drupal
  serviceKey: '__FIX_ME__',
  host: 'your.nodejs.domain',
  debug: true,
  backend: {
    host: 'your.drupal.domain',
  }
};
```
