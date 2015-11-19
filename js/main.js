var x = {"fuck": ['f', 'u', 'c', 'k']}
var y = ["fuck", "absolutly", y]

function gen_counter(init) {
  function counter() {
    var ret = init;
    init = init + 1;
    return ret;
  }
  return counter;
}

cnt1 = gen_counter(1)
cnt2 = gen_counter(2)
console.log(
    cnt1(),
    cnt2(),
    cnt1(),
    cnt2());

(function () {
  var x = 1;
  console.log(x); // 1

  (function(){
    for (var x = 0; x < 10; x++) {
      console.log(x); // 2
    }
  })();

  console.log(x); // 2
})();
