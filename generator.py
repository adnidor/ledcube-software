#!/usr/bin/python3
import json
from sys import argv

if len(argv) != 2:
    print("argument needed")
    exit(1)

frame = json.load(open(argv[1]))

byte0 = 0x00
byte1 = 0x00
byte2 = 0x00
byte3 = 0x00

output = 0x00000000

for i in range(8):
    byte0 |= (frame["top_layer"][i]*128) >> i

for i in range(8):
    byte1 |= (frame["mid_layer"][i]*128) >> i

for i in range(8):
    byte2 |= (frame["bot_layer"][i]*128) >> i

byte3 |= (frame["top_layer"][8]) << 7
byte3 |= (frame["mid_layer"][8]) << 6
byte3 |= (frame["bot_layer"][8]) << 5

print("0x%02x%02x%02x%02x" % (byte3,byte2,byte1,byte0))
