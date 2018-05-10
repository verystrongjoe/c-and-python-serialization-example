"""
needs to install protobuf ( pip install protobuf )




"""
import socket
from foo_pb2 import Foo

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("127.0.0.1", 5555))

foo = Foo()
while True:
    data, addr = sock.recvfrom(1024)
    foo.ParseFromString(data)
    print("Got foo with id={0} and bar={1}".format(foo.id, foo.bar))
