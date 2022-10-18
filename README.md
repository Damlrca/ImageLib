### ImageLib
Static library that implements class Image.

Image class is **a matrix of unsigned chars**.

---
**Branches**:
- master
- new_realization - last version
- lab_realization - old version of realization for institute lab

---

Image **constructors**:
- Image() - create empty Image ith zero size
- Image(int x, int y) - create empty Image with height=x, width=y

Image **methods**:
- height() - returns Image's height
- width()- returns Image's width
- px(int x, int y) - unsafe, returns reference to pixel[x][y] of Image
- at(int x, int y) - safe version of px(x, y), throws an error in case of wrong index
- upscale() - increase size of Image by 2, some linear blur
- resize(int h, int w) - resizes the Image, new Image will be empty

Image **Saving & Loading**:
- fsaveTXT(*name*)/floadTXT(*name*) - saves/loads Image in/from *name* file, as txt file

name.txt:
<pre><code>  3 4
   41  35 190 132
  225 108 214 174
   82 144  73 241
</code></pre>
- fsaveBIN(*name*)/floadBIN(*name*) - saves/loads Image in/from *name* file, as bin file

name.bin:
<pre><code>  03000000 04000000
  29 23 BE 84
  E1 6C D6 AE
  52 90 49 F1
</code></pre>

- format of reading-writing through iostream (size of Image should be correct):
<pre><code>   41  35 190 132
  225 108 214 174
   82 144  73 241
</code></pre>
