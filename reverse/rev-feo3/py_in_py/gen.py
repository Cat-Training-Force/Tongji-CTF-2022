import marshal

source = '''
def check(s):
    return pow(int.from_bytes(s.encode(), 'little'), 65537, 74235029621079090865016547935468410475835146381495511077601407274346356390917) == {}
'''

flag = 'tjctf{can_y0u_f1Nd_Py_1n_pY}'
c = pow(int.from_bytes(flag.encode(), 'little'), 65537, 74235029621079090865016547935468410475835146381495511077601407274346356390917)
print(c)

with open('lib.py', 'w') as f:
    code = compile(source.format(c), '', 'exec', dont_inherit=True)
    byte = marshal.dumps(code)
    f.write(f'code = {repr(list(byte))}\n')