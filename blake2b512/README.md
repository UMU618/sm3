# blake2b512

Calculate blake2b512 hash.

## Compile

Install dependencies:

```pwsh
vcpkg install --x-use-aria2 fastio openssl
```

Then open the .sln file.

## Usage

```pwsh
$ .\blake2b512 UMU
SM3("UMU") = 7f8e290ea5dd226892927c7cfb299b09f8b1712ed208f82d909ae2212b80b3d923070450ab176852591d07efc2f6b674dc421452761e22303f5d983f82951608
```

[openssl]: https://github.com/openssl/openssl
