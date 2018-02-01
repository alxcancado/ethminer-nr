#!/usr/bin/python3
# mining pool performance evaluator
# (c) Ralph Doncaster 2018

import socket
import select
import sys
import time

pools = ( ("us-east1.ethereum.miningpoolhub.com", 20536 ),
		("eth-us-east1.nanopool.org", 9999 ),
		("us1.ethermine.org", 4444 ) )
socks =  []

for pool in pools:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect(pool)
	socks.append(s)
	s.sendall('{"id": 0, "worker": "m0",  "method": "eth_submitLogin", "params": ["0xeb9310b185455f863f526dab3d245809f6854b4d"]}\n'.encode())
	response = s.recv(2048)
	print (response)
	s.sendall('{"id": 1, "method": "mining.subscribe", "params": []}\n'.encode())
	start = time.time()
	response = s.recv(2048)
	print (response)
	print(time.time() - start, s.getpeername())

print("Waiting for data.")
start = time.time()
while socks:
	readable, writable, errs = select.select(socks, [], socks)
	for s in readable:
		response = s.recv(2048)
		print ("%4.6f"% (time.time() - start), s.getpeername())
		print (response)

