
var websocket = new WebSocket("ws://localhost:4344");

websocket.onopen = function () {
    console.log("Connected to Server");
};

websocket.onmessage = function (ev) {
    console.log(ev);
    var obj = JSON.parse(ev.data);
    var tmp = [obj.label , obj.min , obj.max ];
    options.series[1].data.push(tmp);

    var tmp2 = [ obj.label , obj.moy ];
    options.series[0].data.push( tmp2);
    graph.update(options);
};

var onClick = function () {
    websocket.send("save_ann")
};