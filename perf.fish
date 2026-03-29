#!/usr/bin/env fish

# Two ways perf can unwind the call stack:
#   - -g (frame pointers) — fast, low overhead, but requires
#     -fno-omit-frame-pointer at compile time. Can miss frames if any library in
#     the call chain was built without frame pointers.
#  - --call-graph dwarf — reads DWARF debug info (the -g compile flag) to
#    unwind. More accurate and doesn't depend on frame pointers, but records more
#    data per sample and has higher overhead.
perf record -g -o perf.data build/PERF/d07p2 test/d07.txt
perf annotate -l -i perf.data

