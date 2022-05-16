import marshal, types
from lib import code

f = {}
exec(marshal.loads(bytes(code)), f)
print(['Wrong', 'Ok'][f['check'](input())])