import re
define = [
    'template', 'size_t', 'struct', 'constexpr', 'const', 'char', 'uint32_t', 'uint64_t',
    'static', 'using', 'sizeof', 'int', 'bool', 'false', 'true', 'typename', 'class', 'std::copy_n'
]
var = [
    'StringWrapper', 'Pack', 'Buffer', 'EncryptRound1', 'EncryptRound2', 
    'EncryptInner', 'Encrypt', 'Compare', 'Result', 'value', 'str', 'S', 'N', 'I',
    'V0', 'V1', 'V2', 'V3', 'V4', 'K0', 'K1', 'K2', 'K3', 'K4', 'T', 'U', 'B', 'R',
]
with open('in.cpp') as fin, open('out.cpp', 'w') as fout:
    src = fin.read()
    macro = re.findall(r'^#[^\n]*\n', src, re.M)
    src = ''.join(re.findall(r'^[^#][^\n]*', src, re.M))
    src = re.sub(r'tjctf\{[^}]*\}', 'tjctf{...}', src)
    s = re.findall(r'"[^"]*"', src)
    src = re.sub('\n', '', src)
    src = re.sub('\s+', ' ', src)
    i = 1
    for d in define:
        s = i * '_'
        macro.append(f'#define {s} {d}\n')
        src = re.sub(d, s, src)
        i += 1
    for v in var:
        src = re.sub(v, i * '_', src)
        i += 1
    fout.writelines(macro)
    fout.write(src)
