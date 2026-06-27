# HTTP (Hypertext Transfer Protocol)

This is the protocol (language) used by computers to communicate over the web

## Request-Response Model

In the heart of the HTTP protocol is the request-response system:

 - Client (browser) sends a request to the server
 - Server processes the request and sends back a response
 -ike a web page, image,  The response contains the requested resource (letc.) or an error message if something went wrong

## HTTP URL

A URL (Uniform Resource Locator) is the address used to access resources on the web. It consists of several parts:

    - Scheme: Indicates the protocol (e.g., http, https)
    - Host: The domain name or IP address of the server (www.example.com)
    - Port: (optional) The port number on the server (default is 80 for HTTP and 443 for HTTPS)
    - Path: The specific resource on the server (e.g., /path/to/resource)
    - Query String: (optional) Additional parameters for the request (e.g., ?id=123)
    - Fragment: (optional) A specific section within the resource (e.g., #section1)

Example URL: `https://www.example.com:443/path/to/resource?id=123#section1`

There are other protocols like FTP, SMTP, etc., but HTTP is the most widely used for web communication.

## JS fetch API

The Fetch API provides a modern way to make HTTP requests in JavaScript. It is built into most modern browsers and allows you to perform network operations similar to XMLHttpRequest (XHR) but with a more powerful and flexible feature set. Its importent to remember that the fetch API does not come out of the box with the JS language but is provided by the environment: the browser.

### Basic Usage

Here is a simple example of how to use the Fetch API to make a request. The fetch() function takes in two arguments: the URL to which the request is sent and an optional settings object that configures the request. We also need to use the await keyword to wait for the promise to resolve. We are basically sending information to the other side of the world... we need to wait for the response.

```javascript
const response = await fetch(url, settings);
const responseData = await response.json();
```

## Web addresses

Every computer on the internet has a unique address called an IP address. The IP address is a series of numbers separated by dots (IPv4) or colons (IPv6) that identifies a device on the network. However, since IP addresses are hard to remember, we use domain names (like www.example.com) that are easier for humans to recall.

When you enter a web address in your browser, the following happens:

1. resolve DNS: The browser contacts a DNS server to translate the domain name into an IP address.
2. Establishing a Connection: The browser establishes a connection to the server using the IP address.
3. Sending an HTTP Request: The browser sends an HTTP request to the server for the desired resource.
4. Server Response: The server processes the request and sends back an HTTP response containing the requested resource or an error message.

The DNS (Domain Name System) server is what maps the human-friendly domain names to machine-friendly IP addresses.

### IPv4

IPv4 addresses are composed of four sets of numbers (octets) separated by dots. Each octet can range from 0 to 255. For example, `192.168.1.1` is a valid IPv4 address.

### IPv6

IPv6 addresses are composed of eight groups of four hexadecimal digits separated by colons. They were introduced to address the limitations of IPv4, such as the limited number of available addresses. An example of an IPv6 address is `2001:0db8:85a3:0000:0000:8a2e:0370:7334`.

### Domain names

Here is a URL example:
https://en.wikipedia.org/wiki/Domain_name

The domain name in this URL is `en.wikipedia.org` and this is what is associated with an IP address via DNS.

#### Domain name structure

- Top-Level Domain (TLD): The last part of the domain name (e.g., .com, .org, .net)
- Second-Level Domain: The part directly to the left of the TLD (e.g., wikipedia in wikipedia.org)
- Subdomain: Any part to the left of the second-level domain (e.g., en in en.wikipedia.org)

If you want to check the IP address of a domain name you can use the cloudflare DNS lookup api: https://cloudflare-dns.com/help/

ICANN is the organization that manages domain names and IP addresses.

## JS URL API

The URL API in JavaScript provides a way to parse, construct, normalize, and encode URLs. It is built into modern browsers and allows you to work with URLs easily. Here is a simple example of how to use the URL API:

```javascript
const url = new URL('https://www.example.com:443/path/to/resource?id=123#section1');
```

This URL will be parsed into its components and added to an object with properties like `protocol`, `hostname`, `port`, `pathname`, `search`, and `hash`. You can access and manipulate these properties as needed.

## Query parameters

Query parameters are used to send additional information to the server as part of the URL. They are appended to the URL after a question mark (?) and consist of key-value pairs separated by ampersands (&). For example, in the URL `https://www.example.com/path/to/resource?id=123&name=John`, the query parameters are `id=123` and `name=John`.

They rarely change anything significant but at the end of the day the implementation of the server decides what to do with them.

## Async JS

Synchronus JS executes line by line. By nature JS is single threaded meaning it can do one thing at a time. This is not very efficient when dealing with operations that take time to complete like network requests or file reading. To address this, JS provides asynchronous programming capabilities that allow you to perform tasks without blocking the main thread.

### Synchronous

```javascript
console.log('First');
console.log('Second');
console.log('Third');
```

### Asynchronous

```javascript
console.log('First');
setTimeout(() => {
    console.log('Second');
}, 1000);
console.log('Third');
```

`setTimeout` is a method on the `window` object that allows you to schedule a function to be executed after a specified delay (in milliseconds). In the example above, the message 'Second' will be logged to the console after a delay of 1000 milliseconds (1 second), while 'First' and 'Third' will be logged immediately.

`setTimeout(callback, delay)`

Now you might thing that the example above will log all three messages after one second. But that is not the case. The `setTimeout` function is asynchronous, meaning it does not block the execution of the code that follows it. So 'First' is logged immediately, then 'Third' is logged immediately after that, and finally, the program exits which wont give the setTimeout time to execute and we will be left with only 'First' and 'Third' in the console.

### Promises

## Errors in JS

## JSON

## HTTP Methods

## URL Paths

## HTTPS Security

HTTPS is the exact same thing as HTTP but with one added component: security, which is accomplished via encryption. When you visit a website using HTTPS, the communication between your browser and the web server is encrypted using SSL/TLS (Secure Sockets Layer/Transport Layer Security) protocols. This encryption ensures that any data exchanged between your browser and the server is secure and cannot be easily intercepted or tampered with by malicious actors.

Rarely the connection between you the client and the server is a straight line. There are often multiple servers and devices (intermediaries: WIFI, ISP, cloud) in between that help route the data to its destination. HTTPS helps ensure that even if the data passes through multiple points, it remains encrypted and secure. This security goes both ways: from client to server and from server to client.

When you visit a website using HTTPS, you will typically see a padlock icon in the address bar of your browser, indicating that the connection is secure. Additionally, the URL will start with "https://" instead of "http://".
    
### Encryption

Every server generates once a pair of cryptographic keys: a public key and a private key. The public key is shared with anyone who wants to communicate with the server, while the private key is kept secret and secure on the server.

When your browser connects to a server using HTTPS, it retrieves the server's public key and uses it to establish a secure connection. This process involves a handshake where both the client and server agree on encryption methods and exchange session keys for encrypting the data during the session.

0. Server generates a public/private key pair
1. Client contacts Server
2. Server sends its public key to Client
3. Client and Server negotiate a Session Key using the public key
4. Client sends encrypted HTTP request to Server
5. Server decrypts the request
6. Server sends encrypted HTTP response to Client
7. Client decrypts the response

HTTPS does hide the content of communication but does not hide the fact that communication is happening between client and server. The domain name and IP address are still visible to anyone monitoring the network traffic.

HTTPS also adds the peace of mind that you are communicating with the intended server and not an imposter. This is achieved through the use of digital certificates issued by trusted Certificate Authorities (CAs). These certificates verify the identity of the server and ensure that you are connecting to the legitimate website.