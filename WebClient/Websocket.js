
var websocket = new WebSocket("ws://localhost:4344");

websocket.onopen = function () {
    console.log("DONE");
};

websocket.onmessage = function (ev) {
    console.log(ev);
    var obj = JSON.parse(ev.data);
    var tmp = [];
    tmp.push( obj.label );
    tmp.push( obj.min );
    tmp.push( obj.max );
    options.series[1].data.push(tmp);

    var tmp2 = [ obj.label , obj.moy ];
    options.series[0].data.push( tmp2);
    ++i;
    graph.update(options);
};