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


src = 0xF
encoded = encode(src, 4)
print("src: {:08b}, encoded: {:08b}".format(src, encoded))
