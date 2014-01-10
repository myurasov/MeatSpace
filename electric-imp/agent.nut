device.on("update", function(s) {
  server.log("update: " + s);
    local r = http.put("http://api-m2x.att.com/v1/feeds/2b2b76675e15ba0efe1a14c36060fa7d/streams/points", {
      "X-M2X-KEY": "f1100128fcf1f174ca70581900046c83",
      "Content-type": "application/json"
    }, "{ \"value\": \"" + s + "\" }").sendsync();
  });
