from xmlrpc.client import *

proxy = ServerProxy("http://localhost:8000")

print(str(proxy.sq(5)))