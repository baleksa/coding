const http = require('http');
const fs = require('fs');

const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
  fs.readFile('/tmp/output.html', function(err, data) {
    if (err) throw err;
    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/html');
    res.write(data);
    res.end();
  });
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});


// const http = require('http');
// const fs = require('fs');
//
//
// fs.readFile('/tmp/output.html', function(err, html) {
//   if (err) {
//     throw err;
//   }
//   http.createServer(function(request, response) {
//     response.writeHeader(200, {'Content-Type': 'text/html'});
//     response.write(html);
//     response.end();
//   }).listen(8000);
// });
