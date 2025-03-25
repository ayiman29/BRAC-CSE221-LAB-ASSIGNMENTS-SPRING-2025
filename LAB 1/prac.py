def lexi(name_i, name_j):
    for i, j in zip(name_i, name_j):
        if ord(j) > ord(i):
            return True
        elif ord(j) < ord(i):
            return False
    return len(name_j) > len(name_i)

# Test cases using assert

# Basic alphabetical comparisons
assert lexi("apple", "banana") == True  # 'a' < 'b'
assert lexi("banana", "apple") == False  # 'b' > 'a'

# Same starting letters, different subsequent letters
assert lexi("apple", "apricot") == True   # 'p' < 'r'
assert lexi("apricot", "apple") == False  # 'r' > 'p'

# One string is a prefix of the other
assert lexi("cat", "catalog") == True   # "cat" is a prefix of "catalog"
assert lexi("catalog", "cat") == False  # "catalog" is longer, so not less in lexicographic order

# Completely different words
assert lexi("zebra", "aardvark") == False  # 'z' > 'a'

# Equal strings
assert lexi("hello", "hello") == False  # They are equal

# Comparing strings with one extra character at the end
assert lexi("hello", "helloo") == True   # second string is longer
assert lexi("helloo", "hello") == False  # first string is longer

# More prefix examples
assert lexi("abc", "abcd") == False  # "abc" is a prefix of "abcd"
assert lexi("abcd", "abc") == False  # "abcd" is longer

# Testing edge cases with empty strings
assert lexi("", "a") == True    # empty string is less than non-empty
assert lexi("a", "") == False   # non-empty string is not less than empty
assert lexi("", "") == False    # both empty

# Case sensitivity (ASCII comparison)
assert lexi("Python", "python") == True   # 'P' (80) is less than 'p' (112)
assert lexi("python", "Python") == False  # 'p' (112) is greater than 'P' (80)

# Numeric characters
assert lexi("sameprefix1", "sameprefix2") == True   # '1' < '2'
assert lexi("sameprefix2", "sameprefix1") == False  # '2' > '1'

# Additional tests
assert lexi("longerword", "long") == False  # longer first string
assert lexi("long", "longerword") == True   # shorter first string
assert lexi("aaa", "aaab") == True          # extra character makes second greater
assert lexi("aaab", "aaa") == False         # first is longer

print("All tests passed!")
