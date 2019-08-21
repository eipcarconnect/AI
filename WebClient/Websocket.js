
var websocket = new WebSocket("ws://localhost:4344");

websocket.onopen = function () {
    console.log("DONE");
};

websocket.onmessage = function (ev) {
    console.log(ev);
    var obj = JSON.parse(ev.data);
    config.data.datasets[0].data.push(obj.data);
    config.data.labels.push(obj.label);
    graph.update();
};