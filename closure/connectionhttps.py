import socket
from OpenSSL import SSL
from flask import Flask

app = Flask(__name__)

def make_tcp_request():
    # Define the destination address and port for the TCP request
    #hostname = "tcp://7.tcp.eu.ngrok.io"
    hostname = "0.tcp.in.ngrok.io"
    port = 13266
    ##
    try:
    # Create a TCP socket
        with socket.create_connection((hostname, port)) as s:
            context = SSL.Context(SSL.SSLv23_METHOD)

            ssl_conn = SSL.Connection(context, s)
            ssl_conn.set_connect_state()

            ssl_conn.do_handshake()
            # Send a simple HTTP GET request
            request = "GET /ETS-TRMS/login_form.php HTTP/1.1\r\nHost: 192.168.20.5\r\n\r\n"
            ssl_conn.sendall(request.encode())
            response = ssl_conn.recv(1024)
            return response.decode()

    except ConnectionResetError:
        print("Connection reset by peer. Check ngrok configuration.")
        return "Connection reset by peer. Check ngrok configuration."
    except Exception as e:
        # Print or log the exception for debugging
        print(f"Exception during TCP request: {e}")
        return "Error during TCP request"
    ##

#request = "GET / HTTP/1.1\r\nHost:https://172.16.25.100:7007/ETS-TRMS\r\n\r\n"

@app.route('/')
def index():

    ##Debuging
    print("Response to terminal")
    # Make a TCP request and get the response
    tcp_response = make_tcp_request()
    ## Debuging for Naol by print 

    print(tcp_response)

    print("Response to tcp terminal done")
    # Example header check
    if "Content-Type: text/html" in tcp_response:
        print("Response is HTML")

    # Example encoding check
    if "Content-Type: text/html; charset=utf-8" in tcp_response:
        print("Response is UTF-8 encoded HTML")
    ## Debuging end
    # Display the TCP response in the browser
    return tcp_response

if __name__ == '__main__':
    # Run the Flask app on port 5000
    app.run(port=5000,debug=True,use_reloader=False)

## auth: 2aLXeUgDQ1lKaThmqmg2bpUG786_4Gx4denAAAgxZdYMCcBkA
