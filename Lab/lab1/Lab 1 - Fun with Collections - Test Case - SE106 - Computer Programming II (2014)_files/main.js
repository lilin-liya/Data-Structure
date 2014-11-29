var $ = function (s) { return document.getElementById(s); };
var $$ = function (s, e) {
  if (!document.querySelectorAll) return Sizzle(s, e);
  else if (e) return e.querySelectorAll(s);
  else return document.querySelectorAll(s);
};

var selectCtext = function () {
  var l = $$('input.ctext'), i;
  for (i = 0; i < l.length; i++) (function (t) {
    var st = function () { t.focus(); t.select(); }
    t.onclick = st;
  }(l[i]));
};

var supportSizeCss = function () {
  var x = document.createElement('div');
  x.style.cssText = 'width: calc(1px);';
  return !!x.style.length;
};

var fixSize = function () {
  if (supportSizeCss()) return;
  var l = $('assignments_list'), r = $('main');
  var w, h;
  var resize = function () {
    var width = document.body.clientWidth  - 280;
    var height = document.body.clientHeight - 56;
    if (width !== w || height !== h) {
      l.style.height = height + "px";
      r.style.height = height + "px";
      r.style.width  = width  + "px";
    }
  };
  resize();
  setInterval(resize, 500);
  window.onresize = resize;
};

window.onload = function () {
  selectCtext();
  fixSize();
};
