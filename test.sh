#!/bin/bash
./huffman test-text/frankenstein.txt -eo encoded
./huffman encoded -do out.txt
echo
echo "md5sums (should be the same):"
md5sum test-text/frankenstein.txt out.txt
echo
echo "file sizes (encoded file should be smaller):"
du -h test-text/frankenstein.txt encoded
rm encoded out.txt
