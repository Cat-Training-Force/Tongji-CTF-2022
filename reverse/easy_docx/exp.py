from Crypto.Cipher import AES

key=b'not important k~'
iv=bytes([222,173,190,239,1,1,4,5,1,4,1,9,1,9,130,130])
c=bytes([65,85,135,14,130,191,4,47,184,184,116,133,192,173,142,52,124,56,252,0,2,66,15,228,9,204,85,137,119,113,169,223,212,27,218,62,187,69,15,214,230,156,202,143,189,187,157,96])
aes=AES.new(key=key,iv=iv,mode=AES.MODE_CBC)
print(aes.decrypt(c))

# flag{A_ma1war3_w1ll_g3t_ur_s3cr3t_f1le}