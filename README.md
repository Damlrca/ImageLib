### ImageLib
Static library that implements **Image** class, which is **an unsigned char matrix**.

---

**Branches**:
- `master` - main branch
- `new_realization` - last version
- `lab_realization` - old version of realization for institute lab

---

**Project structure**:

- `ImageLib` - main directory of library, constains header and cpp files:
	- `ImageLib.h`
	- `ImageLib.cpp`
- `gtest` - Google Test library
- `test` - directory with tests
- `main` - directory for demo applications

---

### Image class

Image **constructors**:
- `Image()` - create empty Image with zero size
- `Image(x, y)` - create empty Image with height=x, width=y

Image **methods**:
- `height()` - returns Image's height
- `width()`- returns Image's width
- `px(x, y)` - unsafe, returns reference to pixel\[x\]\[y\] of Image
- `at(x, y)` - safe version of px(x, y), throws an error in case of wrong index
- `resize(h, w)` - resizes the Image, new Image will be empty

Image **Saving & Loading**:
- `fsaveTXT(name)/floadTXT(name)` - saves/loads Image in/from *name* file, as txt file.  
name.txt:
```
  3 4
   41  35 190 132
  225 108 214 174
   82 144  73 241
```
- `fsaveBIN(name)/floadBIN(name)` - saves/loads Image in/from *name* file, as bin file.  
name.bin:
```
  03000000  04000000
  29 23 BE 84
  E1 6C D6 AE
  52 90 49 F1
```

- format of reading-writing through `iostream` (size of Image should be correct):
```
   41  35 190 132
  225 108 214 174
   82 144  73 241
```

Image **errors**:
- Image::`image_err` - basic class for all Image errors
- Image::`size_err` - wrong Image size error, unused
- Image::`index_err` - wrong index error, can be thrown in `at(x, y)` functinon