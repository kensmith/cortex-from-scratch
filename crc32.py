#!/usr/bin/env python

import binascii

# 0000000: f07f 0010 9905 0000 9905 0000 9905 0000  ................
# 0000010: 9905 0000 9905 0000 9905 0000 babe cafe  ................
data = '\xf0\x7f\x00\x10' + '\x99\x05\x00\x00' + '\x99\x05\x00\x00' + '\x99\x05\x00\x00' + '\x99\x05\x00\x00' + '\x99\x05\x00\x00' + '\x99\x05\x00\x00'
print ('len(data) = ' + str(len(data)))
crc = binascii.crc32(data)
print 'crc32 = 0x%08x' % -crc
