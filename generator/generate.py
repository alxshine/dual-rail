def encode(src, radix):
    ret = 0
    mask = 2**(radix-1)
    for i in range(radix):
        if i>0:
            ret = ret << 1
        bit = (src & mask) > 0
        src = src << 1
        ret += bit
        ret = ret << 1
        ret += (1-bit)
    return ret

def decode(src, radix):
    ret = 0
    mask = 2**(2*radix-1)
    for i in range(radix):
        bit = (src & mask) > 0
        src = src << 2
        ret += bit
        if i<radix-1:
            ret = ret << 1
    return ret

def testEncodeDecode(radix):
    for src in range(2**radix):
        assert (decode(encode(src, radix), radix) == src)

radix = 4
testEncodeDecode(radix)
