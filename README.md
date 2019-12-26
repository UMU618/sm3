# sm3

Calculate SM3 hash. Codes copied from [openssl][openssl].

## Compile

```bash
cd dynamically-linked-openssl # or statically-linked-openssl
cmake .
make
```

## Usage

```bash
$ echo -n UMU | openssl SM3
(stdin)= be6be53e426652f41c2a79b9fedc1410602218f43cf0931c57898f36620ff10d

$ echo -n UMU618 | openssl SM3
(stdin)= f39af87a8e70d8257db2a4694fb748e5bc445c3d918c067177fd94f606163f55

$ ./sm3 UMU UMU618
SM3("UMU") = be6be53e426652f41c2a79b9fedc1410602218f43cf0931c57898f36620ff10d
SM3("UMU618") = f39af87a8e70d8257db2a4694fb748e5bc445c3d918c067177fd94f606163f55
```

## Notes

- For [statically-linked-openssl](), to avoid dependence on dylibs of [openssl][openssl], I replace `OPENSSL_cleanse(p, HASH_CBLOCK);` with `memset(p, 0, HASH_CBLOCK);` in `crypto/md32_common.h`.

- Only test on macOS Catalina 10.15.2(15C57).

```bash
$ otool -L ./statically-linked-openssl/sm3
./statically-linked-openssl/sm3:
	/usr/local/opt/openssl@1.1/lib/libssl.1.1.dylib (compatibility version 1.1.0, current version 1.1.0)
	/usr/local/opt/openssl@1.1/lib/libcrypto.1.1.dylib (compatibility version 1.1.0, current version 1.1.0)
	/usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 800.7.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1281.0.0)

$ otool -L ./dynamically-linked-openssl/sm3
./dynamically-linked-openssl/sm3:
	/usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 800.7.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1281.0.0)
```

[openssl]: https://github.com/openssl/openssl
