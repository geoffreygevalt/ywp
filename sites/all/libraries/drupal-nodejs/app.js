/**
 * Node.js Integration for Drupal
 * https://www.drupal.org/project/nodejs
 */
'use strict';

var server = require('./lib/server');
var configManager = require('./lib/config-manager');
var configFile = process.argv[2] ? process.argv[2] : process.cwd() + '/nodejs.config.js';

configManager.readFromDisk(configFile);
server.start(configManager);
