
var ScoreTable = function (options) {

  var self = this;

  var $e;
  var template = '<table class="scores" cellpadding="0" cellspacing="0">' +
    '<% for (name in rows) { %>' +
      '<tr class="<%= name %>"><td class="name <%= name %>"><%= name %></td><td class="score"><%= rows[name] %></td></tr>' +
    '<% } %>' +
    '</table>';

  var defaultData = {
    rows: {
      'Mike': 4,
      'Ralph': 9,
      'Tom': 1,
      'Brad': 7,
      'Angelina': 3,
      'John': 7,
      'Sam': 5
    }
  }

  function init() {
    $e = $(options.element);
    self.render();
  }

  self.render = function (data) {

    if (undefined === data) data = {};

    var d = _.clone(defaultData);
    _.extend(d.rows, data.rows);
    var t = _.template(template, d);
    $e.html(t);

    $trs = $('tr', $e);

    $trs = $('tr', $e).sort(function (a, b) {
      return parseInt($('td.score', b).text()) - parseInt($('td.score', a).text());
    })

    $('tbody', $e).append($trs);

    // update team scores
    $('.team1 span').text(parseInt(d.rows.Mike) + parseInt(d.rows.John));
    $('.team2 span').text(parseInt(d.rows.Ralph) + parseInt(d.rows.Tom));
    $('.team3 span').text(parseInt(d.rows.Brad) + parseInt(d.rows.Angelina) + parseInt(d.rows.Sam));

  }

  init();
};
