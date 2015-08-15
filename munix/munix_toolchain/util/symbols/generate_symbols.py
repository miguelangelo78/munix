#!/usr/bin/env python2
# coding: utf-8
"""
	Generate a symbol table from nm output.
"""

import sys

# Write extern + type
def extern(name):
    print ".extern %s" % (name)
    print ".type %s, @function" % (name)
    print ""

# Write an entry
def entry(name):
    print ".long %s" % (name)
    print ".asciz \"%s\"" % (name)
    print ""

ignore = [ "abs", "kernel_symbols_start", "kernel_symbols_end" ]
lines = [ x.strip().split(" ") for x in sys.stdin.readlines() if x not in ignore ]

# Generate the assembly
print ".section .symbols"
print ""
for name in lines:
	if len(name) > 1:
		extern(name[2])

print ".global kernel_symbols_start"
print "kernel_symbols_start:"
print ""
for name in lines:
	if len(name) > 1:
		entry(name[2])

print ".global kernel_symbols_end"
print "kernel_symbols_end:"



