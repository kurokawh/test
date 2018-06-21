https://stackoverflow.com/questions/8246117/compiling-error-on-template-method-return-is-instance-from-inner-class

Clang reports the following:

```
error: missing 'typename' prior to dependent type name
'MyTemplate<T>::Inner' MyTemplate<T>::Inner  MyTemplate<T>::met()
^~~~~~~~~~~~~~~~~~~~ typename  1 error generated.
```

And placing typename in the appropriate place fixes it.
