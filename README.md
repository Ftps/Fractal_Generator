# Fractal_Generator
A program to generate images of fractals based on Mandelbrot and Julia sets using the family of funtions f(z) = z^n + c. Also able to perform conformal transformations on the on the set.


To use the program, just compile using "make" and then run ./Fractal_Generator. You can then select to create an image according to your parameters or you can create a pallette to use in your fractals.

In order to create a fractal, you must specify a the picture's name, the pallette to use and what kind of fractal you want (Mandelbrot or Julia). Mandelbrot fractals will be created using f(z) = z^n + c, where c corresponds to the mapping point in the complex plane, iterating from 0. Julia fractals are created using the same function, but c is the specified point in the Julia Center parameters, and the function is iterated starting from the equivalent mapping point in the complex plane.
The Center Point corresponds to where the mapping of the middle point in the picture will be in the complex plane, the zoom must be entered as a power of 10 (if you wish a zoom of 1e5 times, them the zoom parameter must be filled with a 5 - due to limitations of the long double data type, only zooms up to 1e16 are allowed) and the power corresponds to the number n of the iterable function (only working for n = 2 and n = 3).
The Julia Center point corresponds to the value of c of the iterable function when selecting a Julia Set fractal, its value can be left empty when selecting a Mandelbrot Set fractal. The number of iterations corresponds to the maximum number of iterations the escape algorithm will calculate for each point (this will depend on the zoom and on the area you're generating the fractal). Finally, the Conformal Factor value will apply a transformation of the sort g(z) = z + k/z after each iteration to create different shapes in the fractal (fill in 0 for no conformal mappings between iterations).

TO-DO LIST:
- Windows compatibility;
- and other image organization things;
- use boost:gil for better image manipulation;
- save image parameters after generation;
- zooms deeper than 1e16;

DONE:
- pallette generator;
- preview;
- 2nd and 3rd power fractals;
- general power fractals;
- Python GUI;
- progress status;
- detect identical names;
