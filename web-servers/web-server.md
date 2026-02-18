- Web servers have nothing to do with the hardware. Anything connected to the internet can be a web server. A web server is a peice of software that serves web content.

- a web server:

  1. `listens` on a
  2. `port` for a
  3. `request` sent via a
  4. `transport protocol` and returns a
  5. `response` containing the requested
  6. `resource`

- Once a basic web server starts it just... sits there, idle, waiting for incomming requests. The web server is listening to a specific port given by the OS that the web server is running on.

- every server has 65,535 ports. Ports 1-1023 are called "well-known ports". When a web server is started it occupies by default port 80 for HTTP and port 433 for HTTPS requests. other services or software may be configure to listen to a specific port number. **Web servers themselves can also be configured to listen on different ports if needed, depending on requirements or setup.**

- For example:

  - `http://127.0.0.1` sends a request to port **80** by default.
  - `https://127.0.0.1` sends a request to port **443** by default.
  - `http://127.0.0.1:{portNumber}` sends the request to the specified port number.

- Web clients and web servers communicate using the **H**yper**t**ext **T**ransfer **P**rotocol (HTTP). HTTP isnt just some gibberish that we people dont understand. On the contrary. Here is an example of an HTTP request:

```
GET /orders/123 HTTP/1.1
Host: 127.0.0.1:8000
User-Agent: Manual-Http-Request
```

An HTTP request consists of **3 blocks**

1. Start line:

   - GET - request method
   - /orders/123 - request target
   - HTTP/1.1 - HTTP version

2. Headers (key:value pairs):

   - _here we only have two headers but there could be more_
   - Host - IP and port we are trying to send the request to
   - User-Agent - tell the web server what browser we are using

3. Body (optional, depends on request method)
