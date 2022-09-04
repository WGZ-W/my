A single file name can specify many files using wildcard characters. The wildcard characters in make are ‘*’, ‘?’ and ‘[…]’, the same as in the Bourne shell. 

## 4.4.1 Wildcard Examples

Wildcards can be used in the `recipe` of a rule, where they are expanded by the shell. For example, here is a rule to delete all the object files:

```
clean:
        rm -f *.o
```

Wildcard expansion **`does not happen`** when you define a `variable`. Thus, if you write this:

```
objects = *.o
```

then the value of the variable objects is the actual string ‘*.o’. However, if you use the value of objects in a target or prerequisite, wildcard expansion will take place there. If you use the value of objects in a recipe, the shell may perform wildcard expansion when the recipe runs. To set objects to the expansion, instead use:

```
objects := $(wildcard *.o)
```

# `总结`
- Wildcards can be used in the `recipe` of a rule, where they are expanded by the shell.
- 通配符可以在 rules 的 recipe 中使用，他们将在 shell 中被扩展