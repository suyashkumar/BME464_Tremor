var express = require('express');
var app = express();
app.use(express.static('static'));
var fs = require('fs');

var server = app.listen(8000, function () {
var host = server.address().address;
var port = server.address().port;
console.log('Example app listening at http://%s:%s', host, port);
});
// BEGIN ROUTES
app.get("/datalist",function(req,res){
fs.readdir("static/data",function(err, files){
	files.sort(function(a,b){
		a_conv=parseInt(a.substring(0,a.length-3));
		b_conv=parseInt(b.substring(0,b.length-3));
		return b_conv-a_conv;
	});
	var returnStr={"files":files};
	res.send(returnStr);
});
});
