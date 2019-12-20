# sm3

Calculate SM3 hash

```bash
$ echo -n UMU | openssl SM3
(stdin)= be6be53e426652f41c2a79b9fedc1410602218f43cf0931c57898f36620ff10d

$ echo -n UMU618 | openssl SM3
(stdin)= f39af87a8e70d8257db2a4694fb748e5bc445c3d918c067177fd94f606163f55

$ ./sm3 UMU UMU618
SM3("UMU") = be6be53e426652f41c2a79b9fedc1410602218f43cf0931c57898f36620ff10d
SM3("UMU618") = f39af87a8e70d8257db2a4694fb748e5bc445c3d918c067177fd94f606163f55
```
