;/*FB_PKG_DELIM*/

__d("passiveEventListenerUtil",[],(function(a,b,c,d,e,f){"use strict";b=!1;try{c=Object.defineProperty({},"passive",{get:function(){b=!0}});window.addEventListener("test",null,c)}catch(a){}var g=b;function a(a){return g?a:typeof a==="boolean"?a:a.capture||!1}f.isPassiveEventListenerSupported=g;f.makeEventOptions=a}),66);
__d("isBulletinDotComURI",[],(function(a,b,c,d,e,f){var g=new RegExp("(^|\\.)bulletin\\.com$","i"),h=["https"];function a(a){if(a.isEmpty()&&a.toString()!=="#")return!1;return!a.getDomain()&&!a.getProtocol()?!1:h.indexOf(a.getProtocol())!==-1&&g.test(a.getDomain())}f["default"]=a}),66);
__d("uriIsRelativePath",[],(function(a,b,c,d,e,f){"use strict";function a(a){return!a.getProtocol()&&!a.getDomain()&&!a.getPort()&&a.toString()!==""}f["default"]=a}),66);