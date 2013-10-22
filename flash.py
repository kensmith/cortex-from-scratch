#!/usr/bin/env python2

import telnetlib
import sys

if len(sys.argv) != 2:
    print(sys.argv[0] + ' <bin file>')
    sys.exit(1)

t = telnetlib.Telnet('localhost', 4444)
r = t.read_until('>', 1)

def cmd(c, s):
    t.write(c + '\r')
    t.read_until('>', s)

cmd('reset halt', 1)
cmd('flash write_image erase unlock ' + sys.argv[1] + ' 0x0 bin\r', 500)
cmd('reset halt', 1)
