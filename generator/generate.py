s = [
  14,  0,  4, 15, 13,  7,  1,  4,  2, 14, 15,  2, 11, 13,  8,  1,
   3, 10, 10,  6,  6, 12, 12, 11,  5,  9,  9,  5,  0,  3,  7,  8,
   4, 15,  1, 12, 14,  8,  8,  2, 13,  4,  6,  9,  2,  1, 11,  7,
  15,  5, 12, 11,  9,  3,  7, 14,  3, 10, 10,  0,  5,  6,  0, 13]

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

def generateLUT(name, t, radix, operator):
    print("#ifndef {}".format(name.upper()))
    print("#define {}".format(name.upper()))
    print("{} {}[]".format(t, name), end='')
    print(" = {")
    for i in range(2**(2*radix)):
        lh = decode(i, radix)

        print("\t", end='')
        for j in range(2**(2*radix)):
            rh = decode(j, radix)
            
            value = encode(operator(lh, rh), radix)
            print("{}, ".format(value), end='')
        
        print()
    print("};")
    print("#endif")

def generateSbox(name, t, radix):
    print("#ifndef {}".format(name.upper()))
    print("#define {}".format(name.upper()))
    print("{} {}[]".format(t, name), end='')
    print(" = {")
    for i in range(4):
        print("\t", end='')
        for j in range(2<<radix):
            operand = (i << radix) | j
            lh = decode(operand, radix)
            
            value = encode(s[lh], radix)
            print("{}, ".format(value), end='')
        
        print()
    print("};")
    print("#endif")

op = lambda a,b: (int(a)*int(b))&255
# generateLUT("d_mult", "char", 4, op)
generateSbox("d_sbox", "char", 4)
