from xmlrpc.server import SimpleXMLRPCServer

def sq(a):
    return a * a
server = SimpleXMLRPCServer(("localhost", 8000), logRequests="false")
server.register_function(sq, "sq")

try:
    server.serve_forever()
except Exception as e:
    print(e)
finally:
    server.server_close()