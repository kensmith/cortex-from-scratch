#!/usr/bin/env python

import telnetlib
import sys

if len(sys.argv) != 2:
    print(sys.argv[0] + ' <elf file>')
    sys.exit(1)

t = telnetlib.Telnet('localhost', 4444)
r = t.read_until('>', 1)

def cmd(c, s):
    t.write(c + '\r')
    t.read_until('>', s)

cmd('reset halt', 1)
cmd('flash write_image ' + sys.argv[1] + '\r', 500)
cmd('reset halt', 1)
