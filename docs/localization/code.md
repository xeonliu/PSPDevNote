
# Python处理字符串、字节流
字符串转字节流
```python
binary_stream = v.encode('utf-16-le')
```

字节流转16进制字符串
```py
import binascii
binascii.hexlify(binary_stream).decode('utf-8')
```

16进制字符串转字节序列
```py
binascii.unhexlify(hex_str)
```


字符串数组拼接
```py
''.join(s for s in array)
```

置换字典k,v
```py
reverse_data = {v:k for k, v in data.items()}
```

```py
# Encode the string
encoded_s = [reverse_data[char] for char in str if char in reverse_data]
```

dump to json
```py
with open('output2.json', 'w', encoding='utf-8') as f:
    json.dump(byte_char_dict, f, ensure_ascii=False, indent=4)
```

```
# with open(output_file_path, "wb") as output_file:
#     for k, v in data.items():
#         b = v.encode('utf-16-le')
#         output_file.write(b)
```