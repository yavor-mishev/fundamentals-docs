const http = require("http");

  const server = http.createServer((req, res) => {
    if (req.url === "/") {
      res.write("Hello, World!"); 
      res.end();
    }
    if (req.url === "/about") {
      res.write("This is the about page.");
      res.end();
    }
  });
  server.listen(3000);
  
  console.log("Listening on port 3000...");