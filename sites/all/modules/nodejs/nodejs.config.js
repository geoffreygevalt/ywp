/**
* This configuration file was built using the 'Node.js server configuration builder'.
* For a more fully commented example see the file nodejs.config.js.example in the root of this module
*/
backendSettings = {
  "scheme":"http",
  "host":"",
  "port":8080,
  "key":"/path/to/key/file",
  "cert":"/path/to/cert/file",
  "resource":"/socket.io",
  "publishUrl":"publish",
  "serviceKey":"ywpnodejskey",
  "backend":{
    "port":80,
    "host":"youngwritersproject.org",
    "messagePath":"/nodejs/message"
  },
  "clientsCanWriteToChannels":false,
  "clientsCanWriteToClients":false,
  "extensions":"",
  "debug":false,
  "transports":[
    "websocket",
    "flashsocket",
    "htmlfile",
    "xhr-polling",
    "jsonp-polling",
    "polling"
  ],
  "jsMinification":true,
  "jsEtag":true,
  "logLevel":1
};
