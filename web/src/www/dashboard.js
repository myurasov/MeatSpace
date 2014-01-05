$(function () {

  const M2X_API_KEY = 'f1100128fcf1f174ca70581900046c83';
  const M2X_FEED_ID = '2b2b76675e15ba0efe1a14c36060fa7d';
  const M2X_STREAM_NAME = 'points';

  var m2x = new M2X(M2X_API_KEY);

  var st = new ScoreTable({
    element: '#scoretable'
  });

  setInterval(function () {

    m2x.feeds.stream(M2X_FEED_ID, M2X_STREAM_NAME, function (data) {
      var points = data.value;

      if (data.value !== '-') {

        var rows = points.split(';');

        var d = {};

        for (var i in rows) {
          rows[i] = rows[i].split('=');
          d[rows[i][0]] = rows[i][1];
        }

        st.render({rows: d});
      }

    });

  }, 2000);

});